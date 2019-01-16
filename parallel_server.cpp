//
// Created by jonathan on 12/01/19.
//

#include "parallel_server.h"

//volatile bool clientArrived = false;
//volatile bool clientLeft = false;
//volatile int numOfClients = 0;
void ThreadPool::start(int num_of_threads) {
    for (int i = 0; i < num_of_threads; i++) {
        mThreads.emplace_back([=](){
            while (true) {
                Task* task;
                {
                    std::unique_lock<std::mutex> lock(mEventMutex);
                    mEventVar.wait(lock, [=]() {
                        return mStopping || !mTask.empty();
                    });
                    if (mStopping && mTask.empty()) {
                        break;
                    }
                    task = mTask.front();
                    mTask.pop();
                }
                task->task();


            }
        });
    }
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(mEventMutex);
        mStopping = true;
    }
    mEventVar.notify_all();
    for (auto &thread : mThreads) {
        thread.join();
    }

}

void MyParallelServer::openSocket(int port) {
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    listen(sockfd,5);

}

void MyParallelServer::open(int port, ClientHandler *c) {
    openSocket(port);
    Task* timeout = new MyTimeOut(this->pool, this);
    for (int i = 0; i < numOfThreads - 1; i++) {
        pool->enqueue(new Func(pool, this, c));

    }


    pool->enqueue(timeout);
}
void MyParallelServer::stop() {
    delete pool;
    close(sockfd);
}
