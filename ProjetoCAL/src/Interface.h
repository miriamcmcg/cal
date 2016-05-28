/*
 * Interface.h
 *
 *  Created on: 21/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <unistd.h>
#include "graphviewer.h"
#include "GarbageCentral.h"
#include "matcher.h"
#include <windows.h>

#define IMG_WIDTH	2713
#define	IMG_HEIGHT	1452

using namespace std;

void ClearScreen();
void getCursorXY(int &x, int&y);
void gotoXY(int x, int y);
void clearline();
void clearline(int x, int y);
void waitReturn();

vector<unsigned int> manualPicking(GarbageCentral& gc, unsigned int truck_id);
void getEntry(unsigned int &entrada);
void getEntry(int &entrada);
void getEntry(int &entrada, int start, int end);
void mainMenu(GarbageCentral& gc);
void createPickRoute(GarbageCentral& gc);
void updateCapacityOccupied(GarbageCentral& gc);
void updateAvgSpeedRoad(GarbageCentral& gc);
void updateAvailableRoad(GarbageCentral& gc);
void displayGraphViewer(vector<Section> route, const GarbageCentral& gc);
void addNewContainer(GarbageCentral& gc);

unsigned long askDriver(GarbageCentral& gc);
unsigned long askRoad(GarbageCentral& gc);
vector<Road*> groupRoadsByName(const vector<Road *>& roads);

#endif /* SRC_INTERFACE_H_ */
