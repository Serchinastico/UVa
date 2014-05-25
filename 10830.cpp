#include <cstdio>
#include <cassert>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;

void addNewPrime(int *primes, int &lastPrimeIndex) {
	bool hasFoundNewPrime = false;
	int newPrimeCandidate = primes[lastPrimeIndex];
	while (!hasFoundNewPrime) {
		newPrimeCandidate += 1; // TODO Odd numbers...
		bool isPrime = true;
		for (int iPrime = 0; iPrime <= lastPrimeIndex; iPrime++) {
			int prime = primes[iPrime];
			if (prime * prime > newPrimeCandidate) {
				break;
			} else if (newPrimeCandidate % prime == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime) {
			primes[lastPrimeIndex + 1] = newPrimeCandidate;
			lastPrimeIndex += 1;
			hasFoundNewPrime = true;
		}
	}
}

unsigned long sumOfDivisors(unsigned long value, int *primes, int lastPrimeIndex) {
	unsigned long sumOfDivisors = 1;

	unsigned long remain = value;
	for (int iPrime = 0; iPrime < lastPrimeIndex; iPrime++) {
		int prime = primes[iPrime];
		if (prime * prime > value) {
			break;
		}

		int exponent = 0;
		while (remain % prime == 0) {
			remain /= prime;
			exponent += 1;
		}
		sumOfDivisors *= (pow(prime, exponent + 1) - 1) / (prime - 1);
	}

	if (remain > 1) {
		sumOfDivisors *= (remain * remain - 1) / (remain - 1);
	}
	
	return sumOfDivisors - (value + 1);
}

unsigned long cumulativeSumOfDivisors(unsigned long value, int *primes, int lastPrimeIndex) {
	unsigned long lastPrime = primes[lastPrimeIndex];
	while (lastPrime * lastPrime <= value) {
		addNewPrime(primes, lastPrimeIndex);
		lastPrime = primes[lastPrimeIndex];
	}

	unsigned long cumulativeSumOfDivisors = 0;
	for (unsigned long i = 2; i <= value; i++) {
		cumulativeSumOfDivisors += sumOfDivisors(i, primes, lastPrimeIndex);
	}

	return cumulativeSumOfDivisors;
}

int main() {
	int primes[5000];
	primes[0] = 2; primes[1] = 3;
	primes[2] = 5; primes[3] = 7;
	primes[4] = 11; primes[5] = 13;
	primes[6] = 17; primes[7] = 19;
	int lastPrimeIndex = 7;

	unsigned long value;
	int index = 1;
	while (cin >> value && value != 0) {
		cout << "Case " << index -1 << ": " << cumulativeSumOfDivisors(value, primes, lastPrimeIndex) << endl;
		index += 1;
	}
}