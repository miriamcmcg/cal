/*
 * GDPointer.h
 *
 *  Created on: 20/04/2016
 *      Author: User
 */

#ifndef SRC_GDPOINTER_H_
#define SRC_GDPOINTER_H_

#include "GarbageDeposit.h"

class GDPointer{
private:
	GarbageDeposit *gd_ptr;

public:
	GDPointer(GarbageDeposit *gd){gd_ptr = gd;};
	GarbageDeposit *getPointer(){return gd_ptr;}

	bool operator==(const GDPointer &gd) const {
		return *gd_ptr == *gd.gd_ptr;
	}

	bool operator!=(const GDPointer &gd) const {
		return !(*gd_ptr == *gd.gd_ptr);
	}
};


#endif /* SRC_GDPOINTER_H_ */
