#include <iostream>
#include "Test.h"
#include "NetworkException.h"


int main(){
    try {
        testTCPServer();
    }catch (NetworkException e){
        std::cout << e.getInfo() << " : "<<e.getErrno() << std::endl;
    }
}