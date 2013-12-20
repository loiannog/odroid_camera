//----------------------------------------------------------------------------------------
#ifndef avihelperH
#define avihelperH avihelperH
//----------------------------------------------------------------------------------------
#include <windows.h>
#include <Vfw.h>
#include "aviexception.h"
//----------------------------------------------------------------------------------------

/*!
	\brief The codecs recognized by the \b AVIWrapper class.
*/
typedef enum
{
	codecNoCompression = 0,
	codecMorganMjpg = 1,
	codecMorganMjpg2000 = 2,
	codecIntelJpg = 3,
	codecHuffYUV = 4,
	codecDivx5 = 5,
	codec3ivx = 6,
	codecMjpg2 = 7,
	codecPicVideoWavelet = 8,
	codecPicVideoMjpg = 9,
	codecPicVideoLossLessJpg = 10,
	codecMSVideo = 11,
	codecMSRle = 12,
	codecMSH263 = 13,
	codecMSH261 = 14,
	codecIntelVidR32 = 15,
	codecIntelIndeo510 = 16,
	codecDivxMjpg4lm = 17,
	codecDivxMjpg4fm = 18,
	codecCinepack = 19,
	codecMSMpeg4 = 20,
	codecMax 
} CODEC_T;

//----------------------------------------------------------------------------------------
std::string		AVIErrorToString( DWORD error );
void			BuildTestImage( unsigned char* pData, int width, int height, int bytespp );
DWORD			CodecToFourccCode( CODEC_T codec );
//----------------------------------------------------------------------------------------

#endif // avihelperH