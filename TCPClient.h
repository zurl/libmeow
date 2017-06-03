//
// Created by 张程易 on 30/05/2017.
//

#ifndef MEOW_TCPCLIENT_H
#define MEOW_TCPCLIENT_H


#include <string>
#include <netdb.h>
#include <functional>
#include <aio.h>

class TCPClient {
    friend void tcpClientReadHandler(union sigval context);
    friend void tcpClientWriteHandler(union sigval context);
    static struct addrinfo * hint;
    struct addrinfo * addr;
    int socket = -1;
    std::function<void(void *)> on_read = nullptr;
    std::function<void()> on_write = nullptr;
    std::function<void()> on_read_error = nullptr, on_write_error = nullptr;
    void * read_buffer = nullptr;
    size_t read_buffer_size = 4096;
public:
    TCPClient(const std::string & address, const std::string & port);
    TCPClient & connect();
    TCPClient & close();
    TCPClient & read();
    TCPClient & write(void * data, size_t size);
    TCPClient & onRead(std::function<void(void * data)> callback, std::function<void()> error = nullptr);
    TCPClient & onWrite(std::function<void()> callback, std::function<void()> error = nullptr);
    TCPClient & setReadBufferSize(size_t size);
    virtual ~TCPClient();

};


#endif //MEOW_TCPCLIENT_H
