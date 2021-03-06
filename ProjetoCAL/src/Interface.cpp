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
		cout << " 8 - Display drivers list" << endl;
		cout << " 9 - Add new container" << endl;
		cout << " 0 - Exit Program" << endl << endl;

		cout << "Choose an option: ";
		getEntry(op, 0, 9);

		ClearScreen();

		switch (op)
		{
		case 1:
			try {
				createPickRoute(gc);
			} catch(NotEnoughDrivers &e) {
				cout << "You must have drivers (insert them in text file).\n";
			}
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
		case 8:
			cout << "Drivers: " << endl << endl;
			gc.listDrivers();
			break;
		case 9:
			addNewContainer(gc);
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



void createPickRoute(GarbageCentral& gc) {

	if (! gc.hasDrivers()) {
		throw NotEnoughDrivers();
	}

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

	cout << endl;
	gc.listDrivers();
	cout << endl;

	getCursorXY(x,y);
	int driverID = askDriver(gc);

	while(driverID == -1){
		cout << "No valid Driver, insert again" << endl;
		clearline(x,y);
		driverID = askDriver(gc);
	}

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
			data = gc.createPickingRoute(t, driverID);
		}catch (RouteMissingData& e) {
			cout << "Truck doesn't have enough capacity" << endl;
			return;
		}
		break;
	case 2:
		deposits_id = manualPicking(gc, t);
		try{
			data = gc.createPickingRoute(t, deposits_id, driverID);
		}catch (RouteMissingData& e) {
			cout << "Truck doesn't have enough capacity or info is missing" << endl;
			return;
		}
		break;
	case 0:
		return;
	}



	cout << "Route generated for truck Nr. " << t << ":" << endl;

	auto route = data.first;
	auto failed = data.second;

	if (! route.empty()) {
		cout << route[0].first[0]->print();
		for (unsigned i = 0; i < route.size(); i++) {
			auto info = route[i].first;
			auto roads = route[i].second;

			for (unsigned j = 0; j < roads.size(); j++) {
				cout << "  --->  " << roads[j]->print();
				cout << "  --->  " << info[j+1]->print();
			}
		}
	}


	if (failed.size() != 0)
	{
		cout << "\n\nNo optimal route found for these containers:" << endl;
		for(unsigned int i = 0; i < failed.size(); i++){
			cout << " " << i + 1 << ". " << failed[i]->getID()<< endl;
		}
	}

	cout << flush;

	if (! route.empty() )
		displayGraphViewer(route, gc);
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

		if ( gc.updateDepositOccupied(depID, quantity) )
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


void displayGraphViewer(vector<Section> route, const GarbageCentral& gc)
{
	GraphViewer gv = GraphViewer(IMG_WIDTH, IMG_HEIGHT, false);
	gv.setBackground("map.png");

	gv.createWindow(800, 480);

	gv.defineEdgeDashed(false);
	gv.defineEdgeColor("black");
	gv.defineVertexColor("blue");
	unsigned roadCounter = 0;

	double minX = gc.getMinX();
	double minY = gc.getMinY();
	double rateX = IMG_WIDTH / (gc.getMaxX() - minX);
	double rateY = IMG_HEIGHT / (gc.getMaxY() - minY);


	if (! route.empty()) {
		gv.addNode(route[0].first[0]->getID(),
				(route[0].first[0]->getX() - minX) * rateX,
				(route[0].first[0]->getY() - minY) * rateY);
		gv.setVertexLabel(route[0].first[0]->getID(), route[0].first[0]->print());

		for (unsigned i = 0; i < route.size(); i++) {
			auto info = route[i].first;
			auto roads = route[i].second;

			for (unsigned j = 0; j < roads.size(); j++) {
				gv.addNode(info[j+1]->getID(),
						(info[j+1]->getX() - minX) * rateX,
						(info[j+1]->getY() - minY) * rateY);
				gv.setVertexLabel(info[j+1]->getID(), info[j+1]->print());


				Sleep(200);
				gv.rearrange();

				gv.addEdge(roadCounter, info[j]->getID(), info[j+1]->getID(), EdgeType::DIRECTED);
				roadCounter++;
				Sleep(200);
				gv.rearrange();
			}
		}
	}
}




unsigned long askDriver(GarbageCentral& gc) {
	unsigned long driverID;
	string name;
	bool valid = false;

	do{
		cout << "Driver's name: ";
		getline(cin, name);

		vector<Driver*> drivers = gc.searchDriversExact(name);

		if (drivers.size() == 0)
		{
			int option;

			Driver* d = gc.searchDriverApproximate(name);

			cout << "Did you mean: " << d->getName() << "?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;

			getEntry(option, 1, 2);

			if (option == 1){
				valid = true;
				driverID = d->getID();
			}
		}
		else if(drivers.size() > 1) {
			for (unsigned int i = 0; i < drivers.size(); i++) {
				cout << i+1 << " - " << drivers[i]->getName() << endl;
			}

			int op;
			cout << "Which driver?" << endl;
			cout << "Option: ";
			getEntry(op, 1, (int) drivers.size());
			driverID = drivers[op - 1]->getID();
			valid = true;
		}
		else{
			driverID = drivers[0]->getID();
			cout << "Driver: " << drivers[0]->getName() << endl;
			valid = true;
		}
	}while(!valid);

	return driverID;
}


unsigned long askRoad(GarbageCentral& gc) {
	unsigned long roadID;
	string name;
	bool valid = false;

	do{
		cout << "Road's name: ";
		getline(cin, name);

		vector<Road*> roads = gc.searchRoadsExact(name);

		if (roads.size() == 0)
		{
			int option;
			Road* r = gc.searchRoadApproximate(name);

			cout << "Did you mean: " << r->getName() << "?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;

			getEntry(option, 1, 2);

			if (option == 1){
				roadID = r->getID();
				valid = true;
			}
		}
		else if(roads.size() > 1) {
			vector<Road*> grouped = groupRoadsByName(roads);

			if (grouped.size() > 1) {
				for (unsigned int i = 0; i < grouped.size(); i++) {
					cout << i+1 << " - " << grouped[i]->getName() << endl;
				}

				int op;
				cout << "Which Road?" << endl;
				cout << "Option: ";
				getEntry(op, 1, (int) grouped.size());
				roadID = roads[op - 1]->getID();
				valid = true;
			}
			else {
				roadID = grouped[0]->getID();
				cout << "Road: " << grouped[0]->getName() << endl;
				valid = true;
			}
		}
		else{
			roadID = roads[0]->getID();
			cout << "Road: " << roads[0]->getName() << endl;
			valid = true;
		}
	}while(!valid);

	return roadID;
}



vector<Road*> groupRoadsByName(const vector<Road *>& roads) {
	vector<Road*> grouped;

	grouped.push_back(roads[0]);

	for (unsigned i = 1; i < roads.size(); i++) {
		for (unsigned j = 0; j < grouped.size(); j++) {
			if (roads[i]->getName() == grouped[j]->getName()) {
				break;
			}

			if (j == grouped.size() - 1)
				grouped.push_back(roads[i]);
		}
	}

	return grouped;
}

void addNewContainer(GarbageCentral& gc){
	cout << endl << "Roads: " << endl;
	gc.listRoads();
	cout << endl;

	cout << "Please choose the road where the deposit will be placed\n";
	int roadID = askRoad(gc);

	unsigned int maxCapacity;
	cout << "Capacity of the new container: ";
	getEntry(maxCapacity);

	gc.addRoad(roadID, maxCapacity);
}
