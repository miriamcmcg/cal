/*
 * matcher.h
 *
 *  Created on: 22/05/2016
 *      Author: User
 */

#ifndef SRC_MATCHER_H_
#define SRC_MATCHER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> PrefixFunction(const string& toSearch);
int KMP_MatcherCounter(const string& line, const string& toSearch);
int numStringMatching(string filename, string toSearch);
bool matches(const string& T, const string& P);

int EditDistance(const string& word, const string& toSearch);
float numApproximateStringMatching(string filename, string toSearch);


#endif /* SRC_MATCHER_H_ */
