#include<cstdio>
#include<cstdlib>
#include<thread>
#include<iostream>

using namespace std;

void fooc(){
    printf("Inside the thread \n");
}

void fun(){
    thread threadObj(fooc);
    printf("This line may be printed"
           " before thread terminates\n");
    threadObj.join();
    printf("This line will be printed"
            " after thread ends\n");
}

int main(){
    fun();
    return 0;
}
