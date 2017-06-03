//
// Created by 张程易 on 30/05/2017.
//

#include "NetworkException.h"


NetworkException::NetworkException(const std::string &info, int err) : info(info), err(err) {}

const std::string &NetworkException::getInfo() const {
    return info;
}

int NetworkException::getErrno() const {
    return err;
}
