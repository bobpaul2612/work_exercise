#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"server_socket.h"

using namespace std;

Server_socket::~Server_socket(){
    close(socketfd);
}

int Server_socket::start_socket_server(const char* ip_addr, int port){
    char input_buffer[256] = {};
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socketfd == -1){
        printf("Fail to create a socket.");
    }

    sockaddr_in server_info, client_info;
    unsigned int addrlen = sizeof(client_info);
    bzero(&server_info, sizeof(server_info));

    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(port);
    bind(socketfd, (struct sockaddr *)&server_info, sizeof(server_info));
    listen(socketfd, 5);

    while(1){
        for_clientfd = accept(socketfd, (struct sockaddr*) &client_info, &addrlen);
        recv(for_clientfd, input_buffer, sizeof(input_buffer), 0);
        printf("Get:%s\n",input_buffer);
    }

    return 0;
}