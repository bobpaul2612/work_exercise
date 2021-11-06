#include<iostream>
#include<cstdlib>
#include"utils/client_socket.h"

using namespace std;

int main(){
    int res = 0;
    Client_socket my_socket;
    res = my_socket.create_socket_connection("127.0.0.1", 8788);
    my_socket.send_message("Hi there");
    // cout << res << '\n';
    return 0;
}