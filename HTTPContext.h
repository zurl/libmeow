//
// Created by 张程易 on 03/06/2017.
//

#ifndef MEOW_HTTPCONTEXT_H
#define MEOW_HTTPCONTEXT_H

#include "HTTPRequest.h"

class HTTPContext{
    friend class HTTPServer;
    HTTPRequest * httpRequest = nullptr;
    //HTTPRequest * httpRequest = nullptr;
    char * buffer = nullptr;
    int now = 0;
    bool append(const char * buf, int len){
        if(buffer != nullptr){
            memcpy(buffer + now, buf, len);
            for(int i = std::max(0, now - 4); i + 3 < now + len; i++){
                if(strncmp(buffer + i, "\r\n\r\n", 4) == 0){
                    httpRequest = new HTTPRequest(buffer);
                    bool ret = httpRequest->appendBody(buffer + i + 4, now + len - i);
                    delete[] buffer;
                    buffer = nullptr;
                    return ret;
                }
            }
            return false;
        }
        else{
            return httpRequest->appendBody(buf, len);
        }
    }
public:
    HTTPContext() {
        buffer = (char * )malloc(1024);
    }
    ~HTTPContext(){
        if(buffer != nullptr)delete[] buffer;
        if(httpRequest != nullptr) delete httpRequest;
    }

};

#endif //MEOW_HTTPCONTEXT_H
