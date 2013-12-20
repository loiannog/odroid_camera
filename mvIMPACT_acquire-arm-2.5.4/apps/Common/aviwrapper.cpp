//----------------------------------------------------------------------------------------
#include "aviwrapper.h"
#include <cassert>
//----------------------------------------------------------------------------------------

/*!
	\class AVIWrapper
	\brief Provides an easy way to create and use *.avi-files.

	This class is meant to provide easy access to the AVI file functions. It can be used to generate
	an AVI stream with only a few lines of code.

	Three general methods are supported:

	- Creation of an AVI stream using the standard Windows compression options dialog (interactively)
	- Creation of an AVI stream specifing a codec handler, quality settings and image dimensions 
	  (not interactivly)
	- Creation of an AVI stream from images which are already in jpeg format.
*/

unsigned int AVIWrapper::m_usageCount = 0;

//----------------------------------------------------------------------------------------
/*!
	\brief Constructs a new \b AVIWrapper object.
	\param filename The filename of the AVI file to be created or \e 0 if no file shall be
					created.
	\param mode The access mode for this file.

	Opens and creates an AVI file in the mode specified by the \e mode parameter if
	a filename has been specified. See MSDN for details about the available modes.
*/
AVIWrapper::AVIWrapper( const char* pFilename /* = 0 */, UINT mode /*  = OF_READ */ ) throw(AVIWrapperException) : 
	m_pAVIFile(0), m_pAVIStream(0), m_pAVIStreamCompressed(0), m_AVIStreamFrameCounter(0),
	m_codec(CodecToFourccCode(codecNoCompression))
//----------------------------------------------------------------------------------------
{
	if( m_usageCount == 0 )
	{
		AVIFileInit();
	}
	++m_usageCount;
	if( pFilename )
	{
		int result;
		if( ( result = AVIFileOpen( &m_pAVIFile, pFilename, mode, 0 ) ) == 0 )
		{
			result = AVIFileGetStream( m_pAVIFile, &m_pAVIStream, streamtypeVIDEO, 0 );
		}
		if( result != 0 )
		{
			AVIFileExit();
			throw AVIWrapperException(AVIErrorToString( result ).c_str());
		}
	}
}

//----------------------------------------------------------------------------------------
AVIWrapper::~AVIWrapper( void ) throw()
//----------------------------------------------------------------------------------------
{
	if( m_pAVIFile )
	{
		CloseStreamsAndFiles();
	}
	--m_usageCount;
	if( m_usageCount == 0 )
	{
		AVIFileExit();
	}
}

//----------------------------------------------------------------------------------------
/*!
	\brief Closes the AVI file again.

	Closes all open streams and the AVI file itself. At the moment only one stream can be opened
	at the same time.
*/
void AVIWrapper::CloseAVIFile( void ) throw(AVIWrapperException)
//----------------------------------------------------------------------------------------
{
	if( !m_pAVIFile )
	{
		throw AVIWrapperException( "CloseAVIFile: No file has been opened so far" );
	}
	CloseStreamsAndFiles();
}

//----------------------------------------------------------------------------------------
/*!
	\brief Closes all open stream and the AVI file itself.
*/
void AVIWrapper::CloseStreamsAndFiles( void ) throw()
//----------------------------------------------------------------------------------------
{
	if( m_pAVIStream )
	{
		AVIStreamRelease( m_pAVIStream );
	}
	if( m_pAVIStreamCompressed )
	{
		AVIStreamRelease( m_pAVIStreamCompressed );
	}
	if( m_pAVIFile )
	{
		AVIFileRelease( m_pAVIFile );
	}
	m_pAVIStream = 0;
	m_pAVIStreamCompressed = 0;
	m_pAVIFile = 0;
	m_AVIStreamFrameCounter = 0;
}

//----------------------------------------------------------------------------------------
/*!
	\brief Creates an AVI stream from DIB images.
	\param w The width of the images to be stored in the stream
	\param h The height of the images to be stored in the stream
	\param sampleRate The frames per second entry in the AVI header
	\param quality The JPEG quality (from 0 - 10000)
	\param name The name of the stream in the file
	\param codec The codec to be used for the compression of the DIB data. Pass \e codecMax if 
				 you want to select a codec from the standard Windows compression dialog or
				 a valid codec from the \b CODEC_T enumeration.

	Use this function to create a compressed or uncompressed AVI stream from images in DIB/Bitmap
	format. The images can be stored in a compressed format defined by the specified compression
	handler.

	If your images are already in JPEG format use the function <b>AVIWrapper::CreateAVIStreamFromJPEGs()</b>
	instead.
*/
void AVIWrapper::CreateAVIStreamFromDIBs( int w, int h, int bitcount, DWORD sampleRate, DWORD quality, const char* pName /*= "default"*/, CODEC_T codec /*= codecMax*/ ) throw(AVIException)
//----------------------------------------------------------------------------------------
{
	BITMAPINFOHEADER BmpHeader;
	SetupStreamStructs( BmpHeader, w, h, bitcount, sampleRate, quality, pName, codec );
	BmpHeader.biCompression = BI_RGB;
	AVICOMPRESSOPTIONS* opts[1] = {&m_AVICompressionOptions};
	memset(&m_AVICompressionOptions, 0, sizeof(AVICOMPRESSOPTIONS) );
	PAVISTREAM streams[1] = {m_pAVIStream};

	if( codec == codecMax )
	{
		// show windows compression handler dialog
		AVISaveOptions( 0, 0, 1, (PAVISTREAM*)&streams, (LPAVICOMPRESSOPTIONS*)&opts );
	}
	else	// fill AVICOMPRESSOPTIONS with user parameters 
	{
		m_codec = codec;
		opts[0]->fccType		= streamtypeVIDEO;
		opts[0]->fccHandler		= CodecToFourccCode(codec);
		opts[0]->dwQuality		= quality;
		opts[0]->dwFlags		= AVICOMPRESSF_VALID;
	}
	m_codec = opts[0]->fccHandler;
	int result;
	if( ( result = AVIMakeCompressedStream( &m_pAVIStreamCompressed, m_pAVIStream, &m_AVICompressionOptions, NULL ) ) == AVIERR_OK )
	{
		result = AVIStreamSetFormat( m_pAVIStreamCompressed, 0, &BmpHeader, sizeof(BITMAPINFOHEADER) );
	}
	if( result != 0 )
	{
		CloseStreamsAndFiles();
		throw AVIWrapperException( AVIErrorToString( result ).c_str() );
	}
}

//----------------------------------------------------------------------------------------
/*!
	\brief Creates an AVI stream from JPEG images.
	\param w The width of the images to be stored in the stream
	\param h The height of the images to be stored in the stream
	\param sampleRate The frames per second entry in the AVI header
	\param quality The JPEG quality (from 0 - 10000)
	\param name The name of the stream in the file

	Use this function to create a MJPEG stream from images which are already in JPEG format.

	To create an AVI stream from images in DIB format use the function 
	<b>AVIWrapper::CreateAVIStreamFromDIBs()</b> instead.
*/
void AVIWrapper::CreateAVIStreamFromJPEGs( int w, int h, int bitcount, DWORD sampleRate, DWORD quality, const char* pName /*= "default"*/ ) throw(AVIException)
//----------------------------------------------------------------------------------------
{
	// no 'handler' compression! This section works for already compressed images
	BITMAPINFOHEADER BmpHeader;
	SetupStreamStructs( BmpHeader, w, h, bitcount, sampleRate, quality, pName, codecMorganMjpg );
	BmpHeader.biCompression = CodecToFourccCode(codecMorganMjpg);
	int result;
	if( ( result = AVIStreamSetFormat( m_pAVIStream, 0, &BmpHeader, sizeof(BITMAPINFOHEADER) ) ) != 0 )
	{
		CloseStreamsAndFiles();
		throw AVIWrapperException( AVIErrorToString( result ).c_str() );
	}
}

//----------------------------------------------------------------------------------------
/*!
	\brief Opens an AVI file.
	\param filename The name of the file to be created/opened/used.
	\param mode The access mode for this file.

	Opens and creates an AVI file in the mode specified by the \e mode parameter
	See MSDN for details about the available modes.
*/
void AVIWrapper::OpenAVIFile( const char* pFilename, UINT mode /* = OF_READ */ ) throw(AVIWrapperException)
//----------------------------------------------------------------------------------------
{
	if( m_pAVIFile )
	{
		throw AVIWrapperException( "OpenAVIFile: Another file has been opened already" );
	}
	if( !pFilename )
	{
		throw AVIWrapperException( "OpenAVIFile: No valid filename has been specified" );
	}
	int result;
	if( ( result = AVIFileOpen( &m_pAVIFile, pFilename, mode, 0 ) ) != 0 )
	{
		throw AVIWrapperException( AVIErrorToString( result ).c_str() );
	}
}

//----------------------------------------------------------------------------------------
/*!
	\brief Stores one image in the AVI stream
	\param data Pointer to the image data
	\param size Size (in bytes) of the memory block pointed to by \e data

	This function stores one image in the specified stream.
*/
void AVIWrapper::SaveDataToAVIStream( unsigned char* pData, int size ) throw(AVIWrapperException)
//----------------------------------------------------------------------------------------
{
	PAVISTREAM pAVIStream = ( m_pAVIStreamCompressed ) ? m_pAVIStreamCompressed : m_pAVIStream;
	if( !pAVIStream )
	{
		throw AVIWrapperException( "SaveDataToAVIStream: Stream pointer invalid" );
	}
	int result;
	if( ( result = AVIStreamWrite( pAVIStream, m_AVIStreamFrameCounter++, 1, pData, size, AVIIF_KEYFRAME, 0, 0 ) ) != 0 )
	{
		throw AVIWrapperException( AVIErrorToString( result ).c_str() );
	}
}

//----------------------------------------------------------------------------------------
void AVIWrapper::SetupStreamStructs( BITMAPINFOHEADER& BmpHeader, int w, int h, int bitcount, DWORD sampleRate, DWORD quality, const char* pName /*= "default"*/, CODEC_T codec /*= codecMax*/ ) throw(AVIWrapperException)
//----------------------------------------------------------------------------------------
{
	if( !m_pAVIFile )
	{
		throw AVIWrapperException( "CreateNewAVIStream: No file has been opened so far" );
	}
	if( strlen(pName) > sizeof(m_AVIStreamInfo.szName) )
	{
		throw AVIWrapperException( "CreateNewAVIStream: streamname too long" );
	}
	if( m_pAVIStream || m_pAVIStreamCompressed )
	{
		throw AVIWrapperException( "CreateNewAVIStream: There is already an open stream" );
	}
	// setup AVISTREAMINFO structure
	memset( &m_AVIStreamInfo, 0, sizeof(AVISTREAMINFO) );
	m_AVIStreamInfo.fccType = streamtypeVIDEO;
	m_AVIStreamInfo.fccHandler = CodecToFourccCode(codec);
	m_AVIStreamInfo.wPriority = 10;
	m_AVIStreamInfo.dwScale = 1;
	m_AVIStreamInfo.dwRate = sampleRate; 
	m_AVIStreamInfo.dwQuality = quality; 
	m_AVIStreamInfo.rcFrame.right  = w; 
	m_AVIStreamInfo.rcFrame.bottom = h; 

#if defined(_MSC_VER) && (_MSC_VER >= 1400) // is at least VC 2005 compiler?
	errno_t strcpy_sResult = strcpy_s( m_AVIStreamInfo.szName, 64, pName );
	strcpy_sResult = strcpy_sResult; // remove release build warning
	assert( strcpy_sResult == 0 );
#else
	strcpy( m_AVIStreamInfo.szName, pName );
#endif

	int result;
	if( ( result = AVIFileCreateStream( m_pAVIFile, &m_pAVIStream, &m_AVIStreamInfo) ) != 0 )
	{
		throw AVIWrapperException( AVIErrorToString( result ).c_str() );
	}
	// setup BITMAPINFOHEADER structure
	memset( &BmpHeader, 0, sizeof(BITMAPINFOHEADER) );
	BmpHeader.biSize = sizeof(BITMAPINFOHEADER);
	BmpHeader.biWidth = w;
	BmpHeader.biHeight = h;
	BmpHeader.biPlanes = 1;
	BmpHeader.biBitCount = static_cast<WORD>(bitcount);

	// setup internals
	m_AVIStreamFrameCounter = 0;
}