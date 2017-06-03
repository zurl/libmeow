cmake_minimum_required(VERSION 3.6)
project(meow)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        TCPClient.cpp
        TCPClientTest.cpp
        Main.cpp
        NetworkException.cpp
        TCPServer.cpp
        TCPServerTest.cpp
        HTTPRequestHeader.h
        HTTPHeader.h
        HTTPServer.h
        HTTPFormatError.cpp
        HTTPMethod.h
        StringUtil.h
        HTTPRequest.h HTTPContext.h HTTPResponse.h HTTPResponseHeader.h)
add_executable(meow ${SOURCE_FILES})