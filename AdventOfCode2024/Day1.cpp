#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

list<int> listA;
list<int> listB;


// Import file for both parts

void openFile() {
	fstream inFile;
	int a, b;

	inFile.open("Day1-input.txt");
	if (!inFile) {
		cerr << "Unable to open file.";
		exit(1);
	}

	while (inFile >> a >> b) {
		listA.push_back(a);
		listB.push_back(b);
	}
	
	inFile.close();
}


// Part One

int totalListDifferences() {
	int totalCount = 0;
	listA.sort();
	listB.sort();

	while (listA.size() > 0) {
		int difference = abs(listA.front() - listB.front());
		cout << difference << endl;
		totalCount += difference;
		listA.pop_front();
		listB.pop_front();
	}

	return totalCount;
}

int Day1Part1() {
	openFile();
	cout << totalListDifferences();
	return 0;
}


// Part Two

int similarityScores() {
	int similarityScore = 0;

	for (int i : listA) {
		if (find(listB.begin(), listB.end(), i) != listB.end()) {
			similarityScore += ((count(listB.begin(), listB.end(), i) * i));
		}
	}
	return similarityScore;

}

int Day1Part2() {
	openFile();
	cout << similarityScores();
	return 0;
}
