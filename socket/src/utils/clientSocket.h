#ifndef CLIENT_SOCKET
#define CLIENT_SOCKET
#include<mutex>
using namespace std;

#define MSG_TIMES 100

class ClientSocket{
    private:
        int socketfd = 0;
        int msgIdx = 1;
        mutex lock;
    public:
        ~ClientSocket();
        int createSocketConnection(const char* ip_addr, int port);
        int sendMessage(const char* msg);
};

#endif