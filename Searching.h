//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_SEARCHING_H
#define STONE2_SEARCHING_H


#include "Searcher.h"
#include "PriorityQueue.h"
#include <queue>
#include <set>
#include <algorithm>


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
    State<T> popFirst()
    {
        nodes++;
        State<T> first = StateQueue.getFirst();
        return first;
    }
    State<T> popLast()
    {
        nodes++;
        State<T> first = StateQueue.getLast();
        return first;
    }
    Solution<State<T>>* getWay(State<T>& init, State<T>& goal) {
        std::vector<State<T>> way;
        State<T> temp = goal;
        while (not (temp == init)) {
            way.push_back(temp);
            temp = temp.getBefore();
        }
        way.push_back(init);
        std::reverse(way.begin(), way.end());
        auto * solution = new SearchSolution<T>(way);
        return solution;
    }
    bool searchSet(std::set<State<T>> &set1, State<T> in) {
        for (auto &item: set1) {
            if (item == in) {
                return true;
            }
        }
        return false;
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
