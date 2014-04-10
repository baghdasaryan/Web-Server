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


#include <stdio.h>
#include <stdlib.h>
#include <string>


// Function Definitions
static void error(std::string err);
static void toLowerCase(std::string &str);


// Function Implementations

static void error(std::string err)
{
    perror(err.c_str());
    exit(1);
}

static void toLowerCase(std::string &str)
{
    for (size_t i = 0; i < str.length(); i++)
        str[i] = std::tolower(str[i]);

}


#endif  // __UTILS_H__
