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
template <class S>
class PriorityQueue {
    std::vector<S> queue;
    S getMin() {
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
    void add(S var) {
        queue.push_back(var);
    }
    S getTop() {
        int min = getMin();
        S top = this->queue[min];
        this->queue.erase(min);
        return top;
    }
    int getSize() {
        return this->queue.size();
    }
    bool contains(S var) {
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

    void getOut(S var) {
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


};




#endif //STONE2_PRIORITYQUEUE_H
