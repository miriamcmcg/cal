#include "Reader.h"

using namespace std;


void Reader::readFiles() {

	loadNodes();
	loadLinks();
	loadRelations();
}




void Reader::loadNodes() {

	ifstream in;
	in.open("a.txt", ios::in);


	if (in.good() && in.peek() != ifstream::traits_type::eof()) {
		while (in.good()) {
			unsigned long node_id;
			double latitude_deg, longitude_deg, latitude_rad, longitude_rad;

			string content;
			char dummy;
			stringstream ss;

			getline(in, content);

			if (in.eof())
				break;

			if (in.fail()) {
				cerr << "Error reading nodes.\n" << endl;
				exit(1);
			}

			ss.str(content);
			ss >> node_id >> dummy;
			ss >> latitude_deg >> dummy;
			ss >> longitude_deg >> dummy;
			ss >> latitude_rad >> dummy;
			ss >> longitude_rad;


			double x = EARTH_RADIUS_KM * cos(latitude_rad) * cos(longitude_rad);
			double y = EARTH_RADIUS_KM * cos(latitude_rad) * sin(longitude_rad);
			double z = EARTH_RADIUS_KM * cos(latitude_rad);


			nodes.insert(Node(node_id, x, y, z));
		}
	}

	in.close();
}




void Reader::loadLinks() {

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


			links.insert(Link(road_id, road_name, two_way));


			if (in.fail()) {
				cerr << "Error reading roads.\n" << endl;
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
				cerr << "Error reading relations.\n" << endl;
				exit(3);
			}


			ss.str(content);
			ss >> road_id >> dummy;
			ss >> node1_id >> dummy;
			ss >> node2_id;

			relations.insert(Relationship(road_id, node1_id, node2_id));
		}
	}

	in.close();
}
