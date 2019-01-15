//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_SEARCHING_H
#define STONE2_SEARCHING_H


#include "Searcher.h"
#include "PriorityQueue.h"
#include <queue>
//#include <cstddef>

template <class T>
class Searching : public Searcher<T> {
protected:
    ////
    PriorityQueue<State<T>> StateQueue;
    int nodes;
    State<T> popOpenList()
    {
        nodes++;
        State<T> top = StateQueue.getTop();
        return top;
    }
    Solution<State<T>> getWay() {
        /////////// get path properly
        SearchSolution<State<T>> solution = SearchSolution<State<T>>(this->StateQueue);
        return solution;
    }


public:
    Searching() {
        nodes = 0;
    }
    int listSize() {
        return StateQueue.getSize();
    }



// the search method
    virtual Solution<T> search (Searchable<T> searchable) = 0;
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() {
        return this->nodes;
    }
};



#endif //STONE2_SEARCHING_H
