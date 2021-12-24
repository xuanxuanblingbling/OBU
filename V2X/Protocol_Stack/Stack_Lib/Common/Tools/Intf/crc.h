#ifndef _CRC_H_
#define _CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif

unsigned short do_crc(unsigned short crc_init, unsigned char* SFileBuf, unsigned int clen);

#ifdef __cplusplus
}
#endif

#endif