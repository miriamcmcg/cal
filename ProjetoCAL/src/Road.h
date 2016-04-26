/*
 * Road.h
 *
 *  Created on: 19/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
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
	Road();
	Road(unsigned long ID, string name, double distance, double speed);
	virtual ~Road() {};
	bool operator==(const Road &r) const;
	unsigned long getID() const;
	const string& getName() const;
	double getWeight();
	void setAvgSpeed(double speed);
	void setAvailable(bool av);
	virtual string print() const;
	double getDistance() const;
	double getAvgSpeed() const;
};


#endif /* ROAD_H_ */
