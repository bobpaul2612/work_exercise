#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"serverSocket.h"

using namespace std;

ServerSocket::~ServerSocket(){
    close(masterSocket);
}

int ServerSocket::startSocketServer(const char* ip_addr, int port){
    int opt = TRUE;
    char input_buffer[256] = {};
    int maxSd, sd, activity;
    sockaddr_in server_info, client_info;
    fd_set readFds;

    unsigned int addrlen = sizeof(client_info);
    bzero(&server_info, sizeof(server_info));

    if((masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    

    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = inet_addr(ip_addr);
    server_info.sin_port = htons(port);
    if(bind(masterSocket, (struct sockaddr *)&server_info, sizeof(server_info)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if(listen(masterSocket, 5) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(TRUE){
        FD_ZERO(&readFds);

        FD_SET(masterSocket, &readFds);
        maxSd = masterSocket;

        for(int i = 0; i < MAX_CLIENT_SOCKET; i++){
            sd = clientSockets[i];

            if(sd > 0)
                FD_SET(sd, &readFds);
            if(sd > maxSd)
                maxSd = sd;
        }

        activity = select(maxSd + 1, &readFds, NULL, NULL, NULL);
        if((activity < 0) && (errno!=EINTR)){
            printf("select error");
        }

        if(FD_ISSET(masterSocket, &readFds)){
            addNewClientSocket(server_info);
        }

        getClientMsg(readFds);
    }
    // addNewClientSocket(); 
    // do{
    //     getClientMsg();
    //     sleep(3);
    // }while(clientSockets.size() > 0);
    return 0;
}

int ServerSocket::addNewClientSocket(sockaddr_in serverInfo){
    int newClient = -1;

    if((newClient = accept(masterSocket, 
        (struct sockaddr *)&serverInfo, (socklen_t*)&serverInfo)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_CLIENT_SOCKET; i++){
        if(clientSockets[i] == 0){
            clientSockets[i] = newClient;
            break;
        }
    }

    return newClient;
}

void ServerSocket::getClientMsg(fd_set readFds){
    int sd, received;
    char *clientMsg = (char*)malloc(256 * sizeof(char));

    for(int i = 0; i < MAX_CLIENT_SOCKET; i++){
        sd = clientSockets[i];
        if(FD_ISSET(sd, &readFds)){
            if((received = read(sd, clientMsg, sizeof(clientMsg))) == 0){
                close(sd);
                clientSockets[i] = 0;
            }
            else{
                clientMsg[received] = '\0';
                printf("cliID : %d, Msg : %s \n", sd, clientMsg);
            }
        }
    }
    
}

