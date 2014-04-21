// ######################################### //
// ######################################### //
// ####                                 #### //
// #### Program: C++ Web-Server         #### //
// #### Language: C++                   #### //
// #### Author: Georgi Baghdasaryan     #### //
// #### Email: baghdasaryan@ucla.edu    #### //
// ####                                 #### //
// ######################################### //
// ######################################### //


#ifndef __SERVER_H__
#define __SERVER_H__


#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <sys/wait.h>   /* for the waitpid() system call */
#include <signal.h>     /* signal name macros, and the kill() prototype */
#include <iostream>
#include <fstream>

#include "config.h"
#include "utils.h"


static void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

class Server
{
    public:
        Server(int port, std::string webdir);
        void start();

    private:
        int m_portNum;
        std::string m_webdir;

        // Socket stuff
        int sockfd, newsockfd, portno;
        sockaddr_in serv_addr, cli_addr;
        pid_t pid;
        socklen_t clilen;
        struct sigaction sa;          // for signal SIGCHLD

        void setup();
        bool checkPortNum();
        void requestHandler(int sock);
};


#endif  // __SERVER_H__
