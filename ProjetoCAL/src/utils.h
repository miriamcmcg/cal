/*
 * utils.h
 *
 *  Created on: 21/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
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
typedef pair<vector<GarbageDeposit*>, vector<Road*>> Section;
typedef vector<Section> Route;
typedef pair<Route, vector<GarbageDeposit*>> Data;


#endif /* SRC_UTILS_H_ */
