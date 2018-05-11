#include "mainwindow.h"
#include <QApplication>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <qtutk/ch264decoder.h>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;

    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString message = QString("%1:%2,%3,%4:%5").arg(current_date_time).arg(text).arg(context.file)
             .arg(context.line).arg(msg);
    QByteArray array=message.toLatin1();

    fprintf(stdout, "%s\n", array.data());
    fflush(stdout);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册MessageHandler
    qInstallMessageHandler(outputMessage);

    CH264Decoder::h264_test();

    qDebug() <<"start...";
    MainWindow w;
    w.show();

    /****
    IOTC_Initialize2(0);
    avInitialize(32);
    unsigned int iotcVer;
    IOTC_Get_Version(&iotcVer);
    int avVer = avGetAVApiVer();
    unsigned char *p = (unsigned char *)&iotcVer;
    unsigned char *p2 = (unsigned char *)&avVer;
    char szIOTCVer[16], szAVVer[16];
    sprintf(szIOTCVer, "%d.%d.%d.%d", p[3], p[2], p[1], p[0]);
    sprintf(szAVVer, "%d.%d.%d.%d", p2[3], p2[2], p2[1], p2[0]);
    fprintf(stderr, "IOTCAPI version[%s] AVAPI version[%s]\n", szIOTCVer, szAVVer);

    struct st_LanSearchInfo psLanSearchInfo[12];
    if(psLanSearchInfo != NULL)
    {
        // wait time 1000 ms to get result, if result is 0 you can extend to 2000 ms
        int nDeviceNum = IOTC_Lan_Search(psLanSearchInfo, 12, 1000);
        printf("IOTC_Lan_Search ret[%d]\n", nDeviceNum);
        for(int i=0;i<nDeviceNum;i++)
        {
            printf("UID[%s] Addr[%s:%d]\n", psLanSearchInfo[i].UID, psLanSearchInfo[i].IP, psLanSearchInfo[i].port);
        }
    }
    printf("LAN search done...\n");
    fflush(stdout);
    avDeInitialize();
    IOTC_DeInitialize();
    ***/
    return a.exec();
}
