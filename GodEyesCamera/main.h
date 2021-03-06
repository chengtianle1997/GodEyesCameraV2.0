#pragma once
#include "iostream"
#include "Timer.h"
#include "CameraSDK.h"
#include "FFmpegEncode.h"
#include "GaussCal.h"
#include "ClientNet.h"
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <queue>
#include "cmdline.h"
#include "FileManager.h"
#include "time.h"

using namespace std;

using namespace cv;

stop_watch watch;

Camera camera;

Encoder encoder;

GaussCal Gausscal;

ClientNet client;

FileManager filemanager;

std::mutex m;

GaussCalParam Calparam;

GaussIdentifyParam IdentifyParam;

CameraInitParam camerainitparam;

EncoderParam encoderparam;

EncodeParam encodeparam;

ClientParam clientparam;

CsClientParam csclientparam;

DsClientParam dsclientparam;

CammeraROISetting roi_setting;

//State of occupation
BOOL Buffer0Mutex = 0;
BOOL Buffer1Mutex = 0;

//Indicate got image
BOOL GetImage0 = 0;
BOOL GetImage1 = 0;

//Indicate Calculation end
BOOL CalEnd0 = 0;
BOOL CalEnd1 = 0;

//Indicate the require to encode
BOOL CodeState0 = 0;
BOOL CodeState1 = 0;

//Indicate the require to detect   
//1 represent the buffer to detect
BOOL DetectState0 = 0;
BOOL DetectState1 = 0;


//The double buffer
unsigned char* Buffer0;
unsigned char* Buffer1;

unsigned char* Buffer0Copy;
unsigned char* Buffer1Copy;
//The information of buffer
MV_FRAME_OUT_INFO_EX Buffer0Info;
MV_FRAME_OUT_INFO_EX Buffer1Info;
//The Time Stamp of buffer
SYSTEMTIME Buffer0Time;
SYSTEMTIME Buffer1Time;

int SizeofPixels = 0;
int ImageWidth = 0;
int ImageHeight = 0;

//The Exit Instruction(Set 1 to Stop)
int AcqExit = 0;
int CalExit = 0;
int EncodeExit = 0;
int SendExit = 0;
int TimerExit = 0;
int DetectExit = 0;

//Functional choice
int ResVisAuto = 0;
int ResVisManu = 0;
int EncodeEnable = 0;
int CalEnable = 0;
int EnableSendData = 0; 
//PicSyc
int EnableCSSend = 0;
//DataSyc
int EnableDSSend = 0;
//The New Way to send
int EnableFinalSend = 0;
//LocalServer Or RemoteServer
int EnableRemoteServer = 0;

int PrintDevList = 0;
int SetDevNum = 0;

//Test Encode and Send
//int EnableSendData = 1;
//int EncodeEnable = 1;
//////////////////////

int PerforFramecnt = 0;
int PerforFrameenc = 0;
//Record The FrameRate Every Second
int PerforFramecntAll = 40;
int PerforFrameencAll = 10;
//Wanted FrameRate input
int FrameRateControlPic = 3;
int FrameRateControlData = 3;

//Is First Second
bool IsFirst = true;
bool IsSecond = false;

//The Param for Detect thread
int MaxCnt = 0;
int BeatRecord = 0;

//The Server Information
int Serverport;
int ServerStartup = 8001;
const char* ServerAddr = "127.0.0.1";
//const char* CsServerAddr = "127.0.0.1";

//The Socket Package
//SocketPackage *Sockpack = { 0 };
//The sending queue

static queue<SocketPackage> SendQueue;

//The Application Entrance
//int DeviceNum = 0;
const char* FilePath = "D:\\EncodeResult";
char* FinalPath;
const char* SrNum;

int Format = 0;

bool AnalyzeEnd = false;
bool CalAvrEnd = false;
bool FindBeatEnable = false;

//去水印采集图像
bool UnableTimeStamp = false;

// 0: Calculate Camera (Encode and Calculate) 1: VO Camera or Encode Only Option
int CameraType = 0;
// 选拍方式 1：找拍  2：图像分类  3：全计算模式
int method = 2;

//Mjpeg TimeStamp Save
ofstream mjpegtimestamp;

//Auto Exposure adjustment param
BrightNess bright;
int min_exp = 2000;
int max_exp = 20000;
int exp_step = 500;