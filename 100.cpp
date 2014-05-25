#include <cstdlib>
#include <iostream>
#include <map>

#define ulong unsigned long
using namespace std;

int calculateCycleLength(long step, map<ulong, ulong> &storedValues) {
	if (storedValues.find(step) != storedValues.end()) {
		return storedValues[step];
	} else {
		ulong nextStep;
		if (step % 2 == 0) {
			nextStep = step / 2;
		} else {
			nextStep = 3 * step + 1;
		}
		int cycleLength = 1 + calculateCycleLength(nextStep, storedValues);
		storedValues[step] = cycleLength;
		return cycleLength;
	}
}

int main() {
	int minValue, maxValue, a, b;
	map<ulong, ulong> storedValues;
	storedValues[1] = 1;

	while (cin >> a >> b) {
		if (a < b) {
			minValue = a;
			maxValue = b;
		} else {
			minValue = b;
			maxValue = a;
		}

		int maxCycleLength = -1;
		for (int i = minValue; i <= maxValue; i++) {
			int cycleLength = calculateCycleLength(i, storedValues);
			if (cycleLength > maxCycleLength) {
				maxCycleLength = cycleLength;
			}
		}
		cout << a << " " << b << " " << maxCycleLength << endl;
	}
}