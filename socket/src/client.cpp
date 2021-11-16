#include<cstdlib>
#include<thread>
#include<iostream>
#include<functional>
#include"utils/clientSocket.h"

using namespace std;

int main(){
    int res = 0;
    ClientSocket mySocket;
    res = mySocket.createSocketConnection("127.0.0.1", 8788);
    // mySocket.sendMessage("Hi there : ");

    thread thread01(bind(&ClientSocket::sendMessage, &mySocket, "Hi thread01 : "));
    thread thread02(bind(&ClientSocket::sendMessage, &mySocket, "Hi thread02 : "));
    thread thread03(bind(&ClientSocket::sendMessage, &mySocket, "Hi thread03 : "));

    thread01.join();
    thread02.join();
    thread03.join();

    printf("finish\n");

    // mySocket.sendMsgByThreads();

    return 0;
}