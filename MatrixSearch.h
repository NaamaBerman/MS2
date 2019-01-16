//
// Created by Naama on 15/01/2019.
//

#ifndef STONE2_MATRIXSEARCH_H
#define STONE2_MATRIXSEARCH_H


#include <vector>
#include <string>
#include "Searchable.h"

class MatrixSearch : public Searchable<Point> {
    int startX;
    int startY;
    int endX;
    int endY;
    std::vector<std::vector<State<Point>>> states;
    int matSize;
    std::vector<std::vector<std::string>> asString;

    State<Point> fromStringToState(int r, int c, std::string s) {
        Point p(r,c);
        State<Point> state(p);
        state.setCost(stoi(s));
        return state;
    }

public:

    MatrixSearch(const std::vector<std::vector<std::string>>& s) {
        this->asString = s;
        this->startX = stoi(s[0][0]);
        this->startY = stoi(s[0][1]);
        this->endX = stoi(s[0][2]);
        this->endY = stoi(s[0][3]);
        auto vec = s.begin();
        vec++;
        int row = 0;
        int column = 0;
        for(; vec != s.end(); vec++) {
            this->states.push_back(std::vector<State<Point>>());
            for(auto &item : *vec) {
                //State<Point> current(fromStringToState(row, column, *iter);
                auto tmp = fromStringToState(row, column, item);
                this->states[row].push_back(tmp);
                column++;
            }
            column = 0;
            row++;
        }
        matSize = row;

    }

    virtual std::string toString() {
        std::string result;
        for(auto it = asString.begin(); it != asString.end(); it++) {
            for(auto iter = (*it).begin(); iter != (*it).end(); it++) {
                result += *iter + ",";
            }
        }
        return result;

    }
    virtual State<Point>& getInitialState() {
        return this->states.at(this->startX).at(this->startY);
    }
    virtual State<Point>& getGoalState() {
        return this->states.at(this->endX).at(this->endY);
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
            } else if (row == matSize - 1) {
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
        } else if (column == matSize - 1) {
            if (row == 0) {
                State<Point> temp1 = this->states[row][column - 1];
                if (temp1.getCost() != -1) {
                    possible.push_back(temp1);

                }
                State<Point> temp2 = this->states[row + 1][column];
                if (temp2.getCost() != -1) {
                    possible.push_back(temp2);

                }
            } else if (row == matSize - 1) {
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

        } else if (row == matSize - 1) {
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
