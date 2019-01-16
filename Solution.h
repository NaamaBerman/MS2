//
// Created by Naama on 15/01/2019.
//

#ifndef STONE2_SOLUTION_H
#define STONE2_SOLUTION_H

#include <vector>
#include <string>
#include "Searchable.h"

template <class S> class Solution {
    virtual std::vector<S> getSolution() = 0;

};


template <class T>
class SearchSolution : public Solution<State<T>> {
    std::vector<State<T>> solution;
public:
    SearchSolution(std::vector<State<T>> s) {
        this->solution = s;
    }
    std::vector<State<T>> getSolution() {
        return this->solution;
    }

};


#endif //STONE2_SOLUTION_H
