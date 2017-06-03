//
// Created by 张程易 on 30/05/2017.
//

#ifndef MEOW_NETWORKEXCEPTION_H
#define MEOW_NETWORKEXCEPTION_H


#include <string>

class NetworkException {
    std::string info;
    int err;
public:
    NetworkException(const std::string &info, int err);

    const std::string &getInfo() const;

    int getErrno() const;
};


#endif //MEOW_NETWORKEXCEPTION_H
