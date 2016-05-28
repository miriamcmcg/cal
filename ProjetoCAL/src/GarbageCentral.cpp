#include "GarbageCentral.h"



Data GarbageCentral::getRoute(vector<GarbageDeposit*> to_pick) {

	if (to_pick.size() <= 1)
		throw RouteMissingData();

	auto map = graph.dfs();
	auto map_it = begin(map);

	Route route;
	vector<GarbageDeposit*> missing_deposits;
	GarbageDeposit* gd = new GarbageDeposit();
	vector<GarbageDeposit*>::iterator gd1_it;

	while ( (gd1_it = find(begin(to_pick), end(to_pick), map_it->getPointer())) == end(to_pick) ) {
		map_it++;
	}

	*gd = **gd1_it;
	map_it++;



	while (to_pick.size() > 1) {

		if ( find(to_pick.begin(), to_pick.end(), map_it->getPointer()) != to_pick.end() ) {

			try {
				Section section = getShortestPath(gd, map_it->getPointer());
				updatePicks(to_pick, section);
				route.push_back(section);
				*gd = *section.first[section.first.size() - 1];
			} catch (NoOptimalPath &e) {
				missing_deposits.push_back(map_it->getPointer());

				for (unsigned i = 0; i < to_pick.size(); i++) {
					if ( *to_pick[i] == *(map_it->getPointer()) ) {
						to_pick.erase(begin(to_pick) + i);
						break;
					}
				}
			}
		}

		map_it++;
	}

	delete gd;
	return make_pair(route, missing_deposits);
}




Section GarbageCentral::filter(const Section &p) {

	vector<GarbageDeposit*> gds = p.first;
	vector<GarbageDeposit*> gds_filtered = { gds[0], gds[gds.size() - 1] };

	vector<Road*> roads = p.second;
	vector<Road*> roads_filtered;

	roads_filtered.push_back(roads[0]);
	for (unsigned i = 1; i < roads.size(); i++) {
		if (roads[i]->getName() != roads_filtered[roads_filtered.size() - 1]->getName())
			roads_filtered.push_back(roads[i]);
	}

	return make_pair(gds_filtered, roads_filtered);
}



Section GarbageCentral::convert(const GraphInfo &p) {

	vector<GDPointer> gds_ptr = p.first;
	vector<GarbageDeposit*> gds;

	vector<RoadPointer> roads_ptr = p.second;
	vector<Road*> roads;


	for (unsigned i = 0; i < gds_ptr.size(); i++)
		gds.push_back(gds_ptr[i].getPointer());

	for (unsigned i = 0; i < roads_ptr.size(); i++)
		roads.push_back(roads_ptr[i].getPointer());

	return make_pair(gds, roads);
}




int GarbageCentral::depositPosition(unsigned int id) const {
	for (unsigned int i = 0; i < deposits.size(); i++){
		if (deposits[i]->getID() == id)
			return i;
	}
	return -1;
}



int GarbageCentral::roadPosition(unsigned int id) const {
	for (unsigned int i = 0; i < roads.size(); i++) {
		if (roads[i]->getID() == id)
			return i;
	}

	return -1;
}



int GarbageCentral::truckPosition(unsigned int id) const {
	for (unsigned int i = 0; i < trucks.size(); i++) {
		if (trucks[i].getID() == id)
			return i;
	}

	return -1;
}



void GarbageCentral::sortDeposits(){
	sort(deposits.begin(), deposits.end(), [](const GarbageDeposit* a, const GarbageDeposit* b) {
		return a->getCapacityOccupied() > b->getCapacityOccupied();
	});
}



GarbageCentral::GarbageCentral() {

	treat_plant = new TreatmentPlant(0, "Central", 0, 0, 0);
	deposits.push_back(new GarbageDeposit(1, 0, 0, 0, 9000, 500));
	deposits.push_back(new GarbageDeposit(2, 0, 0, 0, 7000, 1000));
	deposits.push_back(new GarbageDeposit(3, 0, 0, 0, 15000, 9000));
	deposits.push_back(new GarbageDeposit(4, 0, 0, 0, 5600, 100));
	deposits.push_back(new GarbageDeposit(5, 0, 0, 0, 2000, 80));
	deposits.push_back(new GarbageDeposit(6, 0, 0, 0, 7000, 400));


	graph.addVertex(GDPointer(treat_plant));
	for (unsigned i = 0; i < deposits.size(); i++)
		graph.addVertex(GDPointer(deposits[i]));

	roads.push_back(new Road(0, "road 0", 10, 50));
	roads.push_back(new Road(1, "road 1", 5, 50));
	roads.push_back(new Road(2, "road 2", 3, 20));
	roads.push_back(new Road(3, "road 3", 8, 80));
	roads.push_back(new Road(4, "road 4", 3, 50));
	roads.push_back(new Road(5, "road 5", 2, 40));
	roads.push_back(new Road(6, "road 6", 8, 20));
	roads.push_back(new Road(7, "road 7", 8, 80));
	roads.push_back(new Road(8, "road 8", 8, 80));

	graph.addEdge(GDPointer(treat_plant), GDPointer(deposits[0]), RoadPointer(roads[0]));
	graph.addEdge(GDPointer(treat_plant), GDPointer(deposits[1]), RoadPointer(roads[1]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[1]), RoadPointer(roads[2]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[2]), RoadPointer(roads[3]));
	graph.addEdge(GDPointer(deposits[1]), GDPointer(deposits[2]), RoadPointer(roads[4]));
	graph.addEdge(GDPointer(deposits[2]), GDPointer(deposits[4]), RoadPointer(roads[5]));
	graph.addEdge(GDPointer(deposits[1]), GDPointer(deposits[5]), RoadPointer(roads[6]));
	graph.addEdge(GDPointer(deposits[4]), GDPointer(deposits[0]), RoadPointer(roads[7]));
	graph.addEdge(GDPointer(deposits[4]), GDPointer(deposits[5]), RoadPointer(roads[8]));


	// Read trucks
	ifstream in("trucks.txt");
	int cap;
	if (in.good()) {
		while (in >> cap) {
			trucks.push_back(GarbageTruck(cap));
		}
	}
	in.close();


	// Read drivers
	in.open("drivers.txt");
	string name;
	if (in.good()) {
		while (getline(in, name, ';')) {
			drivers.push_back(new Driver(name));

			if (in.peek() == '\n')
				in.ignore(1);
		}
	}
	in.close();
}



GarbageCentral::GarbageCentral(const Reader& r) {


	if (! r.relations.empty()) {

		auto it = begin(r.relations);
		auto it_road = r.links.find(Link(it->road_id));
		auto it_node1 = r.nodes.find(Node(it->node1_id));
		auto it_node2 = r.nodes.find(Node(it->node2_id));

		treat_plant = new TreatmentPlant(it_node1->node_id, "Central", it_node1->x, it_node1->y, it_node1->z);
		GDPointer gd1 = GDPointer(treat_plant);
		graph.addVertex(gd1);

		minX = it_node1->x;
		minY = it_node1->y;
		minZ = it_node1->z;
		maxX = it_node1->x;
		maxY = it_node1->y;
		maxZ = it_node1->y;

		deposits.push_back(new GarbageDeposit(it_node2->node_id, it_node2->x, it_node2->y, it_node2->z));
		GDPointer gd2 = GDPointer(deposits[0]);
		graph.addVertex(gd2);

		if (it_node2->x < minX)
			minX = it_node2->x;
		else if (it_node2->x > maxX)
			maxX = it_node2->x;

		if (it_node2->y < minY)
			minY = it_node2->y;
		else if (it_node2->y > maxY)
			maxY = it_node2->y;

		if (it_node2->z < minZ)
			minZ = it_node2->z;
		else if (it_node2->z > maxZ)
			maxZ = it_node2->z;

		double distance = it_node1->distanceFrom(*it_node2);
		roads.push_back(new Road(it_road->link_id, it_road->link_name, distance, rand() % 70));
		RoadPointer road_ptr = RoadPointer(roads[0]);

		if (it_road->two_way)
		{
			graph.addEdge(gd1, gd2, road_ptr);
			graph.addEdge(gd2, gd1, road_ptr);
		}
		else
			graph.addEdge(gd1, gd2, road_ptr);


		it++;
		for (; it != end(r.relations); it++) {

			it_road = r.links.find(Link(it->road_id));
			it_node1 = r.nodes.find(Node(it->node1_id));
			it_node2 = r.nodes.find(Node(it->node2_id));

			int pos;
			pos = depositPosition(it_node1->node_id);
			if (pos == -1) {
				deposits.push_back(new GarbageDeposit(it_node1->node_id,
						it_node1->x, it_node1->y, it_node1->z));

				pos = deposits.size() - 1;
			}

			gd1 = GDPointer(deposits[pos]);
			graph.addVertex(gd1);

			if (it_node1->x < minX)
				minX = it_node1->x;
			else if (it_node1->x > maxX)
				maxX = it_node1->x;

			if (it_node1->y < minY)
				minY = it_node1->y;
			else if (it_node1->y > maxY)
				maxY = it_node1->y;

			if (it_node1->z < minZ)
				minZ = it_node1->z;
			else if (it_node1->z > maxZ)
				maxZ = it_node1->z;



			pos = depositPosition(it_node2->node_id);
			if (pos == -1) {
				deposits.push_back(new GarbageDeposit(it_node2->node_id,
						it_node2->x, it_node2->y, it_node2->z));
				pos = deposits.size() - 1;
			}

			gd2 = GDPointer(deposits[pos]);
			graph.addVertex(gd2);

			if (it_node2->x < minX)
				minX = it_node2->x;
			else if (it_node2->x > maxX)
				maxX = it_node2->x;

			if (it_node2->y < minY)
				minY = it_node2->y;
			else if (it_node2->y > maxY)
				maxY = it_node2->y;

			if (it_node2->z < minZ)
				minZ = it_node2->z;
			else if (it_node2->z > maxZ)
				maxZ = it_node2->z;


			double distance = it_node1->distanceFrom(*it_node2);

			pos = roadPosition(it_road->link_id);
			if(pos == -1){
				roads.push_back(new Road(it_road->link_id, it_road->link_name, distance, rand() % 70));
				pos = roads.size() - 1;
			}

			road_ptr = RoadPointer(roads[pos]);

			if (it_road->two_way)
			{
				graph.addEdge(gd1, gd2, road_ptr);
				graph.addEdge(gd2, gd1, road_ptr);
			}
			else
				graph.addEdge(gd1, gd2, road_ptr);
		}

		sortDeposits();
	}



	// Read trucks
	ifstream in("trucks.txt");
	int cap;
	if (in.good()) {
		while (in >> cap) {
			trucks.push_back(GarbageTruck(cap));
		}
	}
	in.close();


	// Read drivers
	in.open("drivers.txt");
	string name;
	if (in.good()) {
		while (getline(in, name, ';')) {
			drivers.push_back(new Driver(name));

			if (in.peek() == '\n')
				in.ignore(1);
		}
	}
	in.close();
}



GarbageCentral::~GarbageCentral() {

	for (unsigned i = 0; i < deposits.size(); i++)
		delete deposits[i];

	for (unsigned i = 0; i < roads.size(); i++)
		delete roads[i];


	ofstream out("trucks.txt");
	if (out.good()) {
		for (unsigned i = 0; i < trucks.size(); i++) {
			out << trucks[i].getCapacity() << endl;
		}
	}
}



Section GarbageCentral::getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2) {

	auto gd1_ptr = GDPointer(gd1);
	auto gd2_ptr = GDPointer(gd2);

	if (! graph.myDijkstraShortestPath(gd1_ptr, gd2_ptr))
		throw NoOptimalPath();

	auto res = graph.getPath(gd1_ptr, gd2_ptr);
	auto info = convert(res);

	return info;
}


void GarbageCentral::updatePicks(vector<GarbageDeposit*>& to_pick, Section section) {

	auto nodes = section.first;
	for (unsigned i = 0; i < nodes.size() - 1; i++) {
		for (unsigned j = 0; j < to_pick.size(); j++) {
			if (*nodes[i] == *to_pick[j]) {
				to_pick.erase(begin(to_pick) + j);
				break;
			}
		}
	}
}







void GarbageCentral::updateRoadAvgSpeed(unsigned int roadID, double newSpeed) {

	int pos = roadPosition(roadID);

	if (pos == -1)
		throw RoadNonExistent();

	roads[pos]->setAvgSpeed(newSpeed);
}


void GarbageCentral::updateRoadAvailable(unsigned int roadID, bool available) {

	int pos = roadPosition(roadID);

	if (pos == -1)
		throw RoadNonExistent();

	roads[pos]->setAvailable(available);
}



Data GarbageCentral::createPickingRoute(unsigned int truckID, unsigned int driverID) {

	int pos = truckPosition(truckID);

	if (pos == -1)
		throw TruckNonExistent();

	int driverPos = driverPosition(driverID);

	if (driverPos == -1)
		throw DriverNonExistent();

	GarbageTruck &truck = trucks[pos];
	truck.empty();

	Driver* d = drivers[driverPos];
	truck.updateDriver(d);

	vector<GarbageDeposit*> to_pick = { treat_plant };
	for (unsigned i = 0; i < deposits.size(); i++) {
		unsigned int capOcup = deposits[i]->getCapacityOccupied();
		if ( capOcup != 0 && truck.addCarrying(capOcup) ) {
			to_pick.push_back(deposits[i]);
		}
	}


	Data data;
	try {
		data = getRoute(to_pick);
	} catch (RouteMissingData& e) {
		throw;
	}



	trucks[pos].empty();
	auto route = data.first;

	if (route.size() != 0) {
		route[0].first[0]->empty();
		for (auto section : route) {
			section.first[section.first.size() - 1]->empty();
		}

		sortDeposits();
	}

	return data;
}


Data GarbageCentral::createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id, unsigned int driverID) {

	int pos = truckPosition(truckID);

	if (pos == -1)
		throw TruckNonExistent();

	GarbageTruck &truck = trucks[pos];
	truck.empty();
	vector<GarbageDeposit*> to_pick = { treat_plant };
	for (unsigned i = 0; i < deposits_id.size(); i++) {
		int pos = depositPosition(deposits_id[i]);
		to_pick.push_back(deposits[pos]);

	}

	Data data;
	try {
		data = getRoute(to_pick);
	} catch (RouteMissingData& e) {
		throw;
	}


	trucks[pos].empty();
	auto route = data.first;

	if (route.size() != 0) {
		route[0].first[0]->empty();
		for (auto section : route) {
			section.first[section.first.size() - 1]->empty();
		}

		sortDeposits();
	}

	return data;
}



bool GarbageCentral::updateDepositOccupied(unsigned int depositID, unsigned int capOcup) {

	int pos = depositPosition(depositID);

	if (pos == -1)
		throw DepositNonExistent();

	if(! deposits[pos]->setCapacityOccupied(capOcup))
		return false;

	sortDeposits();
	return true;
}



void GarbageCentral::listTrucks() const {
	cout << " " << setw(4) << "ID" << " |" <<  setw(13) << "Max Capacity" << " |" << setw(30) << "Last Driver" << " |" <<  endl;
	cout << " -----------------------------------------------------" << endl;
	for (unsigned int i = 0; i < trucks.size(); i++){
		cout << " " << setw(4) << trucks[i].getID() << " |" << setw(13) << trucks[i].getCapacity()<< " |" << setw(30) << trucks[i].getDriver()->getName() << " |" <<  endl;
	}
}


bool GarbageCentral::hasTruck(unsigned int id) const {
	return (truckPosition(id) != -1);
}


void GarbageCentral::listDeposits() const {
	cout << " " << setw(15) << "ID" << " |" <<  setw(15) << "Cap. Occupied" <<
			" |" << setw(13) << "Max Capacity" << " |" << setw(27)  << "Coordinates" << " |" << endl;
	cout << " ------------------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < deposits.size(); i++){
		cout << " " << setw(15) << deposits[i]->getID() << " |" << setw(15)
																																																																																																																																																																																																																				<< deposits[i]->getCapacityOccupied() << " |" << setw(13)
																																																																																																																																																																																																																				<< deposits[i]->getMaxCapacity() << " |" << setw(27)
																																																																																																																																																																																																																				<< deposits[i]->coordsString() << " |" << endl;
	}
}


bool GarbageCentral::hasDeposit(unsigned int id) const {
	return (depositPosition(id) != -1);
}


void GarbageCentral::listRoads() const {
	cout << " " << setw(15) << "ID" << " |" <<  setw(50) << "Name" << " |" << setw(11) << "Distance" << " |" << setw(14) <<"Average Speed" << " |"<< endl;
	cout << " ----------------------------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < roads.size(); i++){
		cout << " " << setw(15) << roads[i]->getID() << " |"
				<< setw(50) << roads[i]->getName() << " |"
				<< setw(11) << roads[i]->getDistance() << " |"
				<< setw(14) << roads[i]->getAvgSpeed() << " |\n";
	}
}



bool GarbageCentral::hasRoad(unsigned int id) const {
	return (roadPosition(id) != -1);
}

bool GarbageCentral::truckCanPick(unsigned int truck_id, unsigned int container_id){
	int t_pos = truckPosition(truck_id);
	int c_pos = depositPosition(container_id);
	if(!trucks[t_pos].addCarrying(deposits[c_pos]->getCapacityOccupied())){
		return false;
	}
	return true;
}


double GarbageCentral::getMinX() const {
	return minX;
}

double GarbageCentral::getMinY() const {
	return minY;
}

double GarbageCentral::getMinZ() const {
	return minZ;
}

double GarbageCentral::getMaxX() const {
	return maxX;
}

double GarbageCentral::getMaxY() const {
	return maxY;
}

double GarbageCentral::getMaxZ() const {
	return maxZ;
}



void GarbageCentral::listDrivers() const {
	cout << " " << setw(15) << "ID" << " |" <<  setw(50) << "Name" << " |" << endl;
	cout << " ---------------------------------------------------------------------" << endl;
	for (auto d : drivers){
		cout << " " << setw(15) << d->getID() << " |"
				<< setw(50) << d->getName() << " |\n";
	}
}


vector<Driver*> GarbageCentral::searchDriversExact(string name) {
	vector<Driver*> candidates;

	for (auto driver : drivers) {
		if (matches(driver->getName(), name))
			candidates.push_back(driver);
	}

	return candidates;
}


Driver* GarbageCentral::searchDriverApproximate(string name) {
	int min = 9999;
	Driver* approx;


	for (auto driver : drivers) {
		int distance = EditDistance(driver->getName(), name);

		if (distance < min) {
			min = distance;
			approx = driver;
		}
	}

	return approx;
}


vector<Road*> GarbageCentral::searchRoadsExact(string name){
	vector<Road*> candidates;

	for(auto road : roads){
		if(matches(road->getName(), name))
			candidates.push_back(road);
	}

	return candidates;
}

Road* GarbageCentral::searchRoadApproximate(string name){
	int min = 9999;
	Road* approx;

	for(auto road : roads){
		int distance = EditDistance(road->getName(), name);

		if(distance < min){
			min = distance;
			approx = road;
		}
	}
	return approx;
}

unsigned int GarbageCentral::driverPosition(int driverID){
	unsigned int pos = -1;
	for (unsigned int  i = 0; i < drivers.size(); i++){
		if (drivers[i]->getID() == driverID){
			pos = i;
			break;
		}
	}
	return pos;
}



void GarbageCentral::addRoad(unsigned long roadID) {
	unsigned long ID;
	string name;
	double distance, speed;

	int pos = roadPosition(roadID);

	if (pos == -1)
		throw RoadNonExistent();


	name = roads[pos]->getName();
	ID = searchAvailableRoadID();

	distance = roads[pos]->getDistance() / 2;
	roads[pos]->setDistance(roads[pos]->getDistance() / 2);

	speed = roads[pos]->getAvgSpeed();

	Road* r = new Road(ID, name, distance, speed);
	roads.push_back(r);

	GarbageDeposit* gd = new GarbageDeposit(searchAvailableDepositID(), 0, 0, 0, 8000, 0);
	deposits.push_back(gd);

	graph.addNode(GDPointer(gd), RoadPointer(roads[pos]), RoadPointer(r));
}


unsigned long GarbageCentral::searchAvailableRoadID() {
	bool valid = false;
	int ID = -1;

	while (!valid) {
		ID = (rand() % 100000) + 1;

		if (roadPosition(ID) == -1)
			valid = true;
	}

	return ID;
}


unsigned long GarbageCentral::searchAvailableDepositID() {
	bool valid = false;
	int ID = -1;

	while (!valid) {
		ID = (rand() % 100000) + 1;

		if (depositPosition(ID) == -1)
			valid = true;
	}

	return ID;
}


void GarbageCentral::test() {

	vector<GarbageDeposit*> to_pick;
	to_pick.push_back(treat_plant);

	/***** TEST 1.1 ****/
	//	cout << "Processing deposit 2\n";
	//	cout << "Expected: road 1\n";
	//
	//	to_pick.push_back(deposits[1]);
	/******************/

	/***** TEST 1.2 ****/
	//	cout << "Processing deposit 2\n";
	//	cout << "Expected: road 0, road 2\n";
	//
	//	updateRoadAvailable(1, false);
	//	to_pick.push_back(deposits[1]);
	/******************/


	/***** TEST 1.3 ****/
	//	cout << "Processing deposit 2\n";
	//	cout << "Expected: road 0, road 2\n";
	//
	//	updateRoadAvgSpeed(1, 10);
	//	to_pick.push_back(deposits[1]);
	/******************/


	/***** TEST 2.1 ****/
	//	cout << "Processing deposits 1, 2, 6\n";
	//	cout << "Expected: road 0, road 2, road 4, road 5, road 8\n";
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[5]);
	/******************/


	/***** TEST 2.2 ****/
	// ******* IMPORTANT *******
	//	cout << "Processing deposits 1, 2, 6\n";
	//	cout << "Expected: road 0, road 2, road 6\n";
	//
	//	updateRoadAvailable(4, false);
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[5]);
	/******************/


	/***** TEST 2.3 ****/
	// ******* IMPORTANT *******
	//	cout << "Processing deposits 1, 2, 6\n";
	//	cout << "Expected: road 0, road 2, road 6\n";
	//
	//	updateRoadAvgSpeed(4, 0);		// equivalent to set road 4 unavailable
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[5]);
	/******************/


	/***** TEST 3.1 ****/
	//	cout << "Processing deposits 1, 2, 5\n";
	//	cout << "Expected: road 0, road 2, road 4, road 5\n";
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[4]);
	/******************/


	/***** TEST 3.2 ****/
	// ******* IMPORTANT *******
	//	cout << "Processing deposits 1, 2, 5\n";
	//	cout << "Expected: road 1, road 4, road 5, road 7\n";
	//
	//	updateRoadAvailable(0, false);
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[4]);
	/******************/


	/***** TEST 3.3 ****/
	// ******* IMPORTANT *******
	//	cout << "Processing deposit 1, 2, 5\n";
	//	cout << "Expected: road 1, road 4, road 5\n";
	//	cout << "Note: Deposit 1 shouldn't be reachable\n";
	//
	//	updateRoadAvailable(0, false);
	//	updateRoadAvailable(7, false);
	//
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[4]);
	/******************/


	/***** TEST 4 ****/
	//	cout << "Processing deposit 4\n";
	//	cout << "Deposit 4 shouldn't be reachable\n";
	//
	//	to_pick.push_back(deposits[3]);
	/******************/



	cout << "--------------------------------------------\n";

	Data data = getRoute(to_pick);

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
}


