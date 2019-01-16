//
// Created by jonathan on 12/01/19.
//

#ifndef PROJECT2_PARALLEL_SERVER_H
#define PROJECT2_PARALLEL_SERVER_H

#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <future>
#include <unistd.h>
#include <iostream>
#include "classes.h"
//extern volatile bool clientArrived;
//extern volatile bool clientLeft;
//extern volatile int numOfCLients;
class Task {
public:
    virtual void task() = 0;
};
class ThreadPool {
public:
     //using Task = std::function<void(ClientHandler*, Server*)>;
    ThreadPool(int num_of_threads) {
        start(num_of_threads);
    }
    ~ThreadPool() {
        stop();
    }

    /*
     * our enqueue method will return a future from the type of the return value of task().
     * we use future so we can get data from the task() function that runs of another thread.
     * the data will be the result of the task() function.
     */
    /*template <class T>
    auto enqueue(T task) -> std::future<decltype(task())> {
        //a shared pointer of packaged_task
        //the packaged_task contains a task function
        //the task function returns decltype(task())
        //thh task function's arguments are nothing
        auto wrapper = std::make_shared<std::packaged_task<decltype(task()) (ClientHandler*, Server*)>>(std::move(task));
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mTask.emplace([=]() {
                (*wrapper)(ClientHandler* , Server* );
            });
        }
        mEventVar.notify_one();
        //we needed shared pointer because we used wrapper both in the lambda and in here.
        return wrapper->get_future();
    }*/
    void enqueue(Task* task) {
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mTask.emplace(task);
        }
        mEventVar.notify_one();

    }


    std::condition_variable mEventVar;
    std::mutex mEventMutex;
private:
    std::vector<std::thread> mThreads;
    //std::condition_variable mEventVar;
    //std::mutex mEventMutex;
    bool mStopping = false;
    std::queue<Task*> mTask;
    //volatile bool clientArrived = false;
    void start(int num_of_threads);
    void stop();
};


class MyParallelServer : public Server {

    ThreadPool* pool;

    int numOfThreads;

public:
    int sockfd;
    volatile int counter;
    volatile bool clientArrived;
    volatile bool clientLeft;
    int starter;
    MyParallelServer(int numOfThreads) {
        sockfd = 0;
        counter = 0;
        starter = 10000;
        clientArrived = false;
        clientLeft = false;
        this->numOfThreads = numOfThreads;
        pool = new ThreadPool(numOfThreads);

    }
    virtual void open(int port, ClientHandler* c);
    virtual void stop();
    ~MyParallelServer(){
        stop();
    }


private:
    void openSocket(int port);

};
class MyTimeOut : public Task {
    ThreadPool* pool;
    MyParallelServer* server;
public:
    MyTimeOut(ThreadPool* pool, MyParallelServer* server) {
        this->pool = pool;
        this->server = server;
    }
    virtual void task() {
        while (true) {
            {
                std::unique_lock<std::mutex> lock(pool->mEventMutex);
                if(pool->mEventVar.wait_for(lock,chrono::seconds(60 > server->starter ? 60 : server->starter), [=]() {
                    return server->clientArrived;
                })) {
                    cout << "client arrived" << endl;
                    server->clientArrived = false;
                    pool->mEventVar.wait(lock, [&]() {
                        return server->clientLeft && (server->counter == 0);
                    });
                    cout << "client left" << endl;
                    server->clientLeft = false;

                } else {
                    cout << "time out" << endl;
                    delete pool;
                    close(server->sockfd);
                    exit(0);
                }
                server->starter = 5;
            }

        }
    }
};

class Func : public Task {
    ThreadPool* pool;
    MyParallelServer* server;
    ClientHandler* c;
public:
    Func(ThreadPool* pool, MyParallelServer* server, ClientHandler* c) {
        this->pool = pool;
        this->server = server;
        this->c = c;
    }
    virtual void task() {
        while (true) {

            int  newsockfd;
            int clilen;
            struct sockaddr_in cli_addr;
            clilen = sizeof(cli_addr);
            newsockfd = accept(server->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
            if (newsockfd < 0)	{
                perror("other error");
                exit(3);
            }

            server->counter++;
            server->clientArrived = true;
            pool->mEventVar.notify_one();
            c->handleClient(newsockfd);
            close(newsockfd);
            server->clientLeft = true;
            server->counter--;
           pool->mEventVar.notify_one();
        }
    }
};

#endif //PROJECT2_PARALLEL_SERVER_H
