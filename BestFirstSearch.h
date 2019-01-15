//
// Created by Naama on 13/01/2019.
//

#ifndef STONE2_BESTFIRSTSEARCH_H
#define STONE2_BESTFIRSTSEARCH_H

#include <set>
#include "Searcher.h"
#include "Searching.h"

template <class T>
class BestFirstSearch : public Searching<T> {

public:
    // the search method
    virtual Solution<State<T>> search (Searchable<T> searchable);
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated();
};

template<class T>
Solution<State<T>> BestFirstSearch<T>::search(Searchable<T> searchable) {
    State<T> goal = searchable.getGoalState();
    State<T> initial = searchable.getInitialState();
    this->StateQueue.add(initial);
    initial.setTotalCost(initial.getCost());
    initial.setCompCost(initial.getCost());
    std::set<State<T>> close;
    while (this->StateQueue.getSize() > 0) {
        State<T> current = this->popOpenList();
        close.insert(current);
        if (current == goal) {
            return this->getWay();
        }
        std::list<State<T>> possible = searchable.getAllPossibleStates(current);
        for (State<T> temp : possible) {
            if ((close.find(temp) == close.end()) && (!this->StateQueue.contains(temp))) {
                temp.setBefore(current);
                temp.setCompCost(temp.getCost());
                this->StateQueue.add(temp);
                double total = current.getTotalCost() + temp.getCost();
                temp.setTotalCost(total);
            } else if (current.getTotalCost() + temp.getCost() < temp.getTotalCost()) {
                if (this->StateQueue.contains(temp)) {
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                    this->StateQueue.getOut(temp);
                    this->StateQueue.add(temp);
                } else {
                    temp.setBefore(current);
                    temp.setCompCost(temp.getCost());
                    this->StateQueue.add(temp);
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                }
            }
        }

    }
}


#endif //STONE2_BESTFIRSTSEARCH_H

