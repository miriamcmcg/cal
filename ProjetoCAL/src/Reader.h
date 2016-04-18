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
#include <unordered_set>
#include <boost/functional/hash.hpp>
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


namespace std {
template <>
struct hash<Node> {
	size_t operator() (const Node& n) const {
		size_t seed { 0 };
		boost::hash_combine(seed, n.node_id);
		return seed;
	}
};
}



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



namespace std {
template <>
struct hash<Road> {
	size_t operator() (const Road& r) const {
		size_t seed { 0 };
		boost::hash_combine(seed, r.road_id);
		return seed;
	}
};
}




class Relationship {

public:
	unsigned long road_id;
	unsigned long node1_id;
	unsigned long node2_id;

	Relationship(unsigned long rid, unsigned long n1id, unsigned long n2id) : road_id(rid), node1_id(n1id), node2_id(n2id) {};

	bool operator==(const Relationship &r) const { return (road_id == r.road_id) && (node1_id == r.node1_id) && (node2_id && r.node2_id); };
	friend class GarbageCentral;
};


namespace std {
template <>
struct hash<Relationship> {
	size_t operator() (const Relationship& r) const {
		size_t seed { 0 };
		boost::hash_combine(seed, r.road_id);
		boost::hash_combine(seed, r.node1_id);
		boost::hash_combine(seed, r.node2_id);
		return seed;
	}
};
}







class Reader {

private:
	unordered_set<Node> nodes = {};
	unordered_set<Road> roads = {};
	unordered_set<Relationship> relations = {};

	void loadNodes();
	void loadRoads();
	void loadRelations();
public:
	void readFiles();
	void printInfo();


	friend class GarbageCentral;
};


#endif /* READER_H_ */
