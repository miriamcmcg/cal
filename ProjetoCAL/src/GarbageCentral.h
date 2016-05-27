/*
 * GarbageCentral.h
 *
 *  Created on: 17/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
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
#include "Driver.h"
#include "matcher.h"
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

class GarbageDeposit;
class GarbageTruck;
/**
 * Class GarbageCentral
 */
class GarbageCentral {
private:
	/** Coordinates of the minimum */
	double minX, minY, minZ;
	/** Coordinates of the maximum */
	double maxX, maxY, maxZ;

	/** Graph that will be draw */
	Graph<GDPointer, RoadPointer> graph;
	/** Vector of trucks */
	vector<GarbageTruck> trucks;
	/** Vector of deposits */
	vector<GarbageDeposit*> deposits;
	/** Vector of roads */
	vector<Road*> roads;
	/** Vector of drivers */
	vector<Driver> drivers;
	/** Central identifier */
	TreatmentPlant* treat_plant;

	/**
	 * getRoute function
	 * @param to_pick vector of the Deposits that the truck is going to pick
	 * @return pair that contains a vector with the route and the deposits that was not possible to pick
	 */
	Data getRoute(vector<GarbageDeposit*> to_pick);
	/**
	 *  depositPosition function
	 * @param id of the container
	 * @return index of the position in the deposits vector
	 */
	int depositPosition(unsigned int id) const;
	/**
	 * roadPosition function
	 * @param id of the road
	 * @return index of the position in the roads vector
	 */
	int roadPosition(unsigned int id) const;
	/**
	 * truckPosition function
	 * @param id of the truck
	 * @return index of the position in the truck vector
	 */
	int truckPosition(unsigned int id) const;
	/**
	 * sortDeposits function
	 * sort the containers by the occupied capacity
	 */
	void sortDeposits();
	/**
	 * getShortestPath function
	 * @param gd1 initial point of the path
	 * @param gd2 ending point of the path
	 * @return the shortest path calculates of garbage deposits and roads
	 */
	Section getShortestPath(GarbageDeposit* gd1, GarbageDeposit* gd2);
	/**
	 * updatePicks function
	 * @param to_pick vector of the Deposits that the truck is going to pick
	 * @param section the path of garbage deposits and roads
	 *
	 * erases the nodes that were visited are removed from the section
	 * this way the nodes are not repeated
	 */
	void updatePicks(vector<GarbageDeposit*>& to_pick, Section section);
public:
	/**
	 * Default constructor of GarbageCentral
	 */
	GarbageCentral();
	/**
	 * Constructor of GarbageCentral
	 * @param r reador of the files containing information about trucks, roads and containers
	 */
	GarbageCentral(const Reader& r);
	/**
	 * Destructor of GarbageCentral
	 */
	~GarbageCentral();
	/**
	 * updateRoadAvgSpeed function
	 * @param roadID identifier of the road
	 * @param newSpeed of the road
	 *
	 * update the speed of the road into the newSpeed
	 * if the road does not exist throws a RoadNonExistent exception type
	 */
	void updateRoadAvgSpeed(unsigned int roadID, double newSpeed);
	/**
	 * updateRoadAvailable function
	 * @param roadID identifier of the road
	 * @param available checks if the road is available or not
	 *
	 * update the state of the road into the bool available
	 * if the road does not exist throws a RoadNonExistent exception type
	 */
	void updateRoadAvailable(unsigned int roadID, bool available);
	/**
	 * createPickingRoute function
	 * @param truckID identifier of the truck that will pick the containers of the route created
	 *
	 * create a route taking into consideration the capacity of the truck
	 * if the truck does not exist throws a TruckNonExistent exception type
	 */
	Data createPickingRoute(unsigned int truckID);
	/**
	 * createPickingRoute function
	 * @param truckID identifier of the truck that will pick the containers of the route created
	 * @param deposits_id vector containing the identifier of the containers of the route
	 *
	 * create a manual route that cover the containers of the vector
	 * if the truck does not exist throws a TruckNonExistent exception type
	 */
	Data createPickingRoute(unsigned int truckID, vector<unsigned int> deposits_id);
	/**
	 * updateDepositOccupied function
	 * @param depositID identifier of the container that will be updated
	 * @param capOcup new ocuppied capacity of the container
	 *
	 * update the deposit to capOcup
	 * if the deposit does not exist throws DepositNonExistent exception type
	 *
	 * @param returns true if is a valid capacity
	 */
	bool updateDepositOccupied(unsigned int depositID, unsigned int capOcup);
	/**
	 * listTrucks function
	 *
	 * print the ID of the trucks
	 */
	void listTrucks() const;
	/**
	 * hasTruck function
	 * @param id of the truck
	 *
	 * verify if the truck exist, if not return -1
	 */
	bool hasTruck(unsigned int id) const;
	/**
	 * listDeposits function
	 *
	 * print the ID of the deposits
	 */
	void listDeposits() const;
	/**
	 * hasDeposit function
	 * @param id of the deposit
	 *
	 * verify if the deposit exist, if not return -1
	 */
	bool hasDeposit(unsigned int id) const;
	/**
	 * listRoads function
	 *
	 * print the ID of the roads, the name, the distance and the AvgSpeed
	 */
	void listRoads() const;
	/**
	 * hasRoad function
	 * @param id of the road
	 *
	 * verify if the road exist, if not return -1
	 */
	bool hasRoad(unsigned int id) const;
	/**
	 * truckCanPick function
	 * @param id of the truck
	 * @param id of the container
	 *
	 * verify if the truck has capacity to pick the waste of the container
	 * return true if it has capacity and update the truck capacity
	 * return false if not and do not update the truck capacity
	 */
	bool truckCanPick(unsigned int truck_id, unsigned int container_id);
	/**
	 *filter function
	 *@param p section that will be filtered
	 *@return section of roads and containers not repeated
	 *
	 *filter the section to verify if there are not roads and containers repeated
	 */
	Section filter(const Section &p);
	/**
	 *convert function
	 *@param p section that will be converted
	 *@return section that contains the garbagedeposits and roads pointers
	 *
	 *convert garbagedeposits and roads into pointers
	 */
	Section convert(const GraphInfo &p);
	/**
	 * getMinX function
	 * @return the minimum x coordinate
	 */
	double getMinX() const;
	/**
	 * getMinY function
	 * @return the minimum y coordinate
	 */
	double getMinY() const;
	/**
	 * getMinZ function
	 * @return the minimum z coordinate
	 */
	double getMinZ() const;
	/**
	 * getMaxX function
	 * @return the maximum x coordinate
	 */
	double getMaxX() const;
	/**
	 * getMaxY function
	 * @return the maximum y coordinate
	 */
	double getMaxY() const;
	/**
	 * getMaxZ function
	 * @return the maximum z coordinate
	 */
	double getMaxZ() const;



	void listDrivers() const;
	vector<Driver> searchDriversExact(string name);
	Driver searchDriverApproximate(string name);


	/**
	 * test function
	 *
	 * test the code created
	 */
	void test();
};


#endif /* GARBAGECENTRAL_H_ */
