//
// Created by chern on 11/22/2017.
//

#ifndef INC_2024FINAL_HEAP_H
#define INC_2024FINAL_HEAP_H

#include <stdio.h>

#include "cassert"

/**
 * Builds a min-heap
 */
template <class T>
class Heap {
public:
    Heap();
    Heap(T* array, int length);
    void add(T elem);
    T peek();
    T pop();

    bool operator==(const Heap& rhs);
    Heap operator+(const Heap& b);
private:
    int currSize = 0;
    int maxSize = 10;
    T* heap = new T[10];
    void resize(int newLength);
    void swap(int i, int j);
    T parent(int i);
    int rightChildIndex(int i);
    int leftChildIndex(int i);
    int parentIndex(int i);
};

template <class T>
bool Heap<T>::operator==(const Heap& rhs) {
    // For equality we simply check that the heap arrays are equal, element
    // by element.
    if(currSize != rhs.currSize) {
        return false;
    } else {
        for(int i = 0; i < currSize; i++) {
            if(heap[i] != rhs.heap[i]) {
                return false;
            }
        }

        return true;
    }
}

template <class T>
Heap<T> Heap<T>::operator+(const Heap &b) {
    Heap<T> sum(heap, currSize);

    for(int i = 0; i < b.currSize; i++) {
        sum.add(b.heap[i]);
    }

    return sum;
}

template <class T>
void Heap<T>::resize(int newLength) {
    assert(newLength > maxSize);

    T* newArray = new T[newLength];

    // copy array
    for(int i = 0; i < currSize; i++) {
        newArray[i] = heap[i];
    }

    heap = newArray;
    maxSize = newLength;
}

template <class T>
void Heap<T>::swap(int i, int j) {
    assert(i < currSize);
    assert(j < currSize);

    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template <class T>
T Heap<T>::parent(int i) {
    return heap[parentIndex(i)];
}

template <class T>
int Heap<T>::rightChildIndex(int i) {
    return 2 * i + 1;
}

template <class T>
int Heap<T>::leftChildIndex(int i) {
    return 2 * i;
}

template <class T>
int Heap<T>::parentIndex(int i) {
    return i / 2;
}

template <class T>
void Heap<T>::add(T elem) {
    if(currSize == maxSize) {
        resize(maxSize * 2);
    }

    int index = currSize;

    // put the new element at the bottom of the heap
    heap[index] = elem;
    // increment size
    currSize++;

    // until the heap property is satisfied, bubble it up
    while(elem < parent(index)) {
        int pIndex = parentIndex(index);
        swap(index, pIndex);
        index = pIndex;
    }

    // heap is now repaired
}

template <class T>
T Heap<T>::peek() {
    return heap[0];
}

template <class T>
T Heap<T>::pop() {
    T first = heap[0];

    // swap the last and first elements and decrement size
    swap(0, currSize - 1);
    currSize--;

    // now bubble the topmost element down
    int index = 0;
    while(true) {
        int lcIndex = leftChildIndex(index);
        int rcIndex = rightChildIndex(index);

        int smallestIndex;

        if(rcIndex < currSize) {
            smallestIndex = heap[lcIndex] < heap[rcIndex] ? lcIndex : rcIndex;
        } else if(lcIndex < currSize) {
            smallestIndex = lcIndex;
        } else {
            break;
        }

        // if the heap property is satisfied, we're done
        if(heap[index] <= heap[smallestIndex]) {
            break;
        } else {
            // otherwise, swap and continue
            swap(index, smallestIndex);
            index = smallestIndex;
            continue;
        }
    }

    return first;
}

template <class T>
Heap<T>::Heap() {

}

template <class T>
Heap<T>::Heap(T *array, int length) {
    for(int i = 0; i < length; i++) {
        add(array[i]);
    }
}

#endif //INC_2024FINAL_HEAP_H
