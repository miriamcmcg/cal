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
	double minX, minY, minZ;
	double maxX, maxY, maxZ;

	Graph<GDPointer, RoadPointer> graph;
	vector<GarbageTruck> trucks;
	vector<GarbageDeposit*> deposits;
	vector<Road*> roads;
	TreatmentPlant* treat_plant;

	Data getRoute(vector<GarbageDeposit*> to_pick);
	int depositPosition(unsigned int id) const;
	int roadPosition(unsigned int id) const;
	int truckPosition(unsigned int id) const;
	void sortDeposits();
	Section getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2);
	void updatePicks(vector<GarbageDeposit*>& to_pick, Section section);
public:
	GarbageCentral();
	GarbageCentral(const Reader& r);
	~GarbageCentral();
	void updateRoadAvgSpeed(unsigned int roadID, double newSpeed);
	void updateRoadAvailable(unsigned int roadID, bool available);
	Data createPickingRoute(unsigned int truckID);
	Data createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id);
	void updateDepositOccupied(unsigned int depositID, unsigned int capOcup);
	void listTrucks() const;
	bool hasTruck(unsigned int id) const;
	void listDeposits() const;
	bool hasDeposit(unsigned int id) const;
	void listRoads() const;
	bool hasRoad(unsigned int id) const;
	bool truckCanPick(unsigned int truck_id, unsigned int container_id);
	Section filter(const Section &p);
	Section convert(const GraphInfo &p);
	double getMinX() const;
	double getMinY() const;
	double getMinZ() const;
	double getMaxX() const;
	double getMaxY() const;
	double getMaxZ() const;

	/* PARA EFEITOS DE TESTE */
	void test();
};


#endif /* GARBAGECENTRAL_H_ */
