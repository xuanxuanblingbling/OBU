/*********************************************************************** 
* �� �� �� �� �� NewFourSpanLog.hpp 
* �� �� �� �� �� ͨ�ö��ļ���ͷ�ļ� 
* �� �� �� Ա �� YaoZhiqiang * ����       
�汾  �޸���    ����
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
//���������غ���, �ᱻ�Զ�����    
bool operator==(const NewFourSpanFile &obj1) const    {        
//��ͬ����0������ͬ���ط�0        
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
  /* ����� ID ����λ */    
  char m_BsmIDbuf[8];         
  /* ID��8λ�ַ��� */    
  long m_MsgSelfGPSLatitude;   
  /* ���յ�����Ϣʱ�ı����� GPS γ�� */    
  long m_MsgSelfGPSLongtitude; 
  /* ���յ�����Ϣʱ�ı����� GPS ���� */    
  int m_MsgSelfSpeed;         
  /* ���յ�����Ϣʱ�ı������ٶ� */    
  int m_MsgSelfHeading;        
  /* ���յ�����Ϣʱ�ı������� */
  } __attribute__((packed)) TMsgSelfBsmSet_t;

  #define MSG_SELF_BSM_LEN sizeof(TMsgSelfBsmSet_t)
  typedef struct{    
  int m_MsgOtherID;          
  /* ��Ϣ�� id �ĺ���λ���� */    
  int m_MsgOtherType;        
  /* 1:BSM 2:RSM 3:RSI 4:SPAT 5:MAP */    
  int m_MsgOtherSeqNum;      
  /* ��ʾ������Ϣ�����к� */    
  int m_MsgOtherSecMark;     
  /* ��ʾ����Ϣ�ķ���ʱ�� */    
  long m_MsgOtherLatitude;   
  /* ���� BSM ��Ϣ: ȡ��Ϣ�е� pos.long �ֶ� ���� RSU ���͵���Ϣ��                                                                    
  ���� RSU λ�ù̶���ͳһ��дΪ RSM �� �� refpos.lat �ֶ� */   
  long m_MsgOtherLongtitude; 
  /* ���� BSM ��Ϣ: ȡ��Ϣ�е� pos.long �ֶ� ���� RSU ���͵���Ϣ��                                                                        
  ���� RSU λ�ù̶���ͳһ��дΪ RSM �� �� refpos.long �ֶ� */    
  int m_MsgOtherSpeed;       
  /* ���� BSM ��Ϣ��ȡ��Ϣ�е� speed �ֶ�, ���� RSU ��Ϣ: ��дΪ 0 */    
  int m_MsgOtherHeading;     
  /* ���� BSM ��Ϣ��ȡ��Ϣ�е� heading �ֶ�, ���� RSU ��Ϣ: ��дΪ 0 */    
  int m_MsgEvent;            
  /* ����Ϣ�Ƿ�Ϊ event ��Ϣ(�����Ƿ�Ϊ 7(eventHardBraking)) 0--��ͨ��Ϣ 1--event ��Ϣ */    
  int m_MsgRecvTime;         
  /* ���յ�����Ϣʱ�ı���ʱ�� */    
  TMsgSelfBsmSet_t m_MsgSelfBsmSet
  ;} __attribute__((packed)) TMsgRecvSet_t;
  #define MSG_RECV_SET_LEN sizeof(TMsgRecvSet_t)
  /*! * @} */
  #endif