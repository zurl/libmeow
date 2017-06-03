//
// Created by 张程易 on 03/06/2017.
//

#ifndef MEOW_HTTPRESPONSEHEADER_H
#define MEOW_HTTPRESPONSEHEADER_H

#include "HTTPHeader.h"

class HTTPResponseHeader : public HTTPHeader{
    int code;
    std::string message;
public:
    HTTPResponseHeader() {}

    int getCode() const {
        return code;
    }

    void setCode(int code) {
        HTTPResponseHeader::code = code;
    }

    const std::string &getMessage() const {
        return message;
    }

    void setMessage(const std::string &message) {
        HTTPResponseHeader::message = message;
    }


};

#endif //MEOW_HTTPRESPONSEHEADER_H
