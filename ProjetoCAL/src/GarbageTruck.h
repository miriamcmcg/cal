/*
 * GarbageTruck.h
 *
 *  Created on: 16/04/2016
 *      Author: User
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
	deque<Route> routes;

public:
	GarbageTruck(unsigned int capacity);
	unsigned int getCapacity() const;
	unsigned int getCarrying() const;
	unsigned int getID() const;
	bool addCarrying(unsigned int quantity);
	Route unload();
	void addPickingRoute(Route route);
	void empty();


};



#endif /* GARBAGETRUCK_H_ */
