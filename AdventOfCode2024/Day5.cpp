#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


// Link: adventofcode.com/2024/day/1

map<int, vector<int>> rules;

bool checkKeyNew(int key) {
    if (rules.find(key) == rules.end())
        return true;
    return false;
}

void parseFirstHalf(ifstream& file) {
    string line;
    while (getline(file, line)) {
        if (line.find("|") != string::npos) {
            size_t delimiter = line.find("|");
            int prevNum = stoi(line.substr(0, delimiter));
            int keyNum = stoi(line.substr(delimiter + 1));

            if (checkKeyNew(keyNum)) {
                vector<int> newVector = { prevNum };
                rules[keyNum] = newVector;
            }
            else {
                rules[keyNum].push_back(prevNum);
            }
        }
        else {
            break;
        }
    }
}

bool checkRules(vector<int> currentLine) {
    for (int i = 0; i < currentLine.size(); i++) {
        for (int j = i + 1; j < currentLine.size(); j++) {
            int currentKey = currentLine[i];
            int nextKey = currentLine[j];

            if (find(rules[currentKey].begin(), rules[currentKey].end(), nextKey) != rules[currentKey].end()) {
                return false;
            }
        }
    }
    return true;
}

int findMiddleNum(vector<int> line) {
    return line[(line.size()/2)];
}


// Part One

int parseSecondHalf(ifstream& file) {
    string line;
    int middleNumsAdded = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream is(line);
            string token;
            vector<int> numbers;
            bool isRight = true;

            while (getline(is, token, ',')) {
                stringstream ss(token);
                int n;
                while (ss >> n) {
                    numbers.push_back(n);

                    if (numbers.size() > 1) {
                        if (!checkRules(numbers)) {
                            isRight = false;
                        }
                    }
                }
            }
            if (isRight) {
                middleNumsAdded += findMiddleNum(numbers);
            }
            isRight = true;
        }
        file.close();
    }
    return middleNumsAdded;
}

ifstream openRulesFile() {
    string line;
    ifstream file("Day5-input.txt");
    return file;
}

int Day5Part1() {
    ifstream file = openRulesFile();
    parseFirstHalf(file);
    cout << "Sum of middle numbers: " << parseSecondHalf(file) << endl;

    file.close();
    return 0;
}


// Part Two

vector<int> correctSequence(vector<int> line) {
    vector<int> clonedLine = line;
    sort(clonedLine.begin(), clonedLine.end(), [](int a, int b) {
        return find(rules[a].begin(), rules[a].end(), b) != rules[a].end();
        });
    return clonedLine;
}

int parseSecondHalfIncorrect(ifstream& file) {
    string line;
    int middleNumsAdded = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream is(line);
            string token;
            vector<int> numbers;
            bool isRight = true;

            while (getline(is, token, ',')) {
                stringstream ss(token);
                int n;
                while (ss >> n) {
                    numbers.push_back(n);

                    if (numbers.size() > 1) {
                        if (!checkRules(numbers)) {
                            isRight = false;
                        }
                    }
                }
            }
            if (!isRight) {
                numbers = correctSequence(numbers);
                middleNumsAdded += findMiddleNum(numbers);
            }
            isRight = true;
        }
        file.close();
    }
    return middleNumsAdded;
}

int Day5Part2() {
    ifstream file = openRulesFile();
    parseFirstHalf(file);
    cout << "Sum of middle numbers: " << parseSecondHalfIncorrect(file) << endl;

    file.close();
    return 0;
}
