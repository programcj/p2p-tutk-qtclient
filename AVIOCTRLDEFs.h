/*
 * AVIOCTRLDEFs.h
 *	Define AVIOCTRL Message Type and Context
 *  Created on: 2011-08-12
 *  Author: TUTK
 *
 */

//Change Log:
//
//  2013-06-25 - 1> Add set and get time zone of device.
//                      Add IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ
//                          Client request device to return time zone
//	                    Add IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP
//	                        Device return to client the time zone
//	                    Add IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ
//	                        Client request device to set time zone
//	                    Add IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP 
//	                        Device acknowledge the set time zone request
//
//  2013-06-05 - 1> Add customer defined message type, start from #FF000000
//                  Naming role of message type : IOTYPE_[Company_name]_[function_name]
//                      ex : IOTYPE_TUTK_TEST_REQ, IOTYPE_TUTK_TEST_RESP
//                  Naming role of data structure : [Company_name]_[data_structure_name]
//                      ex : TUTK_SMsgTestReq, TUTK_SMsgTestResp
//                  
//
//  2013-03-10 - 1> Add flow information collection mechanism.
//						Add IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ
//							Device request client to collect flow information.
//						Add IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP
//							Client acknowledge device that request is received.
//						Add IOTYPE_USER_IPCAM_CURRENT_FLOWINFO
//							Client send collected flow information to device.
//				 2> Add IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME command.
//
//	2013-02-19 - 1> Add more detail of status of SWifiAp
//				 2> Add more detail description of STimeDay
//
//	2012-10-26 - 1> SMsgAVIoctrlGetEventConfig
//						Add field: externIoOutIndex, externIoInIndex
//				 2> SMsgAVIoctrlSetEventConfig, SMsgAVIoctrlGetEventCfgResp
//						Add field: externIoOutStatus, externIoInStatus
//
//	2012-10-19 - 1> SMsgAVIoctrlGetWifiResp: -->SMsgAVIoctrlGetWifiResp2
//						Add status description
//				 2> SWifiAp:
//				 		Add status 4: selected but not connected
//				 3> WI-FI Password 32bit Change to 64bit
//				 4> ENUM_AP_ENCTYPE: Add following encryption types
//				 		AVIOTC_WIFIAPENC_WPA_PSK_TKIP		= 0x07,
//						AVIOTC_WIFIAPENC_WPA_PSK_AES		= 0x08,
//						AVIOTC_WIFIAPENC_WPA2_PSK_TKIP		= 0x09,
//						AVIOTC_WIFIAPENC_WPA2_PSK_AES		= 0x0A,
//
//				 5> IOTYPE_USER_IPCAM_SETWIFI_REQ_2:
//						Add struct SMsgAVIoctrlSetWifiReq2
//				 6> IOTYPE_USER_IPCAM_GETWIFI_RESP_2:
//						Add struct SMsgAVIoctrlGetWifiResp2
//  2012-07-18 - added: IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ, IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP
//	2012-05-29 - IOTYPE_USER_IPCAM_DEVINFO_RESP: Modify firmware version
//	2012-05-24 - SAvEvent: Add result type
//
#ifndef _AVIOCTRL_DEFINE_H_
#define _AVIOCTRL_DEFINE_H_

/////////////////////////////////////////////////////////////////////////////////
/////////////////// Message Type Define//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

// AVIOCTRL Message Type
typedef enum {
    IOTYPE_USER_IPCAM_START = 0x01FF,
    IOTYPE_USER_IPCAM_STOP = 0x02FF,
    IOTYPE_USER_IPCAM_AUDIOSTART = 0x0300,
    IOTYPE_USER_IPCAM_AUDIOSTOP = 0x0301,

    IOTYPE_USER_IPCAM_START_ACK = 0x0302,
    IOTYPE_USER_IPCAM_STOP_ACK = 0x0303,
    IOTYPE_USER_IPCAM_AUDIOSTART_ACK = 0x0304,
    IOTYPE_USER_IPCAM_AUDIOSTOP_ACK = 0x0305,

    IOTYPE_USER_IPCAM_SPEAKERSTART = 0x0350,
    IOTYPE_USER_IPCAM_SPEAKERSTOP = 0x0351,

    IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ = 0x0320,
    IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP = 0x0321,
    IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ = 0x0322,
    IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP = 0x0323,

    IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ = 0x0324,
    IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP = 0x0325,
    IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ = 0x0326,
    IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP = 0x0327,

    IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ = 0x0328,	// Get Support Stream
    IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP = 0x0329,

    IOTYPE_USER_IPCAM_DEVINFO_REQ = 0x0330,
    IOTYPE_USER_IPCAM_DEVINFO_RESP = 0x0331,

    IOTYPE_USER_IPCAM_LISTWIFIAP_REQ = 0x0340,
    IOTYPE_USER_IPCAM_LISTWIFIAP_RESP = 0x0341,
    IOTYPE_USER_IPCAM_SETWIFI_REQ = 0x0342,
    IOTYPE_USER_IPCAM_SETWIFI_RESP = 0x0343,
    IOTYPE_USER_IPCAM_GETWIFI_REQ = 0x0344,
    IOTYPE_USER_IPCAM_GETWIFI_RESP = 0x0345,
    IOTYPE_USER_IPCAM_SETWIFI_REQ_2 = 0x0346,
    IOTYPE_USER_IPCAM_GETWIFI_RESP_2 = 0x0347,

    IOTYPE_USER_IPCAM_SETRECORD_REQ = 0x0310,
    IOTYPE_USER_IPCAM_SETRECORD_RESP = 0x0311,
    IOTYPE_USER_IPCAM_GETRECORD_REQ = 0x0312,
    IOTYPE_USER_IPCAM_GETRECORD_RESP = 0x0313,

    IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ = 0x0314,
    IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP = 0x0315,
    IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ = 0x0316,
    IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP = 0x0317,

    IOTYPE_USER_IPCAM_LISTEVENT_REQ = 0x0318,
    IOTYPE_USER_IPCAM_LISTEVENT_RESP = 0x0319,

    IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL = 0x031A,
    IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP = 0x031B,

    IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ = 0x032A,
    IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP = 0x032B,

    IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ = 0x0400,	// Get Event Config Msg Request
    IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP = 0x0401,	// Get Event Config Msg Response
    IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ = 0x0402,	// Set Event Config Msg req
    IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP = 0x0403,	// Set Event Config Msg resp

    IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ = 0x0360,
    IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP = 0x0361,
    IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ = 0x0362,
    IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP = 0x0363,

    IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ = 0x0370,	// Set Video Flip Mode
    IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP = 0x0371,
    IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ = 0x0372,	// Get Video Flip Mode
    IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP = 0x0373,

    IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ = 0x0380,	// Format external storage
    IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_RESP = 0x0381,

    IOTYPE_USER_IPCAM_PTZ_COMMAND = 0x1001,	// P2P PTZ Command Msg

    IOTYPE_USER_IPCAM_EVENT_REPORT = 0x1FFF,	// Device Event Report Msg
    IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME = 0x1002,	// Send from client, used to talk to device that
    // client had received the first I frame

    IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ = 0x0390,
    IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP = 0x0391,
    IOTYPE_USER_IPCAM_CURRENT_FLOWINFO = 0x0392,

    IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ = 0x3A0,
    IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP = 0x3A1,
    IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ = 0x3B0,
    IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP = 0x3B1,
    /*-------------------------------------------------------------*/
    //锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_GET_VERSION_INFO_REQ = 0x572,
    IOTYPE_USER_IPCAM_GET_VERSION_INFO_RESP = 0x573,

    IOTYPE_USER_IPCAM_SET_VERSION_INFO = 0x672,
    IOTYPE_USER_IPCAM_SET_VERSION_INFO_ACK = 0x673,

    IOTYPE_USER_IPCAM_SET_ENTER_EMPOWER = 0x2002,
    IOTYPE_USER_IPCAM_SET_ENTER_EMPOWER_ACK = 0x2003,

    IOTYPE_USER_IPCAM_SET_QUIT_EMPOWER = 0x2004,
    IOTYPE_USER_IPCAM_SET_QUIT_EMPOWER_ACK = 0x2005,

    //刷锟斤拷
    IOTYPE_USER_IPCAM_GET_SWIPED_EMPOWER_REQ = 0x2006,
    IOTYPE_USER_IPCAM_GET_SWIPED_EMPOWER_RESP = 0x2007,
    //锟斤拷权锟剿匡拷锟斤拷
    IOTYPE_USER_IPCAM_IF_EMPOWER = 0x2008,
    IOTYPE_USER_IPCAM_IF_EMPOWER_ACK = 0x2009,

    IOTYPE_USER_IPCAM_SET_DEV_NAME = 0x450, //锟斤拷锟斤拷锟借备锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_SET_DEV_NAME_ACK = 0x451,

    IOTYPE_USER_IPCAM_SET_WIFI_INFO_REQ = 0x452,  //锟斤拷锟斤拷WIFI锟斤拷息SSID 锟斤拷password
    IOTYPE_USER_IPCAM_SET_WIFI_INFO_RESP = 0x453,

    IOTYPE_USER_IPCAM_SETPASSWORD_REQ = 0x454,  //锟睫革拷锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_SETPASSWORD_RESP = 0x455,

    IOTYPE_USER_IPCAM_SETPIRPUSH_REQ = 0x456,  //锟斤拷锟斤拷PIR push 状态
    IOTYPE_USER_IPCAM_SETPIRPUSH_RESP = 0x457,

    IOTYPE_USER_IPCAM_CAMERAADJUST_REQ = 0x458,  //锟斤拷锟斤拷PIR push 状态
    IOTYPE_USER_IPCAM_CAMERAADJUST_REQ_RESP = 0x459,

    IOTYPE_USER_IPCAM_GET_PRODUCT_INFO_REQ = 0x460, //获取产品信息
    IOTYPE_USER_IPCAM_GET_PRODUCT_INFO_RESP = 0x461,

    IOTYPE_USER_IPCAM_GET_BASIC_INFO_REQ = 0x470,  //登陆入口 获取设备基本信息
    IOTYPE_USER_IPCAM_GET_BASIC_INFO_RESP = 0x471,

    //APP升级功能
    IOTYPE_USER_IPCAM_UPDATE_APP_REQ = 0x472,
    IOTYPE_USER_IPCAM_UPDATE_APP_RESP = 0x473,

    IOTYPE_USER_IPCAM_SET_URLREG_REQ = 0x474,
    IOTYPE_USER_IPCAM_SET_URLREG_RESP = 0x475,

    IOTYPE_USER_IPCAM_GET_URLREG_REQ = 0x476,
    IOTYPE_USER_IPCAM_GET_URLREG_RESP = 0x477,

    IOTYPE_USER_IPCAM_SET_URLPUSH_REQ = 0x478,
    IOTYPE_USER_IPCAM_SET_URLPUSH_RESP = 0x479,

    IOTYPE_USER_IPCAM_GET_URLPUSH_REQ = 0x480,
    IOTYPE_USER_IPCAM_GET_URLPUSH_RESP = 0x481,

    IOTYPE_USER_IPCAM_SYSTEM_COMMAND_REQ = 0x482,
    IOTYPE_USER_IPCAM_SYSTEM_COMMAND_RESP = 0x483,
    /////////////////////////////////////////////////////////////////////////

    //删锟斤拷锟斤拷权锟斤拷息
    IOTYPE_USER_IPCAM_DEL_EMPOWER = 0x2010,
    IOTYPE_USER_IPCAM_DEL_EMPOWER_ACK = 0x2011,
    //锟睫革拷锟斤拷权锟斤拷息
    IOTYPE_USER_IPCAM_CHANGE_EMPOWER = 0x2012,
    IOTYPE_USER_IPCAM_CHANGE_EMPOWER_ACK = 0x2013,
    //锟睫改匡拷锟斤拷锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_CHANGE_OPENROOM_PASSWORD = 0x2014,
    IOTYPE_USER_IPCAM_CHANGE_OPENROOM_PASSWORD_ACK = 0x2015,
    //锟睫改癸拷锟斤拷员锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_CHANGE_ADMIN_PASSWORD = 0x2016,
    IOTYPE_USER_IPCAM_CHANGE_ADMIN_PASSWORD_ACK = 0x2017,
    //锟斤拷权锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_GET_EMPOWER_COUNT_REQ = 0x2018,
    IOTYPE_USER_IPCAM_GET_EMPOWER_COUNT_RESP = 0x2019,
    //锟斤拷锟斤拷呕锟饺★拷丫锟斤拷锟饺拷锟斤拷锟较�
    IOTYPE_USER_IPCAM_GET_USER_INFO_REQ = 0x2020,
    IOTYPE_USER_IPCAM_GET_USER_INFO_REQ_RESP = 0x2021,
    //锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_SET_OPENR00M = 0x2022,
    IOTYPE_USER_IPCAM_SET_OPENR00M_ACK = 0x2023,
    //锟斤拷证锟斤拷锟斤拷员锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_VERIFY_ADMIN_PASSWORD = 0x2024,
    IOTYPE_USER_IPCAM_VERIFY_ADMIN_PASSWORD_ACK = 0x2025,
    //锟斤拷锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_DOOR_BELL = 0x2026,
    IOTYPE_USER_IPCAM_DOOR_BELL_ACK = 0x2027,

    //锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_ANTI_TEMPER = 0x2028,
    IOTYPE_USER_IPCAM_ANTI_TEMPER_ACK = 0x2029,

    //锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_AUDIO_FILE_START = 0x2030,
    IOTYPE_USER_IPCAM_AUDIO_FILE_STOP = 0x2031,

    //录锟斤拷停止
    IOTYPE_USER_IPCAM_AUDIO_RECORD_START = 0x2032,
    IOTYPE_USER_IPCAM_AUDIO_RECORD_STOP = 0x2033,

    //锟斤拷锟経ID锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_PRIVDATA_CLEAR = 0x2034,
    IOTYPE_USER_IPCAM_PRIVDATA_CLEAR_ACK = 0x2035,

    //锟斤拷锟斤拷锟斤拷频
    IOTYPE_USER_IPCAM_SET_VEDIO = 0x3037,
    IOTYPE_USER_IPCAM_SET_VEDIO_ACK = 0x3038,

    //锟斤拷锟斤拷锟斤拷频
    IOTYPE_USER_IPCAM_SET_AUDIO = 0x3015,
    IOTYPE_USER_IPCAM_SET_AUDIO_ACK = 0x3016,

    IOTYPE_BELL_PRODUCTINFO_SET = 0x3517,
    IOTYPE_BELL_PRODUCTINFO_SET_ACK = 0x3518,

    IOTYPE_BELL_FACTORYINFO_GET = 0x3519,
    IOTYPE_BELL_FACTORYINFO_GET_ACK = 0x351a,

    IOTYPE_PUSH_SERVERADDR_SET = 0x351B,
    IOTYPE_PUSH_SERVERADDR_SET_ACK = 0x351C,

    //锟斤拷锟斤拷录锟斤拷锟斤拷频
    //	IOTYPE_USER_IPCAM_RECORDAUDIOSTART  = 0x2034,
    //	IOTYPE_USER_IPCAM_RECORDAUDIOSTOP   = 0x2035,
    //	IOTYPE_USER_IPCAM_AUDIO_RECORD_STOP_ACK =  0x2036,

    //锟斤拷锟斤拷录锟斤拷锟斤拷频
    IOTYPE_USER_IPCAM_RECORDAUDIOSTART = 0x3039,
    IOTYPE_USER_IPCAM_RECORDAUDIOSTART_ACK = 0x3040,
    IOTYPE_USER_IPCAM_RECORDAUDIOSTOP = 0x3043,
    IOTYPE_USER_IPCAM_RECORDAUDIOSTOP_ACK = 0x0344,

    IOTYPE_USER_IPCAM_RECEIVEAUDIOSTART = 0x3049,
    IOTYPE_USER_IPCAM_RECEIVEAUDIOSTART_ACK = 0x3050,
    IOTYPE_USER_IPCAM_RECEIVEAUDIOSTOP = 0x3051,
    IOTYPE_USER_IPCAM_RECEIVEAUDIOSTOP_ACK = 0x0352,
    //锟斤拷锟斤拷录锟斤拷锟斤拷频
    IOTYPE_USER_IPCAM_SENDFILEAUDIOSTART = 0x3045,
    IOTYPE_USER_IPCAM_SENDFILEAUDIOSTART_ACK = 0x3046,
    IOTYPE_USER_IPCAM_SENDFILEAUDIOSTOP = 0x3047,
    IOTYPE_USER_IPCAM_SENDFILEAUDIOSTOP_ACK = 0x0348,

    //锟斤拷锟斤拷锟剿讹拷锟斤拷
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_FORWARD = 0x3000,  //前锟斤拷
    IOTYPE_USER_IPCAM_BACK = 0x3001, //锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_LETF = 0x3002,  //锟斤拷锟�
    IOTYPE_USER_IPCAM_RIGHT = 0x3003, //锟揭憋拷
    IOTYPE_USER_IPCAM_EMOTION = 0x3005, //锟揭憋拷
    IOTYPE_USER_IPCAM_LOW = 0x3041, //锟斤拷头
    IOTYPE_USER_IPCAM_HIGH = 0x3042, //抬头
    /*-------------------------------------------------------------*/

    //录锟斤拷
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_START_STOP_RECODE = 0x3019, //录锟斤拷锟斤拷锟�
    IOTYPE_USER_IPCAM_VIDEO_RECODE = 0x3021, //录锟斤拷锟斤拷锟�
    IOTYPE_USER_IPCAM_VIDEO_RECODE_ACK = 0x3022, //录锟斤拷锟斤拷锟�
    IOTYPE_USER_IPCAM_PLAY_VIDEO_RECODE = 0x3035, //锟斤拷锟斤拷录锟斤拷
    IOTYPE_USER_IPCAM_PLAY_VIDEO_RECODE_ACK = 0x3036, //锟斤拷锟斤拷录锟斤拷
    IOTYPE_USER_IPCAM_GET_VIDEO_RECODE_INFO_YTD = 0x3055, //锟斤拷取录锟斤拷锟斤拷锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_GET_VIDEO_RECODE_INFO_YTD_ACK = 0x3056, //锟斤拷取录锟斤拷锟斤拷锟斤拷锟斤拷
    IOTYPE_USER_IPCAM_GET_VIDEO_RECODE_INFO_D = 0x3057,
    IOTYPE_USER_IPCAM_GET_VIDEO_RECODE_INFO_D_ACK = 0x3058,

    /*-------------------------------------------------------------*/

    //锟斤拷锟�
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_WAIT_CHARGING = 0x3063,
    IOTYPE_USER_IPCAM_WAIT_CHARGING_ACK = 0x3064,

    IOTYPE_USER_IPCAM_START_CHARGING = 0x3053,
    IOTYPE_USER_IPCAM_START_CHARGING_ACK = 0x3054,
    /*-------------------------------------------------------------*/
    //锟斤拷锟斤拷锟斤拷锟斤拷
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_SET_ENC_ATTR = 0x3061,
    IOTYPE_USER_IPCAM_SET_ENC_ATTR_ACK = 0x3062,
    /*-------------------------------------------------------------*/

    //锟斤拷锟斤拷LED
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_SET_LED = 0x3063,
    IOTYPE_USER_IPCAM_SET_LED_ACK = 0x3064,
    /*-------------------------------------------------------------*/

    //锟斤拷锟斤拷LED
    /*-------------------------------------------------------------*/
    IOTYPE_USER_IPCAM_WIFI_SSID = 0x3073,
    IOTYPE_USER_IPCAM_WIFI_SSID_ACK = 0x3074,
    /*-------------------------------------------------------------*/

    IOTYPE_USER_IPCAM_SET_CSCATTR = 0x3075,
    IOTYPE_USER_IPCAM_SET_CSCATTR_ACK = 0x3076,

    IOTYPE_USER_IPCAM_GET_CSCATTR = 0x3077,
    IOTYPE_USER_IPCAM_GET_CSCATTR_ACK = 0x3078,

    IOTYPE_USER_IPCAM_TEST1 = 0x3079,

    IOTYPE_USER_IPCAM_TEST2 = 0x3080,

    IOTYPE_USER_IPCAM_TEST3 = 0x3081,

    IOTYPE_USER_IPCAM_TEST4 = 0x3082,

    //Customer defined message type, start from 0xFF00:0000
    //Naming role : IOTYPE_[Company_name]_[function_name]
    //EX:
    //IOTYPE_TUTK_TEST_REQ						=0xFF000001,
    //IOTYPE_TUTK_TEST_RESP						=0xFF000002,

    IOTYPE_USER_History_STREAM_START = 0x3083,  //开始发送历史视频,数据为视频名称(年-月-日/时/分.h264..)
    IOTYPE_USER_History_STREAM_START_ACK = 0x3084,  //开始发送历史视频ACK, 0历史视频不存在(告诉用户),1历史视频存在
    IOTYPE_USER_History_STREAM_STOP = 0x3085,   //停止发送历史视频
    IOTYPE_USER_History_STREAM_STOP_ACK = 0x3086,   //停止发送历史视频ACK

    IOTYPE_USER_History_FILE_GET = 0x3087, //获取历史文件 //屏蔽
    IOTYPE_USER_History_FILE_GET_ACK = 0x3089, //获取历史文件结果, sd卡是否存在,最小时间戳，最大时间戳

    IOTYPE_USER_History_FILE_GET_DAY = 0x308a, //获取sd卡文件目录中的天,最多4天
    IOTYPE_USER_History_FILE_GET_DAY_ACK = 0x308b, //获取sd卡文件目录中的天,最多4天
    IOTYPE_USER_History_FILE_GET_HOUR = 0x308c, //获取sd卡文件目录中的时:条件:那一天
    IOTYPE_USER_History_FILE_GET_HOUR_ACK = 0x308d,  //获取sd卡文件目录中的时:条件:那一天 , ACK
    IOTYPE_USER_History_FILE_GET_MIN = 0x308e, //获取sd卡文件目录中的分:条件:　天/时
    IOTYPE_USER_History_FILE_GET_MIN_ACK = 0x308f,  //获取sd卡文件目录中的分:条件:天/时 , ACK

    IOTYPE_USER_History_FILE_GET_DAYTABS = 0x3090, //获取sd卡文件目录中的天下面的时间表,条件:那一天，如：2017-10-17  查看2017年10月17日存在的时
    IOTYPE_USER_History_FILE_GET_DAYTABS_ACK = 0x3091, //获取sd卡文件目录中的天下面的时间表,24小时*60分钟=1440分钟(一天)

} ENUM_AVIOCTRL_MSGTYPE;

/////////////////////////////////////////////////////////////////////////////////
/////////////////// Type ENUM Define ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
typedef enum {
    AVIOCTRL_OK = 0x00,
    AVIOCTRL_ERR = -0x01,
    AVIOCTRL_ERR_PASSWORD = AVIOCTRL_ERR - 0x01,
    AVIOCTRL_ERR_STREAMCTRL = AVIOCTRL_ERR - 0x02,
    AVIOCTRL_ERR_MONTIONDETECT = AVIOCTRL_ERR - 0x03,
    AVIOCTRL_ERR_DEVICEINFO = AVIOCTRL_ERR - 0x04,
    AVIOCTRL_ERR_LOGIN = AVIOCTRL_ERR - 5,
    AVIOCTRL_ERR_LISTWIFIAP = AVIOCTRL_ERR - 6,
    AVIOCTRL_ERR_SETWIFI = AVIOCTRL_ERR - 7,
    AVIOCTRL_ERR_GETWIFI = AVIOCTRL_ERR - 8,
    AVIOCTRL_ERR_SETRECORD = AVIOCTRL_ERR - 9,
    AVIOCTRL_ERR_SETRCDDURA = AVIOCTRL_ERR - 10,
    AVIOCTRL_ERR_LISTEVENT = AVIOCTRL_ERR - 11,
    AVIOCTRL_ERR_PLAYBACK = AVIOCTRL_ERR - 12,

    AVIOCTRL_ERR_INVALIDCHANNEL = AVIOCTRL_ERR - 0x20,
} ENUM_AVIOCTRL_ERROR; //APP don't use it now

// ServType, unsigned long, 32 bits, is a bit mask for function declareation
// bit value "0" means function is valid or enabled
// in contract, bit value "1" means function is invalid or disabled.
// ** for more details, see "ServiceType Definitation for AVAPIs"
// 
// Defined bits are listed below:
//----------------------------------------------
// bit		fuction
// 0		Audio in, from Device to Mobile
// 1		Audio out, from Mobile to Device 
// 2		PT function
// 3		Event List function
// 4		Play back function (require Event List function)
// 5		Wi-Fi setting function
// 6		Event Setting Function
// 7		Recording Setting function
// 8		SDCard formattable function
// 9		Video flip function
// 10		Environment mode
// 11		Multi-stream selectable
// 12		Audio out encoding format

// The original enum below is obsoleted.
typedef enum {
    SERVTYPE_IPCAM_DWH = 0x00,
    SERVTYPE_RAS_DWF = 0x01,
    SERVTYPE_IOTCAM_8125 = 0x10,
    SERVTYPE_IOTCAM_8125PT = 0x11,
    SERVTYPE_IOTCAM_8126 = 0x12,
    SERVTYPE_IOTCAM_8126PT = 0x13,
} ENUM_SERVICE_TYPE;

// AVIOCTRL Quality Type
typedef enum {
    AVIOCTRL_QUALITY_UNKNOWN = 0x00, AVIOCTRL_QUALITY_MAX = 0x01,	// ex. 640*480, 15fps, 320kbps (or 1280x720, 5fps, 320kbps)
    AVIOCTRL_QUALITY_HIGH = 0x02,	// ex. 640*480, 10fps, 256kbps
    AVIOCTRL_QUALITY_MIDDLE = 0x03,	// ex. 320*240, 15fps, 256kbps
    AVIOCTRL_QUALITY_LOW = 0x04, // ex. 320*240, 10fps, 128kbps
    AVIOCTRL_QUALITY_MIN = 0x05,	// ex. 160*120, 10fps, 64kbps
} ENUM_QUALITY_LEVEL;

typedef enum {
    AVIOTC_WIFIAPMODE_NULL = 0x00, AVIOTC_WIFIAPMODE_MANAGED = 0x01, AVIOTC_WIFIAPMODE_ADHOC = 0x02,
} ENUM_AP_MODE;

typedef enum {
    AVIOTC_WIFIAPENC_INVALID = 0x00, AVIOTC_WIFIAPENC_NONE = 0x01, //
    AVIOTC_WIFIAPENC_WEP = 0x02, //WEP, for no password
    AVIOTC_WIFIAPENC_WPA_TKIP = 0x03,
    AVIOTC_WIFIAPENC_WPA_AES = 0x04,
    AVIOTC_WIFIAPENC_WPA2_TKIP = 0x05,
    AVIOTC_WIFIAPENC_WPA2_AES = 0x06,

    AVIOTC_WIFIAPENC_WPA_PSK_TKIP = 0x07,
    AVIOTC_WIFIAPENC_WPA_PSK_AES = 0x08,
    AVIOTC_WIFIAPENC_WPA2_PSK_TKIP = 0x09,
    AVIOTC_WIFIAPENC_WPA2_PSK_AES = 0x0A,

} ENUM_AP_ENCTYPE;

// AVIOCTRL Event Type
typedef enum {
    AVIOCTRL_EVENT_ALL = 0x00,	// all event type(general APP-->IPCamera)
    AVIOCTRL_EVENT_MOTIONDECT = 0x01,	// motion detect start//==s==
    AVIOCTRL_EVENT_VIDEOLOST = 0x02,	// video lost alarm
    AVIOCTRL_EVENT_IOALARM = 0x03, // io alarmin start //---s--

    AVIOCTRL_EVENT_MOTIONPASS = 0x04, // motion detect end  //==e==
    AVIOCTRL_EVENT_VIDEORESUME = 0x05,	// video resume
    AVIOCTRL_EVENT_IOALARMPASS = 0x06, // IO alarmin end   //---e--

    AVIOCTRL_EVENT_EXPT_REBOOT = 0x10, // system exception reboot
    AVIOCTRL_EVENT_SDFAULT = 0x11, // sd record exception
} ENUM_EVENTTYPE;

// AVIOCTRL Record Type
typedef enum {
    AVIOTC_RECORDTYPE_OFF = 0x00, AVIOTC_RECORDTYPE_FULLTIME = 0x01, AVIOTC_RECORDTYPE_ALARM = 0x02, AVIOTC_RECORDTYPE_MANUAL = 0x03,
} ENUM_RECORD_TYPE;

// AVIOCTRL Play Record Command
typedef enum {
    AVIOCTRL_RECORD_PLAY_PAUSE = 0x00, AVIOCTRL_RECORD_PLAY_STOP = 0x01, AVIOCTRL_RECORD_PLAY_STEPFORWARD = 0x02, //now, APP no use
    AVIOCTRL_RECORD_PLAY_STEPBACKWARD = 0x03, //now, APP no use
    AVIOCTRL_RECORD_PLAY_FORWARD = 0x04, //now, APP no use
    AVIOCTRL_RECORD_PLAY_BACKWARD = 0x05, //now, APP no use
    AVIOCTRL_RECORD_PLAY_SEEKTIME = 0x06, //now, APP no use
    AVIOCTRL_RECORD_PLAY_END = 0x07,
    AVIOCTRL_RECORD_PLAY_START = 0x10,
} ENUM_PLAYCONTROL;

// AVIOCTRL Environment Mode
typedef enum {
    AVIOCTRL_ENVIRONMENT_INDOOR_50HZ = 0x00,
    AVIOCTRL_ENVIRONMENT_INDOOR_60HZ = 0x01,
    AVIOCTRL_ENVIRONMENT_OUTDOOR = 0x02,
    AVIOCTRL_ENVIRONMENT_NIGHT = 0x03,
} ENUM_ENVIRONMENT_MODE;

// AVIOCTRL Video Flip Mode
typedef enum {
    AVIOCTRL_VIDEOMODE_NORMAL = 0x00,
    AVIOCTRL_VIDEOMODE_FLIP = 0x01,
    AVIOCTRL_VIDEOMODE_MIRROR = 0x02,
    AVIOCTRL_VIDEOMODE_FLIP_MIRROR = 0x03,
} ENUM_VIDEO_MODE;

// AVIOCTRL PTZ Command Value
typedef enum {
    AVIOCTRL_PTZ_STOP = 0,
    AVIOCTRL_PTZ_UP = 1,
    AVIOCTRL_PTZ_DOWN = 2,
    AVIOCTRL_PTZ_LEFT = 3,
    AVIOCTRL_PTZ_LEFT_UP = 4,
    AVIOCTRL_PTZ_LEFT_DOWN = 5,
    AVIOCTRL_PTZ_RIGHT = 6,
    AVIOCTRL_PTZ_RIGHT_UP = 7,
    AVIOCTRL_PTZ_RIGHT_DOWN = 8,
    AVIOCTRL_PTZ_AUTO = 9,
    AVIOCTRL_PTZ_SET_POINT = 10,
    AVIOCTRL_PTZ_CLEAR_POINT = 11,
    AVIOCTRL_PTZ_GOTO_POINT = 12,

    AVIOCTRL_PTZ_SET_MODE_START = 13,
    AVIOCTRL_PTZ_SET_MODE_STOP = 14,
    AVIOCTRL_PTZ_MODE_RUN = 15,

    AVIOCTRL_PTZ_MENU_OPEN = 16,
    AVIOCTRL_PTZ_MENU_EXIT = 17,
    AVIOCTRL_PTZ_MENU_ENTER = 18,

    AVIOCTRL_PTZ_FLIP = 19,
    AVIOCTRL_PTZ_START = 20,

    AVIOCTRL_LENS_APERTURE_OPEN = 21,
    AVIOCTRL_LENS_APERTURE_CLOSE = 22,

    AVIOCTRL_LENS_ZOOM_IN = 23,
    AVIOCTRL_LENS_ZOOM_OUT = 24,

    AVIOCTRL_LENS_FOCAL_NEAR = 25,
    AVIOCTRL_LENS_FOCAL_FAR = 26,

    AVIOCTRL_AUTO_PAN_SPEED = 27,
    AVIOCTRL_AUTO_PAN_LIMIT = 28,
    AVIOCTRL_AUTO_PAN_START = 29,

    AVIOCTRL_PATTERN_START = 30,
    AVIOCTRL_PATTERN_STOP = 31,
    AVIOCTRL_PATTERN_RUN = 32,

    AVIOCTRL_SET_AUX = 33,
    AVIOCTRL_CLEAR_AUX = 34,
    AVIOCTRL_MOTOR_RESET_POSITION = 35,
} ENUM_PTZCMD;

/////////////////////////////////////////////////////////////////////////////
///////////////////////// Message Body Define ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*
 IOTYPE_USER_IPCAM_START 				= 0x01FF,
 IOTYPE_USER_IPCAM_STOP	 				= 0x02FF,
 IOTYPE_USER_IPCAM_AUDIOSTART 			= 0x0300,
 IOTYPE_USER_IPCAM_AUDIOSTOP 			= 0x0301,
 IOTYPE_USER_IPCAM_SPEAKERSTART 			= 0x0350,
 IOTYPE_USER_IPCAM_SPEAKERSTOP 			= 0x0351,
 ** @struct SMsgAVIoctrlAVStream
 */
typedef struct {
    unsigned int channel; // Camera Index
    unsigned int reserved;
} SMsgAVIoctrlAVStream;

/*
 IOTYPE_USER_IPCAM_GETSTREAMCTRL_REQ		= 0x0322,
 ** @struct SMsgAVIoctrlGetStreamCtrlReq
 */
typedef struct {
    unsigned int channel;	// Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetStreamCtrlReq;

/*
 IOTYPE_USER_IPCAM_SETSTREAMCTRL_REQ		= 0x0320,
 IOTYPE_USER_IPCAM_GETSTREAMCTRL_RESP	= 0x0323,
 ** @struct SMsgAVIoctrlSetStreamCtrlReq, SMsgAVIoctrlGetStreamCtrlResq
 */
typedef struct {
    unsigned int channel;	// Camera Index
    unsigned char quality;	//refer to ENUM_QUALITY_LEVEL
    unsigned char reserved[3];
} SMsgAVIoctrlSetStreamCtrlReq, SMsgAVIoctrlGetStreamCtrlResq;

/*
 IOTYPE_USER_IPCAM_SETSTREAMCTRL_RESP	= 0x0321,
 ** @struct SMsgAVIoctrlSetStreamCtrlResp
 */
typedef struct {
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
} SMsgAVIoctrlSetStreamCtrlResp;

/*
 IOTYPE_USER_IPCAM_GETMOTIONDETECT_REQ	= 0x0326,
 ** @struct SMsgAVIoctrlGetMotionDetectReq
 */
typedef struct {
    unsigned int channel; 	// Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetMotionDetectReq;

/*
 IOTYPE_USER_IPCAM_SETMOTIONDETECT_REQ		= 0x0324,
 IOTYPE_USER_IPCAM_GETMOTIONDETECT_RESP		= 0x0327,
 ** @struct SMsgAVIoctrlSetMotionDetectReq, SMsgAVIoctrlGetMotionDetectResp
 */
typedef struct {
    unsigned int channel; 		// Camera Index
    unsigned int sensitivity; 	// 0(Disabled) ~ 100(MAX):
    // index		sensitivity value
    // 0			0
    // 1			25
    // 2			50
    // 3			75
    // 4			100
} SMsgAVIoctrlSetMotionDetectReq, SMsgAVIoctrlGetMotionDetectResp;

/*
 IOTYPE_USER_IPCAM_SETMOTIONDETECT_RESP	= 0x0325,
 ** @struct SMsgAVIoctrlSetMotionDetectResp
 */
typedef struct {
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
} SMsgAVIoctrlSetMotionDetectResp;

/*
 IOTYPE_USER_IPCAM_DEVINFO_REQ			= 0x0330,
 ** @struct SMsgAVIoctrlDeviceInfoReq
 */
typedef struct {
    unsigned char reserved[4];
} SMsgAVIoctrlDeviceInfoReq;

/*
 IOTYPE_USER_IPCAM_DEVINFO_RESP			= 0x0331,
 ** @struct SMsgAVIoctrlDeviceInfo
 */
typedef struct {
    unsigned char model[16];	// IPCam mode
    unsigned char vendor[16];	// IPCam manufacturer
    unsigned int version;		// IPCam firmware version	ex. v1.2.3.4 => 0x01020304;  v1.0.0.2 => 0x01000002
    unsigned int channel;		// Camera index
    unsigned int total;			// 0: No cards been detected or an unrecognizeable sdcard that could not be re-formatted.
    // -1: if camera detect an unrecognizable sdcard, and could be re-formatted
    // otherwise: return total space size of sdcard (MBytes)

    unsigned int free;			// Free space size of sdcard (MBytes)
    unsigned char reserved[8];	// reserved
} SMsgAVIoctrlDeviceInfoResp;

/*
 IOTYPE_USER_IPCAM_SETPASSWORD_REQ		= 0x0332,
 ** @struct SMsgAVIoctrlSetPasswdReq
 */
typedef struct {
    char oldpasswd[32];			// The old security code
    char newpasswd[32];			// The new security code
} SMsgAVIoctrlSetPasswdReq;

/*
 IOTYPE_USER_IPCAM_SETPASSWORD_RESP		= 0x0333,
 ** @struct SMsgAVIoctrlSetPasswdResp
 */
typedef struct {
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
} SMsgAVIoctrlSetPasswdResp;

/*
 IOTYPE_USER_IPCAM_LISTWIFIAP_REQ		= 0x0340,
 ** @struct SMsgAVIoctrlListWifiApReq
 */
typedef struct {
    unsigned char reserved[4];
} SMsgAVIoctrlListWifiApReq;

typedef struct {
    char ssid[32]; 				// WiFi ssid
    char mode;	   				// refer to ENUM_AP_MODE
    char enctype;  				// refer to ENUM_AP_ENCTYPE
    char signal;   				// signal intensity 0--100%
    char status;   				// 0 : invalid ssid or disconnected
    // 1 : connected with default gateway
    // 2 : unmatched password
    // 3 : weak signal and connected
    // 4 : selected:
    //		- password matched and
    //		- disconnected or connected but not default gateway
} SWifiAp;

/*
 IOTYPE_USER_IPCAM_LISTWIFIAP_RESP		= 0x0341,
 ** @struct SMsgAVIoctrlListWifiApResp
 */
typedef struct {
    unsigned int number; // MAX number: 1024(IOCtrl packet size) / 36(bytes) = 28
    SWifiAp stWifiAp[1];
} SMsgAVIoctrlListWifiApResp;

/*
 IOTYPE_USER_IPCAM_SETWIFI_REQ			= 0x0342,
 ** @struct SMsgAVIoctrlSetWifiReq
 */
typedef struct {
    unsigned char ssid[32];			//WiFi ssid
    unsigned char password[32];		//if exist, WiFi password
    unsigned char mode;				//refer to ENUM_AP_MODE
    unsigned char enctype;			//refer to ENUM_AP_ENCTYPE
    unsigned char reserved[10];
} SMsgAVIoctrlSetWifiReq;

//IOTYPE_USER_IPCAM_SETWIFI_REQ_2		= 0x0346,
typedef struct {
    unsigned char ssid[32];		// WiFi ssid
    unsigned char password[64];	// if exist, WiFi password
    unsigned char mode;			// refer to ENUM_AP_MODE
    unsigned char enctype;		// refer to ENUM_AP_ENCTYPE
    unsigned char reserved[10];
} SMsgAVIoctrlSetWifiReq2;

/*
 IOTYPE_USER_IPCAM_SETWIFI_RESP			= 0x0343,
 ** @struct SMsgAVIoctrlSetWifiResp
 */
typedef struct {
    int result; //0: wifi connected; 1: failed to connect
    unsigned char reserved[4];
} SMsgAVIoctrlSetWifiResp;

/*
 IOTYPE_USER_IPCAM_GETWIFI_REQ			= 0x0344,
 ** @struct SMsgAVIoctrlGetWifiReq
 */
typedef struct {
    unsigned char reserved[4];
} SMsgAVIoctrlGetWifiReq;

/*
 IOTYPE_USER_IPCAM_GETWIFI_RESP			= 0x0345,
 ** @struct SMsgAVIoctrlGetWifiResp //if no wifi connected, members of SMsgAVIoctrlGetWifiResp are all 0
 */
typedef struct {
    unsigned char ssid[32];		// WiFi ssid
    unsigned char password[32]; // WiFi password if not empty
    unsigned char mode;			// refer to ENUM_AP_MODE
    unsigned char enctype;		// refer to ENUM_AP_ENCTYPE
    unsigned char signal;		// signal intensity 0--100%
    unsigned char status;		// refer to "status" of SWifiAp
} SMsgAVIoctrlGetWifiResp;

//changed: WI-FI Password 32bit Change to 64bit 
//IOTYPE_USER_IPCAM_GETWIFI_RESP_2    = 0x0347,
typedef struct {
    unsigned char ssid[32];	 // WiFi ssid
    unsigned char password[64]; // WiFi password if not empty
    unsigned char mode;	// refer to ENUM_AP_MODE
    unsigned char enctype; // refer to ENUM_AP_ENCTYPE
    unsigned char signal;  // signal intensity 0--100%
    unsigned char status;  // refer to "status" of SWifiAp
} SMsgAVIoctrlGetWifiResp2;

/*
 IOTYPE_USER_IPCAM_GETRECORD_REQ			= 0x0312,
 ** @struct SMsgAVIoctrlGetRecordReq
 */
typedef struct {
    unsigned int channel; // Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetRecordReq;

/*
 IOTYPE_USER_IPCAM_SETRECORD_REQ			= 0x0310,
 IOTYPE_USER_IPCAM_GETRECORD_RESP		= 0x0313,
 ** @struct SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq
 */
typedef struct {
    unsigned int channel;		// Camera Index
    unsigned int recordType;	// Refer to ENUM_RECORD_TYPE
    unsigned char reserved[4];
} SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq;

/*
 IOTYPE_USER_IPCAM_SETRECORD_RESP		= 0x0311,
 ** @struct SMsgAVIoctrlSetRecordResp
 */
typedef struct {
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
} SMsgAVIoctrlSetRecordResp;

/*
 IOTYPE_USER_IPCAM_GETRCD_DURATION_REQ	= 0x0316,
 ** @struct SMsgAVIoctrlGetRcdDurationReq
 */
typedef struct {
    unsigned int channel; // Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetRcdDurationReq;

/*
 IOTYPE_USER_IPCAM_SETRCD_DURATION_REQ	= 0x0314,
 IOTYPE_USER_IPCAM_GETRCD_DURATION_RESP  = 0x0317,
 ** @struct SMsgAVIoctrlSetRcdDurationReq, SMsgAVIoctrlGetRcdDurationResp
 */
typedef struct {
    unsigned int channel; 		// Camera Index
    unsigned int presecond; 	// pre-recording (sec)
    unsigned int durasecond;	// recording (sec)
} SMsgAVIoctrlSetRcdDurationReq, SMsgAVIoctrlGetRcdDurationResp;

/*
 IOTYPE_USER_IPCAM_SETRCD_DURATION_RESP  = 0x0315,
 ** @struct SMsgAVIoctrlSetRcdDurationResp
 */
typedef struct {
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
} SMsgAVIoctrlSetRcdDurationResp;

typedef struct {
    unsigned short year;	// The number of year.
    unsigned char month;	// The number of months since January, in the range 1 to 12.
    unsigned char day;		// The day of the month, in the range 1 to 31.
    unsigned char wday;		// The number of days since Sunday, in the range 0 to 6. (Sunday = 0, Monday = 1, ...)
    unsigned char hour;     // The number of hours past midnight, in the range 0 to 23.
    unsigned char minute;   // The number of minutes after the hour, in the range 0 to 59.
    unsigned char second;   // The number of seconds after the minute, in the range 0 to 59.
} STimeDay;

/*
 IOTYPE_USER_IPCAM_LISTEVENT_REQ			= 0x0318,
 ** @struct SMsgAVIoctrlListEventReq
 */
typedef struct {
    unsigned int channel; 		// Camera Index
    STimeDay stStartTime; 		// Search event from ...
    STimeDay stEndTime;	  		// ... to (search event)
    unsigned char event;  		// event type, refer to ENUM_EVENTTYPE
    unsigned char status; 		// 0x00: Recording file exists, Event unreaded
    // 0x01: Recording file exists, Event readed
    // 0x02: No Recording file in the event
    unsigned char reserved[2];
} SMsgAVIoctrlListEventReq;

typedef struct {
    STimeDay stTime;
    unsigned char event;
    unsigned char status;	// 0x00: Recording file exists, Event unreaded
    // 0x01: Recording file exists, Event readed
    // 0x02: No Recording file in the event
    unsigned char reserved[2];
} SAvEvent;

/*
 IOTYPE_USER_IPCAM_LISTEVENT_RESP		= 0x0319,
 ** @struct SMsgAVIoctrlListEventResp
 */
typedef struct {
    unsigned int channel;		// Camera Index
    unsigned int total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
    // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SAvEvent stEvent[1];		// The first memory address of the events in this package
} SMsgAVIoctrlListEventResp;

/*
 IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 	= 0x031A,
 ** @struct SMsgAVIoctrlPlayRecord
 */
typedef struct {
    unsigned int channel;	// Camera Index
    unsigned int command;	// play record command. refer to ENUM_PLAYCONTROL
    unsigned int Param;		// command param, that the user defined
    STimeDay stTimeDay;		// Event time from ListEvent
    unsigned char reserved[4];
} SMsgAVIoctrlPlayRecord;

/*
 IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
 ** @struct SMsgAVIoctrlPlayRecordResp
 */
typedef struct {
    unsigned int command;	// Play record command. refer to ENUM_PLAYCONTROL
    unsigned int result; 	// Depends on command
    // when is AVIOCTRL_RECORD_PLAY_START:
    //	result>=0   real channel no used by device for playback
    //	result <0	error
    //			-1	playback error
    //			-2	exceed max allow client amount
    unsigned char reserved[4];
} SMsgAVIoctrlPlayRecordResp; // only for play record start command

/*
 IOTYPE_USER_IPCAM_PTZ_COMMAND	= 0x1001,	// P2P Ptz Command Msg
 ** @struct SMsgAVIoctrlPtzCmd
 */
typedef struct {
    unsigned char control;	// PTZ control command, refer to ENUM_PTZCMD
    unsigned char speed;	// PTZ control speed
    unsigned char point;	// no use in APP so far. preset position, for RS485 PT
    unsigned char limit;	// no use in APP so far.
    unsigned char aux;		// no use in APP so far. auxiliary switch, for RS485 PT
    unsigned char channel;	// camera index
    unsigned char reserve[2];
} SMsgAVIoctrlPtzCmd;

/*
 IOTYPE_USER_IPCAM_EVENT_REPORT	= 0x1FFF,	// Device Event Report Msg
 */
/** @struct SMsgAVIoctrlEvent
 */
typedef struct {
    STimeDay stTime;
    unsigned long time; 	// UTC Time
    unsigned int channel; 	// Camera Index
    unsigned int event; 	// Event Type
    unsigned char reserved[4];
} SMsgAVIoctrlEvent;

#if 0

/* 	IOTYPE_USER_IPCAM_GET_EVENTCONFIG_REQ	= 0x0400,	// Get Event Config Msg Request 
 */
/** @struct SMsgAVIoctrlGetEventConfig
 */
typedef struct
{
    unsigned int channel; 		  //Camera Index
    unsigned char externIoOutIndex;//extern out index: bit0->io0 bit1->io1 ... bit7->io7;=1: get this io value or not get
    unsigned char externIoInIndex;//extern in index: bit0->io0 bit1->io1 ... bit7->io7; =1: get this io value or not get
    char reserved[2];
}SMsgAVIoctrlGetEventConfig;

/*
 IOTYPE_USER_IPCAM_GET_EVENTCONFIG_RESP	= 0x0401,	// Get Event Config Msg Response
 IOTYPE_USER_IPCAM_SET_EVENTCONFIG_REQ	= 0x0402,	// Set Event Config Msg req
 */
/* @struct SMsgAVIoctrlSetEventConfig
 * @struct SMsgAVIoctrlGetEventCfgResp
 */
typedef struct
{
    unsigned int channel;        // Camera Index
    unsigned char mail;// enable send email
    unsigned char ftp;// enable ftp upload photo
    unsigned char externIoOutStatus;// enable extern io output //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
    unsigned char p2pPushMsg;// enable p2p push msg
    unsigned char externIoInStatus;// enable extern io input  //bit0->io0 bit1->io1 ... bit7->io7; 1:on; 0:off
    char reserved[3];
}SMsgAVIoctrlSetEventConfig, SMsgAVIoctrlGetEventCfgResp;

/*
 IOTYPE_USER_IPCAM_SET_EVENTCONFIG_RESP	= 0x0403,	// Set Event Config Msg resp
 */
/** @struct SMsgAVIoctrlSetEventCfgResp
 */
typedef struct
{
    unsigned int channel; 	// Camera Index
    unsigned int result;// 0: success; otherwise: failed.
}SMsgAVIoctrlSetEventCfgResp;

#endif

/*
 IOTYPE_USER_IPCAM_SET_ENVIRONMENT_REQ		= 0x0360,
 ** @struct SMsgAVIoctrlSetEnvironmentReq
 */
typedef struct {
    unsigned int channel;		// Camera Index
    unsigned char mode;			// refer to ENUM_ENVIRONMENT_MODE
    unsigned char reserved[3];
} SMsgAVIoctrlSetEnvironmentReq;

/*
 IOTYPE_USER_IPCAM_SET_ENVIRONMENT_RESP		= 0x0361,
 ** @struct SMsgAVIoctrlSetEnvironmentResp
 */
typedef struct {
    unsigned int channel; 		// Camera Index
    unsigned char result;		// 0: success; otherwise: failed.
    unsigned char reserved[3];
} SMsgAVIoctrlSetEnvironmentResp;

/*
 IOTYPE_USER_IPCAM_GET_ENVIRONMENT_REQ		= 0x0362,
 ** @struct SMsgAVIoctrlGetEnvironmentReq
 */
typedef struct {
    unsigned int channel; 	// Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetEnvironmentReq;

/*
 IOTYPE_USER_IPCAM_GET_ENVIRONMENT_RESP		= 0x0363,
 ** @struct SMsgAVIoctrlGetEnvironmentResp
 */
typedef struct {
    unsigned int channel; 		// Camera Index
    unsigned char mode;			// refer to ENUM_ENVIRONMENT_MODE
    unsigned char reserved[3];
} SMsgAVIoctrlGetEnvironmentResp;

/*
 IOTYPE_USER_IPCAM_SET_VIDEOMODE_REQ			= 0x0370,
 ** @struct SMsgAVIoctrlSetVideoModeReq
 */
typedef struct {
    unsigned int channel;	// Camera Index
    unsigned char mode;		// refer to ENUM_VIDEO_MODE
    unsigned char reserved[3];
} SMsgAVIoctrlSetVideoModeReq;

/*
 IOTYPE_USER_IPCAM_SET_VIDEOMODE_RESP		= 0x0371,
 ** @struct SMsgAVIoctrlSetVideoModeResp
 */
typedef struct {
    unsigned int channel; 	// Camera Index
    unsigned char result;	// 0: success; otherwise: failed.
    unsigned char reserved[3];
} SMsgAVIoctrlSetVideoModeResp;

/*
 IOTYPE_USER_IPCAM_GET_VIDEOMODE_REQ			= 0x0372,
 ** @struct SMsgAVIoctrlGetVideoModeReq
 */
typedef struct {
    unsigned int channel; 	// Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlGetVideoModeReq;

/*
 IOTYPE_USER_IPCAM_GET_VIDEOMODE_RESP		= 0x0373,
 ** @struct SMsgAVIoctrlGetVideoModeResp
 */
typedef struct {
    unsigned int channel; 	// Camera Index
    unsigned char mode;		// refer to ENUM_VIDEO_MODE
    unsigned char reserved[3];
} SMsgAVIoctrlGetVideoModeResp;

/*
 /IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ			= 0x0380,
 ** @struct SMsgAVIoctrlFormatExtStorageReq
 */
typedef struct {
    unsigned int storage; 	// Storage index (ex. sdcard slot = 0, internal flash = 1, ...)
    unsigned char reserved[4];
} SMsgAVIoctrlFormatExtStorageReq;

/*
 IOTYPE_USER_IPCAM_FORMATEXTSTORAGE_REQ		= 0x0381,
 ** @struct SMsgAVIoctrlFormatExtStorageResp
 */
typedef struct {
    unsigned int storage; 	// Storage index
    unsigned char result;	// 0: success;
    // -1: format command is not supported.
    // otherwise: failed.
    unsigned char reserved[3];
} SMsgAVIoctrlFormatExtStorageResp;

typedef struct {
    unsigned short index;		// the stream index of camera
    unsigned short channel;		// the channel index used in AVAPIs, that is ChID in avServStart2(...,ChID)
    char reserved[4];
} SStreamDef;

/*	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_REQ			= 0x0328,
 */
typedef struct {
    unsigned char reserved[4];
} SMsgAVIoctrlGetSupportStreamReq;

/*	IOTYPE_USER_IPCAM_GETSUPPORTSTREAM_RESP			= 0x0329,
 */
typedef struct {
    unsigned int number; 		// the quanity of supported audio&video stream or video stream
    SStreamDef streams[1];
} SMsgAVIoctrlGetSupportStreamResp;

/* IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_REQ			= 0x032A, //used to speak. but once camera is connected by App, send this at once.
 */
typedef struct {
    unsigned int channel;		// camera index
    char reserved[4];
} SMsgAVIoctrlGetAudioOutFormatReq;

/* IOTYPE_USER_IPCAM_GETAUDIOOUTFORMAT_RESP			= 0x032B,
 */
typedef struct {
    unsigned int channel;		// camera index
    int format;					// refer to ENUM_CODECID in AVFRAMEINFO.h
    char reserved[4];
} SMsgAVIoctrlGetAudioOutFormatResp;

/* IOTYPE_USER_IPCAM_RECEIVE_FIRST_IFRAME			= 0x1002,
 */
typedef struct {
    unsigned int channel;		// camera index
    char reserved[4];
} SMsgAVIoctrlReceiveFirstIFrame;

/* IOTYPE_USER_IPCAM_GET_FLOWINFO_REQ              = 0x390
 */
typedef struct {
    unsigned int channel;			// camera index
    unsigned int collect_interval;	// seconds of interval to collect flow information
    // send 0 indicates stop collecting.
} SMsgAVIoctrlGetFlowInfoReq;

/* IOTYPE_USER_IPCAM_GET_FLOWINFO_RESP            = 0x391
 */
typedef struct {
    unsigned int channel;			// camera index
    unsigned int collect_interval;	// seconds of interval client will collect flow information
} SMsgAVIoctrlGetFlowInfoResp;

/* IOTYPE_USER_IPCAM_CURRENT_FLOWINFO              = 0x392
 */
typedef struct {
    unsigned int channel;						// camera index
    unsigned int total_frame_count;				// Total frame count in the specified interval
    unsigned int lost_incomplete_frame_count;	// Total lost and incomplete frame count in the specified interval
    unsigned int total_expected_frame_size;		// Total expected frame size from avRecvFrameData2()
    unsigned int total_actual_frame_size;		// Total actual frame size from avRecvFrameData2()
    unsigned int timestamp_ms;					// Timestamp in millisecond of this report.
    char reserved[8];
} SMsgAVIoctrlCurrentFlowInfo;

/* IOTYPE_USER_IPCAM_GET_TIMEZONE_REQ               = 0x3A0
 * IOTYPE_USER_IPCAM_GET_TIMEZONE_RESP              = 0x3A1
 * IOTYPE_USER_IPCAM_SET_TIMEZONE_REQ               = 0x3B0
 * IOTYPE_USER_IPCAM_SET_TIMEZONE_RESP              = 0x3B1
 */
typedef struct {
    int cbSize;							// the following package size in bytes, should be sizeof(SMsgAVIoctrlTimeZone)
    int nIsSupportTimeZone;
    int nGMTDiff;						// the difference between GMT in hours
    char szTimeZoneString[256];			// the timezone description string in multi-bytes char format
} SMsgAVIoctrlTimeZone;

#endif
