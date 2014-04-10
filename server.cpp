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


#include "server.h"


Server::Server(int port)
{
    m_portNum = port;
}

Server::~Server()
{

}

void Server::start()
{
    setup();

    clilen = sizeof(cli_addr);
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        pid = fork(); //create a new process
        if (pid > 0) {
            close(newsockfd);
            continue;
        }

        close(sockfd);
        processRequest(newsockfd);
        if (pid == 0)
            exit(0);
        else if (pid < 0)
            fprintf(stderr, "Fork failed, parent took care of the connection.");
    }
}

void Server::setup()
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

    /****** Kill Zombie Processes ******/
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    /*********************************/
}

bool Server::checkPortNum()
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

void Server::processRequest(int sock)
{
    int n;
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    n = read(sock, buffer, BUFFER_SIZE - 1);
    if (n < 0) fprintf (stderr, "ERROR reading from socket %d", sock);

    printf("Here is the message: %s\n",buffer);
}

void sendData(int sock)
{
    int n = write(sock, "I got your message", 18);
    if (n < 0) fprintf(stderr, "ERROR writing to socket %d", sock);
}
