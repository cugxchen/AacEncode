/* *
 * @program: AccEncode
 *
 * @description: ${description}
 *
 * @author: 909845
 *
 * @create: 2018-06-30 13:55
***/

#ifndef ACCENCODE_PCMBUFFER_H
#define ACCENCODE_PCMBUFFER_H

#include "../../Public/Type.h"
#include <assert.h>
#include <cstring>

/* *
 * @program: Muxer
 *
 * @description: PCM缓存buffer，达到需求的长度才能取出
 *
 * @author: chenxiang
 *
 * @create: 2018-06-11 14:59
***/

using namespace std;

class PcmBuffer
{
public:
    PcmBuffer();

    ~PcmBuffer();

public:
    void Initialize(int nSize);

    Int32 WriteData(UInt8 *pData, int nLen);

    Int32 GetData(UInt8 *pDstData, Int32 nLen);

private:
    UInt8 *GetCurPtr();

private:
    Int32 m_nDataLen = 0;//已有数据长度
    UInt8 *m_pBuf = nullptr;
    Int32 m_nCapacity;
};

#endif //ACCENCODE_PCMBUFFER_H
