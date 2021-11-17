#include<iostream>
#include<cstdlib>
#include"utils/serverSocket.h"

using namespace std;

int main(){
    int res = 0;
    ServerSocket myServer;
    myServer.start("127.0.0.1", 8788);
    return 0;
}