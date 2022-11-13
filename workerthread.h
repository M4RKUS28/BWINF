#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>
#include "zinkimage.h"



class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread();
    ~WorkerThread();

    void startThread(ZinkImage * img);


    unsigned iteration;
private:

    void run();
    ZinkImage * img;



signals:
    void finishedNewImg();
    void finishedAllImages();




};

#endif // WORKERTHREAD_H
