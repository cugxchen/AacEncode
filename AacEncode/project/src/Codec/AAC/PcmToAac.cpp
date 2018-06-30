/* *
 * @program: Muxer
 *
 * @description: ${description}
 *
 * @author: chenxiang
 *
 * @create: 2018-06-11 14:59
***/

#include <faac.h>
#include "PcmToAac.h"
#include <assert.h>
#include <cstring>

PcmToAac::PcmToAac(const SPcm2AacParam &pcm2AacParam) : m_Init(pcm2AacParam)
{
    cout<<"Create PcmToAac."<<endl;
}

PcmToAac::~PcmToAac()
{
    cout<<"Destory ~PcmToAac."<<endl;
    if (nullptr != m_hEncoder)
    {
        faacEncClose(m_hEncoder);
        m_hEncoder = nullptr;
    }
    if (nullptr != m_pPCMBuffer)
    {
        delete[](m_pPCMBuffer);
        m_pPCMBuffer = nullptr;
    }
    if (nullptr != m_pAACBuffer)
    {
        delete[](m_pAACBuffer);
        m_pAACBuffer = nullptr;
    }
}


Bool PcmToAac::Initilize()
{
    assert(m_hEncoder == nullptr);
    Bool bRet = false;
    do
    {
        m_hEncoder = faacEncOpen(m_Init.nSample, m_Init.nChannel, &m_nInputSamples, &m_nMaxOutputBytes);
        if (nullptr == m_hEncoder)
        {
            cout<<"faacEncOpen failed."<<endl;
            break;
        }
        m_pPCMBuffer = new UInt8[GetPcmBufferSize()];
        m_pAACBuffer = new UInt8[m_nMaxOutputBytes];

        faacEncConfigurationPtr pConfigurationPtr;
        pConfigurationPtr = faacEncGetCurrentConfiguration(m_hEncoder);
        pConfigurationPtr->outputFormat = 1;  //0 = Raw; 1 = ADTS  填0部分播放器播不了
        pConfigurationPtr->aacObjectType = LOW;
        pConfigurationPtr->mpegVersion = MPEG2;
        pConfigurationPtr->bitRate = 0;
        pConfigurationPtr->bandWidth = 0;
        pConfigurationPtr->useTns = 1;
        pConfigurationPtr->inputFormat = FAAC_INPUT_16BIT;

        if (!faacEncSetConfiguration(m_hEncoder, pConfigurationPtr))
        {
            cout<<"faacEncSetConfiguration failed."<<endl;
            break;
        }
        m_pcmBuffer.Initialize(GetPcmBufferSize() * 5);//足够大的缓存区

        bRet = false;
    } while (0);

    return bRet;
}


Int32 PcmToAac::Encode(UInt8 *const pInBuf, Int32 const nInBufSize, UInt8 *const pOutBuf, Int32 const nOutBufMaxSize)
{
    Int32 nOutSize = 0;

    m_pcmBuffer.WriteData(pInBuf, nInBufSize);
    if (m_pcmBuffer.GetData(m_pPCMBuffer, GetPcmBufferSize()) > 0)
    {
        Int32 nAac = 0;
        if ((nAac = faacEncEncode(m_hEncoder, (int32_t *) m_pPCMBuffer, m_nInputSamples, m_pAACBuffer, m_nMaxOutputBytes)) > 0)
        {
            if (nAac > 0)
            {
                nOutSize = (nAac > nOutBufMaxSize) ? nOutBufMaxSize : nAac;
                memcpy(pOutBuf, m_pAACBuffer, nOutSize);
            }
        }
    }
    return nOutSize;
}


const UInt32 PcmToAac::GetPcmBufferSize()
{
    return m_nInputSamples * m_Init.nBit / 8;
}

