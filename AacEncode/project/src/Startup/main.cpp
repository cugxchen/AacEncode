#include <iostream>
#include "../Codec/AAC/PcmToAac.h"

using namespace std;

static const Int32 PCM_BUF_LEN = 160;
static const Int32 AAC_BUF_LEN = 10240;

int main()
{
    std::cout << "pcm--->aac    start" << std::endl;

    FILE *fpSrc = fopen("src.pcm", "rb");
    FILE *fpDes = fopen("des.aac", "wb");
    assert(nullptr != fpSrc && nullptr != fpDes);


    SPcm2AacParam param;
    param.nChannel = 1;
    param.nSample = 8000;
    param.nBit = 16;
    PcmToAac   pcmToAac(param);
    pcmToAac.Initilize();


    Int8 srcBuffer[PCM_BUF_LEN] = {0};
    Int8 aacBuffer[AAC_BUF_LEN] = {0};
    Int32 nAac = 0;
    Int32 nPcm = 0;
    while ((nPcm=fread(srcBuffer, sizeof(Int8), PCM_BUF_LEN, fpSrc))>0)
    {
        nAac = pcmToAac.Encode((UInt8*)srcBuffer, nPcm, (UInt8*)aacBuffer, AAC_BUF_LEN);
        if (nAac > 0)
        {
            fwrite(aacBuffer, sizeof(Int8), nAac, fpDes);
        }

    }
    std::cout << "pcm--->aac    end" << std::endl;

    return 0;
}