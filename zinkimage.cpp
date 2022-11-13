#include "zinkimage.h"
#include <random>
#include <QPainter>
#include <iostream>



ZinkImage::ZinkImage(int width, int height)
    : finished(false), iteration(0)
{
    size = QSize(width, height);
    mutexImg = new QMutex;
    mutexMap = new QMutex;

    this->image = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);

    imgMap = new Pixel *[height];
    for(int y = 0; y < height; y++) {
        imgMap[y] = new Pixel [width];
        for(int x = 0; x < width; x++ )
            imgMap[y][x] = Pixel();
    }


}

#include <chrono>

void ZinkImage::calcNextIteration()
{
    QMutexLocker locker(mutexMap);

    bool edited = false;
//    std::default_random_engine generator;
//    std::uniform_int_distribution<int> distribution(1,15);

    for(int y = 0; y < size.height(); y++) {
        for(int x = 0; x < size.width(); x++) {
            if( !imgMap[y][x].isEmpty() && imgMap[y][x].iterationNum != iteration && iteration % imgMap[y][x].crystal->wO == 0 && (y-1) >= 0 && imgMap[y - 1][x].isEmpty() ) {
                imgMap[y-1][x].setCrystal( imgMap[y][x].crystal, iteration);
                edited = true;
            }
        }
    }

    for(int y = 0; y < size.height(); y++) {
        for(int x = 0; x < size.width(); x++) {
            if( !imgMap[y][x].isEmpty() && imgMap[y][x].iterationNum != iteration && iteration % imgMap[y][x].crystal->wU == 0 && (y+1) < size.height() && imgMap[y + 1][x].isEmpty()) {
                imgMap[y+1][x].setCrystal( imgMap[y][x].crystal, iteration );
                edited = true;
            }
        }
    }


    for(int y = 0; y < size.height(); y++) {
        for(int x = 0; x < size.width(); x++) {
            if( !imgMap[y][x].isEmpty() && imgMap[y][x].iterationNum != iteration && iteration % imgMap[y][x].crystal->wL == 0 && (x-1) >= 0 && imgMap[y][x - 1].isEmpty()) {
                imgMap[y][x-1].setCrystal( imgMap[y][x].crystal, iteration );
                edited = true;
            }
        }
    }


    for(int y = 0; y < size.height(); y++) {
        for(int x = 0; x < size.width(); x++) {
            if( !imgMap[y][x].isEmpty() && imgMap[y][x].iterationNum != iteration && iteration % imgMap[y][x].crystal->wR == 0 && (x+1) < size.width() && imgMap[y][x + 1].isEmpty()) {
                imgMap[y][x+1].setCrystal( imgMap[y][x].crystal, iteration );
                edited = true;
            }
        }
    }

    iteration++;

    if(!edited)
        finished = true;
}



void ZinkImage::updateImage()
{
    QMutexLocker locker1(mutexImg);
    QMutexLocker locker2(mutexMap);

    QPainter painter(this->image);

    for( int y = 0; y < size.height(); y++ ) {
        for( int x = 0; x < size.width(); x++ ) {
            painter.setPen(QPen(imgMap[y][x].getColor()));
            painter.drawPoint( x ,y );
        }
    }
    painter.end();

}

bool ZinkImage::isFinished()
{
    return finished;
}


QImage ZinkImage::getImage() const
{
    QMutexLocker locker(mutexImg);
    return *image;
}

QSize ZinkImage::getSize()
{
    return size;
}

void ZinkImage::addStartPoint(QPoint p, int wU, int wO, int wR, int wL, QColor color)
{
    Crystal * crystal = new Crystal(wU, wO, wR, wL, color);
    crystals.append(crystal);

    QMutexLocker locker(mutexMap);

    if(p.x() >= 0 && p.x() < size.width() && p.y() >= 0 && p.y() < size.height())
        this->imgMap[p.y()][p.x()].setCrystal( crystal, -1 );


}
