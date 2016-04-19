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
#include "Road.h"
#include "Exceptions.h"
#include <vector>


using namespace std;

class GarbageDeposit;

class GarbageCentral {
private:
	Graph<GarbageDeposit, Road> graph;
	vector<GarbageDeposit> deposits;
	vector<Road> roads;
	vector<GarbageTruck> trucks;

	void getRoute(vector<GarbageDeposit> to_pick);
	pair<vector<GarbageDeposit>, vector<Road>> filter(pair<vector<GarbageDeposit>, vector<Road>> &p);
public:
	GarbageCentral(const Reader& r);
	pair<vector<GarbageDeposit>, vector<Road>> getShortestPath(const GarbageDeposit& gd1, const GarbageDeposit& gd2);

	void aux();
	void print();
};


#endif /* GARBAGECENTRAL_H_ */
