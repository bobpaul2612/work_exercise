#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<functional>
#include<thread>
#include<time.h>
#include"serverSocket.h"

using namespace std;

ServerSocket::~ServerSocket(){
    close(masterSocket);
}

int ServerSocket::start(const char* ip_addr, int port){
    int opt = true;
    char input_buffer[256] = {};
    int sd, activity;
    sockaddr_in server_info, client_info;
    fd_set readFd;

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

    while(true){
        FD_ZERO(&readFd);
        FD_SET(masterSocket, &readFd);

        activity = select(masterSocket + 1, &readFd, NULL, NULL, NULL);
        if((activity < 0) && (errno!=EINTR)){
            printf("select error");
        }

        if(FD_ISSET(masterSocket, &readFd)){
            int i = addNewClientSocket(server_info);
            threads[i] = thread(bind(&ServerSocket::getClientMsg, this, i));
            threads[i].detach();
        }
        
    }
   
    return 0;
}

int ServerSocket::addNewClientSocket(sockaddr_in serverInfo){
    int newClient = -1, i;
    if((newClient = accept(masterSocket, 
        (struct sockaddr *)&serverInfo, (socklen_t*)&serverInfo)) < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < MAX_CLIENT_SOCKET; i++){
        if(clientSockets[i] == 0){
            clientSockets[i] = newClient;
            break;
        }
    }
    
    return i;
}

int ServerSocket::getClientMsg(int i){
    int sd = clientSockets[i];
    timeval timeout={3,0};
    int received = 0;
    char *clientMsg = new char[256];
    char *resMsg = new char[256];
    fd_set readFd;

    FD_ZERO(&readFd);
    FD_SET(sd, &readFd);

    while(true){
        select(sd + 1, &readFd, NULL, NULL, NULL);

        if(FD_ISSET(sd, &readFd)){
            if((received = read(sd, clientMsg, sizeof(clientMsg))) == 0){
                close(sd);
                clientSockets[i] = 0;
                return 0;
            }
            else{
                char *p;
                p = find(clientMsg, clientMsg + received, '$');
                if(p != clientMsg + received){
                    strncat(resMsg, clientMsg, (int)(p - clientMsg));
                    printf("cliID : %d, Msg : \"%s\" \n", sd, resMsg);
                    if(p + 1 != clientMsg + received)
                        strcpy(resMsg, p + 1);
                    else
                        bzero(resMsg, sizeof(resMsg));
                }else{
                    strcat(resMsg, clientMsg);
                }
            }
        }      
    }
    
    free(clientMsg);
    free(resMsg);

    return 1;
}

/* 
1.斷線 error handler
2.use select  V
3.命名
4.有使用到 new 的都要清掉 (or unique_ptr)
*/