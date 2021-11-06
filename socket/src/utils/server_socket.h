#ifndef SERVER_SOCKET
#define SERVER_SOCKET
using namespace std;

class Server_socket{
    private:
        int socketfd = 0;
        int for_clientfd = 0;
    public:
        ~Server_socket();
        int start_socket_server(const char* ip_addr, int port);
        // int send_message(const char* msg);
};


#endif