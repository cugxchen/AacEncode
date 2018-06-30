#ifndef MUXER_PCMTOAAC_H
#define MUXER_PCMTOAAC_H

#include <faac.h>
#include <iostream>
#include "PcmBuffer.h"

using namespace std;


/* *
 * @program: Muxer
 *
 * @description: 音频PCM编码为AAC格式
 *
 * @author: chenxiang
 *
 * @create: 2018-06-11 14:59
***/
struct SPcm2AacParam
{
    Int32 nSample = 8000;
    Int32 nChannel = 1;
    Int32 nBit = 16;

    friend ostream &operator<<(ostream &stream, const SPcm2AacParam &model)
    {
        stream << "{" << endl;
        stream << "    nSample       = " << model.nSample << endl;
        stream << "    nChannel      = " << model.nChannel << endl;
        stream << "    nBit          = " << model.nBit << endl;
        stream << "}";
        return stream;
    }
};

class PcmToAac
{
public:
    PcmToAac(const SPcm2AacParam &pcm2AacParam);

    virtual ~PcmToAac();

public:
    Bool Initilize();

    Int32 Encode(UInt8 *const pInBuf, Int32 const nInBufSize, UInt8 *const pOutBuf, Int32 const nOutBufMaxSize);

private:
    const UInt32 GetPcmBufferSize();

private:
    SPcm2AacParam m_Init;
    unsigned long m_nInputSamples = 0;//编码输入样本数
    unsigned long m_nMaxOutputBytes = 0;//最大编码输出字节数
    faacEncHandle m_hEncoder = nullptr;
    UInt8 *m_pPCMBuffer = nullptr;
    UInt8 *m_pAACBuffer = nullptr;

    PcmBuffer m_pcmBuffer; //因为编码AAC数据，需要达到规定的数据长度。保存pcm数据，满足规定大小才可取出
};


#endif //MUXER_PCMTOAAC_H
