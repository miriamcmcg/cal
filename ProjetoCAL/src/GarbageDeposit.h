/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_

#include <random>
#include <string>
#include <sstream>
#include "Exceptions.h"

using namespace std;

class GarbageDeposit {
private:
	unsigned long ID;
	unsigned int maxCapacity;
	unsigned int capacityOccupied;
	double x, y, z;
public:
	GarbageDeposit(unsigned long ID, double x, double y, double z,
			unsigned int maxCapacity = 4500, unsigned capacityOccupied = 0);
	virtual ~GarbageDeposit() {};
	bool operator==(const GarbageDeposit &gd) const;
	bool operator!=(const GarbageDeposit &gd) const;
	unsigned int getCapacityOccupied() const;
	void setCapacityOccupied(unsigned int capacityOccupied);
	double getX() const;
	double getY() const;
	double getZ() const;
	unsigned long getID() const;
	unsigned int getMaxCapacity() const;
	void empty();
	void addCapacityOccupied (unsigned int quantity);
	void setMaxCapacity(unsigned int maxCapacity);
	string coordsString();

	virtual string print() const;
};


#endif /* GARBAGEDEPOSIT_H_ */
