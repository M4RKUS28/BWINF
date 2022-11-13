#include "workerthread.h"

WorkerThread::WorkerThread()
{
    iteration = 0;
}

WorkerThread::~WorkerThread()
{
    requestInterruption();
    this->quit();
    this->wait(4000);
}

void WorkerThread::startThread(ZinkImage *img)
{
    if(this->isRunning() || !img)
        return;

    this->img = img;
    this->start();
}

void WorkerThread::run()
{
    while(!img->isFinished() && !isInterruptionRequested()) {

        img->calcNextIteration();
        if( iteration % 1 == 0) {
            iteration = 0;
            img->updateImage();
            emit finishedNewImg();
        } else
            iteration++;
        usleep(50000);
    }
    emit finishedAllImages();
}
