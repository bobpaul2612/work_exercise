#ifndef CLIENT_SOCKET
#define CLIENT_SOCKET
using namespace std;

class ClientSocket{
    private:
        int socketfd = 0;
    public:
        ~ClientSocket();
        int createSocketConnection(const char* ip_addr, int port);
        int sendMessage(const char* msg);
};

#endif