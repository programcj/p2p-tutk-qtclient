#ifndef QTUTKAVSENDAUDIOFILETHREAD_H
#define QTUTKAVSENDAUDIOFILETHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>

#include "qtutkclient.h"

class QTutkAVSendAudioFileThread : public QThread
{
     QTutkClient *tutkclient;

     Q_OBJECT
 public:
     explicit QTutkAVSendAudioFileThread(QThread *parent = 0);

    ~QTutkAVSendAudioFileThread();

    void setQTutkClient(QTutkClient *client) { this->tutkclient = client; }

    void close();

signals:
    void tutkAVSendAudioFileExit();

private:
    void run();
};

#endif // QTUTKAVSENDAUDIOFILETHREAD_H
