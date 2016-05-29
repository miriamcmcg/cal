/*
 * GarbageDeposit.h
 *
 *  Created on: 16/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */


#ifndef GARBAGEDEPOSIT_H_
#define GARBAGEDEPOSIT_H_

#include <random>
#include <string>
#include <sstream>
#include "Exceptions.h"

using namespace std;
/**
 * Class GarbageDeposit
 */
class GarbageDeposit {
private:
	/**identifier of GarbageDeposit */
	unsigned long ID;
	/** maxCapacity of GarbageDeposit*/
	unsigned int maxCapacity;
	/** capacityOccupied of GarbageDeposit*/
	unsigned int capacityOccupied;
	/** coordinates of GarbageDeposit */
	double x, y, z;
public:
	/**
	 * GarbageDeposit default constructor
	 */
	GarbageDeposit() {};
	/**
	 * GarbageDeposit constructor
	 * @param identifier of GarbageDeposit
	 * @param x coordinate of GarbageDeposit
	 * @param y coordinate of GarbageDeposit
	 * @param z coordinate of GarbageDeposit
	 * @param maximum capacity of GarbageDeposit, 4500 default value
	 * @param capacity occupied of GarbageDeposit, 0 default value
	 */
	GarbageDeposit(unsigned long ID, double x, double y, double z,
			unsigned int maxCapacity, unsigned capacityOccupied = 0);
	/**
	 * GarbageDeposit  destructor
	 */
	virtual ~GarbageDeposit() {};
	/**
	 * equal operator
	 * @param gd garbage deposit
	 *
	 * verify if two garbage deposits are equal
	 */
	bool operator==(const GarbageDeposit &gd) const;
	/**
	 * not equal operator
	 * @param gd garbage deposit
	 *
	 * verify if two garbage deposits are not equal
	 */
	bool operator!=(const GarbageDeposit &gd) const;
	/**
	 * getCapacityOccupied function
	 * @return CapacityOccupied of GarbageDeposit
	 */
	unsigned int getCapacityOccupied() const;
	/**
	 * setCapacityOccupied function
	 * @param new value of CapacityOccupied of GarbageDeposit
	 *
	 * @return returns true if is a valid capacity
	 */
	bool setCapacityOccupied(unsigned int capacityOccupied);
	/**
	 * getX function
	 * @return x coordinate of GarbageDeposit
	 */
	double getX() const;
	/**
	 * getY function
	 * @return y coordinate of GarbageDeposit
	 */
	double getY() const;
	/**
	 * getZ function
	 * @return z coordinate of GarbageDeposit
	 */
	double getZ() const;
	/**
	 * getID function
	 * @return identifier of GarbageDeposit
	 */
	unsigned long getID() const;
	/**
	 * getMaxCapacity function
	 *@return maxCapacity of GarbageDeposit
	 */
	unsigned int getMaxCapacity() const;
	/**
	 * empty function
	 *
	 * empty GarbageDeposit by putting the capacityOccupied value to 0
	 */
	void empty();
	/**
	 * addCapacityOccupied function
	 * @param quantity to be added to capacityOccupied of GarbageDeposit
	 *
	 * add quantity value to capacityOccupied of GarbageDeposit
	 */
	void addCapacityOccupied (unsigned int quantity);
	/**
	 * setMaxCapacity function
	 *@param new maxCapacity value of GarbageCapacity
	 */
	void setMaxCapacity(unsigned int maxCapacity);
	/*
	 *coordsString function
	 *@return string of coordinates of GarbageDeposit
	 */
	string coordsString();

	/**
	 * print function
	 * @return the string of the identifier of the GarbageDeposit to print
	 */
	virtual string print() const;


	void setX(double X);
	void setY(double Y);
	void setZ(double Z);
};


#endif /* GARBAGEDEPOSIT_H_ */
