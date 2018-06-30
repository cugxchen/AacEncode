/* *
 * @program: AccEncode
 *
 * @description: ${description}
 *
 * @author: 909845
 *
 * @create: 2018-06-30 13:55
***/

#include <iostream>
#include "PcmBuffer.h"


PcmBuffer::PcmBuffer()
{


}

PcmBuffer::~PcmBuffer()
{
    if (m_pBuf != nullptr)
    {
        delete m_pBuf;
        m_pBuf = nullptr;
    }
}


void PcmBuffer::Initialize(Int32 nSize)
{
    assert(nullptr == m_pBuf);
    m_nCapacity = nSize;
    m_pBuf = new UInt8[m_nCapacity]();
    m_nDataLen = 0;
}

Int32 PcmBuffer::WriteData(UInt8 *pData, Int32 nLen)
{
    assert(nullptr != m_pBuf);
    if (m_nCapacity - m_nDataLen < nLen)
    {
        cout<<"PcmBuffer not enouth."<<endl;
        return -1;
    }

    if (nLen > 0)
    {
        memcpy(GetCurPtr(), pData, nLen);
        m_nDataLen += nLen;
        return nLen;
    }
    return 0;
}

Int32 PcmBuffer::GetData(UInt8 *pDstData, Int32 nLen)
{
    assert(nullptr != m_pBuf);
    if (m_nDataLen < nLen)
    {
        return 0;
    }
    memcpy(pDstData, m_pBuf, nLen);
    memmove(m_pBuf, m_pBuf + nLen, m_nDataLen - nLen);//剩余数据移动到buff头部
    m_nDataLen -= nLen;

    return nLen;
}

UInt8 *PcmBuffer::GetCurPtr()
{
    return m_pBuf + m_nDataLen;
}
