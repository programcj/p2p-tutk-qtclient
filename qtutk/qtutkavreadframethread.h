#ifndef QTUTKAVREADFRAMETHREAD_H
#define QTUTKAVREADFRAMETHREAD_H

#include <QImage>
#include <QObject>
#include <QtCore>
#include <QThread>

#include "qtutkclient.h"

class QTutkAVReadFrameThread : public QThread
{
    int avIndex;

    Q_OBJECT
public:
    explicit QTutkAVReadFrameThread(QThread *parent = 0);

    ~QTutkAVReadFrameThread();

    void setAvIndex(int avindex) { this->avIndex=avindex; }

    void close();

signals:
    void showImage(QImage image);

private:
    void run();

};

#endif // QTUTKAVREADFRAMETHREAD_H
