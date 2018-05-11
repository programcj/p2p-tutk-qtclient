#ifndef QTUTKCLIENT_H
#define QTUTKCLIENT_H

#include <QObject>
#include <QtCore>

#include <stdio.h>
#include "IOTCAPIs.h"
#include "AVAPIs.h"
#include "../AVFRAMEINFO.h"
#include "../AVIOCTRLDEFs.h"

#define     MAX_SIZE_IOCTRL_BUF  2048

class QTutkClient : public QThread
{
    QString tutkid;
    QString user;
    QString pass;
    int SID;
    int speakerCh;
    int avindex;
    bool toClose;
    QMutex lock;

    Q_OBJECT
public:
    explicit QTutkClient(QThread *parent = 0);

    ~QTutkClient();

    void setTutkID(QString tutkid, QString user,QString pass);

    int getSID();
    int getSpeakerCh() {
        QMutexLocker locker(&lock);
        return speakerCh;
    }
    int getAvIndex() {
        QMutexLocker locker(&lock);
        return avindex;
    }

    void close();

    int  sendAVIOCtrl(int type, void *data, int dlen);

signals:
    void tutkConnectSuccess();
    void tutkConnectClose();
    void tutkConnectError(QString message);
    void tutkIOCtrlMessage(int type, void *data, int dlen);

public slots:

private:
    void run();
};

#endif // QTUTKCLIENT_H
