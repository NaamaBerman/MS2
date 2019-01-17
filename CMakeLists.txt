cmake_minimum_required(VERSION 3.12)
project(stone2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(stone2 Searchable.cpp Searchable.h Searcher.cpp Searcher.h BestFirstSearch.cpp BestFirstSearch.h Searching.cpp Searching.h PriorityQueue.cpp PriorityQueue.h Solution.cpp Solution.h AStarSearch.cpp AStarSearch.h BFSsearch.cpp BFSsearch.h DFSsearch.h MatrixSearch.h parallel_server.h parallel_server.cpp serial_server.h classes.h main.cpp)