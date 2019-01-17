//
// Created by Naama on 10/01/2019.
//

#ifndef STONE2_SEARCHABLE_H
#define STONE2_SEARCHABLE_H
#include <list>
#include <string>
#include <iostream>

class Point {
    int x;
    int y;
public:
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    Point(const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }
    Point() {
        this->x = 0;
        this->y = 0;
    }
    friend bool operator == (const Point& p,const Point& d) {
        if (d.x == p.x) {
            if (d.y == p.y) {
                return true;
            }
        }
        return false;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

template <class T> class State {
    // the state represented by a string
    T state;
    // cost to reach this state (set by a setter)
    double cost;
    // the state we came from to this state (setter)
    State<T>* cameFrom = nullptr;
    double totalCost;
    double compareCost;
public:
    State(const T& state) {
        this->state = state;
    }
    ~State() {
        if (this->cameFrom != nullptr) {
            //delete(this->cameFrom);
        }
    }

    State(const State<T>& in) {
        this->state = in.state;
        this->cost = in.cost;
        this->compareCost = in.compareCost;
        this->totalCost = in.totalCost;
        this->cameFrom = in.cameFrom;
    }

    int getX() {
        return state.getX();
    }
    int getY() {
        return state.getY();
    }
    ///////////////
    friend bool operator == (const State<T>& s, const State<T>& d) {
        return (d.state == s.state);
    }
    void setCost(double c) {
        this->cost = c;
    }
    void setTotalCost(double tc) {
        this->totalCost = tc;
    }
    double getCost() {
        return this->cost;
    }

    double getTotalCost() {
        return this->totalCost;
    }
    void setCompCost(double c) {
        this->compareCost = c;
    }
    double getCompareCost() {
        return this->compareCost;
    }
    void setBefore(State<T>& before) {
        this->cameFrom = new State<T>(before);
    }
    State<T> getBefore() {
        return *(this->cameFrom);
    }
    friend bool operator< (const State<T>& s, const State<T>& d) {
        return s.compareCost < d.compareCost;
    }
    friend bool operator> (const State<T>& s, const State<T>& d) {
        return s.compareCost > d.compareCost;
    }
};
template <class T>
class Searchable {
public:
    virtual State<T>& getInitialState() = 0;
    virtual State<T>& getGoalState() = 0;
    // set the parent when adding to the list
    virtual std::list<State<T>> getAllPossibleStates(State<T> s) = 0;
    virtual std::string toString() = 0;

};





#endif //STONE2_SEARCHABLE_H

