#include "algorithms.hpp"

// prints all elements of an array with a name
int printArr(int *arr, int length, string name) {
    cout << name << ": ";
    for(int i = 0; i < length; i++) {
        cout << arr[i] << ",";
    }
    cout << "\n";
    return 0;
}

// swaps two elements in the array
int *swap(int *arr, int indexA, int indexB) {
    int buf = arr[indexA];
    arr[indexA] = arr[indexB];
    arr[indexB] = buf;
    return 0;
}

// copies the whole array
int arrCopy(int *to, int *from, int len) {
    for(int i = 0; i < len; i++) {
        to[i] = from[i];    
    }
    return 0;
}

// finds the minimum of an array
int findMin(int *arr, int len) {
    int min = arr[0];
    for(int i = 0; i < len; i++) {
        if(min > arr[i]) {
            min = arr[i];
        }
    }
    return min;
}

// finds the maximum of an array
int findMax(int *arr, int len) {
    int max = arr[0];
    for(int i = 0; i < len; i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

// insertionsort:
int insertionsort(int *arr, int len) {
    for(int i = 1; i < len; i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j-1] > arr[j]) {
                swap(arr, j, j-1);
            } else {
                break;
            }
        }
    }
    return 0;
}

// bubblesort:
int bubblesort(int *arr, int len) {
    //int len = sizeof(arr)/sizeof(*arr);
    for(int j = len-1; j > 0; j--) {
        for(int i = 0; i < len-1; i++) {
            if(arr[i] > arr[i+1]) {
                swap(arr, i, i+1);
            }
        }
        len--;
    }
    return 0;
}

// mergesort:
// begin is inclusive, end is exclusive
int *merge(int *arr, int *res, int begin, int middle, int end) {
    int iB = begin;
    int iM = middle;
    for(int i = begin; i < end; i++) {
        if(iB < middle && (arr[iB] < arr[iM] || iM >= end)) {
            res[i] = arr[iB];
            iB++;
        } else {
            res[i] = arr[iM];
            iM++;
        }
    }
    return 0;
}

int mergesortLoop(int *arr, int *res, int arrLen, int bucketSize) {
    for(int i = 0; i <= arrLen; i += 2*bucketSize) {
        int m = min(i+bucketSize, arrLen);
        int e = min(i+2*bucketSize, arrLen);
        merge(arr, res, i, m, e);
    }
    if(bucketSize < arrLen) {
        mergesortLoop(res, arr, arrLen, bucketSize*2);
    }
    return 0;
}

int mergesort(int *arr, int len) {
    if(len <= 1) {
        return 0;
    }
    int *sol = new int[len];
    mergesortLoop(arr, sol, len, 1);
    arrCopy(arr, sol, len);
    return 0;
}

// quicksort:
// start and end are inclusive
int getPivot(int *arr, int start, int end) {
    int mid = start + (end-start)/2;
    if((arr[start] <= arr[mid] && arr[mid] <= arr[end]) || (arr[end] <= arr[mid] && arr[mid] <= arr[start])) {
        return mid;
    } else if((arr[mid] <= arr[start] && arr[start] <= arr[end]) || (arr[end] <= arr[start] && arr[start] <= arr[mid])) {
        return start;
    } else {
        return end;
    }
}

// l is inclusive, r is exclusive
int quickResort(int *arr, int l, int r) {
    int pivot = r-1; //getPivot(arr, l, r-1);
    swap(arr, pivot, r-1);
    int iL = l;
    int iR = r-2;
    while(iL<iR) {
        while(arr[iL] < arr[r-1] && iL<r-1) {
            iL++;
        }
        while(arr[iR] >= arr[r-1] && iR>l) {
            iR--;
        }
        if(iL < iR) swap(arr, iL, iR);
    }
    if(arr[iL] > arr[r-1]) swap(arr, iL, r-1);
    return iL;
}

// l is inclusive, r is exclusive
int quicksortLoop(int *arr, int l, int r) {
    if(r-l <= 1) return 0;
    int pivot = quickResort(arr, l, r);
    quicksortLoop(arr, l, pivot);
    quicksortLoop(arr, pivot+1, r);
    return 0;
}

// len is exclusive
int quicksort(int *arr, int len) {
    quicksortLoop(arr, 0, len);
    return 0;
}

// bucketsort:
// checks an overfolw of the calculation max-min+1
bool checkOverflow(int min, int max) {
    int result = max - min + 1;
    if(min <= 0 && max > 0 && result <= 0) {
        return true;
    }
    return false;
}

int bucketsort(int *arr, int len) {
    int min = findMin(arr, len);
    int max = findMax(arr, len);
    // this bucketsort works only for numbers that can all be represented with 31 bits.
    // So e.g. numbers which are in the range min=INT_MIN/2 and max=INT_MAX/2.  
    if(checkOverflow(min, max)) {
        return mergesort(arr, len);
    }
    int numberOfBuckets = 32;
    double bucketRange = ((max - min + 1) * 1.0) / ((numberOfBuckets) * 1.0);
    vector<int> *buckets = new vector<int>[numberOfBuckets];
    for(int i = 0; i < numberOfBuckets; i++) {
        buckets[i].reserve(len/(numberOfBuckets/2));
    }
    for(int i = 0; i < len; i++) {
        int index = (arr[i] - min) / bucketRange;
        buckets[index].push_back(arr[i]);
    }
    for(int i = 0; i < numberOfBuckets; i++) {
        mergesort(&(buckets[i][0]), buckets[i].size());
    }
    int i = 0;
    for(int iBucNumb = 0; iBucNumb < numberOfBuckets; iBucNumb++) {
        for(vector<int>::size_type ibuc = 0; ibuc < buckets[iBucNumb].size(); ibuc++) {
            arr[i] = buckets[iBucNumb][ibuc];
            i++;
        }
    }
    return 0;
}

// c++ standard sort
int cppSort(int *arr, int len) {
    sort(arr, arr+len);
    return 0;        
}

// compares two arrays
bool arrCompare(int *arr1, int *arr2, int len) {
    for(int i = 0; i < len; i++) {
        if(arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// fills a array with random numbers
int getRandomArr(int *arr, int len) {
    srand((unsigned)time(NULL)); // set the seed
    for(int i = 0; i < len; i++) {
        arr[i] = (rand() % 101)-50;
    }
    return 0;
}


// returns the pointer to the function of the sortingalgorithm on the basis of the given number
typedef int (*fncPtr)(int*, int);

fncPtr getFuncPointer(int algoNr) {
    string alg = ALGORITHMS[algoNr].second;
    if(alg.compare("insertionsort") == 0) {
        return &insertionsort;
    } else if(alg.compare("bubblesort") == 0) {
        return &bubblesort;
    } else if(alg.compare("mergesort") == 0) {
        return &mergesort;
    } else if(alg.compare("quicksort") == 0) {
        return &quicksort;
    } else if(alg.compare("bucketsort") == 0) {
        return &bucketsort;
    } else if(alg.compare("c++ standard sort") == 0) {
        return &cppSort;
    }
    return &bubblesort;
}

// returns the time in seconds of the executed sorting algorithm
double benchmark(int algoNr, int len) {
    int (*funcPointer)(int*, int) = getFuncPointer(algoNr);
    if(!funcPointer) return 0.0;

    int *arr = new int[len];
    getRandomArr(arr, len);

    int loops = 5;
    struct timespec start;
	struct timespec end;	
	double time;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(int i=0; i<loops; i++){
		funcPointer(arr, len);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	time = end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec);
	time /= loops;
    return time;
}

// tests the sorting algorithm
bool testShort(int algoNr) {
    int (*funcPointer)(int*, int) = getFuncPointer(algoNr);
    if(!funcPointer) return false;

    int *arrAlg1 = new int[0];
    int arrAlg2[10] = {1,1,1,5,5,5,3,3,3,3};
    int arrAlg3[10] = {1,1,1,1,1,1,1,1,1,1};
    int arrAlg4[10] = {1,2,3,4,5,6,7,8,9,10};
    int arrAlg5[10] = {0,0,0,0};
    int arrAlg6[18] = {1,-1,0,-1,0,1,1,0,-1,-1,1,0,0,-1,1,0,1,-1};
    int arrAlg7[1] = {0};
    int arrAlg8[3] = {INT_MAX, INT_MIN, 0};
    int arrAlg9[2] = {INT_MAX, INT_MIN};
    
    int *arrSol1 = new int[0];
    int arrSol2[10] = {1,1,1,3,3,3,3,5,5,5};
    int arrSol3[10] = {1,1,1,1,1,1,1,1,1,1};
    int arrSol4[10] = {1,2,3,4,5,6,7,8,9,10};
    int arrSol5[10] = {0,0,0,0};
    int arrSol6[18] = {-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,1,1,1,1,1,1};
    int arrSol7[1] = {0};
    int arrSol8[3] = {INT_MIN, 0, INT_MAX};
    int arrSol9[2] = {INT_MIN, INT_MAX};
  
    funcPointer(arrAlg1, 0);
    funcPointer(arrAlg2, 10);
    funcPointer(arrAlg3, 10);
    funcPointer(arrAlg4, 10);
    funcPointer(arrAlg5, 10);
    funcPointer(arrAlg6, 18);
    funcPointer(arrAlg7, 1);
    funcPointer(arrAlg8, 3);
    funcPointer(arrAlg9, 2);

    return
    arrCompare(arrSol1, arrAlg1, 0) &&
    arrCompare(arrSol2, arrAlg2, 0) &&
    arrCompare(arrSol3, arrAlg3, 0) &&
    arrCompare(arrSol4, arrAlg4, 0) &&
    arrCompare(arrSol5, arrAlg5, 0) &&
    arrCompare(arrSol6, arrAlg6, 0) &&
    arrCompare(arrSol7, arrAlg7, 0) &&
    arrCompare(arrSol8, arrAlg8, 0) &&
    arrCompare(arrSol9, arrAlg9, 0);
}

// tests the sorting algorithm
bool testLong(int algoNr) {
    int (*funcPointer)(int*, int) = getFuncPointer(algoNr);
    if(!funcPointer) return false;
    bool res = true;
    for(int i = 0; i < 1000; i++) {
        // create two identical arrays
        int *arrAlg = new int[i];
        getRandomArr(arrAlg, i);
        int *arrSol = new int[i];
        arrCopy(arrSol, arrAlg, i);
        // sort both arrays
        funcPointer(arrAlg, i);
        sort(arrSol, arrSol + i);        
        if(!arrCompare(arrSol, arrAlg, i)) {
            res = false;
        }
    }
    return res;
}

// tests the sorting algorithm
bool testAlg(int algoNr) {
    return testLong(algoNr) && testShort(algoNr);
}