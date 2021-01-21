#ifndef JOBTHREAD_H
#define JOBTHREAD_H

#include <QThread>
#include <QDebug>
#include "core.h"

class JobThread : public QThread
{
    Q_OBJECT
public:
    JobThread(Core *core ,QObject *parent = 0);
    ~JobThread();

private:
    void run() override;
    Core *core;
};

#endif // JOBTHREAD_H
