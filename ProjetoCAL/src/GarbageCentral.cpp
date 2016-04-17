/*
 * GarbageCentral.cpp
 *
 *  Created on: 17/04/2016
 *      Author: User
 */


#include "GarbageCentral.h"



GarbageCentral::GarbageCentral(const Reader& r) {

	for (hashRelationship::const_iterator it = r.relations.begin(); it != r.relations.end(); it++) {

		hashRoad::const_iterator it_road = r.roads.find(Road(it->road_id));
		hashNode::const_iterator it_node1 = r.nodes.find(Node(it->node1_id));
		hashNode::const_iterator it_node2 = r.nodes.find(Node(it->node2_id));


		GarbageDeposit gd1 = GarbageDeposit(it->node1_id);
		GarbageDeposit gd2 = GarbageDeposit(it->node2_id);
		graph.addVertex(gd1);
		graph.addVertex(gd2);

		double distance = it_node1->distanceFrom(*it_node2);

		if (it_road->two_way)
		{
			graph.addEdge(gd1, gd2, distance);
			graph.addEdge(gd2, gd1, distance);
		}
		else
			graph.addEdge(gd1, gd2, distance);
	}
}




void GarbageCentral::print() {

	vector<GarbageDeposit> v = graph.dfs();

	for (unsigned i = 0; i < v.size(); i++) {
		cout << v[i].getID() << endl;
	}
}
