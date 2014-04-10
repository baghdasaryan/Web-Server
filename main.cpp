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


#include <iostream>

#include "server.h"


void displayHelp();

int main(int argc, char *argv[])
{
    int portNum = -1;
    string dir = "";
    for (int c; (c = getopt (argc, argv, "p:d:h")) != -1; ) {
        switch (c) {
            case 'p':
                portNum = atoi(optarg);
                break;
            case 'd':
                dir = optarg;
                break;
            case 'h':
                displayHelp();
                return 0;
                break;
            case '?':
                if (optopt == 'p' || optopt == 'd')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                fprintf("\nPlease see help (./server -h).\n");
            default:
                break;
    }

    fprintf("\n P = %d", portNum);
    fprintf("\n D = %s", dir);

    Server server(portNum == -1? PORT_NUMBER : portNum);
    server.start();
}

void displayHelp()
{
    std::cout << "C++ Web-Server" << std::endl;

    std::cout << "Usage:" << std::endl;
    std::cout << "    ./server --- Start Web-Server on the default port (2048)" << std::endl;
    std::cout << "    ./server -p PORT_NUMBER --- Start server on port PORT_NUMBER" << std::endl;
    std::cout << "    ./server -d DIRECTORY --- Change file directory to DIRECTORY" << std::endl;
    std::cout << "    ./server -h --- Show this message" << std::endl;

    std::cout << "\nAuthor:" << std::endl;
    std::cout << "    Georgi Baghdasaryan" << std::endl;
}
