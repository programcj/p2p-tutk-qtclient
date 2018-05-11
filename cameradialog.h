#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include <QDialog>
#include <QThread>

#include "qtutk/qtutkclient.h"
#include "qtutk/qtutkavreadframethread.h"
#include "qtutk/qtutkavreadaudiodatathread.h"
#include "qtutk/qtutkavsendaudiofilethread.h"

namespace Ui {
class CameraDialog;
}

class CameraDialog : public QDialog
{
    Q_OBJECT

    QTutkClient tutkclient;
    QTutkAVReadFrameThread   tutkAVReadFrameThread;
    QTutkAVReadAudioDataThread tutkAVReadAudioThread;
    QTutkAVSendAudioFileThread  tutkAVSendAudioFileThread;

public:
    explicit CameraDialog(QWidget *parent = 0);
    ~CameraDialog();

private slots:
    void on_btSelectTUTKID_clicked();

    void on_btConnect_clicked();

    void tutkConnectSuccess();
    void tutkConnectClose();
    void tutkConnectFail(QString mess);
    void tutkIOCtrlMessage(int type, void *data, int dlen);
    void tutkAVSendAudioFileExit();
    void showImage(QImage image);

    void on_btPlayVideo_clicked();

    void on_btPlayAudio_clicked();

    void on_btSendAudio_clicked();

    void on_btHistoryDay_clicked();

    void on_btHistoryHour_clicked();

    void on_btHistoryMin_clicked();

    void on_btHistoryFilePlay_clicked();

    void on_btHistoryDTabs_clicked();

private:
    Ui::CameraDialog *ui;
};

#endif // CAMERADIALOG_H
