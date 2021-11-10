#ifndef SERVER_SOCKET
#define SERVER_SOCKET
#include<vector>
using namespace std;
#define MAX_CLIENT_SOCKET 3

class ServerSocket{
    private:
        int socketfd = 0;
        vector<int> clientSockets;
    public:
        ~ServerSocket();
        int startSocketServer(const char* ip_addr, int port);
        int addNewClientSocket();
        char* getClientMsg();
};


#endif