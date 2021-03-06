#ifndef _NET_DATA_CAN_H
#define _NET_DATA_CAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
//测试数据
uint8_t can_buf0[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x2A,0x00,0x05,0x01,0x00,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x3C,0x09,0xDF,0x17,0x87,0x60,0x51,0x45,0x50,0x00,0xE6,0x00,0x01,0x01,0x00,0x02,0x00,\
        0x00,0x00,0x00,0x00,0x00,0x01,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};
uint8_t can_buf1[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x36,0x00,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,\
        0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x64,0x00,0x01,0x02,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x01,0x01,0x00,0x01,0x02,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x3C,0x09,\
        0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};
uint8_t can_buf2[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x36,0x00,0x07,0x01,0x00,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x64,0x00,0x01,0x02,0x00,0x00,\
        0x00,0x00,0x00,0x00,0x01,0x0A,0x00,0x01,0x08,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,\
        0x01,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};
uint8_t can_buf3[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x36,0x00,0x07,0x01,0x00,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x64,0x00,0x01,0x02,0x00,0x00,\
        0x00,0x00,0x00,0x00,0x01,0x0D,0x00,0x01,0x08,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,\
        0x01,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};
uint8_t can_buf4[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x36,0x00,0x07,0x01,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x64,0x00,0x01,0x02,\
        0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x00,0x01,0x06,0x01,0x00,0x02,0x00,0x00,0x00,\
        0x00,0x00,0x00,0x01,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};	
uint8_t can_buf5[] = {0xFF,0xFF,0x01,0x12,0x00,0x00,0x12,0x00,0x01,0x00,0x08,0x55,0x00,\
        0x3C,0x09,0xDF,0x17,0x37,0x55,0x51,0x45,0x02,0x00,0x01,0x3c,0x00,0x00,0xFF};
uint8_t can_buf6[] = {0xFF,0xFF,0x00,0x11,0x00,0x00,0x11,0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,\
        0x51,0x45,0x01,0x01,0x01,0x00,0x05,0x03,0x05,0x02,0x50,0x00,0xFF};	
uint8_t can_buf7[] = {0xFF,0xFF,0x01,0x10,0x00,0x00,0x36,0x00,0x07,0x01,0x00,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x64,0x00,0x01,0x02,0x00,\
        0x00,0x00,0x00,0x00,0x00,0x01,0x0B,0x00,0x01,0x06,0x01,0x00,0x02,0x00,0x00,0x00,0x00,\
        0x00,0x00,0x01,0x3C,0x09,0xDF,0x17,0x96,0x50,0x51,0x45,0x50,0x00,0x00,0xFF};
uint8_t can_buf8[] = {0xFF,0xFF,0x01,0x12,0x00,0x00,0x12,0x00,0x01,0x00,0x02,0x2F,0x00,0x3C,0x09,\
        0xDF,0x17,0x37,0x55,0x51,0x45,0x02,0x00,0x02,0x3c,0x00,0x00,0xFF};
        #ifdef __cplusplus
}
#endif

#endif