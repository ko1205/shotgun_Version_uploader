#ifndef JOBTHREAD_H
#define JOBTHREAD_H

#include <QThread>
#include <QDebug>

class JobThread : public QThread
{
    Q_OBJECT
public:
    bool status;

    JobThread(QObject *parent = 0);
    ~JobThread();

private:
    void run() override;
};

#endif // JOBTHREAD_H
