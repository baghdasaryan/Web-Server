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
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>   /* for the waitpid() system call */
#include <signal.h>     /* signal name macros, and the kill() prototype */




#include <string>
#include "utils.h"
#include "config.h"


#include "server.h"


int main(int argc, char *argv[])
{

    Server server(PORT_NUMBER);
    server.start();



}
