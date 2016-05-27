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
#include "Driver.h"
#include <deque>

/**
 * Class GarbageTruck
 */
class GarbageTruck {
private:
	/**Truck counter */
	unsigned static int TruckCounter;
	/**Identifier of the truck */
	unsigned int ID;
	/**Capacity of the truck */
	unsigned int capacity;
	/**The capacity that the truck is carrying */
	unsigned int carrying;

	Driver* driver;

public:
	/*
	 * GarbageTruck constructor
	 * @param capacity of the truck
	 */
	GarbageTruck(unsigned int capacity);

	/*
	 * getCapacity function
	 * @return the capacity of the truck
	 */
	unsigned int getCapacity() const;

	/*
	 * getCarrying function
	 * @return the capacity that the truck is carrying
	 */
	unsigned int getCarrying() const;
	/*
	 * getID function
	 * @return ID of the truck
	 */
	unsigned int getID() const;
	/*
	 * addCarrying function
	 * @param quantity of garbage that will be added to the truck if possible
	 *
	 * verify if the truck can add the quantity of garbage and update the carrying value
	 * if it is possible to add return true else return false
	 */
	bool addCarrying(unsigned int quantity);
	/*
	 * empty function
	 *
	 * empty truck by putting the carrying value to 0
	 */
	void empty();

	void updateDriver(Driver* driver);

	Driver* getDriver() const;
};



#endif /* GARBAGETRUCK_H_ */
