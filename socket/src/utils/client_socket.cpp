#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"client_socket.h"

using namespace std;

Client_socket::~Client_socket(){
    close(socketfd);
}

int Client_socket::create_socket_connection(const char* ip_addr, int port){
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

int Client_socket::send_message(const char* msg){
    send(socketfd, msg, sizeof(msg), 0);
}