/*
 * Reader.h
 *
 *  Created on: 13/04/2016
 *      Author: User
 */

#ifndef READER_H_
#define READER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <tr1/unordered_set>
#include <cmath>


#define EARTH_RADIUS 			6371000


using namespace std;


inline unsigned long myHashInt(unsigned long x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x);
	return x;
}



class Node {

public:
	unsigned long node_id;
	double x;
	double y;
	double z;


	Node(unsigned long id, double x, double y, double z) : node_id(id), x(x), y(y), z(z) {};
	Node(unsigned long id) : node_id(id), x(-1), y(-1), z(-1) {};

	double distanceFrom(const Node& n) const { return sqrt((x*x - n.x*n.x) + (y*y - n.y*n.y) + (z*z - n.z*n.z)); };

	bool operator==(const Node &n) const { return node_id == n.node_id; };
	friend class GarbageCentral;
};



struct hNode {
	unsigned long operator() (const Node& n1) const {
		return myHashInt(n1.node_id);
	}

	bool operator() (const Node& n1, const Node& n2) const {
		return (n1.node_id == n2.node_id);
	}
};



class Road {

public:
	unsigned long road_id;
	string road_name;
	bool two_way;

	Road(unsigned long id, string name, bool tw) : road_id(id), road_name(name), two_way(tw) {};
	Road(unsigned long id) : road_id(id), road_name(""), two_way(false) {};

	bool operator==(const Road &r) const { return road_id == r.road_id; };

	friend class GarbageCentral;
};



struct hRoad {
	unsigned long operator() (const Road& r1) const {
		return myHashInt(r1.road_id);
	}

	bool operator() (const Road& r1, const Road& r2) const {
		return (r1.road_id == r2.road_id);
	}
};




class Relationship {

public:
	unsigned long road_id;
	unsigned long node1_id;
	unsigned long node2_id;

	Relationship(unsigned long rid, unsigned long n1id, unsigned long n2id) : road_id(rid), node1_id(n1id), node2_id(n2id) {};

	bool operator==(const Relationship &r) const { return road_id == r.road_id && node1_id == r.node1_id && node2_id && r.node2_id; };

	friend class GarbageCentral;
};


struct hRelationship {
	unsigned long operator() (const Relationship& r1) const {
		return myHashInt(r1.road_id + r1.node1_id + r1.node2_id);
	}

	bool operator() (const Relationship& r1, const Relationship& r2) const {
		return ( (r1.road_id == r2.road_id) && (r1.node1_id == r2.node1_id) && (r1.node2_id == r2.node2_id) );
	}
};



typedef tr1::unordered_set<Node, hNode, hNode> hashNode;
typedef tr1::unordered_set<Road, hRoad, hRoad> hashRoad;
typedef tr1::unordered_set<Relationship, hRelationship, hRelationship> hashRelationship;




class Reader {

private:
	hashNode nodes;
	hashRoad roads;
	hashRelationship relations;

	void loadNodes();
	void loadRoads();
	void loadRelations();
public:
	void readFiles();
	void printInfo();


	friend class GarbageCentral;
};


#endif /* READER_H_ */
