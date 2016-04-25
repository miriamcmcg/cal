/*
 * utils.h
 *
 *  Created on: 21/04/2016
 *      Author: User
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include "GDPointer.h"
#include "RoadPointer.h"
#include "GarbageDeposit.h"
#include "Road.h"

#define SOURCE			0
#define	DESTINATION		1


using namespace std;

typedef pair<vector<GDPointer>, vector<RoadPointer>> GraphInfo;
typedef pair<vector<GarbageDeposit*>, vector<Road*>> Path;
typedef vector<Path> Route;
typedef pair<Route, vector<GarbageDeposit*>> Data;


#endif /* SRC_UTILS_H_ */
