#include "jobthread.h"

JobThread::JobThread(Core *core,QObject *parent)
    :QThread(parent)
{
    this->core = core;
}

JobThread::~JobThread()
{

}

void JobThread::run()
{

}
