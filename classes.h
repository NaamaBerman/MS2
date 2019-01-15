//
// Created by jonathan on 05/01/19.
//

#ifndef STONE2_SERVER_SIDE_H
#define STONE2_SERVER_SIDE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <string.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <fstream>

using namespace std;
namespace server_side {

    class ClientHandler {
    public:
        virtual void handleClient(int socket) = 0;
    };

    class Server {
    public:
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop() = 0;
    };

}
using namespace server_side;

template <class Problem, class Solution> class Solver {
public:
    virtual Solution& solve(Problem prob) = 0;

};


template <class Problem, class Solution> class CacheManager {


public:
    virtual bool hasSolution(Problem* prob) = 0;
    virtual Solution* getSolution(Problem* prob) = 0;
    virtual void saveSolution(Problem* prob, Solution* solu) = 0;

};

template <class Problem, class Solution>class FileCacheManeger : public CacheManager<Problem, Solution> {
public:
    virtual bool hasSolution(Problem* prob) {
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);

    }
    virtual Solution* getSolution(Problem* prob) {
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));

        Solution* solu = new Solution();
        solu->fromFile(filename);
        return solu;
    }
    virtual void saveSolution(Problem* prob, Solution* solu){
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));
        solu->toFile(filename);

    }

};

template <class Problem, class Solution> class MyTestClientHandler : public ClientHandler {
    Solver<Problem, Solution>* solver;
    CacheManager<Problem, Solution>* cm;
public:
    MyTestClientHandler(Solver<Problem, Solution>* solver, CacheManager<Problem, Solution>* cm) {
        this->cm = cm;
        this->solver = solver;
    }
    virtual void handleClient(int socket) {
        char buffer[256];
        int n;
        bzero(buffer,256);

        n = read( socket,buffer,255 );

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("Here is the message: %s\n",buffer);

        /* Write a response to the client */
        n = write(socket,"I got your message",18);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

};


class Problem {
    string str;
public:
    Problem(string str) {
        this->str = str;
    }
    string toString() {
        return str;
    }
};
class Solution {
    string solu;
public:
    Solution() {
        solu = "";
    }
    Solution(string str) {
        solu = str;
    }
    void toFile(string file_name) {
        fstream f;
        f.open(file_name);
        f << solu;
        f.close();


    }
    void fromFile(string file_name) {
        fstream f;
        f.open(file_name);
        f >> solu;
        f.close();
    }
};

template <class Problem, class Solution > class StringR : public Solver<Problem, Solution> {
public:
    virtual Solution& solve(Problem prob) {
        string str = prob.toString();
        string result = str += "hi";
        Solution solu(result);
        return solu;



    }

};






#endif //STONE2_SERVER_SIDE_H
