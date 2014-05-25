#include <cstdio>
#include <cassert>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;

unsigned long long cumulativeSumOfDivisors(unsigned long value) {
	unsigned long long cumulativeSumOfDivisors = 0;
	unsigned long long limit = sqrt(value);

	for (unsigned long i = 2; i <= limit; i++) {
		unsigned long long a = ceil(value / (i + 1));
		unsigned long long b = floor(value / i);

		if (a == 0) break;

		unsigned long long sum = (i - 1) * (((b * (b + 1)) / 2) - ((a * (a + 1)) / 2));
		cumulativeSumOfDivisors += sum;
		if (b != i) {
			cumulativeSumOfDivisors += (b - 1) * i;
		}
	}

	return cumulativeSumOfDivisors;
}

int main() {
	unsigned long value;
	int index = 1;

	while (cin >> value && value != 0) {
		cout << "Case " << index  << ": " << cumulativeSumOfDivisors(value) << endl;
		index += 1;
	}
}