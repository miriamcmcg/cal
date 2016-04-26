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

/**
 * Class Road
 */
class Road {
private:
	/** Identifier of the road */
	unsigned long ID;
	/** name of the road */
	string name;
	/** distance of the road */
	double distance;
	/** average speed of the road */
	double avg_speed;
	/**boolean to verify if the road is available*/
	bool available;

public:
	/**
	 * Road default constructor
	 */
	Road();
	/**
	 *Road constructor
	 *@param identifier of the road
	 *@param name of the road
	 *@param distance of the road
	 *@param speed of the road
	 */
	Road(unsigned long ID, string name, double distance, double speed);
	/**
	 * Road destructor
	 */
	virtual ~Road() {};
	/**
	 * equal operator
	 * @param r road
	 *
	 * verify if two roads are equal
	 */
	bool operator==(const Road &r) const;
	/**
	 * getID function
	 * @return identifier of the road
	 */
	unsigned long getID() const;
	/**
	 * getName function
	 * @return name of the road
	 */
	const string& getName() const;
	/**
	 * getWeight function
	 * @return weight of the road
	 */
	double getWeight();
	/**
	 * setAvgSpeed function
	 * @param new speed value of the road
	 */
	void setAvgSpeed(double speed);
	/**
	 * setAvailable function
	 * @param new av status of the road
	 */
	void setAvailable(bool av);
	/**
	 * print function
	 * @return the string of the name of the road to print
	 */
	virtual string print() const;
	/**
	 *getDistance function
	 *@return distance of the road
	 */
	double getDistance() const;
	/**
	 *getAvgSpeed function
	 *@return average speed of the road
	 */
	double getAvgSpeed() const;
};


#endif /* ROAD_H_ */
