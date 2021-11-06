#ifndef CLIENT_SOCKET
#define CLIENT_SOCKET
using namespace std;

class Client_socket{
    private:
        int socketfd = 0;
    public:
        ~Client_socket();
        int create_socket_connection(const char* ip_addr, int port);
        int send_message(const char* msg);
};

#endif