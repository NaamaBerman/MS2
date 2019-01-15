//
// Created by jonathan on 10/01/19.
//

#ifndef STONE2_SERIAL_SERVER_H
#define STONE2_SERIAL_SERVER_H

#include "classes.h"


class param {
    int sockfd;
    ClientHandler* c;
public:
    param(int sockfd, ClientHandler* c) {
        this->sockfd = sockfd;
        this->c = c;
    }
    int getSock() {
        return sockfd;
    }
    ClientHandler* getClientHandler() {
        return c;
    }
};

class MySerialServer : public Server {

public:
    virtual void open(int port, ClientHandler* c) {

        struct sockaddr_in serv_addr;
        int sockfd;
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


        /* Now start listening for the clients, here process will
           * go in sleep mode and will wait for the incoming connection
        */

        listen(sockfd,5);

        pthread_t trid;
        param* ar = new param(sockfd, c);
        pthread_create(&trid, nullptr, clientsLoop, ar);

    }
    virtual void stop() {

    }
    static void* clientsLoop (void* ar) {
        param* ar1 = (param*)ar;
        int sockfd = ar1->getSock();
        int  newsockfd;
        char buffer[256];
        int n;
        int clilen;
        struct sockaddr_in cli_addr;

        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);

        timeval timeout;
        timeout.tv_sec = 100;
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
        /* Accept actual connection from the client */
        while (true) {


            if (newsockfd < 0)	{
                if (errno == EWOULDBLOCK)	{
                    cout << "timeout!" << endl;
                    exit(2);
                }	else	{
                    perror("other error");
                    exit(3);
                }
            }
            ar1->getClientHandler()->handleClient(newsockfd);

            int clilen;
            struct sockaddr_in cli_addr;

            clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        }


    }
};

#endif //STONE2_SERIAL_SERVER_H
