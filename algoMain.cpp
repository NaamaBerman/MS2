//
// Created by Naama on 16/01/2019.
//

#include "AStarSearch.h"
#include "BestFirstSearch.h"
#include "BFSsearch.h"
#include "DFSsearch.h"

using namespace std;
int main() {
    vector<string> a = {"0","0","1","1"};
    vector<string> b = {"1","2"};
    vector<string> c = {"3","4"};
//    vector<string> d = {"1","1","1"};
    cout << "A" << endl;
    vector<vector<string>> mat = {a,b,c};
    MatrixSearch* problem = new MatrixSearch(mat);
    cout << problem->getGoalState().getX() << "," << problem->getGoalState().getY() << endl;
    cout << "a" << endl;
    for (auto &item : problem->getAllPossibleStates(problem->getGoalState()))  {
        cout << item.getX() << "," << item.getY() << endl;
    }

    cout << problem->toString() << endl;

    Solver<Searchable<Point>, Solution<State<Point>>>* solver =
            new DFSsearch<Point, Searchable<Point>, Solution<State<Point>>>();

    auto *res = solver->solve(problem);
    auto sol = res->getSolution();
    for (auto &item : sol) {
        cout << item.getX() << " jj " << item.getY()<< endl;
    }
    //delete res;
    return 0;
}
