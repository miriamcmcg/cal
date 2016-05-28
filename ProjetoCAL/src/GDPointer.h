/*
 * GDPointer.h
 *
 *  Created on: 20/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef SRC_GDPOINTER_H_
#define SRC_GDPOINTER_H_

#include "GarbageDeposit.h"

/**
 * Class CDPointer
 */
class GDPointer{
private:
	/** pointer to the garbage deposit*/
	GarbageDeposit *gd_ptr;

public:
	/**
	 * GDPointer constructor
	 * @param gd pointer to garbage deposit
	 */
	GDPointer(GarbageDeposit *gd);
	/**
	 * getPointer function
	 * @return pointer to garbage deposit
	 */
	GarbageDeposit *getPointer() const;
	/**
	 * operator equal
	 * @param gd garbage deposit pointer
	 *
	 * verify is two garbage deposits are equal
	 */
	bool operator==(const GDPointer &gd) const;
	/**
	 * operator not equal
	 * @param gd garbage deposit pointer
	 *
	 * verify is two garbage deposits are not equal
	 */
	bool operator!=(const GDPointer &gd) const;

	void setPosition(const GDPointer &gd1, const GDPointer &gd2);
};


#endif /* SRC_GDPOINTER_H_ */
