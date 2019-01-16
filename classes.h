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
#include "MatrixSearch.h"

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
    virtual Solution* solve(Problem* prob) = 0;

};


template <class Problem, class Solution> class CacheManager {


public:
    virtual bool hasSolution(Problem* prob) = 0;
    virtual string getSolution(Problem* prob) = 0;
    virtual void saveSolution(Problem* prob, string solu) = 0;

};

template <class Problem, class Solution>class FileCacheManager : public CacheManager<Problem, Solution> {
public:
    virtual bool hasSolution(Problem* prob) {
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);

    }
    virtual string getSolution(Problem* prob) {
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));
        fstream file(filename);
        string line;
        string result;
        while (getline(file, line)) {
            result += line;
        }
        return result;
    }
    virtual void saveSolution(Problem* prob, string solu){
        hash<string> str_hash;
        string filename = to_string(str_hash(prob->toString()));
        fstream file(filename);
        file << solu;

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
        string s;
        vector<string> startPoint;
        vector<string> endPoint;
        vector<string> Points;
        vector<vector<string>> vec;
        vector<vector<string>> vec2;
        while (true) {
            bzero(buffer,256);
            //cout << "Hi" << endl;
            n = read( socket,buffer,255 );

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            string str(buffer);
            cout << str << endl;

            //n = write(socket,str.c_str(),str.length());
            if (str != "end") {
                vec.push_back(splitBy(str, ','));
            }





            if (strcmp(buffer, "end") == 0) {
                endPoint = vec[vec.size() - 1];
                startPoint = vec[vec.size() - 2];
                Points.push_back(startPoint[0]);
                Points.push_back(startPoint[1]);
                Points.push_back(endPoint[0]);
                Points.push_back(endPoint[1]);
                vec2.push_back(Points);
                for (int i = 0; i < vec.size() - 2; i++) {
                    vec2.push_back(vec[i]);
                }
                /*if (cm->hasSolution(&vec2)) {
                    s = cm->getSolution(&vec2);
                } else {
                    MatrixSearch* matrix = new MatrixSearch(vec2);
                    s = StringSolution(solver->solve(matrix));
                    cm->saveSolution(&vec2, &s);
                }*/


                n = write(socket,s.c_str(),s.length());
                if (n < 0) {
                    perror("ERROR writing to socket");
                    exit(1);
                }
                for (vector<string> v: vec2) {
                    for (string s : v) {
                        cout << s;
                        cout << ",";
                    }
                    cout << "yey" << endl;
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
            if (str[i] != c && str[i] != ' ' ) {
                acc+=str[i];
            } else {
                if (acc != "") {
                    vec.push_back(acc);
                }


               acc = "";
            }
            if (i == str.length() - 1) {
                vec.push_back(acc);
            }
        }
        return vec;
    }
    string StringSolution(Solution* solu) {
        std::vector<std::string> s;
        string result;
        State<T> init = solu->getSolution()[0];
        auto it = solu->getSolution().begin();
        it++;
        for(; it != solu->getSolution().end(); ++it) {
            State<T> temp = *(it--);
            if ((*it).getX() > init.getX()) {
                s.push_back("Right");
            } else if ((*it).getX() < init.getX()) {
                s.push_back("Left");
            } else if ((*it).getY() > init.getY()) {
                s.push_back("Down");
            } else if ((*it).getY() < init.getY()) {
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
