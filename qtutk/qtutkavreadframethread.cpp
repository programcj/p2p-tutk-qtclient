#include "qtutkavreadframethread.h"
#include "ch264decoder.h"

#define VIDEO_BUF_SIZE	512000

QTutkAVReadFrameThread::QTutkAVReadFrameThread(QThread *parent): QThread(parent)
{

}

QTutkAVReadFrameThread::~QTutkAVReadFrameThread()
{
    close();
    quit();
    wait(100);
}

void QTutkAVReadFrameThread::close()
{
    this->requestInterruption();
}

void QTutkAVReadFrameThread::run()
{
    int ret=0;
    char buf[VIDEO_BUF_SIZE]={0};
    unsigned char outbuf[2048*1024];

    FRAMEINFO_t frameInfo;
    int outFrmInfoSize = 0;
    unsigned int frmNo;
    int outBufSize = 0;
    int outFrmSize = 0;
    int lostCnt=0;
    int gSleepMs = 10;
    int ow=0,oh=0;

    //        QFile file("vodio.h264");
    //        if(!file.open(QIODevice::ReadWrite))
    //        {
    //        }

    AVCodecContext *pCodecCtx = NULL;
    AVCodecParserContext *pCodecParserCtx = NULL;
    AVCodec *pCodec = NULL;
    AVFrame *pFrame = NULL;             //yuv
    AVPacket packet;                    //h264
    AVPicture picture;                  //储存rgb格式图片
    SwsContext *pSwsCtx = NULL;
    AVCodecID codec_id = AV_CODEC_ID_H264;

    av_register_all();
    avcodec_register_all();

    /* 初始化AVCodec */
    pCodec = avcodec_find_decoder(codec_id);

    /* 初始化AVCodecContext,只是分配，还没打开 */
    pCodecCtx = avcodec_alloc_context3(pCodec);

    /* 初始化AVCodecParserContext */
    pCodecParserCtx = av_parser_init(AV_CODEC_ID_H264);
    if (!pCodecParserCtx)
    {
        qDebug() << "AVCodecParseContext error";
        ::exit(0);
    }

    /* we do not send complete frames,什么意思？ */
    if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
        pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;

    /* 打开解码器 */
    ret = avcodec_open2(pCodecCtx, pCodec, NULL);
    if (ret < 0)
    {
        qDebug() << "avocodec_open2 error";
        ::exit(0);
    }

    bool is_first_time = true;
    pFrame = av_frame_alloc();
    av_init_packet(&packet);
    packet.size = 0;
    packet.data = NULL;

    while(!this->isInterruptionRequested()){
        ret = avRecvFrameData2(avIndex, buf, VIDEO_BUF_SIZE, &outBufSize, &outFrmSize, (char *)&frameInfo, sizeof(FRAMEINFO_t), &outFrmInfoSize, &frmNo);
        if(ret == AV_ER_DATA_NOREADY)
        {
            //printf("AV_ER_DATA_NOREADY[%d]\n", avIndex);
            QThread::usleep(gSleepMs * 1000);
            continue;
        }
        else if(ret == AV_ER_LOSED_THIS_FRAME)
        {
            printf("Lost video frame NO[%d]\n", frmNo);
            lostCnt++;
            //continue;
        }
        else if(ret == AV_ER_INCOMPLETE_FRAME)
        {
#if 1
            if(outFrmInfoSize > 0)
                printf("Incomplete video frame NO[%d] ReadSize[%d] FrmSize[%d] FrmInfoSize[%u] Codec[%d] Flag[%d]\n", frmNo, outBufSize, outFrmSize, outFrmInfoSize, frameInfo.codec_id, frameInfo.flags);
            else
                printf("Incomplete video frame NO[%d] ReadSize[%d] FrmSize[%d] FrmInfoSize[%u]\n", frmNo, outBufSize, outFrmSize, outFrmInfoSize);
#endif
            lostCnt++;
        }
        else if(ret == AV_ER_SESSION_CLOSE_BY_REMOTE)
        {
            printf("[thread_ReceiveVideo] AV_ER_SESSION_CLOSE_BY_REMOTE\n");
            break;
        }
        else if(ret == AV_ER_REMOTE_TIMEOUT_DISCONNECT)
        {
            printf("[thread_ReceiveVideo] AV_ER_REMOTE_TIMEOUT_DISCONNECT\n");
            break;
        }
        else if(ret == IOTC_ER_INVALID_SID)
        {
            printf("[thread_ReceiveVideo] Session cant be used anymore\n");
            break;
        }

        //            if(file.isOpen()) {
        //                    file.write(buf, ret);
        //                    break;
        //            }

//        if(frameInfo.flags == IPC_FRAME_FLAG_IFRAME)
//        {
//            qDebug() << "i_frame " << ret;
//        } else {
//            qDebug() << "p_frame" << ret;
//        }
        if(ret<=0)
            continue;
        /* 返回解析了的字节数 */
        int len = av_parser_parse2(pCodecParserCtx, pCodecCtx,
                                   &packet.data, &packet.size, (uint8_t*)buf, ret,
                                   AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);
        if (packet.size == 0)
            continue;
        int got=0;
        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got, &packet);
        if (got)
        {
            if (is_first_time)  //分配格式转换存储空间
            {

                pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                         pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

                avpicture_alloc(&picture, AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height);

                is_first_time = false;
            }
            /* YUV转RGB */
            sws_scale(pSwsCtx, pFrame->data, pFrame->linesize,
                      0, pCodecCtx->height,
                      picture.data, picture.linesize);

            QImage img(picture.data[0], pCodecCtx->width, pCodecCtx->height, QImage::Format_RGB32);

            //qDebug() << "show image " <<pCodecCtx->width << "  h:"  << pCodecCtx->height;
            emit this->showImage(img);
        }
    }

    av_free_packet(&packet);
    av_frame_free(&pFrame);
    avpicture_free(&picture);
    sws_freeContext(pSwsCtx);
    avcodec_free_context(&pCodecCtx);
    av_parser_close(pCodecParserCtx);

    qDebug() << __FILE__ << ": "<<__FUNCTION__ << " exit";
}

