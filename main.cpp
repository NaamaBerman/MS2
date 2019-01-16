#include <iostream>
#include "parallel_server.h"
#include "classes.h"
#include "Solution.h"
#include "AStarSearch.h"

int main() {
    Solver<Searchable<Point>, Solution<State<Point>>>* solver =
            new AStarSearch<Point, Searchable<Point>, Solution<State<Point>>>();
    CacheManager<Searchable<Point>, Solution<State<Point>>>* cm =
            new FileCacheManager<Searchable<Point>, Solution<State<Point>>>();
    ClientHandler* cl =
            new MyTestClientHandler<Searchable<Point>, Solution<State<Point>>, Point>(solver, cm);
    MyParallelServer parallelServer(5);
    parallelServer.open(5400, cl);

}
