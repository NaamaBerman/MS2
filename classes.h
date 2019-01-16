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
#include <vector>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fstream>
#include "Searchable.h"

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

template <class Problem, class Solution, class T> class MyTestClientHandler : public ClientHandler {
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
        vector<string> startPoint;
        vector<string> endPoint;
        vector<string> Points;
        vector<vector<string>> vec;
        vector<vector<string>> vec2;
        Solution* solu;
        while (true) {
            bzero(buffer,256);
            n = read( socket,buffer,255 );

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            string str(buffer);
            vec.emplace_back(splitBy(str, ','));
            printf("Here is the message: %s\n",buffer);
            if (strcmp(buffer, "end") == 0) {
                endPoint = vec[vec.size() - 1];
                startPoint = vec[vec.size() - 2];
                Points.emplace_back(startPoint[0]);
                Points.emplace_back(startPoint[1]);
                Points.emplace_back(endPoint[0]);
                Points.emplace_back(endPoint[1]);
                vec2.emplace_back(Points);
                for (int i = 0; i < vec.size() - 2; i++) {
                    vec2.emplace_back(vec[i]);
                }
                solu = solver->solve(vec2);
                string s = StringSolution(solu);
                n = write(socket,s.c_str(),s.length());
                if (n < 0) {
                    perror("ERROR writing to socket");
                    exit(1);
                }
                break;
            }



        }

    }

private:
    vector<string> splitBy (string str, char c) {
        string acc;
        vector<string> vec;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != c) {
                acc+=str[i];
            } else {
               vec.emplace_back(acc);
               acc = "";
            }
        }
        return vec;
    }
    string StringSolution(Solution solu) {
        std::vector<std::string> s;
        string result;
        State<T> init = solu[0];
        auto it = solu.begin();
        it++;
        for(; it != solu.end(); ++it) {
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
        for (int i = 0; i < s.size(); i++) {
            if (i == s.size() - 1) {
                result += s[i];
                result += "\r\n";
            } else {
                result += s[i];
                result += ", ";
            }

        }
        return result;
    }

};








#endif //STONE2_SERVER_SIDE_H
