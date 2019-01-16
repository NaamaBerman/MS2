cmake_minimum_required(VERSION 3.12)
project(stone2)

set(CMAKE_CXX_STANDARD 11)

add_executable(stone2 main.cpp Searchable.cpp Searchable.h Searcher.cpp Searcher.h BestFirstSearch.cpp BestFirstSearch.h Searching.cpp Searching.h PriorityQueue.cpp PriorityQueue.h Solution.cpp Solution.h AStarSearch.cpp AStarSearch.h BFSsearch.cpp BFSsearch.h DFSsearch.h MatrixSearch.h classes.h parallel_server.cpp parallel_server.h serial_server.h)