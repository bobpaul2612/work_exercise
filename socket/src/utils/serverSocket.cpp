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
    close(socketfd);
}

int ServerSocket::startSocketServer(const char* ip_addr, int port){
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
    
    addNewClientSocket(); 
    do{
        printf("%s\n",getClientMsg());
        sleep(3);
    }while(clientSockets.size() > 0);
    return 0;
}

int ServerSocket::addNewClientSocket(){
    int newClient = -1;
    listen(socketfd, 5);
    newClient = accept(socketfd, NULL, NULL);

    clientSockets.push_back(newClient);

    return newClient;
}

char* ServerSocket::getClientMsg(){
    int i = 0;
    int received = -1;

    char *clientRes = (char*)malloc(256 * sizeof(char));
    char *fullClientRes = (char*)malloc(256 * sizeof(char));

    do {
        *fullClientRes = '\0';
        do{
            *clientRes = '\0';
            received = recv(clientSockets[0], clientRes, sizeof(clientRes), 0);
            printf("%d : %s\n", received, clientRes);
            if(received > 0){
                strcat(fullClientRes, strcat(clientRes, " "));
            }
            
        } while (received > 0);
        i++;
    } while (*fullClientRes == '\0' && i < 1);
    
    return fullClientRes;
}

// char *checkNewMessage(int clients_sockets[])
// {
//     int i = 0;
//     int received;
//     char *client_response = NULL;
//     char *full_client_response = NULL;

//     client_response = malloc(256 * sizeof(char));
//     full_client_response = malloc(256 * sizeof(char));


//     do {
//         *full_client_response = '\0';
//         do {
//             *client_response = '\0';
//             received = recv(clients_sockets[i], client_response,sizeof(client_response),0);
//             if (received > 0){
//                 strcat(full_client_response, strcat(client_response, " "));
//             }
//         } while (received > 0);
//         i++;
//     } while ((i<3) && (*full_client_response == '\0'));
//     return full_client_response;
// }