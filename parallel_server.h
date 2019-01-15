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
class ThreadPool {
public:
     using Task = std::function<void()>;
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
    template <class T>
    auto enqueue(T task) -> std::future<decltype(task())> {
        //a shared pointer of packaged_task
        //the packaged_task contains a task function
        //the task function returns decltype(task())
        //thh task function's arguments are nothing
        auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mTask.emplace([=]() {
                (*wrapper)();
            });
        }
        mEventVar.notify_one();
        //we needed shared pointer because we used wrapper both in the lambda and in here.
        return wrapper->get_future();
    }
    /*volatile bool& getClientArrived() {
        return clientArrived;
    }*/

    std::condition_variable mEventVar;
    std::mutex mEventMutex;
private:
    std::vector<std::thread> mThreads;
    //std::condition_variable mEventVar;
    //std::mutex mEventMutex;
    bool mStopping = false;
    std::queue<Task> mTask;
    //volatile bool clientArrived = false;
    void start(int num_of_threads);
    void stop();
};


class MyParallelServer : public Server {
    int sockfd;
    ThreadPool* pool;
    volatile int counter;
    int numOfThreads;
    volatile bool clientArrived;
    volatile bool clientLeft;
    int starter;
public:
    MyParallelServer(int numOfThreads) {
        sockfd = 0;
        counter = 0;
        starter = 1000;
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

#endif //PROJECT2_PARALLEL_SERVER_H
