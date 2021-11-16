#ifndef SERVER_SOCKET
#define SERVER_SOCKET

#include<vector>
#include<netinet/in.h>
#include<thread>

using namespace std;
#define MAX_CLIENT_SOCKET 10

// struct getSocket
// {
//     int i;
//     fd_set readFds;
//     getSocket(int i, fd_set readFds) : i(i), readFds(readFds){}
// };


class ServerSocket{
    private:
        int masterSocket = 0;
        int maxSd = 0;
        fd_set readFds;
        vector<int> clientSockets;
        thread threads[MAX_CLIENT_SOCKET] = {};
    public:
        ServerSocket():clientSockets(MAX_CLIENT_SOCKET, 0){}
        ~ServerSocket();
        int startSocketServer(const char* ip_addr, int port);
        int addNewClientSocket(sockaddr_in serverInfo);
        int getClientMsg(int i);
};


#endif