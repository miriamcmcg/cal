/*
 * GarbageCentral.cpp
 *
 *  Created on: 17/04/2016
 *      Author: User
 */


#include "GarbageCentral.h"



Data GarbageCentral::getRoute(vector<GarbageDeposit*> to_pick) {

	if (to_pick.size() <= 1)
		throw RouteMissingData();

	auto map = graph.dfs();
	auto map_it = begin(map);

	unsigned pickedCounter = 0;

	Route route;
	vector<GarbageDeposit*> missing_deposits;
	vector<GarbageDeposit*>::iterator gd1_it;
	vector<GarbageDeposit*>::iterator gd2_it;

	while ( (gd1_it = find(begin(to_pick), end(to_pick), map_it->getPointer())) == end(to_pick) ) {
		map_it++;
	}
	map_it++;
	pickedCounter++;


	while (pickedCounter != to_pick.size()) {

		if ( (gd2_it = find(begin(to_pick), end(to_pick), map_it->getPointer())) != end(to_pick)) {

			try {
				Path section = getShortestPath(*gd1_it, *gd2_it);
				route.push_back(section);
				*gd1_it = *gd2_it;
			} catch (NoOptimalPath &e) {
				missing_deposits.push_back(*gd2_it);
			}

			pickedCounter++;
		}

		map_it++;
	}

	return make_pair(route, missing_deposits);
}




Path GarbageCentral::filter(const Path &p) {

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



Path GarbageCentral::convert(const GraphInfo &p) {

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

	treat_plant = new TreatmentPlant(0, "GarbageCentral", 0, 0, 0);
	deposits.push_back(new GarbageDeposit(1, 0, 0, 0, 9000, 500));
	deposits.push_back(new GarbageDeposit(2, 0, 0, 0, 7000, 1000));
	deposits.push_back(new GarbageDeposit(3, 0, 0, 0, 15000, 9000));
	deposits.push_back(new GarbageDeposit(4, 0, 0, 0, 5600, 100));
	deposits.push_back(new GarbageDeposit(5, 0, 0, 0, 2000, 80));
	deposits.push_back(new GarbageDeposit(6, 0, 0, 0, 7000, 400));


	graph.addVertex(GDPointer(treat_plant));
	for (unsigned i = 0; i < deposits.size(); i++)
		graph.addVertex(GDPointer(deposits[i]));

	roads.push_back(new Road(0, "road 0 (0->1)", 10, 50));
	roads.push_back(new Road(1, "road 1 (0->2)", 5, 50));
	roads.push_back(new Road(2, "road 2 (1->2)", 3, 20));
	roads.push_back(new Road(3, "road 3 (1->3)", 8, 80));
	roads.push_back(new Road(4, "road 4 (2->3)", 3, 50));
	roads.push_back(new Road(5, "road 5 (3->5)", 2, 40));
	roads.push_back(new Road(6, "road 6 (2->6)", 8, 20));
	roads.push_back(new Road(7, "road 7 (5->1)", 8, 80));
	roads.push_back(new Road(8, "road 8 (5->6)", 8, 80));

	graph.addEdge(GDPointer(treat_plant), GDPointer(deposits[0]), RoadPointer(roads[0]));
	graph.addEdge(GDPointer(treat_plant), GDPointer(deposits[1]), RoadPointer(roads[1]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[1]), RoadPointer(roads[2]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[2]), RoadPointer(roads[3]));
	graph.addEdge(GDPointer(deposits[1]), GDPointer(deposits[2]), RoadPointer(roads[4]));
	graph.addEdge(GDPointer(deposits[2]), GDPointer(deposits[4]), RoadPointer(roads[5]));
	graph.addEdge(GDPointer(deposits[1]), GDPointer(deposits[5]), RoadPointer(roads[6]));
	graph.addEdge(GDPointer(deposits[5]), GDPointer(deposits[0]), RoadPointer(roads[7]));
	graph.addEdge(GDPointer(deposits[4]), GDPointer(deposits[5]), RoadPointer(roads[8]));


	ifstream in("trucks.txt");
	int cap;
	if (in.good()) {
		while (in >> cap) {
			trucks.push_back(GarbageTruck(cap));
		}
	}
}



GarbageCentral::GarbageCentral(const Reader& r) {

	auto it = begin(r.relations);
	auto it_road = r.links.find(Link(it->road_id));
	auto it_node1 = r.nodes.find(Node(it->node1_id));
	auto it_node2 = r.nodes.find(Node(it->node2_id));

	treat_plant = new TreatmentPlant(it_node1->node_id, "Central", it_node1->x, it_node1->y, it_node1->z);
	GDPointer gd1 = GDPointer(treat_plant);
	graph.addVertex(gd1);

	deposits.push_back(new GarbageDeposit(it_node2->node_id, it_node2->x, it_node2->y, it_node2->z));
	GDPointer gd2 = GDPointer(deposits[0]);
	graph.addVertex(gd2);

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

		pos = depositPosition(it_node2->node_id);
		if (pos == -1) {
			deposits.push_back(new GarbageDeposit(it_node2->node_id,
					it_node2->x, it_node2->y, it_node2->z));
			pos = deposits.size() - 1;
		}


		gd2 = GDPointer(deposits[pos]);
		graph.addVertex(gd2);


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




	ifstream in("trucks.txt");
	int cap;
	if (in.good()) {
		while (in >> cap) {
			trucks.push_back(GarbageTruck(cap));
		}
	}
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



Path GarbageCentral::getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2) {

	auto gd1_ptr = GDPointer(gd1);
	auto gd2_ptr = GDPointer(gd2);

	if (! graph.myDijkstraShortestPath(gd1_ptr, gd2_ptr))
		throw NoOptimalPath();

	auto res = graph.getPath(gd1_ptr, gd2_ptr);
	auto info = convert(res);

	return info;
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



Data GarbageCentral::createPickingRoute(unsigned int truckID) {

	int pos = truckPosition(truckID);

	if (pos == -1)
		throw TruckNonExistent();

	GarbageTruck &truck = trucks[pos];
	truck.empty();
	vector<GarbageDeposit*> to_pick = { treat_plant };
	for (unsigned i = 0; i < deposits.size(); i++) {
		if ( truck.addCarrying(deposits[i]->getCapacityOccupied()) ) {
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
	route[0].first[SOURCE]->empty();
	for (auto section : route) {
		section.first[DESTINATION]->empty();
	}

	sortDeposits();

	return data;
}


Data GarbageCentral::createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id) {

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
		route[0].first[SOURCE]->empty();
		for (auto section : route) {
			section.first[DESTINATION]->empty();
		}

		sortDeposits();
	}

	return data;
}



void GarbageCentral::updateDepositOccupied(unsigned int depositID, unsigned int capOcup) {

	int pos = depositPosition(depositID);

	if (pos == -1)
		throw DepositNonExistent();

	deposits[pos]->setCapacityOccupied(capOcup);
	sortDeposits();
}



void GarbageCentral::listTrucks() const {
	cout << " " << setw(4) << "ID" << " |" <<  setw(13) << "Max Capacity" << " |" << endl;
	cout << " ---------------------" << endl;
	for (unsigned int i = 0; i < trucks.size(); i++){
		cout << " " << setw(4) << trucks[i].getID()
																											 << " |" << setw(13) << trucks[i].getCapacity()<< " |" <<  endl;
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
	cout << " " << setw(15) << "ID" << " |" <<  setw(25) << "Name" << " |" << setw(9) << "Distance" << " |" << setw(14) <<"Average Speed" << " |"<< endl;
	cout << " -----------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < roads.size(); i++){
		cout << " " << setw(15) << roads[i]->getID() << " |"
				<< setw(25) << roads[i]->getName() << " |"
				<< setw(9) << roads[i]->getDistance() << " |"
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



void GarbageCentral::test() {

	/***** TESTE 1 ****/
	cout << "Processing deposits 1, 2 and 3\n";
	cout << "Expected deposit order: 1 -> 2 -> 3\n";
	cout << "Expected: road 0, road 2, road 4\n";

	//	vector<GarbageDeposit*> to_pick;
	//	to_pick.push_back(treat_plant);
	//	to_pick.push_back(deposits[0]);
	//	to_pick.push_back(deposits[1]);
	//	to_pick.push_back(deposits[2]);
	updateRoadAvailable(0, false);
	updateRoadAvailable(7, false);

	vector<GarbageDeposit*> to_pick;
	to_pick.push_back(treat_plant);
	to_pick.push_back(deposits[1]);
	to_pick.push_back(deposits[5]);
	to_pick.push_back(deposits[0]);

	Data data = getRoute(to_pick);

	auto route = data.first;
	auto failed = data.second;
	for (unsigned i = 0; i < route.size(); i++) {
		auto info = route[i].first;
		auto roads = route[i].second;

		cout << info[SOURCE]->print() << "  --->  ";
		for (unsigned j = 0; j < roads.size(); j++) {
			cout << roads[j]->print() << "  --->  ";
		}
		cout << info[DESTINATION]->print() << endl;
	}

	if (failed.size() != 0)
	{
		cout << "No optimal route found, these containers could not be picked:" << endl;
		for(unsigned int i = 0; i < failed.size(); i++){
			cout << " " << i + 1 << ". " << failed[i]->getID()<< endl;
		}
	}
	/******************/



}


