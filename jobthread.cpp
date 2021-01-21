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
    status = true;
//    while (status) {
//        qDebug() << "ThreadRun";
//    }
}
