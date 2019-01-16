//
// Created by Naama on 15/01/2019.
//

#ifndef STONE2_ASTARSEARCH_H
#define STONE2_ASTARSEARCH_H

#include <set>
#include "Searcher.h"
#include "Searching.h"

template <class T, class P, class S>
class AStarSearch : public Searching<T, P, S> {
    int Heuristic(State<T> s, State<T> goal);
public:
    // the search method
    virtual Solution<State<T>> search (Searchable<T> searchable);
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated();

};

template <class T, class P, class S>
int AStarSearch<T, P, S>::Heuristic(State<T> s, State<T> goal) {
    int n = abs(goal.getX() - s.getX()) + abs(goal.getY() - s.getY());
    return n;
}

template <class T, class P, class S>
Solution<State<T>> AStarSearch<T, P, S>::search(Searchable<T> searchable) {
    State<T> goal = searchable.getGoalState();
    State<T> initial = searchable.getInitialState();
    this->StateQueue.add(initial);
    initial.setTotalCost(initial.getCost());
    initial.setCompCost(initial.getCost() + this->Heuristic(initial, goal));
    std::set<State<T>> close;
    while (this->StateQueue.getSize() > 0) {
        State<T> current = this->popOpenList();
        close.insert(current);
        if (current == goal) {
            return this->getWay(searchable);
        }
        std::list<State<T>> possible = searchable.getAllPossibleStates(current);
        for (State<T> temp : possible) {
            if ((close.find(temp) == close.end()) && (!this->StateQueue.contains(temp))) {
                temp.setBefore(current);
                temp.setCompCost(temp.getCost() + this->Heuristic(temp, goal));
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
                    temp.setCompCost(temp.getCost() + this->Heuristic(temp, goal));
                    this->StateQueue.add(temp);
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                }
            }
        }

    }
}




#endif //STONE2_ASTARSEARCH_H
