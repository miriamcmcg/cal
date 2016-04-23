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
		cout << " 2 - Send a truck" << endl;
		cout << " 3 - Display trucks list" << endl;
		cout << " 4 - Display containers list" << endl;
		cout << " 5 - Display streets list" << endl;
		cout << " 0 - Exit Program" << endl << endl;

		cout << "Choose an option: ";
		getEntry(op, 0, 5);

		ClearScreen();

		switch (op)
		{
		case 1:
			createPickRoute(gc);
			break;
		case 2:
			;
			break;
		case 3:
			cout << "Trucks: " << endl << endl;
			gc.listTrucks();
			break;
		case 4:
			cout << "Containers: " << endl << endl;
			gc.listDeposits();
			break;
		case 5:
			cout << "Streets: " << endl << endl;
			gc.listRoads();
			;
			break;
		case 0:
			return;
		}

		waitReturn();
	}
}

vector<unsigned int> manualPicking(GarbageCentral& gc){
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

		cout << "Insert an ID - by level of emergency (0 to stop inserting): ";


		getEntry(op);

		if (op == 0)
			stop = true;
		else if (find(deposits_id.begin(), deposits_id.end(), op) != deposits_id.end()){
			cout << "Deposit ID already inserted, insert another (0 to stop inserting)";
			clearline(x, y);
			valid = false;
		}
		else if (gc.hasDeposit(op)){
			deposits_id.push_back(op);
			ClearScreen();
			valid = true;
		}
		else {
			cout << "Invalid Deposit ID, insert again (0 to stop inserting)";
			clearline(x, y);
			valid = false;
		}

	}while(!stop);

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
	}while (!valid);

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
		} catch (Unreachable& e){
			cout << "The path is not reachable" << endl;
		}
		break;
	case 2:
		deposits_id = manualPicking(gc);
		try{
			data = gc.createPickingRoute(t, deposits_id);
		}catch (RouteMissingData& e) {
			cout << "Truck doesn't have enough capacity" << endl;
		} catch (Unreachable& e){
			cout << "The path is not reachable" << endl;
		}
		break;
	case 0:
		return;
	}


	auto route = data.first;
	auto failed = data.second;

	cout << "Route generated for truck Nr. " << t << ":" << endl;
	for (unsigned i = 0; i < route.size(); i++) {
		auto info = route[i].first;
		auto roads = route[i].second;

		cout << info[SOURCE]->print() << "  --->  ";
		for (unsigned j = 0; j < roads.size(); j++) {
			cout << roads[j]->print() << "  --->  ";
		}
		cout << info[DESTINATION]->print() << endl;
	}
}
