//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_BESTFIRSTSEARCH_H
#define STONE2_BESTFIRSTSEARCH_H

#include <set>
#include "Searcher.h"
#include "Searching.h"

template <class T, class P, class S>
class BestFirstSearch : public Searching<T, P, S> {

public:
    // the search method
    virtual Solution<State<T>> * search (Searchable<T> * searchable);
// get how many nodes were evaluated by the algorithm
};

template <class T, class P, class S>
Solution<State<T>>* BestFirstSearch<T, P, S>::search(Searchable<T>* searchable) {
    State<T> goal = searchable->getGoalState();
    State<T> initial = searchable->getInitialState();
    initial.setTotalCost(initial.getCost());
    initial.setCompCost(initial.getCost());
    this->StateQueue.add(initial);
    std::set<State<T>> close;
    while (this->StateQueue.getSize() > 0) {
        State<T> current = this->popOpenList();
        close.insert(current);
        if (current == goal) {
            return this->getWay(initial, current);
        }
        std::list<State<T>> possible = searchable->getAllPossibleStates(current);
        for (State<T> temp : possible) {
            if (this->searchSet(close, temp)) continue;
            temp.setCompCost(current.getTotalCost()+temp.getCost());
            double total = current.getTotalCost() + temp.getCost();
            temp.setTotalCost(total);
            if ((not this->searchSet(close, temp)) and (not this->StateQueue.contains(temp))) {
                temp.setBefore(current);
                this->StateQueue.add(temp);
            } else if (current.getTotalCost() + temp.getCost() < temp.getTotalCost()) {
                if (this->StateQueue.contains(temp)) {
                    temp.setBefore(current);
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                    temp.setCompCost(current.getTotalCost()+temp.getCost());
                    this->StateQueue.getOut(temp);
                    this->StateQueue.add(temp);
                } else {
                    temp.setBefore(current);
                    temp.setCompCost(current.getTotalCost()+temp.getCost());
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                    this->StateQueue.add(temp);
                }
            }
        }

    }
}



////////////////////////////////////////////////





#endif //STONE2_BESTFIRSTSEARCH_H

