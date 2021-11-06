#include<iostream>
#include<cstdlib>
#include"utils/clientSocket.h"

using namespace std;

int main(){
    int res = 0;
    ClientSocket mySocket;
    res = mySocket.createSocketConnection("127.0.0.1", 8788);
    // for(int i = 0; i < 5; i++){
    mySocket.sendMessage("Hi there123");
    // }
    // cout << res << '\n';
    return 0;
}