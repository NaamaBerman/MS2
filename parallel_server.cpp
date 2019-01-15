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
                Task task;
                {
                    std::unique_lock<std::mutex> lock(mEventMutex);
                    mEventVar.wait(lock, [=]() {
                        return mStopping || !mTask.empty();
                    });
                    if (mStopping && mTask.empty()) {
                        break;
                    }
                    task = std::move(mTask.front());
                    mTask.pop();
                }
                task();


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
    for (int i = 0; i < numOfThreads - 1; i++) {
        pool->enqueue([&] () mutable {
            while (true) {
                int x;
                //cout << "1" << endl;
                cin >> x;
                //b = true;
                counter++;
                clientArrived = true;
                pool->mEventVar.notify_one();
                int y;
                cin >> y;
                clientLeft = true;
                counter--;
                pool->mEventVar.notify_one();
            }


        });

    }


    auto listen = pool->enqueue([&] () mutable {
        while (true) {
            {
                std::unique_lock<std::mutex> lock(pool->mEventMutex);
                if(pool->mEventVar.wait_for(lock,chrono::seconds(5 > starter ? 5 : starter), [=]() {
                    return clientArrived;
                })) {
                    cout << "client arrived" << endl;
                    clientArrived = false;
                    pool->mEventVar.wait(lock, [&]() {
                        return clientLeft && (counter == 0);
                    });
                    cout << "client left" << endl;
                    clientLeft = false;

                } else {
                    cout << "time out" << endl;
                    delete pool;
                    close(sockfd);
                    exit(0);
                }
                starter = 5;
            }

        }
    });
}
void MyParallelServer::stop() {
    delete pool;
    close(sockfd);
}