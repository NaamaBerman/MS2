
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
    virtual S* solve(P* p) {
        return search(p);
    }
    // the search method
    virtual Solution<State<T>>* search (Searchable<T>* searchable) = 0;
// get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() = 0;


};


#endif //STONE2_SEARCHER_H
