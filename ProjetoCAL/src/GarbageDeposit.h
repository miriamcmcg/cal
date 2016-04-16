/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_



class TrashDeposit {

	static unsigned int TrashCounter;

	unsigned int ID;
	unsigned int maxCapacity;
	unsigned int capacityOccupied;


	TrashDeposit(unsigned int ID, unsigned int maxCapacity, unsigned capacityOccupied);
};


#endif /* GARBAGEDEPOSIT_H_ */
