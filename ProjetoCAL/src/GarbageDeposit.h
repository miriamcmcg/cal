/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_

#include <random>

using namespace std;

class GarbageDeposit {
private:
	unsigned long ID;
	unsigned int maxCapacity;
	unsigned int capacityOccupied;
public:
	GarbageDeposit(unsigned long ID, unsigned int maxCapacity = 4500, unsigned capacityOccupied = 0);
	bool operator==(const GarbageDeposit &gd) const;
	bool operator!=(const GarbageDeposit &gd) const;
	unsigned int getCapacityOccupied() const;
	void setCapacityOccupied(unsigned int capacityOccupied);
	unsigned long getID() const;
	unsigned int getMaxCapacity() const;
	void empty();
	void addCapacityOccupied (unsigned int quantity);
	void setMaxCapacity(unsigned int maxCapacity);

};


#endif /* GARBAGEDEPOSIT_H_ */
