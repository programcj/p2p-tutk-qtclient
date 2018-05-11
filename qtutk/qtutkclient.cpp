#include "qtutkclient.h"

QTutkClient::QTutkClient(QThread *parent) : QThread(parent)
{
    this->SID=-1;
    this->speakerCh=-1;
    this->toClose=false;
    this->avindex=-1;
}

QTutkClient::~QTutkClient()
{
    close();
    quit();
    wait();
}

void QTutkClient::setTutkID(QString tutkid, QString user, QString pass)
{
    this->tutkid=tutkid;
    this->user=user;
    this->pass=pass;
}

int QTutkClient::getSID()
{
    QMutexLocker locker(&lock);
    return SID;
}

void QTutkClient::close()
{
    this->toClose=true;
    this->requestInterruption();
}

int QTutkClient::sendAVIOCtrl(int type, void *data, int dlen)
{
    int ret=0;
    if(this->avindex<0)
        return -1;

    ret=avSendIOCtrl(this->avindex, type, (const char*)data, dlen);

    return ret;
}

void QTutkClient::run()
{
    QByteArray tutkid=this->tutkid.toLatin1();
    QByteArray user=this->user.toLatin1();
    QByteArray pass= this->pass.toLatin1();
    this->toClose=false;

    int tmpSID = IOTC_Get_SessionID();
    if(tmpSID < 0)
    {
        qDebug() <<  QString("IOTC_Get_SessionID error code [%1]").arg(tmpSID);
        emit this->tutkConnectError("IOTC_Get_SessionID");
        return ;
    }
    qDebug()  <<"[] thread_ConnectCCR::IOTC_Get_SessionID, ret=" << tmpSID;
    if(tmpSID <0 )
    {
        qDebug()  << "IOTC_Get_SessionID failed " <<  tmpSID;
        emit this->tutkConnectError("IOTC_Get_SessionID");
        return ;
    }

    SID=IOTC_Connect_ByUID_Parallel(tutkid.data(), tmpSID);
    qDebug()  << "  [] thread_ConnectCCR::IOTC_Connect_ByUID_Parallel, ret=" <<SID << " TutkID:" <<tutkid << ", User:"
              <<user <<", pass:" <<pass;
    if(SID < 0)
    {
        qDebug()  <<"IOTC_Connect_ByUID_Parallel failed " << SID;
        emit this->tutkConnectError("IOTC_Connect_ByUID_Parallel");
        return ;
    }
    speakerCh = IOTC_Session_Get_Free_Channel(SID);

    struct st_SInfo Sinfo;
    memset(&Sinfo, 0, sizeof(struct st_SInfo));
    char *mode[] = {"P2P", "RLY", "LAN"};

    int nResend;
    unsigned int srvType;

    int avIndex = avClientStart2(SID, user.data(), pass.data(), 20, &srvType, 0, &nResend);

    if(nResend == 0)
    {
        qDebug() <<"Resend is not supported.";
    }
    qDebug()  <<  "Step 2: call avClientStart2 ....... >" << avIndex;
    if(avIndex < 0)
    {
        printf("avClientStart2 failed[%d]\n", avIndex);

        IOTC_Session_Close(SID);

        emit this->tutkConnectError("avClientStart2");
        return ;
    }

    if(IOTC_Session_Check(SID, &Sinfo) == IOTC_ER_NoERROR)
    {
        if( isdigit( Sinfo.RemoteIP[0] ))
            printf("Device is from %s:%d[%s] Mode=%s NAT[%d] IOTCVersion[%X]\n",
                   Sinfo.RemoteIP,
                   Sinfo.RemotePort,
                   Sinfo.UID, mode[(int)Sinfo.Mode], Sinfo.NatType, Sinfo.IOTCVersion);

    }
    {
        QMutexLocker locker(&lock);
        this->avindex=avIndex;
    }
    emit this->tutkConnectSuccess();

    qDebug() << QString("avClientStart2 OK[%1], Resend[%2]").arg( avIndex).arg(nResend);
    avClientCleanBuf(avIndex);

    unsigned int ioType;
    char ioCtrlBuf[MAX_SIZE_IOCTRL_BUF];
    int ret=0;

    while(!this->isInterruptionRequested()){
        ret = avRecvIOCtrl(avIndex, &ioType, (char *)&ioCtrlBuf, MAX_SIZE_IOCTRL_BUF, 1000);
        if(ret >= 0)  {
            emit this->tutkIOCtrlMessage(ioType,ioCtrlBuf, ret);
        } else if(ret != AV_ER_TIMEOUT)  {
            printf("avIndex[%d], avRecvIOCtrl error, code[%d]\n",avIndex, ret);
            break;
        }
    }
    this->avindex=-1;
    avClientStop(avIndex);
    IOTC_Session_Close(SID);
    this->SID=-1;
    qDebug() << "tutk close" ;
    //if(!this->toClose) {
        emit this->tutkConnectClose();
   // }
}

