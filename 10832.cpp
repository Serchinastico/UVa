#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef pair<double, int> myPair;

struct myVector {
	int x;
	int y;
	int z;
};

bool startMission(unsigned int f, unsigned int b, unsigned int r, unsigned int n, myVector *buoys, 
		double &time, double &traveled, double &fuelLeft, double &fromHome) {
	int permutations[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	double minDistance = 999999999;
	do {
		double distance = 0;
		for (int i = 1; i <= n; i++) {
			double dx = buoys[permutations[i]].x - buoys[permutations[i - 1]].x;
			double dy = buoys[permutations[i]].y - buoys[permutations[i - 1]].y;
			double dz = buoys[permutations[i]].z - buoys[permutations[i - 1]].z;
			distance += sqrt(abs(dx * dx + dy * dy + dz * dz));
		}

		if (distance < minDistance) {
			minDistance = distance;
		}
	} while (next_permutation(permutations + 1, permutations + n + 1));

	bool success = minDistance < (f * r / b);

	if (success) {
		time = minDistance / r;
		fuelLeft = f - (time * b);
		traveled = minDistance;
	} else {
		traveled = (f * r / b);
		fromHome = minDistance - traveled;
	}

	return success;
}

int main() {
	unsigned int f, b, r, n, i = 1;
	myVector buoys[20 + 1]; // We add the starting point as a buoy for simplicity
	buoys[0].x = 0; buoys[0].y = 0; buoys[0].z = 1;
	double time, traveled, fuelLeft, fromHome;

	cout << setprecision(2) << fixed;
	while (cin >> f >> b >> r >> n && f != 0 && b != 0 && r != 0 && n != 0) {
		for (int i = 1; i <= n; i++) {
			cin >> buoys[i].x >> buoys[i].y >> buoys[i].z;
		}

		bool success = startMission(f, b, r, n, buoys, time, traveled, fuelLeft, fromHome);

		cout << "Mission " << i << ": ";
		if (success) {
			cout << "SUCCESS!! Time: " << time << "  Traveled: " << traveled << "  Fuel Left: " << fuelLeft << endl;
		} else {
			cout << "FAILURE!! Traveled: " << traveled << "  From Home: " << fromHome << endl;
		}

		i += 1;
	}
}