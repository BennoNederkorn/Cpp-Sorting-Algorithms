#include <random>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::string;
using std::pair;
using std::min;
using std::vector;
using std::sort;
using std::floor;

const pair<int, string> ALGORITHMS[]  = {{1, "insertionsort"}, {2, "bubblesort"}, {3, "mergesort"}, {4, "quicksort"}, {5, "bucketsort"}, {6, "c++ standard sort"}};

bool testAlg(int algoNr);
int *bubblesort(int* arr);
double benchmark(int algoNr, int len);