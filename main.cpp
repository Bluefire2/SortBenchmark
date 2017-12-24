#include <iostream>
#include "SortBenchmark.h"

using namespace std;
void printArray(int* array, int length) {
    for(int i = 0; i < length; i++) {
        cout << array[i];
        if(i != length - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

bool isSorted(int* array, int length) {
    for(int i = 1; i < length; i++) {
        int a = array[i - 1], b = array[i];
        if(array[i - 1] > array[i]) {
            printf("%i, %i, at index %i\n", a, b, i - 1);
            return false;
        }
    }
    return true;
}

int main() {
    bool repeat = true;

    while(repeat) {
        // take user input
        int iterations, arrayLength, dataGenRuleCode;

        // convoluted way of doing input validation
        // https://stackoverflow.com/a/2076144/1175276
        while (true) {
            cout << "Enter number of iterations: ";
            if (cin >> iterations) {
                break;
            } else {
                cout << "Please enter a valid integer" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        while (true) {
            cout << "Enter array length:";
            if (cin >> arrayLength) {
                break;
            } else {
                cout << "Please enter a valid integer" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        while (true) {
            cout
                    << "Enter the type of data to test on (0 = random, 1 = almost sorted, 2 = reverse, 3 = few unique elements):";
            if (cin >> dataGenRuleCode) {
                break;
            } else {
                cout << "Please enter a valid integer" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // parse the rule out
        SortBenchmark::DataGenRule rule;
        switch (dataGenRuleCode) {
            default:
            case 0:
                rule = SortBenchmark::random_values;
                break;
            case 1:
                rule = SortBenchmark::almost_sorted;
                break;
            case 2:
                rule = SortBenchmark::reverse;
                break;
            case 3:
                rule = SortBenchmark::few_unique;
                break;
        }

        // run algos:
        cout << "Bubble sort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::bubblesort, iterations, arrayLength, rule)
             << " microseconds" << endl;
        cout << "Selection sort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::selectionsort, iterations, arrayLength, rule)
             << " microseconds" << endl;
        cout << "Insertion sort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::insertionsort, iterations, arrayLength, rule)
             << " microseconds" << endl;
        cout << "Mergesort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::mergesort, iterations, arrayLength, rule)
             << " microseconds" << endl;
        cout << "Heapsort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::heapsort, iterations, arrayLength, rule)
             << " microseconds" << endl;
        cout << "Quicksort: ";
        cout << SortBenchmark::runAlgoBenchmark(SortBenchmark::quicksort, iterations, arrayLength, rule)
             << " microseconds" << endl;

        // ask if user wants to go again
        string repeatStr;
        cout << "Again? (y/n)" << endl;
        cin >> repeatStr;
        if(repeatStr != "y") {
            repeat = false;
        }
    }
    return 0;
}
