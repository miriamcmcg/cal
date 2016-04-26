/*
 * GDPointer.h
 *
 *  Created on: 20/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef SRC_GDPOINTER_H_
#define SRC_GDPOINTER_H_

#include "GarbageDeposit.h"

class GDPointer{
private:
	GarbageDeposit *gd_ptr;

public:
	GDPointer(GarbageDeposit *gd);
	GarbageDeposit *getPointer();
	bool operator==(const GDPointer &gd) const;
	bool operator!=(const GDPointer &gd) const;

};


#endif /* SRC_GDPOINTER_H_ */
