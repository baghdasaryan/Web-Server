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


#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>	/* for the waitpid() system call */
#include <signal.h>	/* signal name macros, and the kill() prototype */


#define PORT 2048


#include <string>
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

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}


void dostuff (int sock)
{
   int n;
   char buffer[256];
      
   bzero(buffer,256);
   n = read(sock,buffer,255);
   if (n < 0) error("ERROR reading from socket");
   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);
   if (n < 0) error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    struct sigaction sa;          // for signal SIGCHLD

/*    // Check if port number was provided
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    portno = atoi(argv[1]);
*/
    portno = PORT;

    // open a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd,5);

    clilen = sizeof(cli_addr);

    /****** Kill Zombie Processes ******/
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    /*********************************/

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
    } /* end of while */
    return 0; /* we never get here */
}

std::string getFileName(const std::string &request)
{
    return "";
}
