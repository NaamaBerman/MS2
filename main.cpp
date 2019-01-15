#include <iostream>
#include "classes.h"
#include <fstream>
#include "serial_server.h"
#include "parallel_server.h"

int main() {
    /*hash<string> h;

    ofstream fl;
    fl.open(to_string(h("a")));
    Problem p;
    Solution s;
    FileCacheManeger<Problem, Solution> f;
    cout<<f.hasSolution(p)<<endl;*/
    /*Problem pro("abc");
    Solution sol;
    FileCacheManeger<Problem, Solution>* fcm;
    StringR<Problem, Solution>* solver;
    MyTestClientHandler<Problem, Solution>* c = new MyTestClientHandler<Problem, Solution>(solver, fcm);
    MySerialServer s;
    s.open(5400, c);
    while (true) {

    }*/


    /*ThreadPool* pool = new ThreadPool(6);
    //volatile bool b = pool.getClientArrived();

    volatile counter c;
    auto a = pool->enqueue([&] () mutable {
        int x;
        //cout << "1" << endl;
        cin >> x;
        //b = true;
        c.count++;
        clientArrived = true;
        pool->mEventVar.notify_one();
        int y;
        cin >> y;
        clientLeft = true;
        c.count--;
        pool->mEventVar.notify_one();
        return x;
    });
    auto d = pool->enqueue([&] () mutable {
        int x;
        //cout << "1" << endl;
        cin >> x;
        //b = true;
        c.count++;
        clientArrived = true;
        pool->mEventVar.notify_one();
        int y;
        cin >> y;
        clientLeft = true;
        c.count--;
        pool->mEventVar.notify_one();
        return x;
    });
    auto cl = pool->enqueue([&] () mutable {
        int x;
        //cout << "1" << endl;
        cin >> x;
        //b = true;
        c.count++;
        clientArrived = true;
        pool->mEventVar.notify_one();
        int y;
        cin >> y;
        clientLeft = true;
        c.count--;
        pool->mEventVar.notify_one();
        return x;
    });

    auto listen = pool->enqueue([&] () mutable {
        while (true) {
            {
                std::unique_lock<std::mutex> lock(pool->mEventMutex);
                if(pool->mEventVar.wait_for(lock,chrono::seconds(5), [=]() {
                    return clientArrived;
                })) {
                    cout << "client arrived" << endl;
                    clientArrived = false;
                    pool->mEventVar.wait(lock, [&]() {
                        return clientLeft && (c.count == 0);
                    });
                    cout << "client left" << endl;
                    clientLeft = false;

                } else {
                    cout << "time out" << endl;
                    exit(0);
                }

            }

        }
    });
    delete pool;*/
    Problem pro("abc");
    Solution sol;
    FileCacheManeger<Problem, Solution>* fcm;
    StringR<Problem, Solution>* solver;
    MyTestClientHandler<Problem, Solution>* c = new MyTestClientHandler<Problem, Solution>(solver, fcm);
    MyParallelServer p(2);
    p.open(5400, c);


    return 0;
}