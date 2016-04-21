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
#include <random>
#include <vector>



#define SOURCE			0
#define	DESTINATION		1


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

	Route getRoute(vector<GarbageDeposit*> to_pick);
	FilteredPath filter(const GraphInfo &p);
	int depositPosition(unsigned int id);
	int roadPosition(unsigned int id);
	int truckPosition(unsigned int id);
public:
	GarbageCentral();
	GarbageCentral(const Reader& r);
	~GarbageCentral();
	FilteredPath getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2);
	void updateRoadAvgSpeed(unsigned int roadID, double newSpeed);
	void updateRoadAvailable(unsigned int roadID, bool available);
	void createPickingRoute(unsigned int truckID);
	void pickGarbage(unsigned int truckID);

	void aux();
	void print();
};


#endif /* GARBAGECENTRAL_H_ */
