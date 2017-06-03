#include <iostream>
#include "Test.h"
#include "NetworkException.h"
#include "HTTP/HTTPServer.h"

int main(){
    try {
        HTTPServer httpServer("0.0.0.0", "12345");
        httpServer.onRecv([](HTTPContext & ctx){
            ctx.getResponse()->appendBody(ctx.getRequest()->getHeader().getPath());
        });
        httpServer.listen();
    }catch (NetworkException e){
        std::cout << e.getInfo() << " : "<<e.getErrno() << std::endl;
    }
}