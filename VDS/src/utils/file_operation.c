#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "general_config.h"
#include "file_operation.h"
#include "wj_log.h"


int32_t file_read(const int8_t *filename, uint8_t content_save_buf[], uint32_t content_buf_size, uint32_t *content_size)
{
    FILE *fp = NULL;
    size_t file_size = 0;
    int64_t pos = 0;

    if((NULL == filename) || (NULL == content_save_buf) || (0 == content_buf_size) || (NULL == content_size))
    {
        
        return FILE_OPER_FAILED;
    }

    fp = fopen(filename, "rb");
    if (NULL == fp)
    {
        
        return FILE_OPER_FAILED;
    }
    fseek(fp, 0L, SEEK_END);    
    file_size = ftell(fp);    
    if (file_size == 0)
    {
        //LogErr(MODULE_NAME, "empty file");
        fclose(fp);
        return FILE_OPER_FAILED;
    }

    if (file_size > content_buf_size)
    {
        printf("====[test] filesize %d  bufsize %d ==\n",file_size,content_buf_size);
        //LogErr(MODULE_NAME, "file content save buf is not big enough,%d %d", file_size, content_buf_size);
        fclose(fp);
        return FILE_OPER_FAILED;
    }

    rewind(fp);

    if(0 == (file_size = fread(content_save_buf, 1, file_size, fp)))
    {
        //LogErr(MODULE_NAME, "read file failed");
        fclose(fp);
        return FILE_OPER_FAILED;
    }

    fclose(fp);

    *content_size = file_size;

    //LogDebug(MODULE_NAME, "read file %s success, file size %d", filename, file_size);
    return 0;
}


int32_t file_write(const uint8_t *filename, uint8_t *data, uint32_t data_size)
{
    FILE *fp = NULL;

    if ((NULL == filename) || (NULL == data) || (0 == data_size))
    {
        //LogErr(MODULE_NAME, "wrong para");
        return FILE_OPER_FAILED;
    }

    fp = fopen(filename, "w");
    if (NULL == fp)
    {
        //LogErr(MODULE_NAME, "open file %s failed", filename);
        return FILE_OPER_FAILED;
    }

    if(0 == fwrite(data, data_size, 1, fp))
    {
        //LogErr(MODULE_NAME, "write failed");
        fclose(fp);
        return FILE_OPER_FAILED;
    }

    fclose(fp);
    //LogDebug(MODULE_NAME, "write file %s success", filename);
    return FILE_OPER_SUCCESS;
}
