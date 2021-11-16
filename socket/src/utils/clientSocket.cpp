#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<thread>
#include <charconv>
#include<mutex>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"clientSocket.h"

using namespace std;


ClientSocket::~ClientSocket(){
    close(socketfd);
}

int ClientSocket::createSocketConnection(const char* ip_addr, int port){
    socketfd = socket(AF_INET,  SOCK_STREAM, 0);

    if(socketfd == -1){
        printf("Fail to create a socket.");
    }

    sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(ip_addr);
    info.sin_port = htons(port);

    int err = connect(socketfd,(struct sockaddr *)&info, sizeof(info));
    if(err == -1){
        printf("Connection error");
    }

    return socketfd;
}

int ClientSocket::sendMessage(const char* msg){

    char *sendMsg = (char*)malloc(256 * sizeof(char));
    int len = (int)strlen(msg);

    for(int i = 0; i < MSG_TIMES; i++){
        bzero(sendMsg, 256);
        array<char, 64> num;
        
        lock.lock();
        to_chars(num.data(), num.data() + num.size(), msgIdx++);
        lock.unlock();

        strcat(sendMsg, msg);
        
        strcat(sendMsg, num.data());


        
        write(socketfd, sendMsg, strlen(sendMsg));
        sleep(1);
    }

    close(socketfd);
    return socketfd;

//     for(int i = 0; i < 10; i++)
//         printf("%d: \"%s\"\n", (int)strlen(msg), msg);
//     printf("send \"%s\" finish\n\n", msg);
//     return 0;
}

