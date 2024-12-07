#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "HeaderAll.h" 

using namespace std;

bool recurseAscend(vector<int> list, int currentInt) {
    if (currentInt == list.size() - 1) {
        return true;
    }

    if ((list[currentInt] < list[currentInt + 1]) && ((list[currentInt + 1] - list[currentInt]) < 4)) {
        return recurseAscend(list, currentInt + 1);
    }
    else {
        return false;
    }
}

bool recurseDescend(vector<int> list, int currentInt) {
    if (currentInt == list.size() - 1) {
        return true;
    }

    if ((list[currentInt] > list[currentInt + 1]) && ((list[currentInt] - list[currentInt + 1]) < 4)) {
        return recurseDescend(list, currentInt + 1);
    }
    else {
        return false;
    }
}

bool isSafe(vector<int> list) {
    return recurseAscend(list, 0) || recurseDescend(list, 0);
}

int validateOrder() {
    string line;
    ifstream file("Day2-input.txt");
    int numCorrect = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream is(line);
            int n;
            vector<int> numbers;
            while (is >> n) {
                numbers.push_back(n);
            }
            if (isSafe(numbers)) {
                numCorrect++;
            }
        }
        file.close();
    }
    return numCorrect;
}

int Day2Part1() {
    cout << validateOrder();
    return 0;
}

bool isSafeDampened(vector<int> list) {
    for (int i = 0; i < list.size(); ++i) {
        vector<int> cloneList = list;
        cloneList.erase(cloneList.begin() + i);

        if (isSafe(cloneList)) {
            return true;
        }
    }
    return false;
}

int validateDampenedOrder() {
    string line;
    ifstream file("Day2-input.txt");
    int numCorrect = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream is(line);
            int n;
            vector<int> numbers;
            while (is >> n) {
                numbers.push_back(n);
            }
            if (isSafe(numbers)||isSafeDampened(numbers)) {
                numCorrect++;
            }
        }
        file.close();
    }
    return numCorrect;
}

int Day2Part2() {
    cout << validateDampenedOrder();
    return 0;
}
