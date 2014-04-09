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

void error(std::string err)
{
    perror(err.c_str());
    exit(1);
}

#endif  // __UTILS_H__
