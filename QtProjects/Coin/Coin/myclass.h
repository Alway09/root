#ifndef MYCLASS_H
#define MYCLASS_H
#include <QObject>

class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass();
    ~MyClass(){}

public slots:
    void doWork();
    void setrunning(bool running);

signals:
    void send(bool);
    void finished();
    void runningChanged(bool running);

private:
    bool m_running;
};

#endif // MYCLASS_H
