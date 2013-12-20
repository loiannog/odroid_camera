//----------------------------------------------------------------------------------------
#include "avihelper.h"
//----------------------------------------------------------------------------------------

using namespace std;

//----------------------------------------------------------------------------------------
/*!
	\brief Builds an error string from an AVI error code.
	\param error The error code to be converted.

	Helper function to convert an AVI error code into a string.
*/
string AVIErrorToString( DWORD error )
//----------------------------------------------------------------------------------------
{
	string errormsg("AVI error '");
	switch( error )
	{
		case AVIERR_BADFLAGS       : errormsg.append( "AVIERR_BADFLAGS" );       break;
		case AVIERR_BADFORMAT      : errormsg.append( "AVIERR_BADFORMAT" );      break;
		case AVIERR_BADHANDLE      : errormsg.append( "AVIERR_BADHANDLE" );      break;
		case AVIERR_BADPARAM       : errormsg.append( "AVIERR_BADPARAM" );       break;
		case AVIERR_BADSIZE        : errormsg.append( "AVIERR_BADSIZE" );        break;
		case AVIERR_BUFFERTOOSMALL : errormsg.append( "AVIERR_BUFFERTOOSMALL" ); break;
		case AVIERR_CANTCOMPRESS   : errormsg.append( "AVIERR_CANTCOMPRESS" );   break;
		case AVIERR_COMPRESSOR     : errormsg.append( "AVIERR_COMPRESSOR" );     break;
		case AVIERR_NOCOMPRESSOR   : errormsg.append( "AVIERR_NOCOMPRESSOR" );   break;
		case AVIERR_NODATA         : errormsg.append( "AVIERR_NODATA" );         break;
		case AVIERR_FILEOPEN       : errormsg.append( "AVIERR_FILEOPEN" );       break;
		case AVIERR_FILEREAD       : errormsg.append( "AVIERR_FILEREAD" );       break;
		case AVIERR_FILEWRITE      : errormsg.append( "AVIERR_FILEWRITE" );      break;
		case AVIERR_INTERNAL       : errormsg.append( "AVIERR_INTERNAL" );       break;
		case AVIERR_MEMORY         : errormsg.append( "AVIERR_MEMORY" );         break;
		case AVIERR_READONLY       : errormsg.append( "AVIERR_READONLY" );       break;
		case AVIERR_UNSUPPORTED    : errormsg.append( "AVIERR_UNSUPPORTED" );    break;
		case AVIERR_USERABORT      : errormsg.append( "AVIERR_USERABORT" );      break;
		case REGDB_E_CLASSNOTREG   : errormsg.append( "REGDB_E_CLASSNOTREG" );   break;
		default:
			return "Unrecognized error";
	}
	return( errormsg.append( "' occurred" ) );
}

//----------------------------------------------------------------------------------------
/*!
	\brief Builds a test image.
	\param pData Pointer to the memory in which to build the test image.
	\param width The width of the test image.
	\param height The height of the test image.
	\param bytespp The bytes per pixel of the test image.

	This function is only needed for testing purposes. It builds a moving vertical 
	grey ramp in the memory pointed to by \e pData. In each new image will move one
	pixel to the right in order to simulate movement.
*/
void BuildTestImage( unsigned char* pData, int width, int height, int bytespp )
//----------------------------------------------------------------------------------------
{
	static int count = 0;
	unsigned char* p = pData;

	for( int i=0; i<height; i++ )
	{
		for( int j=0; j<width; j++ )
		{
			for( int x=0; x<bytespp; x++ )
			{
				p[x] = static_cast<unsigned char>(j+count%256);
			}
			p += bytespp;
		}
	}
	++count;
}

//----------------------------------------------------------------------------------------
/*!
	\brief Convertes a user selected codec into the corresponding 4 character code
	\param codec The codec to be converted.
*/
DWORD CodecToFourccCode( CODEC_T codec )
//----------------------------------------------------------------------------------------
{
	switch (codec)
	{
		case codecNoCompression:       return mmioFOURCC( 'D', 'I', 'B', ' ' );
		case codecMorganMjpg:          return mmioFOURCC( 'M', 'J', 'P', 'G' );
		case codecMorganMjpg2000:      return mmioFOURCC( 'M', 'J', '2', 'C' );
		case codecIntelJpg:            return mmioFOURCC( 'M', 'J', 'P', 'G' );
		case codecHuffYUV:             return mmioFOURCC( 'H', 'F', 'Y', 'U' );
		case codecDivx5:               return mmioFOURCC( 'd', 'i', 'v', 'x' );
		case codec3ivx:                return mmioFOURCC( '3', 'i', 'v', '2' );
		case codecMjpg2:               return mmioFOURCC( 'e', 'm', '2', 'v' );
		case codecPicVideoWavelet:     return mmioFOURCC( 'p', 'v', 'w', '2' );
		case codecPicVideoMjpg:        return mmioFOURCC( 'm', 'j', 'p', 'x' );
		case codecPicVideoLossLessJpg: return mmioFOURCC( 'p', 'i', 'm', 'j' );
		case codecMSVideo:             return mmioFOURCC( 'm', 's', 'v', 'c' );
		case codecMSRle:               return mmioFOURCC( 'm', 'r', 'l', 'e' );
		case codecMSH263:              return mmioFOURCC( 'm', '2', '6', '3' );
		case codecMSH261:              return mmioFOURCC( 'm', '2', '6', '1' );
		case codecIntelVidR32:         return mmioFOURCC( 'i', 'v', '3', '2' );
		case codecIntelIndeo510:       return mmioFOURCC( 'i', 'v', '5', '0' );
		case codecDivxMjpg4lm:         return mmioFOURCC( 'd', 'i', 'v', '3' );
		case codecDivxMjpg4fm:         return mmioFOURCC( 'd', 'i', 'v', '4' );
		case codecCinepack:            return mmioFOURCC( 'c', 'v', 'i', 'd' );
		case codecMSMpeg4:             return mmioFOURCC( 'm', 'p', 'g', '4' );
		case codecMax:                 return mmioFOURCC( 'D', 'I', 'B', ' ' );
		default:
			break;
	}
	throw AEUnsupportedCodec();
}