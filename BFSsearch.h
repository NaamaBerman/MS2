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
    virtual Solution<State<T>> search (Searchable<T> searchable);
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated();
};

template <class T, class P, class S>
Solution<State<T>> BFSsearch<T, P, S>::search(Searchable<T> searchable) {
    State<T> initial = searchable.getInitialState();
    std::queue<T> q;
    q.push(initial);
    std::set<State<T>> used;
    used.insert(initial);
    while (q.size() > 0) {
        State<T> current = q.back();
        q.pop();
        std::list<State<T>> possible = searchable.getAllPossibleStates(current);
        for (State<T> temp : possible) {
            if ((used.find(temp) == used.end())) {
                q.push(temp);
                temp.setBefore(current);
                used.insert(temp);
            }
        }
    }
    return this->getWay(searchable);


}


#endif //STONE2_BFSSEARCH_H
