//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_SEARCHING_H
#define STONE2_SEARCHING_H


#include "Searcher.h"
#include "PriorityQueue.h"
#include <queue>


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
    Solution<State<T>> getWay(Searchable<T> searchable) {
        std::vector<State<T>> way;
        std::vector<State<T>> solutions;
        State<T> goal = searchable.getGoalState();
        State<T> init = searchable.getInitialState();
        State<T> temp = goal;
        while (temp != init) {
            way.push_back(temp);
            temp = temp.getBefore();
        }
        way.push_back(init);
        for(auto it = way.end; it != way.begin(); --it) {
            solutions.push_back(*it);
        }
        SearchSolution<State<Point>> solution = SearchSolution<State<T>>(solutions);
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