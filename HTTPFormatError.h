//
// Created by 张程易 on 02/06/2017.
//

#ifndef MEOW_HTTPFORMATERROR_H
#define MEOW_HTTPFORMATERROR_H


#include <string>

class HTTPFormatError {
    std::string info;
public:
    HTTPFormatError(const std::string &info);
};


#endif //MEOW_HTTPFORMATERROR_H
