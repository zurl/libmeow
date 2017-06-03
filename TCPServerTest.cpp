//
// Created by 张程易 on 01/06/2017.
//

#include "TCPServer.h"
#include "HTTPRequestHeader.h"
#include "HTTPServer.h"

void testTCPServer(){
    HTTPServer httpServer("0.0.0.0", "12345");
    httpServer.listen();
}