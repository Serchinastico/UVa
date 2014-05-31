#include <cstdio>
#include <cassert>
#include <map>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <utility>

using namespace std;

typedef unsigned long long ull;

ull solveTestCase(ull n, ull a, ull b) {
	map<ull, ull> visitedSoldiers;
	bool hasFoundCycle = false;
	ull nextSoldier = 0, prevSoldier = 0;
	ull index = 0;
	while (!hasFoundCycle) {
		prevSoldier = nextSoldier;

		nextSoldier = (nextSoldier * nextSoldier) % n;
		nextSoldier = (nextSoldier * a) % n;
		nextSoldier = (nextSoldier + b) % n;

		if (visitedSoldiers.find(nextSoldier) == visitedSoldiers.end()) {
			visitedSoldiers[nextSoldier] = index;
			index += 1;
		} else {
			hasFoundCycle = true;
		}
	}

	return n - (index - visitedSoldiers[nextSoldier]);
}

int main() {
	ull n, a, b;

	while (cin >> n && n != 0) {
		cin >> a >> b;
		a = a % n;
		b = b % n;
		cout << solveTestCase(n, a, b) << endl;
	}
}