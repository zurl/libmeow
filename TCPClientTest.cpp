//
// Created by 张程易 on 30/05/2017.
//


#include "TCPClient.h"
#include <errno.h>
void testTCPClient(){
    TCPClient client("www.baidu.com", "80");
    char buf[1024];

    client.onRead([&client, buf](void * data){
        putchar('%');
        char * str = (char *) data;
        for(int i = 0; i < 32; i++) putchar(*(str + i));
        putchar('\n');
        client.read();
    });

    client.onWrite([&client](){
        putchar('%');
        client.read();
    });

    client.connect();
    //client.read();
    while(true){
        char c;
        char * ptr = buf;
        while((c=getchar())!='?')*ptr++ = c;
        client.write((void *)buf, strlen(buf));
        if(buf[0] == '?')break;
    }
    return;
}