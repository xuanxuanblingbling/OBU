/*********************************************************************** 
* 文 件 名 称 ： NewFourSpanLog.hpp 
* 功 能 描 述 ： 通用读文件类头文件 
* 开 发 人 员 ： YaoZhiqiang * 日期       
版本  修改人    描述
* ========== ======= ========= ======================================= 
* 2020-08-18 V1.0    YaoZhiqiang   Create * * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/
#ifndef __NEW_FOUR_SPAN_LOG_HPP__
#define __NEW_FOUR_SPAN_LOG_HPP__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*! @file NewFourSpanLog.hpp 
* @brief This file defines NewFourSpanLog class. 
*/
/*! @class NewFourSpanLog 
*  @brief A helper class used to handle log files 
*  @addtogroup HelperClass *  
@{ */
class NewFourSpanFile{public:    
/*!    
* Constructor, takes a C style string as parameter    
* @param file C style string containing a file URI.    
*/    
NewFourSpanFile(string &p_sFileName);    
NewFourSpanFile() {}    
~NewFourSpanFile();    
int OpenFile();    
int WriteFile(uint8_t *p_n8Data, size_t p_u32Len);    
int ReadFile(uint8_t *p_n8Data, size_t p_u32Len);    
string GetFileName() const { return m_file_name; }    
void SetFileName(string &file_name) { m_file_name = file_name; }    
bool IsFileExist();    int CloseFile();    
//操作符重载函数, 会被自动调用    
bool operator==(const NewFourSpanFile &obj1) const    {        
//相同返回0，不相同返回非0        
if (!this->m_file_name.compare(obj1.m_file_name))        
{            
return true;        
}       
 else        
 {            
return false;        
}    
}public:    
fstream *m_file_stream;
private:    
string m_file_name;
};
typedef struct{    int m_MsgSelfID;      
  /* 自身的 ID 后三位 */    
  char m_BsmIDbuf[8];         
  /* ID的8位字符串 */    
  long m_MsgSelfGPSLatitude;   
  /* 接收到此消息时的本车的 GPS 纬度 */    
  long m_MsgSelfGPSLongtitude; 
  /* 接收到此消息时的本车的 GPS 经度 */    
  int m_MsgSelfSpeed;         
  /* 接收到此消息时的本车的速度 */    
  int m_MsgSelfHeading;        
  /* 接收到此消息时的本车航向 */
  } __attribute__((packed)) TMsgSelfBsmSet_t;

  #define MSG_SELF_BSM_LEN sizeof(TMsgSelfBsmSet_t)
  typedef struct{    
  int m_MsgOtherID;          
  /* 消息中 id 的后三位数字 */    
  int m_MsgOtherType;        
  /* 1:BSM 2:RSM 3:RSI 4:SPAT 5:MAP */    
  int m_MsgOtherSeqNum;      
  /* 表示此条消息的序列号 */    
  int m_MsgOtherSecMark;     
  /* 表示此消息的发送时间 */    
  long m_MsgOtherLatitude;   
  /* 对于 BSM 消息: 取消息中的 pos.long 字段 对于 RSU 发送的消息，                                                                    
  由于 RSU 位置固定，统一填写为 RSM 中 的 refpos.lat 字段 */   
  long m_MsgOtherLongtitude; 
  /* 对于 BSM 消息: 取消息中的 pos.long 字段 对于 RSU 发送的消息，                                                                        
  由于 RSU 位置固定，统一填写为 RSM 中 的 refpos.long 字段 */    
  int m_MsgOtherSpeed;       
  /* 对于 BSM 消息：取消息中的 speed 字段, 对于 RSU 消息: 填写为 0 */    
  int m_MsgOtherHeading;     
  /* 对于 BSM 消息：取消息中的 heading 字段, 对于 RSU 消息: 填写为 0 */    
  int m_MsgEvent;            
  /* 此消息是否为 event 消息(此项是否为 7(eventHardBraking)) 0--普通消息 1--event 消息 */    
  int m_MsgRecvTime;         
  /* 接收到此消息时的本地时间 */    
  TMsgSelfBsmSet_t m_MsgSelfBsmSet
  ;} __attribute__((packed)) TMsgRecvSet_t;
  #define MSG_RECV_SET_LEN sizeof(TMsgRecvSet_t)
  /*! * @} */
  #endif