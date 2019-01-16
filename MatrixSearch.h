//
// Created by Naama on 15/01/2019.
//

#ifndef STONE2_MATRIXSEARCH_H
#define STONE2_MATRIXSEARCH_H


#include <vector>
#include <string>
#include "Searchable.h"

class MatrixSearch : public Searchable<Point> {
    State<Point> initial;
    State<Point> goal;
    std::vector<std::vector<State<Point>>> states;
    int matSize;

    State<Point> fromStringToState(int r, int c, std::string s) {
        Point p = Point(r,c);
        State<Point> state = State<Point>(p);
        state.setCost(stoi(s));
        return state;
    }

public:
    MatrixSearch(std::vector<std::vector<std::string>> s) {
        int sRow = stoi(s[0][0]);
        int sColumn = stoi(s[0][1]);
        int eRow = stoi(s[0][3]);
        int eColumn = stoi(s[0][4]);
        auto it = s.begin();
        it++;
        int row = 0;
        int column = 0;
        for(; it != s.end(); it++) {
            for(auto iter = (*it).begin(); iter != (*it).end(); it++) {
                State<Point> current = fromStringToState(row, column, *iter);
                this->states[row].push_back(current);
                column++;
            }
            column = 0;
            row++;
        }
        matSize = row;
        initial = this->states[sRow][sColumn];
        goal = this->states[eRow][eColumn];
    }
    virtual State<Point> getInitialState() {
        return initial;
    }
    virtual State<Point> getGoalState() {
        return goal;
    }

    virtual std::list<State<Point>> getAllPossibleStates(State<Point> s) {
        std::list<State<Point>> possible;
        int row = s.getX();
        int column = s.getY();

        if (column == 0) {
            if (row == 0) {
                State<Point> temp1 = this->states[row][column + 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row + 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }
            } else if (row == matSize) {
                State<Point> temp1 = this->states[row][column + 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row - 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }

            } else {
                State<Point> temp1 = this->states[row][column + 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row - 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }
                State<Point> temp3 = this->states[row + 1][column];
                if (temp3.getCost() != -1) {
                    possible.push_back(temp3);

                }

            }
        } else if (column == matSize) {
            if (row == 0) {
                State<Point> temp1 = this->states[row][column - 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row + 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }
            } else if (row == matSize) {
                State<Point> temp1 = this->states[row][column - 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row - 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);
                }
            } else {
                State<Point> temp1 = this->states[row][column - 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row - 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }
                State<Point> temp3 = this->states[row + 1][column];
                if (temp3.getCost() != -1) {
                    possible.push_back(temp3);

                }

            }

        } else if (row == 0) {
            State<Point> temp1 = this->states[row][column + 1];
            if (temp1.getCost() != -1) {
                possible.push_back(temp1);

            }
            State<Point> temp2 = this->states[row][column - 1];
            if (temp2.getCost() != -1) {
                possible.push_back(temp2);

            }
            State<Point> temp3 = this->states[row + 1][column];
            if (temp3.getCost() != -1) {
                possible.push_back(temp3);

            }

        } else if (row == matSize) {
            State<Point> temp1 = this->states[row][column + 1];
            if (temp1.getCost() != -1) {
                possible.push_back(temp1);

            }
            State<Point> temp2 = this->states[row][column - 1];
            if (temp2.getCost() != -1) {
                possible.push_back(temp2);

            }
            State<Point> temp3 = this->states[row - 1][column];
            if (temp3.getCost() != -1) {
                possible.push_back(temp3);

            }
        } else {
            State<Point> temp1 = this->states[row][column + 1];
            if (temp1.getCost() != -1) {
                possible.push_back(temp1);

            }
            State<Point> temp2 = this->states[row][column - 1];
            if (temp2.getCost() != -1) {
                possible.push_back(temp2);

            }
            State<Point> temp3 = this->states[row + 1][column];
            if (temp3.getCost() != -1) {
                possible.push_back(temp3);

            }
            State<Point> temp4 = this->states[row - 1][column];
            if (temp4.getCost() != -1) {
                possible.push_back(temp4);

            }
        }
        return possible;

    }

};


#endif //STONE2_MATRIXSEARCH_H
