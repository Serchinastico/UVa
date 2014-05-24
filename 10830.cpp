#include <cstdio>
#include <cassert>
#include <map>
#include <iostream>

using namespace std;

unsigned long sumOfDivisors(unsigned long value) {
	unsigned long limit = value / 2;
	unsigned long sumOfDivisors = 0;
	for (unsigned long i = 2; i <= limit; i++) {
		if (value % i == 0) {
			sumOfDivisors += i;
		}
	}
	return sumOfDivisors;
}

unsigned long cumulativeSumOfDivisors(unsigned long value) {
	unsigned long cumulativeSumOfDivisors = 0;
	for (unsigned long i = 4; i <= value; i++) {
		cumulativeSumOfDivisors += sumOfDivisors(i);
	}
	return cumulativeSumOfDivisors;
}

void runTests() {
	assert(sumOfDivisors(0) == 0);
	assert(sumOfDivisors(1) == 0);
	assert(sumOfDivisors(2) == 0);
	assert(sumOfDivisors(3) == 0);
	assert(sumOfDivisors(4) == 2);
	assert(sumOfDivisors(24) == 35);
	assert(cumulativeSumOfDivisors(2) == 0);
	assert(cumulativeSumOfDivisors(100) == 3150);
}

void solveProblemBruteForce() {
	unsigned long value;
	int index = 1;
	while (cin >> value && value != 0) {
		cout << "Case " << index << ": " << cumulativeSumOfDivisors(value) << endl;
		index += 1;
	}
}

void solveProblemSieveOfEratosthenes() {
	unsigned long cumulativeSumOfDivisors[200000000];
	for (unsigned long i = 0; i <= 200000000; i++) {
		cumulativeSumOfDivisors[i] = i;
	}
	cout << cumulativeSumOfDivisors[192731];
}

int main() {
	#ifdef TEST
		runTests();
	#endif
	solveProblemSieveOfEratosthenes();
}