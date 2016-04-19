/*
 * Road.h
 *
 *  Created on: 19/04/2016
 *      Author: User
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <string>


class Road {
private:
	unsigned long ID;
	string name;

public:
	Road() { ID = 0; name = ""; };
	Road(unsigned long ID, string name) { this->ID = ID; this->name = name; };

	bool operator==(const Road &r) const {
		return ID == r.ID;
	}

	unsigned long getID() const {
		return ID;
	}

	const string& getName() const {
		return name;
	}
};


#endif /* ROAD_H_ */
