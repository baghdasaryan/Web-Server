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


#ifndef __CONFIG_H__
#define __CONFIG_H__


#include <string>


#define PORT_NUMBER 2048
#define NUM_CONNECTIONS 5
#define BUFFER_SIZE 32768 // 2^15
#define WEB_DIRECTORY "."

// Errors
const std::string ERR_404 = "404 Not Found";


#endif  // __CONFIG_H__
