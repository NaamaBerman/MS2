//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_SEARCHING_H
#define STONE2_SEARCHING_H


#include "Searcher.h"
#include "PriorityQueue.h"
#include <queue>
#include <set>


template <class T, class P, class S>
class Searching : public Searcher<T, P, S> {
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
    Solution<State<T>>* getWay(State<T>& init, State<T>& goal) {
        std::vector<State<T>> way;
        std::vector<State<T>> solutions;
        State<T> temp = goal;
        while (not (temp == init)) {
            way.push_back(temp);
            temp = temp.getBefore();
        }
        way.push_back(init);
        for(auto it = way.end(); it != way.begin(); --it) {
            solutions.push_back(*it);
        }
        auto * solution = new SearchSolution<T>(solutions);
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
    virtual Solution<State<T>>* search (Searchable<T>* searchable) = 0;
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() {
        return this->nodes;
    }
};



#endif //STONE2_SEARCHING_H
