#ifndef SERVER_SOCKET
#define SERVER_SOCKET
using namespace std;
#define MAX_CLIENT_SOCKET 3

class ServerSocket{
    private:
        int socketfd = 0;
        int clientSocket[MAX_CLIENT_SOCKET];
    public:
        ~ServerSocket();
        int startSocketServer(const char* ip_addr, int port);
        int addNewClientSocket();
        char* getClientMsg();
};


#endif