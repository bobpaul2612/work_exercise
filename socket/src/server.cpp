#include<iostream>
#include<cstdlib>
#include"utils/server_socket.h"

using namespace std;

int main(){
    int res = 0;
    Server_socket my_server;
    my_server.start_socket_server("127.0.0.1", 8788);
    return 0;
}