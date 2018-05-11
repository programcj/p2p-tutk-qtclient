#ifndef QTUTKAVREADAUDIODATATHREAD_H
#define QTUTKAVREADAUDIODATATHREAD_H

#include <QThread>
#include "qtutkclient.h"

class QTutkAVReadAudioDataThread : public QThread
{
    int avIndex;
public:
    QTutkAVReadAudioDataThread();

    ~QTutkAVReadAudioDataThread();

    void setAvIndex(int avindex) { this->avIndex=avindex; }

    void close();

private:
    void run();
};

#endif // QTUTKAVREADAUDIODATATHREAD_H
