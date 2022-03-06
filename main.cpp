#include <time.h>
#include <random>
#include <iostream>

using namespace std;

const int NUMBERS_SIZE = 5000;

int genRandInt(int low, int high){
    return low + rand() % (high - low +1);
}
void fillArrays(int arr1[], int arr2[], int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

int Partition(int numbers[], int lowIndex, int highIndex, int midPoint){
    int pivot = numbers[midPoint];
    bool done = false;
    while(!done){
        while(numbers[lowIndex] < pivot){
            lowIndex += 1;
        }
        while(numbers[highIndex] > pivot){
            highIndex -= 1;
        }
        if(lowIndex >= highIndex){
            done = true;
        }
        else{
            int temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;

            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

void Quicksort_midpoint(int numbers[], int i, int k){
    if(i >= k){
        return;
    }
    int mid = (i + k)/ 2;
    // cout << "1";
    // cout << "High: " << k << endl;
    // cout << "Mid: " << mid << endl;
    // cout << "Low: " << i << endl;
    int lowIndex = Partition(numbers, i, k, mid);
    // cout << "0";
    Quicksort_midpoint(numbers, i, lowIndex);
    Quicksort_midpoint(numbers, lowIndex+1, k);
    // cout << endl << endl;
}
void Quicksort_medianOfThree(int numbers[], int i, int k){
    if(i >= k){
        return;
    }
    int a = numbers[i];
    int b = numbers[(i+k)/2];
    int c = numbers[k];
    int medianPivot = -1;
    
    if((a <= b && b < c) || (a >= b && b > c)){
        medianPivot = b;
    }
    else if ((b <= c && c < a) || (b >= c && c > a)){
        medianPivot = c;
    }
    else if((c <= a && a < b) || (c >= a && a > b)){
        medianPivot = a;
    }
    else{
        cout << "Special Case Error" << endl;
        cout << "A: " << a << ", B: " << b << ", C: " << c << endl;
    }

    int lowIndex = Partition(numbers, i, k, medianPivot);
    Quicksort_midpoint(numbers, i, lowIndex);
    Quicksort_midpoint(numbers, lowIndex+1, k);
}
void InsertionSort(int numbers[], int numbersSize){
    int i = 0;
    int j = 0;
    int temp = 0;

    for(i = 0; i < numbersSize; ++i){
        j = i;
        while(j > 0 && numbers[j] < numbers[j-1]){
            temp = numbers[j];
            numbers[j] = numbers[j-1];
            numbers[j-1] = temp;
            --j;
        }
    }
}

int main(){
    int array1[NUMBERS_SIZE];
    int array2[NUMBERS_SIZE];
    int array3[NUMBERS_SIZE];
    fillArrays(array1, array2, array3);
    // cout << "Array Filled" << endl;

    clock_t quickmidTimeStart = clock();
    // cout << "QuickSort Midpoint Start" << endl;
    Quicksort_midpoint(array1, 0, NUMBERS_SIZE-1);
    clock_t quickmidTimeEnd = clock();
    // cout << "QuickSort Midpoint End" << endl;

    // cout << "QuickSort Median Start" << endl;
    clock_t quickmedianTimeStart = clock();
    Quicksort_medianOfThree(array2, 0, NUMBERS_SIZE-1);
    clock_t quickmedianTimeEnd = clock();
    // cout << "QuickSort Median End" << endl;

    // cout << "QuickSort Insertion Start" << endl;
    clock_t insertionTimeStart = clock();
    InsertionSort(array3, NUMBERS_SIZE);
    clock_t insertionTimeEnd = clock();
    // cout << "QuickSort Insertion End" << endl;
    
    double quickmedianelapsedTime = (quickmedianTimeEnd - quickmedianTimeStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    double quickmidelapsedTime = (quickmidTimeEnd - quickmidTimeStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    double insertelapsedTime = (insertionTimeEnd - insertionTimeStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "QuickSort Midpoint Runtime: " << quickmidelapsedTime << endl;
    cout << "QuickSort Median-of-Three Runtime: " << quickmedianelapsedTime << endl;
    cout << "Insertion Sort Runtime: " << insertelapsedTime << endl;
    return 1;
}