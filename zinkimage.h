#ifndef ZINKIMAGE_H
#define ZINKIMAGE_H


#include <QImage>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QPoint>
#include <QList>


struct Crystal {
    Crystal() {}
    Crystal(int wU, int wO, int wR, int wL, QColor color);
    QColor color;
    unsigned orientierung;
    int wU, wO, wR, wL;
};

inline Crystal::Crystal(int wU, int wO, int wR, int wL, QColor color)
{
    this->wU = wU;
    this->wO = wO;
    this->wR = wR;
    this->wL = wL;
    this->color = color;

}


struct Pixel {
    Pixel() {
        crystal = nullptr;
    }

    void setCrystal(Crystal * crystal, unsigned iteration) {
        this->crystal = crystal;
        this->iterationNum = iteration;
    }

    QColor getColor() {
        if(!isEmpty())
            return crystal->color;
        else
            return Qt::white;

    }
    bool isEmpty() {
        return crystal == nullptr;
    }

    unsigned iterationNum;
    Crystal * crystal;
};


class ZinkImage
{
public:
    ZinkImage(int width, int height);


    void calcNextIteration();
    void updateImage();
    bool isFinished();
    QImage getImage() const;
    QList <QPoint> startPoints;
    QSize getSize();

    void addStartPoint(QPoint p, int wU, int wO, int wR, int wL, QColor color);

    Pixel getPixelAt(QPoint p);
private:
    QVector<Crystal*> crystals;
    QImage * image;
    QMutex * mutexImg,
           * mutexMap;
    double grothRates[4];
    Pixel ** imgMap;
    QSize size;
    bool finished;

    size_t iteration;



};

#endif // ZINKIMAGE_H
