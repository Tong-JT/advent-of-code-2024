#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "HeaderAll.h" 

using namespace std;

int matchString() {
    string line;
    ifstream file("Day3-input.txt");
    regex mul("mul\\((\\d+),(\\d+)\\)");
    int addedUp = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            auto wordsBegin = sregex_iterator(line.begin(), line.end(), mul);
            auto wordsEnd = sregex_iterator();

            for (sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
                smatch match = *i;

                string num1 = match.str(1);
                string num2 = match.str(2);

                int n1 = stoi(num1);
                int n2 = stoi(num2);

                int multiplied = n1 * n2;
                addedUp += multiplied;
            }
        }
        file.close();
    }

    return addedUp;
}

int Day3Part1() {
    cout << matchString();
    return 0;
}

int matchSwitchString() {
    string line;
    ifstream file("Day3-input.txt");

    regex mulPlus("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");
    int addedUp = 0;
    bool mulEnabled = true;

    if (file.is_open()) {
        while (getline(file, line)) {

            auto wordsBegin = sregex_iterator(line.begin(), line.end(), mulPlus);
            auto wordsEnd = sregex_iterator();

            for (sregex_iterator i = wordsBegin; i != wordsEnd; i++) {
                smatch match = *i;

                string match_str = match.str();
                if (match_str == "do()") {
                    mulEnabled = true;
                    cout << "do" << endl;
                }
                else if (match_str == "don't()") {
                    mulEnabled = false;
                    cout << "don't" << endl;
                }
                else if (match_str.find("mul") != string::npos) {
                    string num1 = match.str(1);
                    string num2 = match.str(2);

                    int n1 = stoi(num1);
                    int n2 = stoi(num2);

                    int multiplied = n1 * n2;

                    if (mulEnabled) {
                        cout << n1 << " and " << n2 << endl;
                        addedUp += multiplied;
                    }
                }
            }
        }
        file.close();
    }

    return addedUp;
}





int Day3Part2() {
    cout << matchSwitchString();
    return 0;
}