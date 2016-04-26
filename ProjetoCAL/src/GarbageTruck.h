/*
 * GarbageTruck.h
 *
 *  Created on: 16/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef GARBAGETRUCK_H_
#define GARBAGETRUCK_H_

#include "utils.h"
#include "Exceptions.h"
#include <deque>


class GarbageTruck {
private:
	unsigned static int TruckCounter;
	unsigned int ID;
	unsigned int capacity;
	unsigned int carrying;
public:
	GarbageTruck(unsigned int capacity);
	unsigned int getCapacity() const;
	unsigned int getCarrying() const;
	unsigned int getID() const;
	bool addCarrying(unsigned int quantity);
	void empty();
};



#endif /* GARBAGETRUCK_H_ */
