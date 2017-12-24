//
// Created by chern on 11/22/2017.
//

#ifndef INC_2024FINAL_SORTBENCHMARK_H
#define INC_2024FINAL_SORTBENCHMARK_H

#include <cstdlib>
#include <chrono>
#include <functional>

using namespace std;

// https://ngathanasiou.wordpress.com/2015/04/01/benchmarking-in-c/
template<typename TimeT = std::chrono::microseconds>
struct measure {
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args &&... args) {
        auto start = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<
                TimeT>(
                std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

class SortBenchmark {
private:
    static void randomFill(int* array, int length) {
        srand((unsigned) time(nullptr));
        int min = 0, max = length;
        int range = max - min;

        for (int i = 0; i < length; i++) {
            array[i] = min + rand() % range;
        }
    }

    static void almostSortedFill(int* array, int length) {
        srand((unsigned) time(nullptr));
        int range = 20;
        int diff = range / 2; // maybe make this depend on the length?

        for (int i = 0; i < length; i++) {
            int min = i - diff < 0 ? 0 : i - diff;
            array[i] = min + rand() % diff;
        }
    }

    static void reverseFill(int* array, int length) {
        for (int i = 0; i < length; i++) {
            array[i] = length - 1 - i;
        }
    }

    static void fewUniqueFill(int* array, int length) {
        srand((unsigned)time(nullptr));
        int unique = 100;

        for(int i = 0; i < length; i++) {
            array[i] = rand() % (unique - 1);
        }
    }

    static void swap(int* array, int i, int j);

    static int partition(int* array, int from, int to);

    static void quicksortInner(int* array, int from, int to);

    static void merge(int* array, int from, int split, int to, int* into);

    static void splitAndMerge(int* array, int from, int to, int* into);

public:
    enum DataGenRule {
        random_values,
        almost_sorted,
        reverse,
        few_unique
    };

    static void heapsort(int* array, int length);

    static void quicksort(int* array, int length);

    static void mergesort(int* array, int length);

    static void bubblesort(int* array, int length);

    static void insertionsort(int* array, int length);

    static void selectionsort(int* array, int length);

    static long long int runAlgoBenchmark(void (* algo)(int*, int), int* array, int length) {
        return measure<>::execution(algo, array, length);
    }

    static long runAlgoBenchmark(void (* algo)(int*, int), int iterations, int arrayLength, DataGenRule rule = random_values) {
        // total time tracker
        long totalTime = 0;
        void (* genFunction)(int*, int);

        // select the array generator function according to the rule
        switch(rule) {
            default: // fall-through to randomFill so CLion doesn't complain
            case random_values:
                genFunction = &randomFill;
                break;
            case almost_sorted:
                genFunction = &almostSortedFill;
                break;
            case reverse:
                genFunction = &reverseFill;
                break;
            case few_unique:
                genFunction = &fewUniqueFill;
                break;
        }

        // do this a bunch of times
        for (int i = 0; i < iterations; i++) {
            // generate a random array
            auto* a = new int[arrayLength];
            genFunction(a, arrayLength);

            // calculate time elapsed
            long time = runAlgoBenchmark(algo, a, arrayLength);

            // increment the tracker
            totalTime += time;
        }

        return totalTime;
    }
};


#endif //INC_2024FINAL_SORTBENCHMARK_H
