/*
 * GarbageCentral.h
 *
 *  Created on: 17/04/2016
 *      Author: User
 */

#ifndef GARBAGECENTRAL_H_
#define GARBAGECENTRAL_H_

#include "GarbageDeposit.h"
#include "TreatmentPlant.h"
#include "GarbageTruck.h"
#include "Reader.h"
#include "Graph.h"
#include "Road.h"
#include "Exceptions.h"
#include "GDPointer.h"
#include "RoadPointer.h"
#include "utils.h"
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

class GarbageDeposit;
class GarbageTruck;

class GarbageCentral {
private:
	Graph<GDPointer, RoadPointer> graph;
	vector<GarbageTruck> trucks;
	vector<GarbageDeposit*> deposits;
	vector<Road*> roads;
	TreatmentPlant* treat_plant;

	Data getRoute(vector<GarbageDeposit*> to_pick);
	FilteredPath filter(const GraphInfo &p);
	int depositPosition(unsigned int id);
	int roadPosition(unsigned int id);
	int truckPosition(unsigned int id);
	void sortDeposits();
public:
	GarbageCentral();
	GarbageCentral(const Reader& r);
	~GarbageCentral();
	FilteredPath getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2);
	void updateRoadAvgSpeed(unsigned int roadID, double newSpeed);
	void updateRoadAvailable(unsigned int roadID, bool available);
	Data createPickingRoute(unsigned int truckID);
	Data createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id);
	void pickGarbage(unsigned int truckID);
	void listTrucks();
	bool hasTruck(unsigned int id);
	void listDeposits();
	bool hasDeposit(unsigned int id);
	void listRoads();

	void aux();
	void print();
};


#endif /* GARBAGECENTRAL_H_ */
