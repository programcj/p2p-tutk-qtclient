#include "qtutkavreadaudiodatathread.h"
#include "stdio.h"
#include "../tools.h"
#include <QAudioFormat>
#include <QAudioOutput>

QTutkAVReadAudioDataThread::QTutkAVReadAudioDataThread()
{

}

QTutkAVReadAudioDataThread::~QTutkAVReadAudioDataThread()
{
    close();
    quit();
    wait();
}

void QTutkAVReadAudioDataThread::close()
{
    this->requestInterruption();
}

void QTutkAVReadAudioDataThread::run()
{
    //设置采样格式 */
    QAudioFormat audioFormat;
    //设置采样率 */
    audioFormat.setSampleRate(8000);
    //设置通道数 */
    audioFormat.setChannelCount(1);
    //设置采样大小，一般为8位或16位 */
    audioFormat.setSampleSize(16);
    //设置编码方式 */
    audioFormat.setCodec("audio/pcm");
    //设置字节序 */
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    //设置样本数据类型 */
    audioFormat.setSampleType(QAudioFormat::UnSignedInt);

    //音频设备信息 */
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(audioFormat)) {
        qDebug()<<"default format not supported try to use nearest";
        audioFormat = info.nearestFormat(audioFormat);
    }
   QAudioOutput *audioOutput = new QAudioOutput(audioFormat, this);
  QIODevice   *streamOut = audioOutput->start();

#define AUDIO_BUF_SIZE	1024
#define AUDIO_DATA_LENGTH 640
#define AUDIO_DATA_T0_LENGTH 320

    FRAMEINFO_t frameInfo;
    unsigned int frmNo;
    int ret;
    unsigned char buf[AUDIO_BUF_SIZE]={0};
    unsigned char SendBuffer1[AUDIO_DATA_LENGTH];

    while(!this->isInterruptionRequested()){
        ret = avRecvAudioData(avIndex, (char*)buf, AUDIO_BUF_SIZE, (char *)&frameInfo, sizeof(FRAMEINFO_t), &frmNo);
        if(ret == AV_ER_SESSION_CLOSE_BY_REMOTE)
        {
            printf("[thread_ReceiveAudio] AV_ER_SESSION_CLOSE_BY_REMOTE\n");
            break;
        }
        else if(ret == AV_ER_REMOTE_TIMEOUT_DISCONNECT)
        {
            printf("[thread_ReceiveAudio] AV_ER_REMOTE_TIMEOUT_DISCONNECT\n");
            break;
        }
        else if(ret == IOTC_ER_INVALID_SID)
        {
            printf("[thread_ReceiveAudio] Session cant be used anymore\n");
            break;
        }
        else if(ret == AV_ER_LOSED_THIS_FRAME)
        {
            //printf("Audio AV_ER_LOSED_THIS_FRAME[%d]\n", frmNo);
            continue;
        }
        else if (ret == AV_ER_DATA_NOREADY)
        {
            QThread::usleep(40000);
            continue;
        }
        else if(ret < 0)
        {
            printf("Other error[%d]!!!\n", ret);
            continue;
        }

        Tools::g711u_decode((short*) SendBuffer1, buf, AUDIO_DATA_T0_LENGTH);
        //play...
       streamOut->write((char*)SendBuffer1,AUDIO_DATA_LENGTH);
        qDebug() << "audio:" <<ret;
    }
    streamOut->close();
    audioOutput->stop();
    delete audioOutput;
    qDebug() << __FILE__ << ": "<<__FUNCTION__ << " exit";
}

