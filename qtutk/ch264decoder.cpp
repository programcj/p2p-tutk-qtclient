#include "ch264decoder.h"
#include <QDebug>

CH264Decoder::CH264Decoder()
{
    createYUVTab_16();
}

CH264Decoder::~CH264Decoder()
{
    deleteYUVTab();
}

void CH264Decoder::deleteYUVTab()
{
    av_free(colortab);
    av_free(rgb_2_pix);
}

void CH264Decoder::createYUVTab_16()
{
    int i;
    int u, v;

    colortab = (int *)av_malloc(4*256*sizeof(int));
    u_b_tab = &colortab[0*256];
    u_g_tab = &colortab[1*256];
    v_g_tab = &colortab[2*256];
    v_r_tab = &colortab[3*256];

    for (i=0; i<256; i++)
    {
        u = v = (i-128);

        u_b_tab[i] = (int) ( 1.772 * u);
        u_g_tab[i] = (int) ( 0.34414 * u);
        v_g_tab[i] = (int) ( 0.71414 * v);
        v_r_tab[i] = (int) ( 1.402 * v);
    }

    rgb_2_pix = (unsigned int *)av_malloc(3*768*sizeof(unsigned int));

    r_2_pix = &rgb_2_pix[0*768];
    g_2_pix = &rgb_2_pix[1*768];
    b_2_pix = &rgb_2_pix[2*768];

    for(i=0; i<256; i++)
    {
        r_2_pix[i] = 0;
        g_2_pix[i] = 0;
        b_2_pix[i] = 0;
    }

    for(i=0; i<256; i++)
    {
        r_2_pix[i+256] = (i & 0xF8) << 8;
        g_2_pix[i+256] = (i & 0xFC) << 3;
        b_2_pix[i+256] = (i ) >> 3;
    }

    for(i=0; i<256; i++)
    {
        r_2_pix[i+512] = 0xF8 << 8;
        g_2_pix[i+512] = 0xFC << 3;
        b_2_pix[i+512] = 0x1F;
    }

    r_2_pix += 256;
    g_2_pix += 256;
    b_2_pix += 256;
}

void CH264Decoder::displayYUV_16(unsigned int *pdst, unsigned char *y, unsigned char *u, unsigned char *v, int width, int height, int src_ystride, int src_uvstride, int dst_ystride)
{
    int i, j;
    int r, g, b, rgb;

    int yy, ub, ug, vg, vr;

    unsigned char* yoff;
    unsigned char* uoff;
    unsigned char* voff;

    int width2 = width/2;
    int height2 = height/2;

    for(j=0; j<height2; j++)
    {
        yoff = y + j * 2 * src_ystride;
        uoff = u + j * src_uvstride;
        voff = v + j * src_uvstride;

        for(i=0; i<width2; i++)
        {
            yy  = *(yoff+(i<<1));
            ub = u_b_tab[*(uoff+i)];
            ug = u_g_tab[*(uoff+i)];
            vg = v_g_tab[*(voff+i)];
            vr = v_r_tab[*(voff+i)];

            b = yy + ub;
            g = yy - ug - vg;
            r = yy + vr;

            rgb = r_2_pix[r] + g_2_pix[g] + b_2_pix[b];

            yy = *(yoff+(i<<1)+1);
            b = yy + ub;
            g = yy - ug - vg;
            r = yy + vr;

            pdst[(j*dst_ystride+i)] = (rgb)+((r_2_pix[r] + g_2_pix[g] + b_2_pix[b])<<16);

            yy = *(yoff+(i<<1)+src_ystride);
            b = yy + ub;
            g = yy - ug - vg;
            r = yy + vr;

            rgb = r_2_pix[r] + g_2_pix[g] + b_2_pix[b];

            yy = *(yoff+(i<<1)+src_ystride+1);
            b = yy + ub;
            g = yy - ug - vg;
            r = yy + vr;

            pdst [((2*j+1)*dst_ystride+i*2)>>1] = (rgb)+((r_2_pix[r] + g_2_pix[g] + b_2_pix[b])<<16);
        }
    }
}
int CH264Decoder::initial()
{
    avcodec_register_all();
    av_init_packet(&packet);

    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec)
    {
        printf("avcodec_find_encoder failed");
        return -1;
    }

    context = avcodec_alloc_context3(codec);
    if (!context)
    {
        printf("avcodec_alloc_context3 failed");
        return -2;
    }

    context->codec_type = AVMEDIA_TYPE_VIDEO;
    context->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(context, codec, NULL) < 0)
    {
        printf("avcodec_open2 failed");
        return -3;
    }

    frame = av_frame_alloc();
    if (!frame)
    {
        return -4;
    }

    return 0;
}

void CH264Decoder::unInitial()
{
    avcodec_close(context);
    av_free(context);
    av_frame_free(&frame);
}



/**
 * 将AVFrame(YUV420格式)保存为JPEG格式的图片
 *
 * @param width YUV420的宽
 * @param height YUV42的高
 *
 */
int MyWriteJPEG(AVFrame* pFrame, int width, int height, int iIndex)
{
    // 输出文件路径
    char out_file[100] = {0};
    snprintf(out_file, sizeof(out_file), "%s%d.jpg", "/tmp/", iIndex);

    // 分配AVFormatContext对象
    AVFormatContext* pFormatCtx = avformat_alloc_context();

    // 设置输出文件格式
    pFormatCtx->oformat = av_guess_format("mjpeg", NULL, NULL);
    // 创建并初始化一个和该url相关的AVIOContext
    if( avio_open(&pFormatCtx->pb, out_file, AVIO_FLAG_READ_WRITE) < 0) {
        printf("Couldn't open output file.");
        return -1;
    }

    // 构建一个新stream
    AVStream* pAVStream = avformat_new_stream(pFormatCtx, 0);
    if( pAVStream == NULL ) {
        return -1;
    }

    // 设置该stream的信息
    AVCodecContext* pCodecCtx = pAVStream->codec;

    pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
    pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    pCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
    pCodecCtx->width = width;
    pCodecCtx->height = height;
    pCodecCtx->time_base.num = 1;
    pCodecCtx->time_base.den = 25;

    // Begin Output some information
    av_dump_format(pFormatCtx, 0, out_file, 1);
    // End Output some information

    // 查找解码器
    AVCodec* pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
    if( !pCodec ) {
        printf("Codec not found.");
        return -1;
    }
    // 设置pCodecCtx的解码器为pCodec
    if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 ) {
        printf("Could not open codec.");
        return -1;
    }

    //Write Header
    avformat_write_header(pFormatCtx, NULL);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    //Encode
    // 给AVPacket分配足够大的空间
    AVPacket pkt;
    av_new_packet(&pkt, y_size * 3);

    //
    int got_picture = 0;
    int ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_picture);
    if( ret < 0 ) {
        printf("Encode Error.\n");
        return -1;
    }
    if( got_picture == 1 ) {
        //pkt.stream_index = pAVStream->index;
        ret = av_write_frame(pFormatCtx, &pkt);
    }

    av_free_packet(&pkt);

    //Write Trailer
    av_write_trailer(pFormatCtx);

    printf("Encode Successful.\n");

    if( pAVStream ) {
        avcodec_close(pAVStream->codec);
    }
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);

    return 0;
}

uint8_t *fileReadAll(int *length){
    const char *filename = "vodio.h264";
    uint8_t *buff=NULL;
    FILE *fp=fopen(filename,"rb");
    if(fp){
        fseek(fp, 0, SEEK_END);
        int len=ftell(fp);
        fseek(fp,0,SEEK_SET);
        buff=(uint8_t *)malloc(len);
        fread(buff,len,1,fp);
        fclose(fp);
        return buff;
    }
}

void CH264Decoder::h264_test()
{
    const char *filename = "vodio.h264";
    int videoStream = -1;
    AVCodecContext *pCodecCtx;
    AVFormatContext *pFormatCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    struct SwsContext *pSwsCtx;
    AVPacket packet;
    int frameFinished;
    int PictureSize;
    uint8_t *outBuff;

    //注册编解码器
    av_register_all();
    // 初始化网络模块
    avformat_network_init();
    // 分配AVFormatContext
    pFormatCtx = avformat_alloc_context();

    //打开视频文件
    if( avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0 ) {
        printf ("av open input file failed!\n");
        exit (1);
    }

    //获取流信息
    if( avformat_find_stream_info(pFormatCtx, NULL) < 0 ) {
        printf ("av find stream info failed!\n");
        exit (1);
    }
    //获取视频流
    for( int i = 0; i < pFormatCtx->nb_streams; i++ ) {
        if ( pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ) {
            videoStream = i;
            break;
        }
    }
    if( videoStream == -1 ) {
        printf ("find video stream failed!\n");
        exit (1);
    }

    // 寻找解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if( pCodec == NULL ) {
        printf ("avcode find decoder failed!\n");
        exit (1);
    }

    //打开解码器
    if( avcodec_open2(pCodecCtx, pCodec, NULL) < 0 ) {
        printf ("avcode open failed!\n");
        exit (1);
    }

    //为每帧图像分配内存
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    if( (pFrame == NULL) || (pFrameRGB == NULL) ) {
        printf("avcodec alloc frame failed!\n");
        exit (1);
    }

    // 确定图片尺寸
    PictureSize = avpicture_get_size(AV_PIX_FMT_YUVJ420P, pCodecCtx->width, pCodecCtx->height);
    outBuff = (uint8_t*)av_malloc(PictureSize);
    if( outBuff == NULL ) {
        printf("av malloc failed!\n");
        exit(1);
    }
    avpicture_fill((AVPicture *)pFrameRGB, outBuff, AV_PIX_FMT_YUVJ420P, pCodecCtx->width, pCodecCtx->height);

    //设置图像转换上下文
    pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                             pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUVJ420P,
                             SWS_BICUBIC, NULL, NULL, NULL);

    int i = 0;
    while( av_read_frame(pFormatCtx, &packet) >= 0 ) {
        if( packet.stream_index == videoStream ) {
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            if( frameFinished ) {
                // 保存为jpeg时不需要反转图像
                static bool b1 = true;
                if( b1 ) {
                    MyWriteJPEG(pFrame, pCodecCtx->width, pCodecCtx->height, i ++);

                    b1 = false;
                }

                //SaveAsBMP(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i ++, 24);
            }
        } else {
            int a=2;
            int b=a;
        }

        av_free_packet(&packet);
    }

    sws_freeContext(pSwsCtx);

    av_free(pFrame);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}

int CH264Decoder::decode(uint8_t *pDataIn, int nInSize, uint8_t *pDataOut,int *nWidth, int *nHeight)
{
    av_init_packet(&packet);
    packet.size = nInSize;
    packet.data = pDataIn;

    if (packet.size > 0)
    {
        int got_picture=0;
        int ret= avcodec_decode_video2(context, frame, &got_picture, &packet);
        if (ret < 0)
        {
            printf("avcodec_encode_video2 failed");
            return -2;
        }

        if (got_picture)
        {
            *nWidth = context->width;
            *nHeight = context->height;

            displayYUV_16((unsigned int*)pDataOut, frame->data[0], frame->data[1],frame->data[2],
                    *nWidth,*nHeight,frame->linesize[0],frame->linesize[2],*nWidth);
        }
    }
    else
    {
        printf("no data to decode");
        return -1;
    }

    return 0;
}

