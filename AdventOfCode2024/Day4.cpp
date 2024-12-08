#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<char>> xmasArray;
vector<char> xmas = { 'X','M','A','S' };

vector<char> splitString(string string)
{
	vector<char> charVector;
    for (char i: string) {
        charVector.push_back(i);
    }
	return charVector;
}

int loadVectorArray() {
    string line;
    ifstream file("Day4-input.txt");
    vector<char> row;

    if (file.is_open()) {
        while (getline(file, line)) {
            row = splitString(line);
            xmasArray.push_back(row);
        }
        file.close();
    }
    return 0;
}

bool testSquare(int row, int col, int numParsed, string direction) {

	if (row >= 0 && row < xmasArray.size() && col >= 0 && col < xmasArray[0].size()) {

		if (numParsed > 3) {
			return false;
		}

		char letter = xmasArray[row][col];

        if (letter != xmas[numParsed]) {
            return false;
        }
        else if (numParsed == 3) {
            return true;
        }
        else {
            if (direction == "right") {
                return testSquare(row, col + 1, numParsed + 1, direction);
            }
            else if (direction == "down-right") {
                return testSquare(row + 1, col + 1, numParsed + 1, direction);
            }
            else if (direction == "left") {
                return testSquare(row, col - 1, numParsed + 1, direction);
            }
            else if (direction == "up-left") {
                return testSquare(row - 1, col - 1, numParsed + 1, direction);
            }
            else if (direction == "down") {
                return testSquare(row + 1, col, numParsed + 1, direction);
            }
            else if (direction == "down-left") {
                return testSquare(row + 1, col - 1, numParsed + 1, direction);
            }
            else if (direction == "up") {
                return testSquare(row - 1, col, numParsed + 1, direction);
            }
            else if (direction == "up-right") {
                return testSquare(row - 1, col + 1, numParsed + 1, direction);
            }
        }
	}

	return false;
}

int initialiseSearch() {
    int numCounted = 0;
    for (int i = 0; i < xmasArray.size(); i++) {
        for (int j = 0; j < xmasArray[i].size(); j++) {
            if (testSquare(i, j, 0, "right")) numCounted++;
            if (testSquare(i, j, 0, "down-right")) numCounted++;
            if (testSquare(i, j, 0, "left")) numCounted++;
            if (testSquare(i, j, 0, "up-left")) numCounted++;
            if (testSquare(i, j, 0, "down")) numCounted++;
            if (testSquare(i, j, 0, "down-left")) numCounted++;
            if (testSquare(i, j, 0, "up")) numCounted++;
            if (testSquare(i, j, 0, "up-right")) numCounted++;
        }
    }
    return numCounted;
}

int Day4Part1() {
    loadVectorArray();
    int numXmas = initialiseSearch();
    cout << numXmas;
    return 0;
}

char returnSquare(int row, int col) {
    if (row >= 0 && row < xmasArray.size() && col >= 0 && col < xmasArray[0].size()) {
        return xmasArray[row][col];
    }
}

bool checkMas(char a, char b) {
    return ((a == 'M') && (b == 'S') || (b == 'M') && (a == 'S'));
}

int initialiseSearchX() {
    int numCounted = 0;
    for (int i = 0; i < xmasArray.size(); i++) {
        for (int j = 0; j < xmasArray[i].size(); j++) {

            if (xmasArray[i][j] == 'A') {
                char downRight = returnSquare(i + 1, j + 1);
                char downLeft = returnSquare(i + 1, j - 1);
                char upRight = returnSquare(i - 1, j + 1);
                char upLeft = returnSquare(i - 1, j - 1);

                if (checkMas(downRight, upLeft) && checkMas(downLeft, upRight)) {
                    numCounted++;
                }

            }
        }
    }
    return numCounted;
}

int Day4Part2() {
    loadVectorArray();
    int numXmas = initialiseSearchX();
    cout << numXmas;
    return 0;
}