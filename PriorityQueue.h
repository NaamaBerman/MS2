//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_PRIORITYQUEUE_H
#define STONE2_PRIORITYQUEUE_H

#include<climits>
#include <iostream>

using namespace std;
#include "Searchable.h"
#include <vector>
template <class T>
class PriorityQueue {
    std::vector<T> queue;
    T getMin() {
        int size = queue.size();
        if (size == 0) {
            return nullptr;
        }
        int min = 0;
        int i = 0;
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            if (*it < min) {
                min = i;
            }
            i++;
        }
        return min;
    }
public:
    // Constructor
    PriorityQueue() {
    }
    void add(T var) {
        queue.push_back(var);
    }
    T getTop() {
        int min = getMin();
        T top = this->queue[min];
        this->queue.erase(min);
        return top;
    }
    int getSize() {
        return this->queue.size();
    }
    bool contains(T var) {
        int i = 0;
        int index = -1;
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            if (*it == var) {
                index = i;
            }
            i++;
        }
        return index != -1;
    }

    void getOut(T var) {
        int i = 0;
        int index = -1;
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            if (*it == var) {
                index = i;
            }
            i++;
        }
        this->queue.erase(index);

    }

    // to heapify a subtree with the root at given index
    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && headArr[l] < headArr[i])
            smallest = l;
        if (r < heap_size && headArr[r] < headArr[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(&headArr[i], &headArr[smallest]);
            MinHeapify(smallest);
        }
    }

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    int extractMin() {
        if (heap_size <= 0)
            return INT_MAX;
        if (heap_size == 1)
        {
            heap_size--;
            return headArr[0];
        }

        // Store the minimum value, and remove it from heap
        int root = headArr[0];
        headArr[0] = headArr[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val) {
        headArr[i] = new_val;
        while (i != 0 && headArr[parent(i)] > headArr[i])
        {
            swap(&headArr[i], &headArr[parent(i)]);
            i = parent(i);
        }
    }


    // Returns the minimum key (key at root) from min heap

    // Deletes a key stored at index i
    void deleteKey(int i) {
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    // Inserts a new key 'k'
    void insertKey(int k) {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        headArr[i] = k;

        // Fix the min heap property if it is violated
        while (i != 0 && headArr[parent(i)] > headArr[i])
        {
            swap(&headArr[i], &headArr[parent(i)]);
            i = parent(i);
        }
    }


// A utility function to swap two elements
    void swap(T *x, T *y)
    {
        T temp = *x;
        *x = *y;
        *y = temp;
    }


};




#endif //STONE2_PRIORITYQUEUE_H
