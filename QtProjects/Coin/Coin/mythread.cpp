#include "mythread.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

MyThread::MyThread(){}

void MyThread::run(){
    long sleepTime(100000);
    std::srand(std::time(NULL));
    while(true){
        if(std::rand() % 2){
            emit send(true);
        }else{
            emit send(false);
        }
        QThread::usleep(sleepTime);

        if(sleepTime > 15000){
            sleepTime -= 10000;
        } else if(sleepTime > 1000){
            sleepTime -= 100;
        } else if(sleepTime > 100){
            sleepTime -= 5;
        } else if(sleepTime > 1){
            --sleepTime;
        }
    }
}
