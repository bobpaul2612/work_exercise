#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
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
    listen(socketfd, 5);

    for(int i = 0; i < MAX_CLIENT_SOCKET;){
        clientSocket[i] = addNewClientSocket();
        
    }

    // for_clientfd = accept(socketfd, (struct sockaddr*) &client_info, &addrlen);
    // while(1){
    //     recv(for_clientfd, input_buffer, sizeof(input_buffer), 0);
    //     printf("Get:%s\n",input_buffer);
    //     // close(for_clientfd);
    // }

    return 0;
}

int ServerSocket::addNewClientSocket(){
    int newClient = -1;
    listen(socketfd, 5);
    newClient = accept(socketfd, NULL, NULL);

    return newClient;
}

char* ServerSocket::getClientMsg(){
    int i = 0;
    int received = -1;
    char receiveMsg[256] = {};

    while(i<3){
        // received = recv()
    }

    // receiveMsg = recv(clientSocket, )
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