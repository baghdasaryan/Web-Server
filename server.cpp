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


Server::Server(int port, std::string webdir)
{
    m_portNum = port;
    m_webdir = webdir;

    setup();
}

void Server::start()
{
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
        requestHandler(newsockfd);
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
    int curPortNum = getsockname(sockfd, (struct sockaddr *) &testSock, &testLen);
    if (curPortNum != 0)
        error("ERROR checking port number");
    else if (ntohs(testSock.sin_port) != m_portNum)
        return false;
    return true;
}

void Server::requestHandler(int sock)
{
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    int n = read(sock, buffer, BUFFER_SIZE - 1);
    if (n < 0) fprintf (stderr, "ERROR reading from socket %d", sock);

    // Print message to the console
    fprintf(stdout, "\n***********************************\n");
    fprintf(stdout, "        Here is the Message        \n");
    fprintf(stdout, "***********************************\n");
    fprintf(stdout, "%s\n", buffer);


    // Get requested file's name
    char *cFileName = strtok(buffer, " ");
    cFileName = strtok(NULL, " ");
    std::string fileName = "";
    fprintf(stdout, "%s", cFileName);
    if (cFileName == NULL || (cFileName[0] == '/' && cFileName[1] == '\0'))
        fileName = "index.html";
    else
        fileName = cFileName;

    fileName = m_webdir + fileName;
    std::ifstream ifs;
    ifs.open(fileName.c_str(), std::ifstream::in);
    if (!ifs.is_open()) {
        std::string msg = "HTTP/1.1 " + ERR_404 + "\r\nContent-Length: 36\r\nContent-Type: text/plain\r\n\r\nSorry, we couldn't find that file.\r\n";
        n = write(sock, msg.c_str(), msg.length());
        if (n < 0) fprintf(stderr, "ERROR writing to socket %d", sock);
        return;
    }

    std::string responseFile = "";
    char c = ifs.get();
    while (ifs.good()) {
        responseFile += c;
        c = ifs.get();
    }
    ifs.close();

    std::string header = "HTTP/1.1 200\r\n";
    if (fileName[0] == '/' && fileName.rfind('.') != std::string::npos) {
        //fileName = fileName.substr(1);
        std::string fileExt = fileName.substr(fileName.rfind('.'));
        toLowerCase(fileExt);

        // Check file extension and stuff like that
        if (fileExt == ".txt")
            header += "Content-Type: text/plain\r\n";
        else if (fileExt == ".html" || fileExt == ".htm")
            header += "Content-Type: text/html; charset=utf-8\r\n";
        else if (fileExt == ".gif")
            header += "Content-Type: image/gif\r\n";
        else if (fileExt == ".jpeg" || fileExt == ".jpg")
            header += "Content-Type: image/jpeg\r\n";
        else if (fileExt == ".png")
            header += "Content-Type: image/png\r\n";
    }
    bzero(buffer, BUFFER_SIZE);
    sprintf(buffer, "%d", (int) (responseFile.length()));
    header += "Content-Length: " + std::string(buffer) + "\r\n\r\n";

    n = write(sock, header.c_str(), header.length());
    if (n < 0) fprintf(stderr, "ERROR writing to socket %d", sock);
    n = write(sock, responseFile.c_str(), responseFile.length());
    if (n < 0) fprintf(stderr, "ERROR writing to socket %d", sock);
}
