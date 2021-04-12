#include "myclass.h"
#include <QThread>
#include <iostream>

MyClass::MyClass() : QObject(), m_running(true){}

void MyClass::doWork(){
    long sleepTime(100000);
    std::srand(std::time(NULL));
    m_running = true;
    while(m_running){
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
    emit finished();
}

void MyClass::setrunning(bool running)
{
    m_running = running;
}
