//
// Created by Naama on 15/01/2019.
//

#ifndef STONE2_BFSSEARCH_H
#define STONE2_BFSSEARCH_H

#include <set>
#include "Searcher.h"
#include "Searching.h"

template <class T, class P, class S>
class BFSsearch : public Searching<T, P , S>{

public:
    // the search method
    virtual Solution<State<T>>* search (Searchable<T>* searchable);
// get how many nodes were evaluated by the algorithm
};

template <class T, class P, class S>
Solution<State<T>>* BFSsearch<T, P, S>::search(Searchable<T>* searchable) {
    State<T> initial = searchable->getInitialState();
    State<T> goal = searchable->getGoalState();
    initial.setTotalCost(initial.getCost());
    initial.setCompCost(initial.getCost());
    this->StateQueue.add(initial);
    std::set<State<T>> used;
    used.insert(initial);
    while (this->StateQueue.getSize() > 0) {
        State<T> current = this->popFirst();
        if (current == goal) {
            goal = current;
        }
        std::list<State<T>> possible = searchable->getAllPossibleStates(current);
        for (State<T> temp : possible) {
            if (!this->searchSet(used, temp)) {
                double total = current.getTotalCost() + temp.getCost();
                temp.setTotalCost(total);
                temp.setCompCost(current.getTotalCost()+temp.getCost());
                temp.setBefore(current);
                this->StateQueue.add(temp);
                used.insert(temp);
            }
        }
    }
    return this->getWay(initial, goal);


}



#endif //STONE2_BFSSEARCH_H
