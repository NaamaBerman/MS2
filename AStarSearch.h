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
    bool searchSet(std::set<State<T>> &set1, State<T> in) {
        for (auto &item: set1) {
            if (item == in) {
                return true;
            }
        }
        return false;
    }
public:
    // the search method
    virtual Solution<State<T>>* search (Searchable<T>* searchable);
};

template <class T, class P, class S>
int AStarSearch<T, P, S>::Heuristic(State<T> s, State<T> goal) {
    int n = abs(goal.getX() - s.getX()) + abs(goal.getY() - s.getY());
    return n;
}

template <class T, class P, class S>
Solution<State<T>>* AStarSearch<T, P, S>::search(Searchable<T>* searchable) {
    State<T> goal = searchable->getGoalState();
    State<T> initial = searchable->getInitialState();
    initial.setTotalCost(initial.getCost());
    initial.setCompCost(initial.getCost() + this->Heuristic(initial, goal));
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
            if (searchSet(close, temp)) continue;
            temp.setCompCost(current.getTotalCost()+temp.getCost() + this->Heuristic(temp, goal));
            double total = current.getTotalCost() + temp.getCost();
            temp.setTotalCost(total);
            if ((not searchSet(close, temp)) and (not this->StateQueue.contains(temp))) {
                temp.setBefore(current);
                this->StateQueue.add(temp);
            } else if (current.getTotalCost() + temp.getCost() < temp.getTotalCost()) {
                if (this->StateQueue.contains(temp)) {
                    temp.setBefore(current);
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                    temp.setCompCost(current.getTotalCost()+temp.getCost() + this->Heuristic(temp, goal));
                    this->StateQueue.getOut(temp);
                    this->StateQueue.add(temp);
                } else {
                    temp.setBefore(current);
                    temp.setCompCost(current.getTotalCost()+temp.getCost() + this->Heuristic(temp, goal));
                    double total = current.getTotalCost() + temp.getCost();
                    temp.setTotalCost(total);
                    this->StateQueue.add(temp);
                }
            }
        }

    }
}

#endif //STONE2_ASTARSEARCH_H
