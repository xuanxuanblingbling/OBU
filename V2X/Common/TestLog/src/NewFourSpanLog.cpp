/***********************************************************************
 * 文 件 名 称 ： NewFourSpanLog.cpp
 * 功 能 描 述 ： 通用读文件类
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-08-18 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
***********************************************************************/

#include "NewFourSpanLog.hpp"

#define MODULE_NAME "TEST_LOG"
#define USE_ZLOG 1U
#include "Debug.h"

using namespace std;

NewFourSpanFile::NewFourSpanFile(string &p_sFileName)
{
    m_file_stream = new fstream(p_sFileName.c_str(), ios::app | ios::out | ios::in);
    m_file_name = p_sFileName;
}

NewFourSpanFile::~NewFourSpanFile()
{
    if (m_file_stream->is_open())
    {
        m_file_stream->sync();
        m_file_stream->close();
        m_file_name.clear();
        delete m_file_stream;
        m_file_stream = nullptr;
    }
}

int NewFourSpanFile::OpenFile()
{
    if (!m_file_stream->is_open())
    {
        m_file_stream->open(m_file_name.c_str(), ios::app | ios::out | ios::in);
        if (m_file_stream->fail())
        {
            ERR("failed to open:%s:%d.\n", m_file_name.c_str(), m_file_stream->rdstate());
            return -1;
        }
    }
    return 0;
}

int NewFourSpanFile::WriteFile(uint8_t *p_n8Data, size_t p_u32Len)
{
    if (-1 == OpenFile())
    {
        return -1;
    }
    m_file_stream->write(reinterpret_cast<const char *>(p_n8Data), p_u32Len);
    if (m_file_stream->fail())
    {
        ERR("failed to write:%s:%d.\n", m_file_name.c_str(), m_file_stream->rdstate());
        m_file_stream->sync();
        m_file_stream->close();
        return -1;
    }
    m_file_stream->sync();
    return 0;
}

int NewFourSpanFile::ReadFile(uint8_t *p_n8Data, size_t p_u32Len)
{
    if (-1 == OpenFile())
    {
        return -1;
    }
    m_file_stream->read(reinterpret_cast<char *>(p_n8Data), p_u32Len);
    if (m_file_stream->fail())
    {
        ERR("failed to read:%s:%d.\n", m_file_name.c_str(), m_file_stream->rdstate());
        m_file_stream->sync();
        m_file_stream->close();
        return -1;
    }
    m_file_stream->sync();
    return 0;
}

bool NewFourSpanFile::IsFileExist()
{
    return access(m_file_name.c_str(), F_OK) ? false : true;
}

int NewFourSpanFile::CloseFile()
{
    if (m_file_stream->is_open())
    {
        m_file_stream->sync();
        m_file_stream->close();
    }
    return 0;
}