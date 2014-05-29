#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>

using namespace std;

struct vector2d {
	double x;
	double y;
};

const double PI = 2 * acos(0);

typedef pair<vector2d, vector2d> vectorPair;

vectorPair solveTestCase(double R, double r, double x, double y) {
	vectorPair solution;
	solution.first.x = 0; solution.first.y = 0;
	solution.second.x = 0; solution.second.y = 0;

	// Intersection between {c=(0, 0), r=|r + R|} and {c=(t.x, t.y), r=r}
	double D = sqrt(x * x + y * y);
	double r0 = r + R;
	double r1 = r;
	if (r0 + r1 > D && D > abs(r0 - r1)) {
		double delta = 0.25 * sqrt((D + r0 + r1) * (D + r0 - r1) * (D - r0 + r1) * (-D + r0 + r1));
		double pxa = (x / 2) + (x * (r0 * r0 - r1 * r1)) / (2 * D * D);
		double pxb = (-2 * y * delta) / (D * D);
		double cx1 = pxa + pxb;
		double cx2 = pxa - pxb;

		double pya = (y / 2) + (y * (r0 * r0 - r1 * r1)) / (2 * D * D);
		double pyb = (-2 * x * delta) / (D * D);
		double cy1 = pya - pyb;
		double cy2 = pya + pyb;

		// Angle between (cx, cy) and (R + r, 0)
		double alpha1 = atan2(cy1, cx1);
		double alpha2 = atan2(cy2, cx2);

		if (alpha1 < 0) {alpha1 += 2 * PI;}
		if (alpha2 < 0) {alpha2 += 2 * PI;}

		// Calculate the angles that the small circle has rotated
		double beta1 = (alpha1 * R) / r;
		double beta2 = (alpha2 * R) / r;
		// Calculate position of p1 and p2 (finally!) from (cx, cy) with beta angle.
		if (alpha1 < alpha2) {
			solution.first.x = cx1 - sin(alpha1 + beta1) * r;
			solution.first.y = cy1 + cos(alpha1 + beta1) * r;
			solution.second.x = cx2 - sin(alpha2 + beta2) * r;
			solution.second.y = cy2 + cos(alpha2 + beta2) * r;
		} else {
			solution.second.x = cx1 - sin(alpha1 + beta1) * r;
			solution.second.y = cy1 + cos(alpha1 + beta1) * r;
			solution.first.x = cx2 - sin(alpha2 + beta2) * r;
			solution.first.y = cy2 + cos(alpha2 + beta2) * r;
		}
	}

	return solution;
}

int main() {
	double R, r, x, y;
	int index = 1;
	cout << setprecision(3) << fixed;
	while (cin >> R >> r >> x >> y && R != 0 && r != 0) {
		vectorPair solution = solveTestCase(R, r, x, y);
		cout << "Case " << index << ":";
		if (solution.first.x == 0 && solution.first.y == 0 && solution.second.x == 0 && solution.second.y == 0) {
			cout << endl << "IMPOSSIBLE" << endl;
		} else {
			cout << endl << solution.first.x << " " << solution.first.y << endl << solution.second.x << " " << solution.second.y << endl;
		}
		index += 1;
	}
}