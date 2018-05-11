#include "qtutkavsendaudiofilethread.h"
#include <QDebug>
#include "../tools.h"

QTutkAVSendAudioFileThread::QTutkAVSendAudioFileThread(QThread *parent): QThread(parent)
{

}

QTutkAVSendAudioFileThread::~QTutkAVSendAudioFileThread()
{
    close();
    quit();
    wait();
}

void QTutkAVSendAudioFileThread::close()
{
    this->requestInterruption();
}

extern "C" {

static int  _tutkAVServerFun(char *szViewAccount,char *szViewPassword)
{
    szViewAccount=szViewPassword=NULL;
    return 1;
}

}

void QTutkAVSendAudioFileThread::run()
{
#define AUDIO_DATA_T0_LENGTH 320

    unsigned char iotbuf[20];
    memset(iotbuf,0 ,sizeof(iotbuf));
    iotbuf[0]=tutkclient->getSpeakerCh();

    qDebug() << "start ipcam speak:" <<  QDateTime::currentDateTime();

    tutkclient->sendAVIOCtrl(IOTYPE_USER_IPCAM_SPEAKERSTART, iotbuf, sizeof(iotbuf));

    int avIndex = avServStart2(tutkclient->getSID(), _tutkAVServerFun, 10,16,tutkclient->getSpeakerCh());

    qDebug() << "start ipcam speak end:" <<  QDateTime::currentDateTime();

    char AudioBufferG711[AUDIO_DATA_T0_LENGTH];
    char inputbuff[640];

    FRAMEINFO_t frameInfo;
    int ret=0;

    memset(&frameInfo, 0, sizeof(FRAMEINFO_t));
    frameInfo.codec_id = MEDIA_CODEC_AUDIO_PCM;
    frameInfo.flags = (AUDIO_SAMPLE_8K << 2) | (AUDIO_DATABITS_16 << 1) | AUDIO_CHANNEL_MONO;
    QFile f("/home/cj/nfs_files/audio.pcm");

    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open failed." ;
        return ;
    }
    int rlen=0;

    while(!this->isInterruptionRequested()){
        rlen=f.read(inputbuff, sizeof(inputbuff));
        if(f.atEnd()){
            f.seek(0);
        }
        Tools::g711u_encode((unsigned char *) AudioBufferG711, ((short *) (inputbuff)), AUDIO_DATA_T0_LENGTH);

        //qDebug() << "avSendAudioData:" << AUDIO_DATA_T0_LENGTH;

        ret = avSendAudioData(avIndex, AudioBufferG711, AUDIO_DATA_T0_LENGTH, &frameInfo, sizeof(FRAMEINFO_t));
        if (ret == AV_ER_SESSION_CLOSE_BY_REMOTE) {
            qDebug() << "thread_AudioFrameData AV_ER_SESSION_CLOSE_BY_REMOTE";
        } else if (ret == AV_ER_REMOTE_TIMEOUT_DISCONNECT) {
            qDebug() << "thread_AudioFrameData AV_ER_REMOTE_TIMEOUT_DISCONNECT";
        } else if (ret == IOTC_ER_INVALID_SID) {
            qDebug() << "Session cant be used anymore";
        } else if (ret == AV_ER_EXCEED_MAX_SIZE) {
            QThread::usleep(500);
        } else if (ret < 0) {
            qDebug() <<"avSendAudioData error "<<ret;
            break;
        }
        QThread::msleep(35);
    }
    tutkclient->sendAVIOCtrl(IOTYPE_USER_IPCAM_SPEAKERSTOP, iotbuf, sizeof(iotbuf));

    emit this->tutkAVSendAudioFileExit();

    qDebug() << "exit";
}

