/*
 * Reader.cpp
 *
 *  Created on: 13/04/2016
 *      Author: User
 */

#include "Reader.h"

using namespace std;


void Reader::readFiles() {

	loadNodes();
	loadRoads();
	loadRelations();
}




void Reader::loadNodes() {

	ifstream in;
	in.open("a.txt", ios::in);


	if (in.good() && in.peek() != ifstream::traits_type::eof()) {
		while (in.good()) {
			char dummy;
			unsigned long node_id;
			double latitude_deg, longitude_deg, latitude_rad, longitude_rad;


			in >> node_id >> dummy;
			in >> latitude_deg >> dummy;
			in >> longitude_deg >> dummy;
			in >> latitude_rad >> dummy;
			in >> longitude_rad >> dummy;

			nodes.insert(Node(node_id, latitude_deg, longitude_deg, latitude_rad, longitude_rad));

			if (in.eof())
				break;

			if (in.fail()) {
				cerr << "Erro1" << endl;
				exit(1);
			}
		}
	}

	in.close();
}




void Reader::loadRoads() {

	ifstream in;
	in.open("b.txt", ios::in);


	if (in.good() && in.peek() != ifstream::traits_type::eof()) {
		while (in.good()) {
			char dummy;
			unsigned long road_id;
			string road_name, two_way_string;
			bool two_way;


			in >> road_id >> dummy;
			getline(in, road_name, ';');
			getline(in, two_way_string, '\n');

			two_way = two_way_string == "True" ? true : false;


			if (in.eof())
				break;


			roads.insert(Road(road_id, road_name, two_way));


			if (in.fail()) {
				cerr << "Erro2" << endl;
				exit(2);
			}
		}
	}

	in.close();
}





void Reader::loadRelations() {

	ifstream in;
	in.open("c.txt", ios::in);

	if (in.good() && in.peek() != ifstream::traits_type::eof()) {
		while (in.good()) {
			unsigned long road_id, node1_id, node2_id;
			string content;
			char dummy;
			stringstream ss;


			getline(in, content);

			if (in.eof())
				break;

			if (in.fail()) {
				cerr << "Erro3" << endl;
				exit(3);
			}


			ss.str(content);
			ss >> road_id >> dummy >> node1_id >> dummy >> node2_id;

			relations.insert(Relationship(road_id, node1_id, node2_id));
		}
	}

	in.close();
}




void Reader::printInfo() {

	cout << "Nodes" << endl;

	int i = 1;
	for (hashNode::iterator it = nodes.begin(); it != nodes.end(); it++) {
		cout << i << ": "
				<< it->node_id << " "
				<< it->latitude_deg << " "
				<< it->longitude_deg << " "
				<< it->latitude_rad << " "
				<< it->longitude_rad << endl;
		i++;
	}

	cout << "***********************************************************\n";


	cout << "Roads" << endl;

	i = 1;
	for (hashRoad::iterator it = roads.begin(); it != roads.end(); it++) {
		cout << i << ": "
				<< it->road_id << " "
				<< it->road_name << " ";

		if (it->two_way) cout << "True\n";
		else cout << "False\n";
		i++;
	}

	cout << "***********************************************************\n";

	cout << "Relations" << endl;

	i = 1;
	for (hashRelationship::iterator it = relations.begin(); it != relations.end(); it++) {
		cout << i << ": "
				<< it->road_id << " "
				<< it->node1_id << " "
				<< it->node2_id << endl;
		i++;
	}
}
