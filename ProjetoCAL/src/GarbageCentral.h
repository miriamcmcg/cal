/*
 * GarbageCentral.h
 *
 *  Created on: 17/04/2016
 *      Author: User
 */

#ifndef GARBAGECENTRAL_H_
#define GARBAGECENTRAL_H_

#include "GarbageDeposit.h"
#include "GarbageTruck.h"
#include "Reader.h"
#include "Graph.h"
#include <vector>


using namespace std;

class GarbageDeposit;

class GarbageCentral {
private:
	Graph<GarbageDeposit> graph;
	vector<GarbageDeposit> deposits;
	vector<GarbageTruck> trucks;

public:
	GarbageCentral(const Reader& r);
	void print();
};


#endif /* GARBAGECENTRAL_H_ */
