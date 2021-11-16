#ifndef SERVER_SOCKET
#define SERVER_SOCKET

#include<vector>
#include<netinet/in.h>
#include<thread>

using namespace std;
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT_SOCKET 10

struct getSocket
{
    int i;
    fd_set readFds;
    getSocket(int i, fd_set readFds) : i(i), readFds(readFds){}
};


class ServerSocket{
    private:
        int masterSocket = 0;
        vector<int> clientSockets;
        thread threads[MAX_CLIENT_SOCKET] = {};
        
    public:
        ServerSocket():clientSockets(MAX_CLIENT_SOCKET, 0){}
        ~ServerSocket();
        int startSocketServer(const char* ip_addr, int port);
        int addNewClientSocket(sockaddr_in serverInfo, fd_set readFds);
        int getClientMsg(getSocket *readFds);
};


#endif