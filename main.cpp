#include <iostream>
#include "parallel_server.h"
#include "classes.h"
#include "Solution.h"
#include "AStarSearch.h"
#include "BestFirstSearch.h"
#include "DFSsearch.h"
#include "BFSsearch.h"

int main(int argc, char *argv[]) {
    Solver<Searchable<Point>, Solution<State<Point>>>* solver =
            new AStarSearch<Point, Searchable<Point>, Solution<State<Point>>>();
    CacheManager<Searchable<Point>, Solution<State<Point>>>* cm =
            new FileCacheManager<Searchable<Point>, Solution<State<Point>>>();
    ClientHandler* cl =
            new MyTestClientHandler<Searchable<Point>, Solution<State<Point>>, Point>(solver, cm);
    MyParallelServer parallelServer(5);
    int port = atoi(argv[1]);
    parallelServer.open(port, cl);

    return 0;


}
