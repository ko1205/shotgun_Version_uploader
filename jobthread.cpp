#include "jobthread.h"

JobThread::JobThread(QObject *parent)
    :QThread(parent)
{

}

JobThread::~JobThread()
{

}

void JobThread::run()
{
    int count;
    status = true;
    while (status) {
        qDebug() << "ThreadRun" << count;
        count++;
    }
    qDebug() << "run Process";
}
