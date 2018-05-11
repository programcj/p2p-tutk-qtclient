#include "cameradialog.h"
#include "ui_cameradialog.h"
#include <QtConcurrent/QtConcurrent>

#include <stdio.h>
#include "IOTCAPIs.h"
#include "AVAPIs.h"
#include "AVFRAMEINFO.h"
#include "AVIOCTRLDEFs.h"

#include "dialogtutksearch.h"
#include "tools.h"

#pragma pack(push,1)
typedef struct _PRODUCE_INFO {
    char model[16];  //型号 /
    char hardwareversion[16];  //版本 /
    char Sofewareversion[16];  //版本 /
    char produced_date[16];  //生产日期 /
    char serial[32];  //序列号 /
    char tutk_uid[32];  //UID /
    char eth0_macaddr[16];  //网卡mac地址 /
    char bell_name[16]; //门铃名称 /
    char TutkLoginPassword[16]; //tutk登陆密码[备份的] /
} produce_info_t;

#pragma pack(pop)

CameraDialog::CameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraDialog)
{
    ui->setupUi(this);

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
    qDebug() << QString("IOTCAPI version[%1] AVAPI version[%2]").arg(szIOTCVer).arg(szAVVer);

    //tutk black fun
    connect(&this->tutkclient, SIGNAL(tutkConnectClose()),this, SLOT(tutkConnectClose()));
    connect(&this->tutkclient, SIGNAL(tutkConnectError(QString)),this, SLOT(tutkConnectFail(QString)));
    connect(&this->tutkclient, SIGNAL(tutkConnectSuccess()),this, SLOT(tutkConnectSuccess()));
    connect(&this->tutkclient, SIGNAL(tutkIOCtrlMessage(int,void*,int)), this, SLOT(tutkIOCtrlMessage(int,void*,int)));
    connect(&tutkAVSendAudioFileThread,SIGNAL(tutkAVSendAudioFileExit()),this,SLOT(tutkAVSendAudioFileExit()));
    connect(&tutkAVReadFrameThread, SIGNAL(showImage(QImage)), this, SLOT(showImage(QImage)));
}

CameraDialog::~CameraDialog()
{
    if(tutkclient.isRunning()){
        tutkclient.close();
        QThread::sleep(1);
    }
    avDeInitialize();
    IOTC_DeInitialize();
    delete ui;
}

//select tutkid
void CameraDialog::on_btSelectTUTKID_clicked()
{
    DialogTutkSearch dialog;
    if(dialog.exec()==QDialog::Accepted){
        ui->lineEdit_TutkID->setText(dialog.tutkID);
        QFile file(":/tutkpassword.txt");
        if(file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            while(1){
                QString line=in.readLine();
                if(line.length()<3)
                    break;
                if(line.startsWith(ui->lineEdit_TutkID->text())) {
                    QStringList list= line.split(",");
                    QString pass=list[1];
                    ui->lineEdit_TutkPass->setText(pass);
                }
            }
            file.close();
        } else {
            qDebug() << "rc file not open";
        }
    }
}

//button start connect
void CameraDialog::on_btConnect_clicked()
{
    if(this->tutkclient.isRunning()){
        this->tutkclient.close();
    } else {
        QString user=ui->lineEdit_TutkUser->text();
        QString pass=ui->lineEdit_TutkPass->text();
        QString tutkid=ui->lineEdit_TutkID->text();

        this->tutkclient.setTutkID(tutkid, user, pass);
        this->tutkclient.start();
    }
}

//qtutkclient black connect success
void CameraDialog::tutkConnectSuccess()
{
    ui->btConnect->setText("Connect Success");
    unsigned char data[20];
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_IPCAM_GET_PRODUCT_INFO_REQ,data, sizeof(data));
}

void CameraDialog::tutkConnectClose()
{
    tutkAVReadFrameThread.close();
    tutkAVReadAudioThread.close();
    tutkAVSendAudioFileThread.close();
    ui->btConnect->setText("Not Connect");
}

void CameraDialog::tutkConnectFail(QString mess)
{
    ui->btConnect->setText("Not Connect");
    ui->textEdit_Info->setText( mess );
}

//qtutk iot message
void CameraDialog::tutkIOCtrlMessage(int type, void *data, int dlen)
{
    qDebug() << "tutk mess:" << QString().sprintf("0x%02X , len=%d", type, dlen);

    if(type==IOTYPE_USER_IPCAM_START_ACK) {
        if(!tutkAVReadFrameThread.isRunning()){
            tutkAVReadFrameThread.setAvIndex(this->tutkclient.getAvIndex());
            tutkAVReadFrameThread.start();
        }
    }
    if(type==IOTYPE_USER_IPCAM_STOP_ACK){
        tutkAVReadFrameThread.close();
    }
    if(type==IOTYPE_USER_IPCAM_GET_PRODUCT_INFO_RESP){ //
        produce_info_t *pinfo=(produce_info_t*)data;

        QString info=QString("version:%1\nSN:%2\nTutkID:%3\nPass:%4").arg(pinfo->Sofewareversion)
                .arg(pinfo->serial).arg(pinfo->tutk_uid).arg(pinfo->TutkLoginPassword);
        ui->textEdit_Info->setText(info);
    }
    if(type==IOTYPE_USER_History_FILE_GET_DAY_ACK){
        char *p=( char *)data;
        if(p[0]==0){
            ui->textEdit_Info->setText("SDCard not");
        } else {
            QString info=QString("HistoryDays:");
            p++;
            for(int i=0;i<dlen;i+=3) {
                if(p[i]==0 || p[i+1]==0 || p[i+2]==0)
                    break;
                QString day=QString("%1-%2-%3,").arg((int)(p[i]+2000)).arg((int)p[i+1]).arg((int)p[i+2]);
                info.append(day);
            }
            ui->textEdit_Info->setText(info);
        }
    }
    if(type>=IOTYPE_USER_History_FILE_GET_HOUR_ACK) {
        QString info=QString("HistoryDays:%1").arg((char*)data);
        ui->textEdit_Info->setText(info);
    }
    if(type>=IOTYPE_USER_History_FILE_GET_DAYTABS_ACK){
        QByteArray array=QByteArray((char*)data, dlen);
        QString hex=Tools::arrayToHexString(array);
        qDebug() << "Tabs:" << hex;
        QString info=QString("HistoryDay tabs(%1)").arg(dlen);
        ui->textEdit_Info->setText(info);
    }
}

void CameraDialog::tutkAVSendAudioFileExit()
{

}

void CameraDialog::showImage(QImage image)
{
    QImage img=image.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
    //image.save("/tmp/aa.png");
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void CameraDialog::on_btPlayVideo_clicked()
{
    if(!this->tutkclient.isRunning()){
        return ;
    }
    unsigned char data[20];
    memset(data,0 ,sizeof(data));
    if(!tutkAVReadFrameThread.isRunning()){
        this->tutkclient.sendAVIOCtrl(IOTYPE_USER_IPCAM_START,data, sizeof(data));
    } else {
        this->tutkclient.sendAVIOCtrl(IOTYPE_USER_IPCAM_STOP,data, sizeof(data));
    }
}

void CameraDialog::on_btPlayAudio_clicked()
{
    unsigned char data[20];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }

    if(tutkAVReadAudioThread.isRunning()){
        this->tutkclient.sendAVIOCtrl(IOTYPE_USER_IPCAM_AUDIOSTOP,data, sizeof(data));
        tutkAVReadAudioThread.close();
    } else {
        this->tutkclient.sendAVIOCtrl(IOTYPE_USER_IPCAM_AUDIOSTART,data, sizeof(data));
        tutkAVReadAudioThread.setAvIndex(this->tutkclient.getAvIndex());
        tutkAVReadAudioThread.start();
    }
}

void CameraDialog::on_btSendAudio_clicked()
{
    if(!this->tutkclient.isRunning()){
        return ;
    }
    if(tutkAVSendAudioFileThread.isRunning()){
        tutkAVSendAudioFileThread.close();
        return ;
    }
    tutkAVSendAudioFileThread.setQTutkClient(&this->tutkclient);
    tutkAVSendAudioFileThread.start();
}

void CameraDialog::on_btHistoryDay_clicked()
{
    unsigned char data[20];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_History_FILE_GET_DAY,data, sizeof(data));
}

void CameraDialog::on_btHistoryHour_clicked()
{
    char data[20];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }
    strcpy(data, "2017-10-17");
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_History_FILE_GET_HOUR,data, sizeof(data));
}

void CameraDialog::on_btHistoryMin_clicked()
{
    char data[33];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }
    strcpy(data, "2017-10-17/15");
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_History_FILE_GET_MIN,data, sizeof(data));
}

void CameraDialog::on_btHistoryFilePlay_clicked()
{
    char data[33];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }
    //./ffmpeg -i vodio.h264 -an -filter:v setpts=3.0*PTS vodio.mp4
    strcpy(data, "2018-05-11/15/30");
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_History_STREAM_START,data, sizeof(data));
}

void CameraDialog::on_btHistoryDTabs_clicked()
{
    char data[20];
    memset(data,0 ,sizeof(data));
    if(!this->tutkclient.isRunning()){
        return ;
    }
    strcpy(data, "2018-05-11");
    this->tutkclient.sendAVIOCtrl(IOTYPE_USER_History_FILE_GET_DAYTABS,data, sizeof(data));
}
