
//
// Created by Naama on 10/01/2019.
//

#ifndef STONE2_SEARCHER_H
#define STONE2_SEARCHER_H

#include "Searchable.h"
#include "Solution.h"
#include "classes.h"
#include "MatrixSearch.h"


template <class T, class P, class S>
class Searcher : public Solver<P, S> {
    virtual Solution<State<T>> solve(P p) {
        Searchable<T>* searchable = MatrixSearch(p);
        return search(searchable);
    }
    // the search method
    Solution<State<T>> search (Searchable<T> searchable);
// get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated();


};


#endif //STONE2_SEARCHER_H
