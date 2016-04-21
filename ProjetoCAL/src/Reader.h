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
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <cmath>


#define EARTH_RADIUS_KM 			6371


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

	double distanceFrom(const Node& n) const { return sqrt(pow(x - n.x, 2) + pow(y - n.y, 2) + pow(z - n.z, 2)); };

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



class Link {

public:
	unsigned long link_id;
	string link_name;
	bool two_way;

	Link(unsigned long id, string name, bool tw) : link_id(id), link_name(name), two_way(tw) {};
	Link(unsigned long id) : link_id(id), link_name(""), two_way(false) {};

	bool operator==(const Link &r) const { return link_id == r.link_id; };
	friend class GarbageCentral;
};



namespace std {
template <>
struct hash<Link> {
	size_t operator() (const Link& r) const {
		size_t seed { 0 };
		boost::hash_combine(seed, r.link_id);
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
	unordered_set<Link> links = {};
	unordered_set<Relationship> relations = {};

	void loadNodes();
	void loadLinks();
	void loadRelations();
public:
	void readFiles();
	void printInfo();


	friend class GarbageCentral;
};


#endif /* READER_H_ */
