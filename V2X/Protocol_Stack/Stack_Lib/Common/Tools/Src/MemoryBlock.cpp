#include "MemoryBlock.h"
#include <memory>
#include <iostream>
#include <assert.h>
extern "C"
{
#include "wj_log.h"
}

MemoryBlock::MemoryBlock(int buf_size) : size(buf_size)
{
    //LogPrint(LOG_LEVEL_DEBUG, "MemoryBlock", "memory allocate size = %d\n", size);
    buf = static_cast<unsigned char *>(calloc(1, buf_size));
    assert(buf != nullptr);
}

MemoryBlock::~MemoryBlock()
{
    //LogPrint(LOG_LEVEL_DEBUG, "MemoryBlock", "memory free\n");
    free(buf);
    buf = NULL;
}
