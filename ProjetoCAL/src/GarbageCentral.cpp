/*
 * GarbageCentral.cpp
 *
 *  Created on: 17/04/2016
 *      Author: User
 */


#include "GarbageCentral.h"
#include <algorithm>




pair<vector<GarbageDeposit>, vector<Road>> GarbageCentral::filter(pair<vector<GarbageDeposit>, vector<Road>> &p) {

	vector<GarbageDeposit> gds = p.first;
	vector<GarbageDeposit> gds_filtered = { gds[0], gds[gds.size() - 1] };

	vector<Road> roads = p.second;
	vector<Road> roads_filtered;

	roads_filtered.push_back(roads[0]);
	for (unsigned i = 1; i < roads.size(); i++) {
		if (roads[i].getName() != roads_filtered[roads_filtered.size() - 1].getName())
			roads_filtered.push_back(roads[i]);
	}

	return make_pair(gds_filtered, roads_filtered);
}




bool compareGD(const GarbageDeposit& a, const GarbageDeposit& b) {
	return a.getCapacityOccupied() > b.getCapacityOccupied();
}


GarbageCentral::GarbageCentral(const Reader& r) {

	for (auto it = begin(r.nodes); it != end(r.nodes); it++) {
		deposits.push_back(GarbageDeposit(it->node_id));
	}

	for (auto it = begin(r.links); it != end(r.links); it++) {
		roads.push_back(Road(it->link_id, it->link_name));
	}



	for (auto it = begin(r.relations); it != end(r.relations); it++) {

		auto it_road = r.links.find(Link(it->road_id));
		auto it_node1 = r.nodes.find(Node(it->node1_id));
		auto it_node2 = r.nodes.find(Node(it->node2_id));

		GarbageDeposit gd1 = GarbageDeposit(it->node1_id);
		GarbageDeposit gd2 = GarbageDeposit(it->node2_id);
		graph.addVertex(gd1);
		graph.addVertex(gd2);

		double distance = it_node1->distanceFrom(*it_node2);


		if (it_road->two_way)
		{
			graph.addEdge(gd1, gd2, Road(it_road->link_id, it_road->link_name), distance);
			graph.addEdge(gd2, gd1, Road(it_road->link_id, it_road->link_name), distance);
		}
		else
			graph.addEdge(gd1, gd2, Road(it_road->link_id, it_road->link_name), distance);
	}


	sort(deposits.begin(), deposits.end(), compareGD);
}



pair<vector<GarbageDeposit>, vector<Road>>
GarbageCentral::getShortestPath(const GarbageDeposit& gd1, const GarbageDeposit& gd2) {

//	if (! graph.myDijkstraShortestPath(gd1, gd2))
//		throw NoPathFound();

	graph.myDijkstraShortestPath(gd1);
	auto res = graph.getPath(gd1, gd2);
	return res;
}



void GarbageCentral::getRoute(vector<GarbageDeposit> to_pick) {

	auto map = graph.dfs();
	auto map_it = begin(map);

	unsigned pickedCounter = 0;

	pair<vector<GarbageDeposit>, vector<Road>> result;
	vector<GarbageDeposit>::iterator gd1_it;
	vector<GarbageDeposit>::iterator gd2_it;

	while ( (gd1_it = find(begin(to_pick), end(to_pick), *map_it)) == end(to_pick) ) {
		map_it++;
	}
	map_it++;
	pickedCounter++;


	while (pickedCounter != to_pick.size()) {

		if ( (gd2_it = find(begin(to_pick), end(to_pick), *map_it)) != end(to_pick)) {

			try {
				result = getShortestPath(*gd1_it, *gd2_it);
				result = filter(result);
			} catch (NoPathFound &e) {
				cout << "Cant link path\n";
				return;
			}

			auto v1 = result.first;
			auto v2 = result.second;

			cout << result.first[0].getID() << "  --->  ";
			for (unsigned i = 0; i < v2.size(); i++) {
				cout << v2[i].getName() << "  --->  ";
			}
			cout << result.first[1].getID() << endl;

			*gd1_it = *gd2_it;
			pickedCounter++;
		}

		map_it++;
	}
}



void GarbageCentral::aux() {

	vector<GarbageDeposit> vec;
	vec.push_back(deposits[0]);
	vec.push_back(deposits[1]);
	vec.push_back(deposits[5]);

	getRoute(vec);
}



void GarbageCentral::print() {

	vector<GarbageDeposit> v = graph.dfs();

	for (auto gd : v) {
		cout << gd.getID() << endl;
	}
}
