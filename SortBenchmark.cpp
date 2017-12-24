//
// Created by chern on 11/22/2017.
//

#include <cmath>
#include "SortBenchmark.h"
#include "Heap.h"

void copyArray(int* source, int* dest, int length) {
    for(int i = 0; i < length; i++) {
        dest[i] = source[i];
    }
}

void SortBenchmark::swap(int* array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void SortBenchmark::heapsort(int* array, int length) {
    /**
     * Heapsort
     *
     * Build a min-heap from the array, then pop elements from the heap to fill
     * the new array.
     */
    Heap<int> heap(array, length);

    for(int i = 0; i < length; i++) {
        array[i] = heap.pop();
    }
}

int SortBenchmark::partition(int* array, int from, int to) {
    int pivot = array[to], i = from - 1;

    for(int j = from; j < to; j++) {
        if(array[j] < pivot) {
            i++;
            swap(array, i, j);
        }
    }

    if(array[to] < array[i + 1]) {
        swap(array, i + 1, to);
    }

    return i + 1;
}

void SortBenchmark::quicksort(int* array, int length) {
    /**
     * Quicksort
     *
     * Partition the array into two halves using the last element as a pivot,
     * then quicksort the two halves separately.
     */
    quicksortInner(array, 0, length - 1);
}

void SortBenchmark::quicksortInner(int* array, int from, int to) {
    if(from < to) {
        int p = partition(array, from, to);
        quicksortInner(array, from, p - 1);
        quicksortInner(array, p + 1, to);
    }
}

void SortBenchmark::mergesort(int* array, int length) {
    /**
     * Mergesort
     *
     * Split the array into chunks continuously, until the chunks are one
     * element each. Then, merge pairs of adjacent chunks until we're back to
     * the original length.
     */
    // copy the array
    int* B = new int[length];
    for(int i = 0; i < length; i++) {
        B[i] = array[i];
    }

    splitAndMerge(B, 0, length, array);
}

void SortBenchmark::splitAndMerge(int* array, int from, int to, int* into) {
    if(to - from == 1) {
        // we're done, no need to sort
    } else {
        // split the array into two
        int split = (to + from) / 2;

        // recursively apply sorting to both halves
        splitAndMerge(into, from, split, array);
        splitAndMerge(into, split, to, array);

        // now merge the two sorted arrays
        merge(array, from, split, to, into);
    }
}

void SortBenchmark::merge(int* array, int from, int split, int to, int* into) {
    int i = from, j = split;

    for(int k = i; k < to; k++) {
        if(i < split && (j >= to || array[i] <= array[j])) {
            into[k] = array[i];
            i++;
        } else {
            into[k] = array[j];
            j++;
        }
    }
}

void SortBenchmark::bubblesort(int* array, int length) {
    /**
     * Bubble sort
     *
     * Walk through the array, swapping adjacent elements if they're out of
     * order. Keep walking until no elements need to be swapped.
     */
    bool sorted;

    // a nice and simple bubble sort :)
    do {
        sorted = true;
        for(int i = 1; i < length; i++) {
            if(array[i - 1] > array[i]) {
                swap(array, i - 1, i);
                sorted = false;
            }
        }
    } while(!sorted);
}

void SortBenchmark::insertionsort(int* array, int length) {
    /**
     * Insertion sort
     *
     * Start with a "sorted" array of just the first element. For each
     * subsequent element, find its place in the sorted array and put it there.
     */
    // iterate over each element of the array, apart from the first
    for(int i = 1; i < length; i++) {
        // keep swapping until elements are no longer out of order
        for(int j = i; j > 0, array[j - 1] > array[j]; j--) {
            swap(array, j - 1, j);
        }
    }
}

void SortBenchmark::selectionsort(int* array, int length) {
    /**
     * Selection sort
     *
     * Iterate through the array, find the smallest element, and put it in
     * first place. Iterate over the rest of the array, find the next smallest,
     * put it in second place. Et cetera until all elements have been added.
     */

    for(int i = 0; i < length; i++) {
        int smallestIndex = i;
        for(int j = i + 1; j < length; j++) {
            if(array[j] < array[smallestIndex]) {
                smallestIndex = j;
            }
        }

        swap(array, i, smallestIndex);
    }
}
