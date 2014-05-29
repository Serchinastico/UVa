#include <cstdio>
#include <iostream>
#include <climits>
#include <set>

using namespace std;

typedef set<int> heights;

int executeActionOnAfternoon(int hp1, int hp2, int m, int *treeHeights, int treesCount, int seedsCount, int treeWatered, int currentDay);

void printTreeHeights(int *treeHeights, int treesCount) {
	cout << "[";
	for (int iTree = 0; iTree < treesCount; iTree++) {
		cout << treeHeights[iTree];
		if (iTree != treesCount - 1) {
			cout << ", ";
		}
	}
	cout << "]";
}

void calculateNewTreeHeight(int hp1, int hp2, int *treeHeights, int &seedsCount, int treeIndex) {
	treeHeights[treeIndex] += 1;
	if (treeHeights[treeIndex] == hp1 || treeHeights[treeIndex] == hp2) {
		seedsCount += 1;
	} 
}

void passMorningAndNoon(int hp1, int hp2, int *treeHeights, int treesCount, int &seedsCount, int treeWatered) {
	for (int iTree = 0; iTree < treesCount; iTree++) {
		calculateNewTreeHeight(hp1, hp2, treeHeights, seedsCount, iTree);
	}

	if (treeWatered != -1) {
		calculateNewTreeHeight(hp1, hp2, treeHeights, seedsCount, treeWatered);
	}
}

int executeActionOnEvening(int hp1, int hp2, int m, int *treeHeights, int treesCount, int seedsCount, int currentDay) {
	if (currentDay > 10) {return 0;}
	cout << "executeActionOnEvening(hp1:" << hp1 << ", hp2:" << hp2 << ", m:" << m << ", treesCount:" << treesCount << ", seedsCount:" << seedsCount << ", currentDay:" << currentDay << ") : ";
	printTreeHeights(treeHeights, treesCount);
	cout << endl;

	int minNumberOfDaysRequired = INT_MAX;

	for (int iTree = 0; iTree < treesCount; iTree++) {
		if (treeHeights[iTree] < 3 * m) {
			int minNumberOfDaysRequiredWateringTree = executeActionOnAfternoon(hp1, hp2, m, treeHeights, treesCount, seedsCount, iTree, currentDay + 1);
			if (minNumberOfDaysRequiredWateringTree < minNumberOfDaysRequired) {
				minNumberOfDaysRequired = minNumberOfDaysRequiredWateringTree;
			}
		}
	}

	return minNumberOfDaysRequired;
}

int executeActionOnAfternoon(int hp1, int hp2, int m, int *treeHeights, int treesCount, int seedsCount, int treeWatered, int currentDay) {
	cout << "executeActionOnAfternoon(hp1:" << hp1 << ", hp2:" << hp2 << ", m:" << m << ", treesCount:" << treesCount << ", seedsCount:" << seedsCount << ", treeWatered:" << treeWatered << ", currentDay:" << currentDay << ") : ";
	printTreeHeights(treeHeights, treesCount);
	cout << " -> ";

	passMorningAndNoon(hp1, hp2, treeHeights, treesCount, seedsCount, treeWatered);

	printTreeHeights(treeHeights, treesCount);
	cout << seedsCount << endl;

	int firstTreeHeight = treeHeights[0];
	bool hasFinishedPlanting = treesCount == m;
	for (int iTree = 0; iTree < treesCount && hasFinishedPlanting; iTree++) {
		hasFinishedPlanting = treeHeights[iTree] == firstTreeHeight;
	}

	if (hasFinishedPlanting) {
		cout << "HAS FINISHED" << endl;
		return currentDay;
	}

	int minNumberOfDaysRequiredPlantingSeed = INT_MAX;
	if (treesCount < m && seedsCount > 0) {
		treeHeights[treesCount] = 0;
		minNumberOfDaysRequiredPlantingSeed = executeActionOnEvening(hp1, hp2, m, treeHeights, treesCount + 1, seedsCount - 1, currentDay);
	}
	int minNumberOfDaysRequiredNotPlantingSeed = executeActionOnEvening(hp1, hp2, m, treeHeights, treesCount, seedsCount, currentDay);
	return min(minNumberOfDaysRequiredPlantingSeed, minNumberOfDaysRequiredNotPlantingSeed);
}

int getMinNumberOfDaysRequired(int hp1, int hp2, int m) {
	int treeHeights[16];
	int treesCount = 0, seedsCount = 1, currentDay = 0;
	return executeActionOnAfternoon(hp1, hp2, m, treeHeights, treesCount, seedsCount, -1, currentDay);
}

int main() {
	int testCasesCount, hp1, hp2, m;

	cin >> testCasesCount;
	for (int iTestCase = 1; iTestCase <= testCasesCount; iTestCase++) {
		cin >> hp1 >> hp2 >> m;

		int minNumberOfDaysRequired = getMinNumberOfDaysRequired(hp1, hp2, m);
		cout << "Case " << iTestCase << ": " << minNumberOfDaysRequired << endl;
	}
}