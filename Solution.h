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
    std::vector<std::string> StringSolution() {
        std::vector<std::string> s;
        State<T> init = this->solution[0];
        auto it = this->solution.begin();
        it++;
        for(; it != this->solution.end(); ++it) {
            State<T> temp = *(it--);
            if (*it.getX() > init.getX()) {
                s.push_back("Right");
            } else if (*it.getX() < init.getX()) {
                s.push_back("Left");
            } else if (*it.getY() > init.getY()) {
                s.push_back("Down");
            } else if (*it.getY() < init.getY()) {
                s.push_back("Up");
            }
        }
        return s;
    }
};


#endif //STONE2_SOLUTION_H
