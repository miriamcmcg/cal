/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_

#include <random>

class GarbageDeposit {
private:
	unsigned long ID;
	unsigned int maxCapacity;
	unsigned int capacityOccupied;

public:
	GarbageDeposit(unsigned long ID, unsigned int maxCapacity = 4500, unsigned capacityOccupied = 0) {
		this->ID = ID;
		this->maxCapacity = maxCapacity;

		if (capacityOccupied != 0)
			this->capacityOccupied = capacityOccupied;
		else
			this->capacityOccupied = (rand() % 3000) + 100;
	};

	bool operator==(const GarbageDeposit &gd) const {
		return ID == gd.ID;
	}

	bool operator!=(const GarbageDeposit &gd) const {
		return !(ID == gd.ID);
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


	void empty() {
		capacityOccupied = 0;
	}


	void addCapacityOccupied (unsigned int quantity) {
		// TODO THROW
		if (capacityOccupied + quantity > maxCapacity)
			;

		capacityOccupied += quantity;
	}
};


#endif /* GARBAGEDEPOSIT_H_ */
