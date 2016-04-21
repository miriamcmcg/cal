/*
 * GarbageTruck.h
 *
 *  Created on: 16/04/2016
 *      Author: User
 */

#ifndef GARBAGETRUCK_H_
#define GARBAGETRUCK_H_

#include "utils.h"
#include <queue>


class GarbageTruck {
private:
	unsigned static int TruckCounter;

	unsigned int ID;
	unsigned int capacity;
	unsigned int carrying;
	queue<Route> routes;

public:

	GarbageTruck(unsigned int capacity) {
		this->ID = ++TruckCounter;
		this->capacity = capacity;
		this->carrying = 0;
	}


	unsigned int getCapacity() const {
		return capacity;
	}

	unsigned int getCarrying() const {
		return carrying;
	}

	unsigned int getID() const {
		return ID;
	}


	bool addCarrying(unsigned int quantity) {

		if (carrying + quantity > capacity)
			return false;

		carrying += quantity;
		return true;
	}


	Route unload() {
		// TODO THROW
		if (routes.empty()) ;

		carrying = 0;
		Route r = routes.front();
		routes.pop();

		return r;
	}

	void addPickingRoute(Route route) {
		routes.push(route);
	}
};



#endif /* GARBAGETRUCK_H_ */
