/*
 * matcher.cpp
 *
 *  Created on: 22/05/2016
 *      Author: User
 */

#include "matcher.h"


vector<int> PrefixFunction(const string& P) {
	unsigned m = P.length();
	vector<int> v(m + 1);
	int k = -1;
	unsigned q = 0;

	v[0] = -1;

	while (q < P.length()) {
		while (k >= 0 && P[k] != P[q])
			k = v[k];

		k++;
		q++;
		v[q] = k;
	}

	return v;
}


int KMP_MatcherCounter(const string& T, const string& P) {
	unsigned count = 0;
	vector<int> PI = PrefixFunction(P);
	int i = 0, m = 0;

	while (m + i < (int) T.length()) {

		if (P[i] == T[m + i]) {
			if (i == (int) P.length() - 1)
				count++;
			i++;
		}
		else if (PI[i] > -1) {
			m = m + i - PI[i];
			i = PI[i];
		}
		else {
			m = m + i + 1;
			i = 0;
		}
	}

	return count;
}


int numStringMatching(string filename, string toSearch) {
	ifstream in;
	int total = 0;

	in.open(filename.c_str());
	if (in.good()) {
		string line;
		while (getline(in, line)) {
			total += KMP_MatcherCounter(line, toSearch);
		}
	}
	in.close();
	return total;
}



bool matches(const string& T, const string& P) {
	bool found = 0;
	vector<int> PI = PrefixFunction(P);
	int i = 0, m = 0;

	while (!found && m + i < (int) T.length()) {

		if (P[i] == T[m + i]) {
			if (i == (int) P.length() - 1)
				found = true;
			i++;
		}
		else if (PI[i] > -1) {
			m = m + i - PI[i];
			i = PI[i];
		}
		else {
			m = m + i + 1;
			i = 0;
		}
	}

	return found;
}


int EditDistance(const string& T, const string& P) {

	unsigned m = P.length();
	unsigned n = T.length();
	vector < vector<int> > D(m + 1, vector<int>(n + 1));	// m x n vector of ints

	for (unsigned i = 0; i <= m; i++) D[i][0] = i;
	for (unsigned j = 0; j <= n; j++) D[0][j] = j;

	for (unsigned i = 1; i <= m; i++) {
		for (unsigned j = 1; j <= n; j++) {
			if (P[i-1] == T[j-1])
				D[i][j] = D[i-1][j-1];
			else
				D[i][j] = 1 + min( min(D[i-1][j-1], D[i-1][j]), D[i][j-1] );
		}
	}

	return D[m][n];
}


float numApproximateStringMatching(string filename, string toSearch) {
	ifstream in;
	int total = 0, count = 0;

	in.open(filename.c_str());
	if (in.good()) {
		string word;

		while (in >> word) {
			total += EditDistance(word, toSearch);
			count++;
		}
	}

	return  (float) total / count;
}
