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
    std::string dir = "";
    for (int c; (c = getopt (argc, argv, "p:d:h")) != -1; ) {
        switch (c) {
            case 'p':
                portNum = atoi(optarg);
                break;
            case 'd':
                dir = optarg;
                // TODO: Check directory
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
                fprintf(stderr, "\nPlease see help (./server -h).\n");
            default:
                break;
        }
    }

    Server server(portNum == -1? PORT_NUMBER : portNum);
    server.start();
}

void displayHelp()
{
    fprintf(stdout, "C++ Web-Server\n");

    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "    ./server --- Start Web-Server on the default port (2048)\n");
    fprintf(stdout, "    ./server -p PORT_NUMBER --- Start server on port PORT_NUMBER\n");
    fprintf(stdout, "    ./server -d DIRECTORY --- Change file directory to DIRECTORY\n");
    fprintf(stdout, "    ./server -h --- Show this message\n");

    fprintf(stdout, "\nAuthor:\n");
    fprintf(stdout, "    Georgi Baghdasaryan\n");
}
