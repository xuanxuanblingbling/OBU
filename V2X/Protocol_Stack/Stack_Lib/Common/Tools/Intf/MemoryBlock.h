#ifndef _MEMORY_BLOCK_H_
#define _MEMORY_BLOCK_H_

struct MemoryBlock
{
public:
    explicit MemoryBlock(int buf_size);
    ~MemoryBlock();

public:
    //const int size;
    int size;
    unsigned char *buf;
};

#endif