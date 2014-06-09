#include <cstdio>
#include <cassert>
#include <map>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <utility>

using namespace std;

typedef map<unsigned int, unsigned int> IntMap;
typedef pair<unsigned int, unsigned int> IntPair;

unsigned int fib(unsigned int n, IntMap &fibMap) {
	if (fibMap.find(n) != fibMap.end()) {
		return fibMap[n];
	}

	int k = n / 2;
	int a = fib(k + 1, fibMap);
	int b = fib(k, fibMap);

	int fib;
	if (n % 2 == 1) {
		fib = a * a + b * b;
	} else {
		fib = b * (2 * a - b);
	}
	fibMap[n] = fib;

	return fib;
}

IntPair solveTestCase(unsigned int years, IntMap &fibMap) {
	IntPair solution;
	solution.first = fib(years + 2, fibMap) - 1;
	solution.second = solution.first + fib(years + 1, fibMap);
	return solution;
}

int main() {
	int years;
	IntMap fibMap;

	fibMap[0] = 0;
	fibMap[1] = 1;
	fibMap[2] = 1;
	fibMap[3] = 2;
	fibMap[4] = 3;
	fibMap[5] = 5;
	fibMap[6] = 8;
	fibMap[7] = 13;
	fibMap[8] = 21;
	fibMap[9] = 34;

	while (cin >> years && years != -1) {
		IntPair solution = solveTestCase(years, fibMap);
		cout << solution.first << ' ' << solution.second << endl;
	}
}