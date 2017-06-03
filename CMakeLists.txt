cmake_minimum_required(VERSION 3.6)
project(meow)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Main.cpp
        NetworkException.cpp
        TCP/TCPServer.cpp
        HTTP/HTTPRequestHeader.h
        HTTP/HTTPHeader.h
        HTTP/HTTPServer.h
        HTTP/HTTPFormatError.cpp
        HTTP/HTTPMethod.h
        StringUtil.h
        HTTP/HTTPRequest.h HTTP/HTTPContext.h HTTP/HTTPResponse.h HTTP/HTTPResponseHeader.h)
add_executable(meow ${SOURCE_FILES})