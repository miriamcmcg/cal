#include "Interface.h"

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

void getCursorXY(int &x, int&y) {

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void clearline()
{
	int x,y;
	getCursorXY(x,y);
	gotoXY(0,y);
	for(x = 0; x < 80; x++) {cout << " ";};
	gotoXY(0,y);
}

void clearline(int x, int y){
	gotoXY(x,y);
	for (int x_clear = x; x_clear < 80; x_clear++) {cout << " ";};
	gotoXY(x,y);
}

void waitReturn()
{
	cout << "\nPressione ENTER para regressar. ";
	cin >> noskipws;
	cin.ignore(1000, '\n');
	ClearScreen();
}

void getEntry(unsigned int &entrada)
{
	bool valid = false;
	int x, y;
	getCursorXY(x,y);
	for (int x_clear = x; x_clear < 80; x_clear++) {cout << " ";};
	gotoXY(x,y);
	do
	{
		cin >> entrada;

		if (cin.fail())
		{
			clearline();
			cout << "Error. Insert valid data.\n";
			cin.clear();
		}
		else
			valid = true;

		if (!valid)
		{
			clearline(x, y);
		}
		cin.ignore(1000, '\n');
	} while (!valid);
}

void getEntry(int &entrada)
{
	bool valid = false;
	int x, y;
	getCursorXY(x,y);
	for (int x_clear = x; x_clear < 80; x_clear++) {cout << " ";};
	gotoXY(x,y);
	do
	{
		cin >> entrada;

		if (cin.fail())
		{
			clearline();
			cout << "Error. Insert valid data.\n";
			cin.clear();
		}
		else
			valid = true;

		if (!valid)
		{
			clearline(x, y);
		}
		cin.ignore(1000, '\n');
	} while (!valid);
}

void getEntry(int &entrada, int start, int end)
{
	bool valid = false;
	int x, y;
	getCursorXY(x,y);
	for (int x_clear = x; x_clear < 80; x_clear++) {cout << " ";};
	gotoXY(x,y);
	do
	{
		cin >> entrada;

		if (cin.fail())
		{
			clearline();
			cout << "Error. Insert valid data.\n";
			cin.clear();
		}
		else if( entrada < start || entrada > end){
			cout << "Error. Insert valid data.\n";
		}
		else
			valid = true;

		if (!valid)
		{
			clearline(x, y);
		}
		cin.ignore(1000, '\n');
	} while (!valid);
}



void mainMenu(GarbageCentral& gc){

	while(true)
	{
		int op = 0;

		cout << "ECOPoints" << endl << endl;

		cout << " 1 - Create a picking route" << endl;
		cout << " 2 - Display trucks list" << endl;
		cout << " 3 - Display containers list" << endl;
		cout << " 4 - Display streets list" << endl;
		cout << " 5 - Update deposit's capacity occupied" << endl;
		cout << " 6 - Update speed on a road" << endl;
		cout << " 7 - Update road's availability" << endl;
		cout << " 0 - Exit Program" << endl << endl;

		cout << "Choose an option: ";
		getEntry(op, 0, 7);

		ClearScreen();

		switch (op)
		{
		case 1:
			createPickRoute(gc);
			break;
		case 2:
			cout << "Trucks: " << endl << endl;
			gc.listTrucks();
			break;
		case 3:
			cout << "Containers: " << endl << endl;
			gc.listDeposits();
			break;
		case 4:
			cout << "Streets: " << endl << endl;
			gc.listRoads();
			break;
		case 5:
			updateCapacityOccupied(gc);
			break;
		case 6:
			updateAvgSpeedRoad(gc);
			break;
		case 7:
			updateAvailableRoad(gc);
			break;
		case 0:
			return;
		}

		waitReturn();
	}
}



vector<unsigned int> manualPicking(GarbageCentral& gc, unsigned int truck_id){
	vector<unsigned int> deposits_id;
	bool valid = true;
	bool stop = false;
	unsigned int op = 0;

	do{
		if (valid)
		{
			cout << "Deposits: " << endl << endl;
			gc.listDeposits();
			cout << " -----------------------------" << endl;

			cout << "Deposits inserted: " << endl ;
			for(unsigned int i = 0; i < deposits_id.size(); i++){
				cout << " " << deposits_id[i] << endl;
			}
			cout << endl;
		}

		int x, y;
		getCursorXY(x,y);

		cout << "Insert an ID (0 to stop inserting): ";


		getEntry(op);

		if (op == 0)
			stop = true;
		else if (find(deposits_id.begin(), deposits_id.end(), op) != deposits_id.end()){
			cout << "Deposit ID already inserted, choose another.";
			clearline(x, y);
			valid = false;
		}
		else if (gc.hasDeposit(op)){
			if (gc.truckCanPick(truck_id, op)){
				deposits_id.push_back(op);
				ClearScreen();
				valid = true;
			}
			else{
				cout << "Truck has no capacity, choose another.";
				clearline(x, y);
				valid = false;
			}
		}
		else {
			cout << "Invalid Deposit ID, insert again (0 to stop inserting)";
			clearline(x, y);
			valid = false;
		}

	} while(!stop);

	return deposits_id;
}



void createPickRoute(GarbageCentral& gc){

	cout << "Trucks: " << endl << endl;
	gc.listTrucks();
	cout << endl;

	int t;
	bool valid = false;

	cout << "Choose a truck to make the route (0 to go back): ";
	int x, y;
	getCursorXY(x,y);

	do {
		getEntry(t);

		if (t == 0)
			return;
		else if (gc.hasTruck(t))
			valid = true;
		else
		{
			cout << "Invalid truck ID, insert again";
			clearline(x, y);
		}
	} while (!valid);

	int op = 0;

	cout << "Creating a picking route" << endl << endl;

	cout << " 1 - Automatic" << endl;
	cout << " 2 - Manual" << endl;
	cout << " 0 - Back" << endl << endl;

	cout << "Choose an option: ";
	getEntry(op, 0, 2);

	ClearScreen();

	Data data;
	vector<unsigned int> deposits_id;

	switch(op){
	case 1:
		try{
			data = gc.createPickingRoute(t);
		}catch (RouteMissingData& e) {
			cout << "Truck doesn't have enough capacity" << endl;
			return;
		}
		break;
	case 2:
		deposits_id = manualPicking(gc, t);
		try{
			data = gc.createPickingRoute(t, deposits_id);
		}catch (RouteMissingData& e) {
			cout << "Truck doesn't have enough capacity or info is missing" << endl;
			return;
		}
		break;
	case 0:
		return;
	}


	auto route = data.first;
	auto failed = data.second;

	cout << "Route generated for truck Nr. " << t << ":" << endl;
	for (unsigned i = 0; i < route.size(); i++) {
		auto path = gc.filter(route[i]);
		auto info = path.first;
		auto roads = path.second;

		cout << info[SOURCE]->print() << "  --->  ";
		for (unsigned j = 0; j < roads.size(); j++) {
			cout << roads[j]->print() << "  --->  ";
		}
		cout << info[DESTINATION]->print() << endl << endl;
	}

	if (failed.size() != 0)
	{
		cout << "No optimal route found for these containers:" << endl;
		for(unsigned int i = 0; i < failed.size(); i++){
			cout << " " << i + 1 << ". " << failed[i]->getID()<< endl;
		}
	}
}




void updateCapacityOccupied(GarbageCentral& gc) {

	cout << "Deposits: " << endl << endl;
	gc.listDeposits();
	cout << " -----------------------------" << endl;

	int x, y;
	int depID;
	int quantity;
	bool valid = false;

	cout << "Insert an ID (0 to go back): ";
	getCursorXY(x,y);


	do {
		getEntry(depID);

		if (depID == 0)
			return;
		else if (gc.hasDeposit(depID))
			valid = true;
		else
		{
			cout << "Invalid deposit ID, insert again";
			clearline(x, y);
		}
	} while (!valid);

	clearline();

	cout << endl << "Insert new level of occupation: ";
	getCursorXY(x,y);
	valid = false;
	do {
		getEntry(quantity);

		if (quantity >= 0)
			valid = true;
		else
		{
			cout << "Invalid quantity, insert again";
			clearline(x, y);
		}
	} while (!valid);


	gc.updateDepositOccupied(depID, quantity);
}




void updateAvgSpeedRoad(GarbageCentral& gc) {

	cout << "Roads: " << endl << endl;
	gc.listRoads();
	cout << " -----------------------------" << endl;

	int x, y;
	int roadID;
	int avg_speed;
	bool valid = false;

	cout << "Insert an ID (0 to go back): ";
	getCursorXY(x,y);


	do {
		getEntry(roadID);

		if (roadID == 0)
			return;
		else if (gc.hasRoad(roadID))
			valid = true;
		else
		{
			cout << "Invalid road ID, insert again";
			clearline(x, y);
		}
	} while (!valid);


	clearline();

	cout << endl << "Insert current average speed: ";
	getCursorXY(x,y);

	valid = false;
	do {
		getEntry(avg_speed);

		if (avg_speed >= 0)
			valid = true;
		else
		{
			cout << "Invalid quantity, insert again";
			clearline(x, y);
		}
	} while (!valid);


	gc.updateRoadAvgSpeed(roadID, avg_speed);
}



void updateAvailableRoad(GarbageCentral& gc) {

	cout << "Roads: " << endl << endl;
	gc.listRoads();
	cout << " -----------------------------" << endl;

	int x, y;
	int roadID;
	int availability;

	bool valid = false;

	cout << "Insert an ID (0 to go back): ";
	getCursorXY(x,y);


	do {
		getEntry(roadID);

		if (roadID == 0)
			return;
		else if (gc.hasRoad(roadID))
			valid = true;
		else
		{
			cout << "Invalid road ID, insert again";
			clearline(x, y);
		}

	} while (!valid);

	clearline();

	cout << endl;
	cout << "1 - Available" << endl;
	cout << "2 - Unavailable" << endl;

	getCursorXY(x,y);
	getEntry(availability, 1, 2);

	if (availability == 1)
		gc.updateRoadAvailable(roadID, true);
	else
		gc.updateRoadAvailable(roadID, false);
}
