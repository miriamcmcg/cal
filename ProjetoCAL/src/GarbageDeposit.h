/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_



class GarbageDeposit {
private:
	static unsigned int TrashCounter;

	unsigned long ID;
	unsigned int maxCapacity;
	unsigned int capacityOccupied;

public:
	GarbageDeposit(unsigned long ID, unsigned int maxCapacity = 4500, unsigned capacityOccupied = 0) { this->ID = ID; };
	bool operator==(const GarbageDeposit &gd) const {
		return ID == gd.ID;
	}


	unsigned int getCapacityOccupied() const {
		return capacityOccupied;
	}

	void setCapacityOccupied(unsigned int capacityOccupied) {
		this->capacityOccupied = capacityOccupied;
	}

	unsigned long getID() const {
		return ID;
	}

	unsigned int getMaxCapacity() const {
		return maxCapacity;
	}

	void setMaxCapacity(unsigned int maxCapacity) {
		this->maxCapacity = maxCapacity;
	}
};


#endif /* GARBAGEDEPOSIT_H_ */
