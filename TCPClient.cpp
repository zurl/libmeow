//
// Created by 张程易 on 30/05/2017.
//

#include <cstdlib>
#include <memory>
#include "TCPClient.h"
#include "NetworkException.h"
#include <thread>
#include <aio.h>
#include <cstdlib>
#include <unistd.h>

struct Pair{
    TCPClient * client;
    struct aiocb * cb;
    Pair(TCPClient *client, aiocb *cb) : client(client), cb(cb) {}
};

struct addrinfo * TCPClient::hint = nullptr;

void tcpClientReadHandler(union sigval context){
    putchar('/');
    Pair * pair = (Pair * )context.sival_ptr;
    TCPClient * that = pair->client;
    if(aio_error(pair->cb)){
        if( that->on_read_error != nullptr){
            that->on_read_error();
        }
    }else{
        if( that->on_read != nullptr){
            that->on_read(that->read_buffer);
        }
    }
    free(pair->cb);
    free(pair);
}

void tcpClientWriteHandler(union sigval context){
    putchar('k');
    Pair * pair = (Pair * )context.sival_ptr;
    TCPClient * that = pair->client;
    if(aio_error(pair->cb)){
        if( that->on_write_error != nullptr ){
            that->on_write_error();
        }
    }else{
        if( that->on_write != nullptr){
            that->on_write();
        }
    }
    free(pair->cb);
    free(pair);
}


TCPClient::TCPClient(const std::string &address, const std::string &port) {
    if( hint == nullptr){
        hint = (addrinfo *) malloc (sizeof(struct addrinfo));
        memset(hint, 0, sizeof(struct addrinfo));
        hint->ai_socktype = SOCK_STREAM; // allow tcp
        hint->ai_family = AF_UNSPEC; // allow 0.0.0.0
    }
    int ret = getaddrinfo(address.c_str(), port.c_str(), hint, &addr);
    if( ret != 0){
        throw NetworkException("Error at `getaddrinfo`", errno);
    }
    this->read_buffer = malloc(this->read_buffer_size);
}

TCPClient::~TCPClient() {
    if(addr != nullptr) freeaddrinfo(addr);
}

TCPClient & TCPClient::connect() {
    struct addrinfo * addr_ptr = this->addr;
    while(addr_ptr != nullptr){
        this->socket = ::socket(addr_ptr->ai_family, addr_ptr->ai_socktype, addr_ptr->ai_protocol);
        if(this->socket >= 0){
            int ret = ::connect(this->socket, addr_ptr->ai_addr, addr_ptr->ai_addrlen);
            if( ret == 0) break;
        }
        addr_ptr = addr_ptr->ai_next;
    }
    if( this->socket < 0 || addr_ptr == nullptr){
        this->socket = -1;
        throw NetworkException("Error at `socket`", errno);
    }
    return *this;
}


TCPClient & TCPClient::onRead(std::function<void(void *)> callback, std::function<void()> error) {
    this->on_read = callback;
    this->on_read_error = error;
    return *this;
}

TCPClient & TCPClient::onWrite(std::function<void()> callback, std::function<void()> error) {
    this->on_write = callback;
    this->on_write_error = error;
    return *this;
}

TCPClient & TCPClient::close() {
    ::close(this->socket);
    this->socket = -1;
    return *this;
}


TCPClient & TCPClient::write(void * data, size_t size) {
    if( this->socket == -1) {
        throw NetworkException("Error: unopened socket", errno);
    }
    struct aiocb * write_cb = (aiocb *) malloc(sizeof(aiocb));
    write_cb->aio_sigevent.sigev_notify = SIGEV_THREAD;
    write_cb->aio_sigevent.sigev_notify_function = tcpClientWriteHandler;
    write_cb->aio_sigevent.sigev_notify_attributes = NULL;
    write_cb->aio_sigevent.sigev_value.sival_ptr = new Pair(this, write_cb);
    write_cb->aio_fildes = this->socket;
    write_cb->aio_buf = data;
    write_cb->aio_nbytes = size;
    if( ::aio_write(write_cb) < 0){
        throw NetworkException("Error at aiowrite", errno);
    }
    return *this;
}

TCPClient & TCPClient::read() {
    if( this->socket == -1) {
        throw NetworkException("Error: unopened socket", errno);
    }
    if( this->read_buffer == nullptr){
        throw NetworkException("Error: no buffer exist", errno);
    }
    struct aiocb * read_cb = (aiocb *) malloc(sizeof(aiocb));
    read_cb->aio_sigevent.sigev_notify = SIGEV_THREAD;
    read_cb->aio_sigevent.sigev_notify_function = tcpClientReadHandler;
    read_cb->aio_sigevent.sigev_notify_attributes = NULL;
    read_cb->aio_sigevent.sigev_value.sival_ptr = new Pair(this, read_cb);
    read_cb->aio_fildes = this->socket;
    read_cb->aio_buf = this->read_buffer;
    read_cb->aio_nbytes =  this->read_buffer_size;
    if(::aio_read(read_cb) < 0){
        throw NetworkException("Error at aio_read ", errno);
    }
    return *this;
}

TCPClient &TCPClient::setReadBufferSize(size_t size) {
    this->read_buffer_size = size;
    if(this->read_buffer != nullptr){
        free(this->read_buffer);
        this->read_buffer = malloc(size);
    }
    return *this;
}

