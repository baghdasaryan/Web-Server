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


#include <string>

#include "server.h"
#include "utils.h"


void displayHelp();

int main(int argc, char *argv[])
{
    int portNum = PORT_NUMBER;
    std::string dir = WEB_DIRECTORY;
    for (int c; (c = getopt (argc, argv, "p:d:h")) != -1; ) {
        switch (c) {
            case 'p':
                portNum = atoi(optarg);
                break;
            case 'd':
                dir += optarg;
                fprintf(stdout, "Please make sure that directory %s exists\n", dir.c_str());
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

    Server server(portNum, dir);
    server.start();
}

void displayHelp()
{
    fprintf(stdout, "C++ Web-Server\n");

    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "    ./server --- Start Web-Server on the default port (2048)\n");
    fprintf(stdout, "    ./server -p PORT_NUMBER --- Start server on port PORT_NUMBER\n");
    fprintf(stdout, "    ./server -d /PATH/TO/DIR --- Change file directory to directory ./PATH/TO/DIR\n");
    fprintf(stdout, "    ./server -h --- Show this message\n");

    fprintf(stdout, "\nAuthor:\n");
    fprintf(stdout, "    Georgi Baghdasaryan\n");
}
