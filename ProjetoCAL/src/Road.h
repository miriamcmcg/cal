/*
 * Road.h
 *
 *  Created on: 19/04/2016
 *      Author: User
 */

#ifndef ROAD_H_
#define ROAD_H_

#include <string>
#include <limits>

using namespace std;

const double DOUBLE_MAX = numeric_limits<double>::max();


class Road {
private:
	unsigned long ID;
	string name;
	double distance;
	double avg_speed;
	bool available;

public:
	Road() { ID = 0; name = ""; distance = 0; avg_speed = 0; available = true;};
	Road(unsigned long ID, string name, double distance, double speed)
	{ this->ID = ID; this->name = name; this->distance = distance; avg_speed = speed; available = true; };

	bool operator==(const Road &r) const {
		return ID == r.ID;
	}

	unsigned long getID() const {
		return ID;
	}

	const string& getName() const {
		return name;
	}

	double getWeight() {

		if (!available || avg_speed == 0)
			return DOUBLE_MAX;

		return distance / avg_speed;
	}

	void setAvgSpeed(double speed) {
		avg_speed = speed;
	}

	void setAvailable(bool av) {
		available = av;
	}
};


#endif /* ROAD_H_ */
