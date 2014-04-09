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


#include "config.h"
#include "utils.h"


/*
int pid = fork();
if (pid < 0) {
    // Fork failed
    error("ERROR on fork");
    exit(1);
}
else if (pid == 0) {
    // Child process

}
else {
    // Parent process

}
*/

class Server
{
    public:
        Server(int port)
        {
            m_portNum = port;
        }

//        ~Server() { }

//        void getFile() { }
        void start()
        {
            setup();

    /****** Kill Zombie Processes ******/
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    /*********************************/
    clilen = sizeof(cli_addr);
            while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        pid = fork(); //create a new process
        if (pid < 0)
            error("ERROR on fork");

        if (pid == 0)  { // fork() returns a value of 0 to the child process
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else //returns the process ID of the child process to the parent
            close(newsockfd); // parent doesn't need this 
            }
        }

        void setup()
        {
            // Create a socket
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) 
                error("ERROR opening socket");

            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = INADDR_ANY;
            serv_addr.sin_port = htons(m_portNum);

            if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
                error("ERROR on binding");

            // Check the port number
            if (!checkPortNum())
                error("ERROR socket port number mismatch");

            listen(sockfd, NUM_CONNECTIONS);

        }

        bool checkPortNum()
        {
            // Verify that the socket port number is same as the given one
            sockaddr_in testSock;
            socklen_t testLen = sizeof(testSock);
            int curPortNum = getsockname(sockfd, ( struct sockaddr * )&testSock, &testLen);
            if (curPortNum != 0)
                error("ERROR obtaining checking port number");
            else if (ntohs(testSock.sin_port) != m_portNum)
                return false;
            return true;
        }

    private:
        int m_portNum;

        // Socket stuff
        int sockfd, newsockfd, portno;
        sockaddr_in serv_addr, cli_addr;



    pid_t pid;
    socklen_t clilen;
    struct sigaction sa;          // for signal SIGCHLD
};


#endif  // __SERVER_H__
