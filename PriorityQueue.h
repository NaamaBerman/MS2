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
    int getMin() {
        int size = queue.size();
        if (size == 0) {
            return -1;
        }
        int min = 0;
        int i = 0;
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            if (*it < queue[min]) {
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
        getOut(top);
        return top;
    }

    S getFirst() {
        S first = this->queue[0];
        getOut(first);
        return first;
    }
    S getLast() {
        S last = this->queue[this->queue.size() - 1];
        getOut(last);
        return last;
    }
    int getSize() {
        return this->queue.size();
    }
    bool contains(S var) {
        for(auto &it : queue) {
            if (it == var) {
                return true;
            }
        }
        return false;
    }

    void getOut(S var) {
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            if (*it == var) {
                this->queue.erase(it);
                return;
            }
        }

    }



};




#endif //STONE2_PRIORITYQUEUE_H
