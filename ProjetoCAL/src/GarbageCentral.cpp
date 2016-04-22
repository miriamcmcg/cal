/*
 * GarbageCentral.cpp
 *
 *  Created on: 17/04/2016
 *      Author: User
 */


#include "GarbageCentral.h"



Data GarbageCentral::getRoute(vector<GarbageDeposit*> to_pick) {



	if (to_pick.size() <= 0)
		throw RouteMissingData();

	vector< GarbageDeposit* > missing_deposits;

	auto map = graph.dfs();
	auto map_it = begin(map);

	unsigned pickedCounter = 0;

	Route route;
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
				FilteredPath section = getShortestPath(*gd1_it, *gd2_it);
				route.push_back(section);
				*gd1_it = *gd2_it;
			} catch (NoOptimalPath &e) {
				missing_deposits.push_back(*gd2_it);
			} catch (Unreachable& e) {
				throw;
			}

			pickedCounter++;
		}

		map_it++;
	}

	return make_pair(route, missing_deposits);
}




FilteredPath GarbageCentral::filter(const GraphInfo &p) {

	vector<GDPointer> gds = p.first;
	vector<GarbageDeposit*> gds_filtered = { gds[0].getPointer(), gds[gds.size() - 1].getPointer() };

	vector<RoadPointer> roads = p.second;
	vector<Road*> roads_filtered;

	roads_filtered.push_back(roads[0].getPointer());
	for (unsigned i = 1; i < roads.size(); i++) {
		if (roads[i].getPointer()->getName() != roads_filtered[roads_filtered.size() - 1]->getName())
			roads_filtered.push_back(roads[i].getPointer());
	}

	return make_pair(gds_filtered, roads_filtered);
}





int GarbageCentral::depositPosition(unsigned int id){
	for (unsigned int i = 0; i < deposits.size(); i++){
		if (deposits[i]->getID() == id)
			return i;
	}
	return -1;
}



int GarbageCentral::roadPosition(unsigned int id) {
	for (unsigned int i = 0; i < roads.size(); i++) {
		if (roads[i]->getID() == id)
			return i;
	}

	return -1;
}



int GarbageCentral::truckPosition(unsigned int id) {
	for (unsigned int i = 0; i < trucks.size(); i++) {
		if (trucks[i].getID() == id)
			return i;
	}

	return -1;
}



GarbageCentral::GarbageCentral() {

	treat_plant = new TreatmentPlant(0, "GarbageCentral");
	deposits.push_back(new GarbageDeposit(1, 1000, 9000));
	deposits.push_back(new GarbageDeposit(2, 1000, 100));
	deposits.push_back(new GarbageDeposit(3, 1000, 9000));
	deposits.push_back(new GarbageDeposit(4, 1000, 100));

	graph.addVertex(GDPointer(treat_plant));
	for (unsigned i = 0; i < deposits.size(); i++)
		graph.addVertex(GDPointer(deposits[i]));

	roads.push_back(new Road(0, "starting road", 10, 20));
	roads.push_back(new Road(1, "rua 1", 7, 50));
	roads.push_back(new Road(2, "rua 2", 8, 54));
	roads.push_back(new Road(3, "rua 3", 10, 70));
	roads.push_back(new Road(4, "rua 4", 2, 30));
	roads.push_back(new Road(5, "rua 5", 5, 40));

	graph.addEdge(GDPointer(treat_plant), GDPointer(deposits[0]), RoadPointer(roads[0]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[1]), RoadPointer(roads[1]));
	graph.addEdge(GDPointer(deposits[1]), GDPointer(deposits[2]), RoadPointer(roads[2]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[2]), RoadPointer(roads[3]));
	graph.addEdge(GDPointer(deposits[0]), GDPointer(deposits[3]), RoadPointer(roads[4]));
	//graph.addEdge(GDPointer(deposits[2]), GDPointer(deposits[3]), RoadPointer(roads[5]));


	trucks.push_back(GarbageTruck(8000));
	trucks.push_back(GarbageTruck(10000));
	trucks.push_back(GarbageTruck(5000));
}



GarbageCentral::GarbageCentral(const Reader& r) {

	for (auto it = begin(r.relations); it != end(r.relations); it++) {

		auto it_road = r.links.find(Link(it->road_id));
		auto it_node1 = r.nodes.find(Node(it->node1_id));
		auto it_node2 = r.nodes.find(Node(it->node2_id));

		int pos;
		pos = depositPosition(it_node1->node_id);

		if (pos == -1) {
			deposits.push_back(new GarbageDeposit(it_node1->node_id));
			pos = deposits.size() - 1;
		}

		GDPointer gd1 = GDPointer(deposits[pos]);
		graph.addVertex(gd1);

		pos = depositPosition(it_node2->node_id);

		if (pos == -1) {
			deposits.push_back(new GarbageDeposit(it_node2->node_id));
			pos = deposits.size() - 1;
		}

		GDPointer gd2 = GDPointer(deposits[pos]);
		graph.addVertex(gd2);


		double distance = it_node1->distanceFrom(*it_node2);

		pos = roadPosition(it_road->link_id);

		if(pos == -1){
			roads.push_back(new Road(it_road->link_id, it_road->link_name, distance, rand() % 70));
			pos = roads.size() - 1;
		}

		RoadPointer r = RoadPointer(roads[pos]);

		if (it_road->two_way)
		{
			graph.addEdge(gd1, gd2, r);
			graph.addEdge(gd2, gd1, r);
		}
		else
			graph.addEdge(gd1, gd2, r);
	}

	sortDeposits();
}



GarbageCentral::~GarbageCentral() {

	for (unsigned i = 0; i < deposits.size(); i++)
		delete deposits[i];

	for (unsigned i = 0; i < roads.size(); i++)
		delete roads[i];
}



FilteredPath GarbageCentral::getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2) {

	auto gd1_ptr = GDPointer(gd1);
	auto gd2_ptr = GDPointer(gd2);

	try {
		if (! graph.myDijkstraShortestPath(gd1_ptr, gd2_ptr))
			throw NoOptimalPath();
	} catch(Unreachable& e){
		throw;
	}

	auto res = graph.getPath(gd1_ptr, gd2_ptr);
	auto info = filter(res);

	return info;
}



void GarbageCentral::updateRoadAvgSpeed(unsigned int ID, double newSpeed) {

	int pos = roadPosition(ID);

	//TODO THROW
	if (pos == -1);

	roads[pos]->setAvgSpeed(newSpeed);
}


void GarbageCentral::updateRoadAvailable(unsigned int ID, bool available) {

	int pos = roadPosition(ID);

	//TODO THROW
	if (pos == -1);

	roads[pos]->setAvailable(available);
}



Data GarbageCentral::createPickingRoute(unsigned int truckID) {

	int pos = truckPosition(truckID);

	//TODO THROW
	if (pos == -1);

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
		cout << "Truck doesn't have enough capacity\n";
		throw;
	} catch (Unreachable& e){
		throw;
	}


	truck.addPickingRoute(data.first);
	return data;
}

Data GarbageCentral::createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id) {

	int pos = truckPosition(truckID);

	//TODO THROW
	if (pos == -1);

	GarbageTruck &truck = trucks[pos];
	truck.empty();
	vector<GarbageDeposit*> to_pick = { treat_plant };
	for (unsigned i = 0; i < deposits_id.size(); i++) {
		int pos = depositPosition(deposits_id[i]);
		if ( truck.addCarrying(deposits[pos]->getCapacityOccupied()) ) {
			to_pick.push_back(deposits[pos]);
		}
	}

	Data data;
	try {
		data = getRoute(to_pick);
	} catch (RouteMissingData& e) {
		throw;
	} catch (Unreachable& e){
		throw;
	}


	truck.addPickingRoute(data.first);
	return data;
}

void GarbageCentral::sortDeposits(){
	sort(deposits.begin(), deposits.end(), [](const GarbageDeposit* a, const GarbageDeposit* b) {
		return a->getCapacityOccupied() > b->getCapacityOccupied();
	});
}

void GarbageCentral::pickGarbage(unsigned int truckID) {

	int pos = truckPosition(truckID);

	//TODO THROW
	if (pos == -1);

	Route route = trucks[pos].unload();

	for (auto section : route) {
		section.first[SOURCE]->empty();
		section.first[DESTINATION]->empty();
	}

	sortDeposits();

	for (auto info : route) {
		auto v1 = info.first;
		auto v2 = info.second;
	}
}



void GarbageCentral::aux() {

	vector<GarbageDeposit*> vec;
	vec.push_back(deposits[0]);
	vec.push_back(deposits[2]);

	getRoute(vec);

	updateRoadAvgSpeed(2, 20);
	getRoute(vec);

	updateRoadAvgSpeed(0, 0);
	getRoute(vec);

	cout << "-----------------------------\n";
	updateRoadAvgSpeed(2, 70);
	updateRoadAvgSpeed(0, 50);
	vec.pop_back();
	vec.push_back(deposits[3]);

	getRoute(vec);

	updateRoadAvailable(3, false);
	getRoute(vec);

	updateRoadAvailable(2, false);
	getRoute(vec);

	updateRoadAvailable(4, false);
	getRoute(vec);
}



void GarbageCentral::print() {

	vector<GDPointer> v = graph.dfs();

	for (auto gd : v) {
		cout << gd.getPointer()->getID() << endl;
	}
}

void GarbageCentral::listTrucks(){
	cout << " " << setw(4) << "ID" << " |" <<  setw(9) << "Capacity" << " |" << endl;
		cout << " -----------------" << endl;
	for (unsigned int i = 0; i < trucks.size(); i++){
		cout << " " << setw(4) << trucks[i].getID() << " |" << setw(9) << trucks[i].getCapacity()<< " |" <<  endl;
	}
}

bool GarbageCentral::hasTruck(unsigned int id){
	return (truckPosition(id) != -1);
}

void GarbageCentral::listDeposits(){
	cout << " " << setw(15) << "ID" << " |" <<  setw(10) << "Capacity" << " |" << endl;
	cout << " -----------------------------" << endl;
	for (unsigned int i = 0; i < deposits.size(); i++){
		cout << " " << setw(15) << deposits[i]->getID() << " |" << setw(10) << deposits[i]->getCapacityOccupied() << " |"<< endl;
	}
}

bool GarbageCentral::hasDeposit(unsigned int id){
	return (depositPosition(id) != -1);
}

void GarbageCentral::listRoads(){
	cout << " " << setw(15) << "ID" << " |" <<  setw(25) << "Name" << " |" << endl;
	cout << " --------------------------------------------" << endl;
	for (unsigned int i = 0; i < roads.size(); i++){
		cout << " " << setw(15) << roads[i]->getID() << " |" << setw(25) << roads[i]->getName() << " |"<< endl;
	}
}
