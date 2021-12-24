#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <stdint.h>

#define FILE_OPER_FAILED    (-1)    /*读取文件失败*/
#define FILE_OPER_SUCCESS   (0)     /*读取文件成功*/

extern  int32_t file_read(const int8_t *filename, uint8_t content_save_buf[], uint32_t content_buf_size, uint32_t *content_size);

extern  int32_t file_write(const uint8_t *filename, uint8_t *data, uint32_t data_size);
#endif
