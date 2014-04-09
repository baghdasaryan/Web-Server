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


#ifndef __UTILS_H__
#define __UTILS_H__


#include <string>


// Function Definitions
void error(std::string err);


// Function Implementations

void error(std::string err)
{
    perror(err.c_str());
    exit(1);
}


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


#endif  // __UTILS_H__
