#ifndef SERVER_SOCKET
#define SERVER_SOCKET

#include<vector>
#include<netinet/in.h>

using namespace std;
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT_SOCKET 10


class ServerSocket{
    private:
        int masterSocket = 0;
        vector<int> clientSockets;
    public:
        ServerSocket():clientSockets(MAX_CLIENT_SOCKET, 0){}
        ~ServerSocket();
        int startSocketServer(const char* ip_addr, int port);
        int addNewClientSocket(sockaddr_in serverInfo);
        void getClientMsg(fd_set readFds);
};


#endif