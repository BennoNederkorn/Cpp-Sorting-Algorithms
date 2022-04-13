#include "main.hpp"

// delete all chars of the string that are not between 0 and 5
string transformString(string str) {
    string res = "";
    int l = sizeof(ALGORITHMS)/sizeof(*ALGORITHMS);
    char c = '0' + ALGORITHMS[l-1].first;
    while(str.length() > 0) {
        if('1' <= str[0] && str[0] <= c) {
            res.push_back(str[0]);
        }
        str.erase(0,1);
    }
    return res;
}

// delete all chars of the string which are duplicated
string deleteDoubleLetters(string str) {
    string res = "";
    for(string::size_type s = 0; s < str.length(); s++) {
        bool exist = false;
        for(string::size_type r = 0; r < res.length(); r++) {
            if(res[r] == str[s]) {
                exist = true;
                break;
            }
        }
        if(!exist) {
            res.push_back(str[s]);
        }
    }
    return res;
}

// cast a string array into a int array
int getAlgoArr(string algoStr, int *algoArr) {
    for(string::size_type i = 0; i < algoStr.length(); i++) {
        algoArr[i] = algoStr[i] - '0' - 1;
    }
    return 0; 
}

// prints all elements of an array
int printArr(int *arr, int length) {
    for(int i = 0; i < length; i++) {
        cout << arr[i];
    }
    cout << "\n";
    return 0;
}

// tests the sorting algorithm
int test(int algNr) {
    bool res = testAlg(algNr);
    if(res) {
        cout << ALGORITHMS[algNr].second << " is correct.\n";
    } else {
        cout << ALGORITHMS[algNr].second << " does not yet work correctly.\n";
    }
    return 0;
}

int main() {
    cout << "This program compares the efficency of sortingalgorithms.\n";

    // get the length of the array
    int len = 0;  
    cout << "Choose the length of the array, which shoud be sorted and compared:\n";
    cin >> len;
    if(cin.fail()) {
        cout << "Please enter only numbers.\n";
        return 0;
    }
    if(len <= 0) {
        cout << "Please enter only positive numbers.\n";
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // discards everything in the input stream

    // get the string with all the possible algorithms
    cout << "Which algorithms do you want to compare?\n";
    for(long unsigned int i = 0; i < sizeof(ALGORITHMS)/sizeof(*ALGORITHMS); i++) {
        cout << "[" << ALGORITHMS[i].first << "] " << ALGORITHMS[i].second << "\n";
    }
    string algoStr = "";
    getline(cin, algoStr);

    // transform string to int* 
    algoStr = transformString(algoStr);
    algoStr = deleteDoubleLetters(algoStr);
    int lenAlgoArr = algoStr.length();
    int *algoArr = new int[lenAlgoArr];
    getAlgoArr(algoStr, algoArr);

    // test and measure the execution time of the algorithm
    for(int i = 0; i < lenAlgoArr; i++) {
        test(algoArr[i]);
        double time = benchmark(algoArr[i], len);
        cout << ALGORITHMS[algoArr[i]].second << " took " << time << " seconds.\n";
    }
    return 0;
}