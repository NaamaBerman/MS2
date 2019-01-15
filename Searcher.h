
//
// Created by Naama on 10/01/2019.
//

#ifndef STONE2_SEARCHER_H
#define STONE2_SEARCHER_H

#include "Searchable.h"
#include "Solution.h"


template <class T>
class Searcher {
    // the search method
    Solution<T> search (Searchable<T> searchable);
// get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated();


};


#endif //STONE2_SEARCHER_H
