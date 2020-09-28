#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
#include <cmath>

using namespace std;

double calculate(vector<string> a);

string charToString(char c);

int findStringIndexInVector(string s, vector<string> v);

vector<string> oneCal(vector<string> v, int index);

vector<string> varNames;
vector<string> varValues;
vector<string> stdFormula;


int main() {
    cout << "Define vars \n" << "Calculate\n" << "Support ^\n" << "Input \'exit\' to exit\n";
    start:
    string wholeLine = "";
    stdFormula.clear();
    getline(cin, wholeLine);
    wholeLine.erase(remove(wholeLine.begin(), wholeLine.end(), ' '), wholeLine.end());// remove all space in the line
    if (wholeLine == "exit") {
        return 0;
    }
    int placeOfEqual = wholeLine.find('='); // check equal sign for var define
    if (isalpha(wholeLine.at(0)) && placeOfEqual != -1) {//check if alphabet already exists


        string name = wholeLine.substr(0, placeOfEqual);
        string value = wholeLine.substr(placeOfEqual + 1,
                                        wholeLine.size() - placeOfEqual - 1);
        //get value and name for next step

        if (count(varNames.begin(), varNames.end(), name)) {
            varValues[findStringIndexInVector(name, varNames)] = value;//change value


        } else {
            varNames.push_back(name);//add new entry
            varValues.push_back(value);
        }
        cout << "\ndefined variable list\n";
        for (int i = 0; i < varValues.size(); i++) {
            cout << varNames[i] << " = " << varValues[i] << endl;
        }//shown vars defined

        goto start;//finished for further command
    } else {
        bool lastIsDigit = false;
        int i = 0;
        while (i < wholeLine.length()) {
            if (isalpha(wholeLine.at(i))) {
                string value = varValues[findStringIndexInVector(charToString(wholeLine.at(i)),
                                                                 varNames)];//get value from the global list
                wholeLine.replace(i, 1, value);
            }
            i++;//the whole line length changes so not for loop
        }
        for (int i = 0; i < wholeLine.length(); i++) { //merge information from string to vector< string>
            if (isdigit(wholeLine.at(i)) || wholeLine.at(i) == '.') {
                if (!lastIsDigit) { //+----1
                    stdFormula.push_back(charToString(wholeLine.at(i)));
                    lastIsDigit = true;
                } else {//2---3
                    stdFormula[stdFormula.size() - 1].append(charToString(wholeLine.at(i)));

                }
            } else if (!lastIsDigit) {//)---+
                stdFormula.push_back(charToString(wholeLine.at(i)));

            } else {//2---+
                stdFormula.push_back(charToString(wholeLine.at(i)));
                lastIsDigit = false;

            }
        }//the wholeLine should be neatly defined in stdFormula now
        //each number and each par, each operator occupies one space

        cout << calculate(stdFormula) << endl;//put calculation in functions for easy recursion


    }
    goto start;//finished for further command
}


double calculate(vector<string> a) {

    while (findStringIndexInVector("(", a) != -1) {
        int start = findStringIndexInVector("(", a);
        int end = start + 1;
        int multiParCheck = 0;
        next:
        if (a[end] == "(") {
            multiParCheck++;

        } else if (a[end] == ")") {
            if (multiParCheck == 0) {
                goto finish;
            } else {
                multiParCheck--;
            }
        }
        end++;
        goto next;
        finish:
        vector<string> subV;//construction of simpler line to be calculated
        for (int i = (start + 1); i <= (end - 1); i++) {
            subV.push_back(a[i]);
        }
        a.erase(a.begin() + start, a.begin() + end);
        a[start] = to_string(calculate(subV));//the recursion for multiple pars
    }

    while (findStringIndexInVector("^", a) != -1) {
        a = oneCal(a, findStringIndexInVector("^", a));
    }
    while (findStringIndexInVector("*", a) != -1) {
        a = oneCal(a, findStringIndexInVector("*", a));
    }
    while (findStringIndexInVector("/", a) != -1) {
        a = oneCal(a, findStringIndexInVector("/", a));
    }
    while (findStringIndexInVector("+", a) != -1) {
        a = oneCal(a, findStringIndexInVector("+", a));
    }
    while (findStringIndexInVector("-", a) != -1) {
        a = oneCal(a, findStringIndexInVector("-", a));
    }
    double ans = stod(a[0]);
    ans = ans / 1.0;
    return ans;
    cout << "???";
}


string charToString(char c) {
    string v;
    v.push_back(c);
    return v;
}

int findStringIndexInVector(string s, vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        if (s == v[i]) {
            return i;
        }
    }
    return -1;
}

vector<string> oneCal(vector<string> v, int index) {

    if (v[index] == "^") {
        double ans = pow(stod(v[index - 1]), stod(v[index + 1]));
        v.erase(v.begin() + index);
        v.erase(v.begin() + index);
        v[index - 1] = to_string(ans);
    } else if (v[index] == "/") {
        double ans = stod(v[index - 1]) / stod(v[index + 1]);
        v.erase(v.begin() + index);
        v.erase(v.begin() + index);
        v[index - 1] = to_string(ans);
    } else if (v[index] == "*") {
        double ans = stod(v[index - 1]) * stod(v[index + 1]);
        v.erase(v.begin() + index);
        v.erase(v.begin() + index);
        v[index - 1] = to_string(ans);
    } else if (v[index] == "+") {
        double ans = stod(v[index - 1]) + stod(v[index + 1]);
        v.erase(v.begin() + index);
        v.erase(v.begin() + index);
        v[index - 1] = to_string(ans);
    } else if (v[index] == "-") {
        double ans = stod(v[index - 1]) - stod(v[index + 1]);
        v.erase(v.begin() + index);
        v.erase(v.begin() + index);
        v[index - 1] = to_string(ans);
    }
    return v;
}