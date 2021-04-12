#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread();
    ~MyThread(){};

    void run();

signals:
    void send(bool);
};

#endif // MYTHREAD_H
