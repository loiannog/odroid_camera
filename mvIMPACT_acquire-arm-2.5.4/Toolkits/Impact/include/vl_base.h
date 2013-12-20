#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning ( disable:4005 ) // '_WIN32_WINNT' : macro redefinition
#define _WIN32_WINNT 0x0500
#pragma warning ( pop )
#endif




#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __vl_base_h__
#define __vl_base_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ostypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_vl_base_0000_0000 */
/* [local] */ 

//=--------------------------------------------------------------------------=
// (C) Copyright 2002-2012 MATRIX VISION GmbH.  All Rights Reserved.
// (C) Copyright 1997-2012 Impuls Bildanalyse GmbH.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#if defined(__BORLANDC__)
#pragma option -b
#endif
#if !defined(NO_VL_BASE_AUTOLINK)
#if defined(__BORLANDC__)
#pragma comment(lib,"vlb_base.lib")
#pragma message ("Automatically linking with vlb_base.lib")
#else
#if defined(_M_X64)
#if _MSC_VER >= 1500
#pragma comment(lib,"vl_base.lib")
#pragma message ("Automatically linking with vl_base.lib")
#else
#pragma comment(lib,"vl_base64.lib")
#pragma message ("Automatically linking with vl_base64.lib")
#endif
#else
#pragma comment(lib,"vl_base.lib")
#pragma message ("Automatically linking with vl_base.lib")
#endif
#endif
#endif


#ifdef MVIMPACT_H_ // include guard of the main C++ header
namespace mvIMPACT {
	namespace mvIMPACT_C {
#endif // #ifdef MVIMPACT_H_


// Calling method for C Functions and C++ global and class methods.
// With other words: everything without a this-pointer
#define IPL_C_CALLTYPE __stdcall
#define IPL_C_CALLTYPEVAR __cdecl

// Calling method for the C++ methods with a this pointer.
// C++ static methods or C++ functions use IPL_C_CALLTYPE[VAR]
#define IPL_CPP_CALLTYPE // nothing == 'C++-call'
#define IPL_CPP_CALLTYPEVAR __cdecl

#ifdef VL_BASE_COMPILING
// when compiling the dll
#define VL_BASE_DLLEXPORT	__declspec(dllexport)
#undef __MIDL_DECLSPEC_DLLEXPORT
#define __MIDL_DECLSPEC_DLLEXPORT	__declspec(dllexport)
#undef __MIDL_DECLSPEC_DLLIMPORT
#define __MIDL_DECLSPEC_DLLIMPORT	__declspec(dllexport)
#else
// when using the dll
#define VL_BASE_DLLEXPORT	__declspec(dllimport)
#undef __MIDL_DECLSPEC_DLLEXPORT
#define __MIDL_DECLSPEC_DLLEXPORT	__declspec(dllimport)
#undef __MIDL_DECLSPEC_DLLIMPORT
#define __MIDL_DECLSPEC_DLLIMPORT	__declspec(dllimport)
#endif
#define	IPL_DONT_CARE	( -1 )

#define	IPL_TRUE	( 1 )

#define	IPL_FALSE	( 0 )



extern RPC_IF_HANDLE __MIDL_itf_vl_base_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vl_base_0000_0000_v0_0_s_ifspec;


#ifndef __vl_base_LIBRARY_DEFINED__
#define __vl_base_LIBRARY_DEFINED__

/* library vl_base */
/* [helpstring][version][uuid] */ 

typedef /* [helpstring] */ _IPL_FRESULT IPL_FRESULT;

typedef /* [helpstring] */ _IPL_CHAR IPL_CHAR;

typedef /* [helpstring] */ _IPL_UCHAR IPL_UCHAR;

typedef /* [helpstring] */ _IPL_SHORT IPL_SHORT;

typedef /* [helpstring] */ _IPL_USHORT IPL_USHORT;

typedef /* [helpstring] */ _IPL_INT IPL_INT;

typedef /* [helpstring] */ _IPL_UINT IPL_UINT;

typedef /* [helpstring] */ _IPL_LONG IPL_LONG;

typedef /* [helpstring] */ _IPL_ULONG IPL_ULONG;

typedef /* [helpstring] */ _IPL_FLOAT IPL_FLOAT;

typedef /* [helpstring] */ _IPL_DOUBLE IPL_DOUBLE;

typedef /* [helpstring] */ _IPL_VOID IPL_VOID;

typedef /* [helpstring] */ _IPL_WORD IPL_WORD;

typedef /* [helpstring] */ _IPL_DWORD IPL_DWORD;

typedef /* [helpstring] */ _IPL_BUFHANDLE IPL_BUFHANDLE;

typedef /* [helpstring] */ _IPL_ERRORID IPL_ERRORID;

typedef /* [helpstring] */ _IPL_TIME IPL_TIME;

typedef /* [helpstring] */ _IPL_BOOL IPL_BOOL;

typedef /* [helpstring] */ _IPL_FILE_HANDLE IPL_FILE_HANDLE;

typedef /* [helpstring] */ _IPL_PROCESS_ID IPL_PROCESS_ID;

typedef /* [helpstring] */ _IPL_THREAD_ID IPL_THREAD_ID;

typedef /* [helpstring] */ _IPL_COLOR IPL_COLOR;

typedef /* [helpstring] */ _IPL_HWND IPL_HWND;

typedef /* [helpstring] */ _IPL_HDC IPL_HDC;

typedef /* [helpstring] */ _IPL_HMENU IPL_HMENU;

typedef /* [helpstring] */ _IPL_HKEY IPL_HKEY;

typedef /* [helpstring] */ _IPL_HFILE IPL_HFILE;

typedef /* [helpstring] */ _IPL_HTHREAD IPL_HTHREAD;

typedef /* [helpstring] */ _IPL_HICON IPL_HICON;

typedef /* [helpstring] */ _IPL_HCURSOR IPL_HCURSOR;

typedef /* [helpstring] */ _IPL_HMODULE IPL_HMODULE;

typedef /* [helpstring] */ _IPL_VOID_PTR IPL_VOID_PTR;

typedef /* [helpstring] */ _IPL_CONST_VOID_PTR IPL_CONST_VOID_PTR;

/* [helpstring] */ 
enum BASE_ERROR
    {	IPL_NOT_SPECIFIED	= -100,
	IPL_INVALID_PTR	= -101,
	IPL_FUNCTION_ABORT	= -102,
	IPL_MEMORY_ERROR	= -103,
	IPL_SIZEMISMATCH_ERROR	= -104,
	IPL_ALLOCATION_ERROR	= -105,
	IPL_DATATYPE_ERROR	= -106,
	IPL_HANDLE_ERROR	= -107,
	IPL_FREE_ERROR	= -108,
	IPL_DIM_ERROR	= -109,
	IPL_DIM_SIZEMISMATCH_ERROR	= -110,
	IPL_INVALID_PARAM_ERROR	= -111,
	IPL_DEVICE_ACCESS_ERROR	= -112,
	IPL_LABEL_INDEX_ERROR	= -113,
	IPL_ATTRIBUTE_ERROR	= -114,
	IPL_LICENSE_NO_SERIAL_NUMBER	= -115,
	IPL_LICENSE_NO_KEY	= -116,
	IPL_LICENSE_WRONG_KEY	= -117,
	IPL_LICENSE_AUTHENTIFICATOR	= -118,
	IPL_LICENSE_EXPIRED	= -119,
	IPL_LICENSE_WRONG_MODE	= -120,
	IPL_PARSER_ERROR	= -121,
	IPL_LICENSE_TAMPERED	= -122,
	IPL_NOT_SUPPORTED	= -123,
	IPL_RLE_PARSER_ERROR	= -124,
	IPL_RLE_ENCODING_ERROR	= -125,
	IPL_RLE_IMAGE_ERROR	= -126,
	IPL_MODULE_NOT_FOUND	= -127,
	IPL_BUFFERLOCK_TIMEOUT	= -128
    } ;
typedef /* [public] */ enum BASE_ERROR BASE_ERROR;

/* [helpstring] */ 
enum IPL_BUFFER_DATATYPE
    {	IPL_DTNONE	= 0,
	IPL_DTCHAR	= 1,
	IPL_DTUCHAR	= 2,
	IPL_DTSHORT	= 3,
	IPL_DTUSHORT	= 4,
	IPL_DTLONG	= 5,
	IPL_DTULONG	= 6,
	IPL_DTFLOAT	= 7,
	IPL_DTDOUBLE	= 8
    } ;
typedef /* [public] */ enum IPL_BUFFER_DATATYPE IPL_BUFFER_DATATYPE;

/* [helpstring] */ 
enum IPL_BUFFER_ATTRIBUTE
    {	IPL_NOTALLOCATED	= 0,
	IPL_IMAGEBUF	= 1,
	IPL_LUTBUF	= 2,
	IPL_HISTBUF	= 3,
	IPL_PROFBUF	= 4,
	IPL_KERNELBUF	= 5,
	IPL_STRUCTBUF	= 6,
	IPL_ARRAY	= 7,
	IPL_RESULTBUF	= 8,
	IPL_POINTBUF	= 9,
	IPL_LINEBUF	= 10,
	IPL_INLUTBUF	= 11,
	IPL_OUTLUTBUF	= 12,
	IPL_POLYGONBUF	= 13,
	IPL_RLEBUF	= 14,
	IPL_BAYERMOSAICBUF	= 15
    } ;
typedef /* [public] */ enum IPL_BUFFER_ATTRIBUTE IPL_BUFFER_ATTRIBUTE;

/* [helpstring] */ 
enum IPL_BUFCTRLFLAGS
    {	IPL_XYOFF	= -2,
	IPL_SIZE	= -1,
	IPL_XSIZE	= 0,
	IPL_YSIZE	= 1,
	IPL_NB_ZSLICES	= 2,
	IPL_NB_TSLICES	= 3,
	IPL_NB_BANDS	= 4,
	IPL_DATATYPE	= 5,
	IPL_USAGETYPE	= 6,
	IPL_NUMDEVICE	= 7,
	IPL_XCENTER	= 8,
	IPL_YCENTER	= 9,
	IPL_CHILDID	= 13,
	IPL_XOFF	= 14,
	IPL_YOFF	= 15,
	IPL_ZOFF	= 16,
	IPL_TOFF	= 17,
	IPL_BDOFF	= 18,
	IPL_PARBUFHANDLE	= 20,
	IPL_BITSPERSAMPLE	= 21,
	IPL_CALIBRATE_Z_SLICES	= 22,
	IPL_CALIBRATE_TIME_SLICES	= 23,
	IPL_CALIBRATE_X_SIZE	= 24,
	IPL_CALIBRATE_Y_SIZE	= 25,
	IPL_CAL_MODE	= 29,
	IPL_DBB_FLAGS	= 30,
	IPL_DBB_NAME	= 31,
	IPL_DBB_HANDLE	= 32,
	IPL_DBB_NAME_LENGTH	= 33,
	IPL_DEVICE_BUFFER_HANDLE	= 34,
	IPL_DBB_FILE_FLAGS	= 35,
	IPL_ISCALIBRATED_X_SIZE	= 36,
	IPL_ISCALIBRATED_Y_SIZE	= 37,
	IPL_ISCALIBRATED_Z_SLICES	= 38,
	IPL_ISCALIBRATED_TIME_SLICES	= 39,
	IPL_DATATYPESIZE	= 40,
	IPL_SEQUENCE_DURATION	= 41,
	IPL_THREAD_SAFE	= 42,
	IPL_COLOR_SPACE	= 43,
	IPL_PIXEL_FORMAT	= 44,
	IPL_MIN_GREY_VAL	= 45,
	IPL_MAX_GREY_VAL	= 46,
	IPL_STRUCT_COUNT_1	= 47,
	IPL_BAYER_RED_GAIN	= 200,
	IPL_BAYER_RED_OFFSET	= 201,
	IPL_BAYER_GREEN_GAIN	= 202,
	IPL_BAYER_GREEN_OFFSET	= 203,
	IPL_BAYER_BLUE_GAIN	= 204,
	IPL_BAYER_BLUE_OFFSET	= 205,
	IPL_BAYER_DIGITAL_GAIN	= 206,
	IPL_BAYER_PARITY	= 207,
	IPL_BUFFER_POINTER	= 208,
	IPL_MEMORY_ARRAY	= 209
    } ;
typedef /* [public] */ enum IPL_BUFCTRLFLAGS IPL_BUFCTRLFLAGS;

/* [helpstring] */ 
enum IPL_COL_SPACE
    {	COL_UNKNOWN	= 0L,
	COL_CMY	= 0x1L,
	COL_GRAY	= 0x2L,
	COL_HLS	= 0x4L,
	COL_HSV	= 0x8L,
	COL_RGB	= 0x10L,
	COL_XYZ601	= 0x20L,
	COL_XYZ709	= 0x40L,
	COL_XYZITU	= 0x80L,
	COL_YCC601	= 0x100L,
	COL_YIQ	= 0x200L,
	COL_YUV	= 0x400L,
	COL_BAYER_MOSAIC	= 0x800L
    } ;
typedef /* [hidden] */ enum IPL_COL_SPACE IPL_COL_SPACE;

/* [helpstring] */ 
enum IPL_COMPRESSION_FLAGS
    {	IPL_NO_COMPRESSION	= 0,
	IPL_LZW_COMPRESSION	= 1
    } ;
typedef /* [public] */ enum IPL_COMPRESSION_FLAGS IPL_COMPRESSION_FLAGS;

/* [helpstring] */ 
enum IPL_SAVE_FLAGS
    {	IPL_DONT_SAVE_DATA	= 0,
	IPL_SAVE_DATA	= 1
    } ;
typedef /* [public] */ enum IPL_SAVE_FLAGS IPL_SAVE_FLAGS;

/* [helpstring] */ 
enum IPL_DIMENSION
    {	IPL_DIM_BANDS	= 0,
	IPL_DIM_Z	= 1,
	IPL_DIM_TIME	= 2,
	IPL_DIM_X	= 3,
	IPL_DIM_Y	= 4
    } ;
typedef /* [public] */ enum IPL_DIMENSION IPL_DIMENSION;

/* [helpstring] */ 
enum IPL_DRAWINGMODE
    {	IPL_FILL	= 1,
	IPL_OUTLINE	= 2
    } ;
typedef /* [public] */ enum IPL_DRAWINGMODE IPL_DRAWINGMODE;

/* [helpstring] */ 
enum IPL_LOCATION
    {	IPL_LOC_MEMORY	= 0,
	IPL_LOC_DISK	= 1
    } ;
typedef /* [public] */ enum IPL_LOCATION IPL_LOCATION;

/* [helpstring] */ 
enum IPL_GEOTRANS
    {	IPL_NEAREST_NEIGHBOR	= 0,
	IPL_BILINEAR	= 1,
	IPL_BICUBIC	= 2
    } ;
typedef /* [public] */ enum IPL_GEOTRANS IPL_GEOTRANS;

/* [helpstring] */ 
enum IPL_DEVICEINFOFLAGS
    {	IPL_NONE	= 0,
	IPL_DISK_BASED	= 0x40000000,
	IPL_PERSISTENT	= 0x20000000,
	IPL_PREALLOC	= 0x10000000,
	IPL_USER_MEM	= 0x200000
    } ;
typedef /* [public] */ enum IPL_DEVICEINFOFLAGS IPL_DEVICEINFOFLAGS;

/* [helpstring] */ 
enum IPL_DISPLAY_MODE
    {	IPL_MONO	= 0,
	IPL_RGB	= 1
    } ;
typedef /* [public] */ enum IPL_DISPLAY_MODE IPL_DISPLAY_MODE;

/* [helpstring] */ 
enum IPL_MAP_MODE
    {	IPL_NOT_INVERTED	= 0,
	IPL_INVERTED	= 1
    } ;
typedef /* [public] */ enum IPL_MAP_MODE IPL_MAP_MODE;

/* [helpstring] */ 
enum IPL_LOCK_MODE
    {	IPL_LOCK_READ	= 0,
	IPL_LOCK_WRITE	= 1,
	IPL_NO_LOCK	= 2
    } ;
typedef /* [public] */ enum IPL_LOCK_MODE IPL_LOCK_MODE;

/* [helpstring] */ 
enum IPL_LICENSE_MODE
    {	IPL_MD2	= 0,
	IPL_RSA_EXPIRE_30D	= 1,
	IPL_RSA_EXPIRE_13M	= 2
    } ;
typedef /* [public] */ enum IPL_LICENSE_MODE IPL_LICENSE_MODE;

/* [helpstring] */ 
enum IPL_MORPH
    {	IPL_WHITE	= 0xffffffff,
	IPL_BLACK	= 0
    } ;
typedef /* [public] */ enum IPL_MORPH IPL_MORPH;

/* [helpstring] */ 
enum IPL_POLARITY
    {	IPL_POLARITY_AUTO	= 0,
	IPL_WHITE_ON_BLACK	= 1,
	IPL_BLACK_ON_WHITE	= 2
    } ;
typedef /* [hidden] */ enum IPL_POLARITY IPL_POLARITY;

/* [helpstring] */ 
enum IPL_KERNEL_MODE
    {	IPL_CLIP_DISABLE	= 0,
	IPL_ABSOLUTE	= 1,
	IPL_SATURATE	= 2,
	IPL_ABSOLUTE_SATURATE	= 3
    } ;
typedef /* [public] */ enum IPL_KERNEL_MODE IPL_KERNEL_MODE;

/* [helpstring] */ 
enum IPL_OVERSCAN_MODE
    {	IPL_OVERSCAN_DISABLE	= 0,
	IPL_OVERSCAN_TRANS	= 2
    } ;
typedef /* [public] */ enum IPL_OVERSCAN_MODE IPL_OVERSCAN_MODE;

/* [helpstring] */ 
enum IPL_NBHOOD_MODE
    {	IPL_CTLID_NORMFACTOR	= 1,
	IPL_CTLID_CLIPFLAG	= 2,
	IPL_CTLID_OVERSCAN	= 3,
	IPL_CTLID_OVERSCAN_REPLACE	= 4,
	IPL_CTLID_XCEN	= 5,
	IPL_CTLID_YCEN	= 6,
	IPL_CTLID_BACKGNDINDEX	= 7,
	IPL_CTLID_OBJECTINDEX	= 8,
	IPL_CTLID_BINPROCMODE	= 9,
	IPL_CTLID_RANGELOW	= 10,
	IPL_CTLID_RANGEHIGH	= 11
    } ;
typedef /* [public] */ enum IPL_NBHOOD_MODE IPL_NBHOOD_MODE;

/* [helpstring] */ 
enum IPL_LABEL_MODE
    {	IPL_RECT4_3x3	= -103,
	IPL_RECT8_3x3	= -104
    } ;
typedef /* [public] */ enum IPL_LABEL_MODE IPL_LABEL_MODE;

/* [helpstring] */ 
enum IPL_BINPROC_MODE
    {	IPL_BINPROCMODE_EQUAL	= 10,
	IPL_BINPROCMODE_NOT_EQUAL	= 11,
	IPL_BINPROCMODE_RANGE	= 12,
	IPL_BINPROCMODE_NOT_EQUAL_CST	= 13
    } ;
typedef /* [public] */ enum IPL_BINPROC_MODE IPL_BINPROC_MODE;


enum IPL_SYSTEM_PARAM
    {	IPL_VL_IPL_USE_THREADS	= 0,
	IPL_VL_IPL_USE_VECTOR_EXTENSIONS	= 1,
	IPL_VL_IPL_NUM_THREADS	= 2,
	IPL_VL_BLOBLOC_USE_THREADS	= 3,
	IPL_VL_BLOBLOC_NUM_THREADS	= 4,
	IPL_VL_PAT_USE_THREADS	= 5,
	IPL_VL_PAT_NUM_THREADS	= 6,
	IPL_VL_BLOB_USE_THREADS	= 7,
	IPL_VL_BLOB_NUM_THREADS	= 8
    } ;
typedef /* [public] */ enum IPL_SYSTEM_PARAM IPL_SYSTEM_PARAM;

struct IPL_POINT
    {
    IPL_LONG xpos;
    IPL_LONG ypos;
    } ;
typedef /* [helpstring] */ struct IPL_POINT IPL_POINT;

struct IPL_POINT_DOUBLE
    {
    IPL_DOUBLE xpos;
    IPL_DOUBLE ypos;
    } ;
typedef /* [helpstring] */ struct IPL_POINT_DOUBLE IPL_POINT_DOUBLE;

struct IPL_POINT3D_DOUBLE
    {
    IPL_DOUBLE xpos;
    IPL_DOUBLE ypos;
    IPL_DOUBLE zpos;
    } ;
typedef /* [helpstring] */ struct IPL_POINT3D_DOUBLE IPL_POINT3D_DOUBLE;

struct IPL_LINE
    {
    IPL_ULONG x0;
    IPL_ULONG y0;
    IPL_ULONG x1;
    IPL_ULONG y1;
    } ;
typedef /* [helpstring] */ struct IPL_LINE IPL_LINE;

struct IPL_LINE_DOUBLE
    {
    IPL_DOUBLE x0;
    IPL_DOUBLE y0;
    IPL_DOUBLE x1;
    IPL_DOUBLE y1;
    } ;
typedef /* [helpstring] */ struct IPL_LINE_DOUBLE IPL_LINE_DOUBLE;

struct IPL_DEVICEINFO
    {
    IPL_LONG DevId;
    IPL_DEVICEINFOFLAGS Flags;
    IPL_CHAR *IdentStr;
    } ;
typedef /* [helpstring] */ struct IPL_DEVICEINFO IPL_DEVICEINFO;

struct IPL_CALIBRATE
    {
    IPL_CHAR chUnit[ 32 ];
    IPL_LONG iPower;
    IPL_DOUBLE dfOffset;
    IPL_LONG iSize;
    IPL_DOUBLE dValues[ 1 ];
    } ;
typedef /* [helpstring] */ struct IPL_CALIBRATE IPL_CALIBRATE;

struct IPL_RECT
    {
    IPL_LONG left;
    IPL_LONG right;
    IPL_LONG top;
    IPL_LONG bottom;
    } ;
typedef /* [helpstring] */ struct IPL_RECT IPL_RECT;

struct IPL_TRACE_STRUCT
    {
    IPL_PROCESS_ID Process;
    IPL_THREAD_ID Thread;
    IPL_TIME Time;
    } ;
typedef /* [helpstring] */ struct IPL_TRACE_STRUCT IPL_TRACE_STRUCT;

typedef IPL_BOOL ( __stdcall *BASE_ONPROGRESS_PTR )( 
    IPL_LONG Total,
    IPL_LONG Done,
    IPL_VOID_PTR Cookie);


EXTERN_C const IID LIBID_vl_base;


#ifndef __vl_base_MODULE_DEFINED__
#define __vl_base_MODULE_DEFINED__


/* module vl_base */
/* [dllname][uuid] */ 

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetPtrEx( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode,
    /* [in] */ IPL_LONG XPos,
    /* [in] */ IPL_LONG YPos,
    /* [in] */ IPL_LONG Band,
    /* [in] */ IPL_LONG Slice,
    /* [in] */ IPL_LONG Frame,
    /* [in] */ IPL_LONG Width,
    /* [in] */ IPL_LONG Height,
    /* [full][out] */ IPL_LONG *Pitch,
    /* [full][out] */ IPL_UCHAR **Ptr);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_ReleasePtrEx( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode,
    /* [in] */ IPL_LONG XPos,
    /* [in] */ IPL_LONG YPos,
    /* [in] */ IPL_LONG Band,
    /* [in] */ IPL_LONG Slice,
    /* [in] */ IPL_LONG Frame,
    /* [in] */ IPL_LONG Width,
    /* [in] */ IPL_LONG Height,
    /* [full][in] */ IPL_UCHAR *Ptr);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetPtr( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode,
    /* [in] */ IPL_LONG Band,
    /* [in] */ IPL_LONG Slice,
    /* [in] */ IPL_LONG Frame,
    /* [full][out] */ IPL_LONG *Pitch,
    /* [full][out] */ IPL_UCHAR **Ptr);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_ReleasePtr( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode,
    /* [in] */ IPL_LONG Band,
    /* [in] */ IPL_LONG Slice,
    /* [in] */ IPL_LONG Frame,
    /* [full][in] */ IPL_UCHAR *Ptr);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAlloc1D( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_BUFFER_DATATYPE Datatype,
    /* [in] */ IPL_BUFFER_ATTRIBUTE Attribute,
    /* [full][in] */ const IPL_DEVICEINFO *DeviceInfo);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAlloc2D( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_BUFFER_DATATYPE Datatype,
    /* [in] */ IPL_BUFFER_ATTRIBUTE Attribute,
    /* [full][in] */ const IPL_DEVICEINFO *DeviceInfo);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAlloc( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG Bands,
    /* [in] */ IPL_ULONG Slices,
    /* [in] */ IPL_ULONG Frames,
    /* [in] */ IPL_BUFFER_DATATYPE Datatype,
    /* [in] */ IPL_BUFFER_ATTRIBUTE Attribute,
    /* [full][in] */ const IPL_DEVICEINFO *DeviceInfo);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAllocChild1D( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_BUFHANDLE Parent,
    /* [in] */ IPL_ULONG XOffset,
    /* [in] */ IPL_ULONG YOffset,
    /* [in] */ IPL_ULONG BandOffset,
    /* [in] */ IPL_ULONG SliceOffset,
    /* [in] */ IPL_ULONG FrameOffset,
    /* [in] */ IPL_ULONG Width);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAllocChild2D( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_BUFHANDLE Parent,
    /* [in] */ IPL_ULONG XOffset,
    /* [in] */ IPL_ULONG YOffset,
    /* [in] */ IPL_ULONG BandOffset,
    /* [in] */ IPL_ULONG SliceOffset,
    /* [in] */ IPL_ULONG FrameOffset,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAllocChild( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_BUFHANDLE Parent,
    /* [in] */ IPL_ULONG XOffset,
    /* [in] */ IPL_ULONG YOffset,
    /* [in] */ IPL_ULONG BandOffset,
    /* [in] */ IPL_ULONG SliceOffset,
    /* [in] */ IPL_ULONG FrameOffset,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG Bands,
    /* [in] */ IPL_ULONG Slices,
    /* [in] */ IPL_ULONG Frames);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufFree( 
    /* [in] */ IPL_BUFHANDLE Buffer);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_DeferredBufFree( 
    /* [in] */ IPL_BUFHANDLE Buffer);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufFreeAll( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufTranslateChild( 
    /* [in] */ IPL_BUFHANDLE Child,
    /* [in] */ IPL_ULONG XOffset,
    /* [in] */ IPL_ULONG YOffset,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufControl( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_BUFCTRLFLAGS Item,
    /* [full][in] */ IPL_CONST_VOID_PTR Value);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufInquire( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_BUFCTRLFLAGS Item,
    /* [full][out] */ IPL_VOID_PTR Value);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetBufData( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Band,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [full][out] */ IPL_VOID_PTR Data);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetBufDataEx( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Band,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG XPos,
    /* [in] */ IPL_ULONG LinePitch,
    /* [full][out] */ IPL_VOID_PTR Data,
    /* [in] */ IPL_BUFFER_DATATYPE Datatype);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_PutBufData( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Band,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [full][in] */ IPL_CONST_VOID_PTR Data);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_PutBufDataEx( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Band,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG XPos,
    /* [in] */ IPL_ULONG LinePitch,
    /* [full][out] */ IPL_CONST_VOID_PTR Data,
    /* [in] */ IPL_BUFFER_DATATYPE Datatype);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetDispData( 
    /* [in] */ IPL_BUFHANDLE Image,
    /* [in] */ IPL_BUFHANDLE MappingLut,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [in] */ IPL_DISPLAY_MODE DisplayMode,
    /* [in] */ IPL_MAP_MODE MapMode,
    /* [in] */ IPL_ULONG RedBandIndex,
    /* [in] */ IPL_ULONG GreenBandIndex,
    /* [in] */ IPL_ULONG BlueBandIndex,
    /* [in] */ IPL_ULONG RedLutBandIndex,
    /* [in] */ IPL_ULONG GreenLutBandIndex,
    /* [in] */ IPL_ULONG BlueLutBandIndex,
    /* [in] */ IPL_BOOL Red,
    /* [in] */ IPL_BOOL Green,
    /* [in] */ IPL_BOOL Blue,
    /* [in] */ IPL_ULONG BitShift,
    /* [full][out] */ IPL_VOID_PTR Data);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetDispDataOverlay( 
    /* [size_is][in] */ IPL_BUFHANDLE Images[  ],
    /* [size_is][in] */ IPL_BUFHANDLE MappingLuts[  ],
    /* [size_is][in] */ IPL_BUFHANDLE DisplayLuts[  ],
    /* [in] */ IPL_ULONG nImages,
    /* [in] */ IPL_ULONG X,
    /* [in] */ IPL_ULONG Y,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_ULONG Slice,
    /* [in] */ IPL_ULONG Frame,
    /* [full][out] */ IPL_VOID_PTR Data);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_ERRORID __stdcall IPL_SetErrorCode( 
    /* [in] */ IPL_ERRORID Error);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_ERRORID __stdcall IPL_GetErrorCode( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_ERRORID __stdcall IPL_GetErrorCode2( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT const IPL_CHAR *__stdcall IPL_StringifyErrorCode( 
    IPL_ERRORID Code);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT const IPL_CHAR *__stdcall IPL_GetErrorString( 
    IPL_ERRORID Code);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT const IPL_CHAR *__stdcall IPL_GetErrorOrigin( 
    IPL_ERRORID Code);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufFreeDim( 
    /* [full][out][in] */ IPL_BUFHANDLE *Buffer,
    /* [in] */ IPL_DIMENSION Dimension,
    /* [size_is][full][in] */ const IPL_ULONG *Offsets,
    /* [in] */ IPL_ULONG nOffsets,
    /* [in] */ IPL_LOCATION Location);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufCombine( 
    /* [size_is][full][in] */ const IPL_BUFHANDLE *Buffers,
    /* [in] */ IPL_ULONG nBuffers,
    /* [full][out][in] */ IPL_BUFHANDLE *Destination,
    /* [in] */ IPL_DIMENSION Dimension,
    /* [in] */ IPL_ULONG Width,
    /* [in] */ IPL_ULONG Height,
    /* [in] */ IPL_GEOTRANS Mode,
    /* [full][in] */ const IPL_DEVICEINFO *DeviceInfo);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufOverlay( 
    /* [size_is][full][in] */ const IPL_BUFHANDLE *Images,
    /* [size_is][full][in] */ const IPL_BUFHANDLE *MappingLuts,
    /* [size_is][full][in] */ const IPL_BUFHANDLE *DisplayLuts,
    /* [in] */ IPL_ULONG nImages,
    /* [full][out][in] */ IPL_BUFHANDLE *Destination);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GrDrawPolygon( 
    /* [in] */ IPL_BUFHANDLE Image,
    /* [in] */ IPL_DRAWINGMODE Mode,
    /* [in] */ IPL_LONG Index,
    /* [size_is][full][in] */ const IPL_POINT *Points,
    /* [in] */ IPL_ULONG nPoints);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GrDrawEllipse( 
    /* [in] */ IPL_BUFHANDLE BufHandle,
    /* [in] */ IPL_LONG XCen,
    /* [in] */ IPL_LONG YCen,
    /* [in] */ IPL_LONG MajorAxis,
    /* [in] */ IPL_LONG MinorAxis,
    /* [in] */ IPL_LONG OutlineColor,
    /* [in] */ IPL_LONG FillColor);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_PushProgressFunction( 
    /* [full][in] */ IPL_VOID_PTR ProgressFunction,
    /* [full][in] */ IPL_VOID_PTR Cookie);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_PopProgressFunction( 
    /* [full][out] */ IPL_VOID_PTR *ProgressFunction,
    /* [full][out] */ IPL_VOID_PTR *Cookie);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_VOID_PTR __stdcall IPL_PeekProgressFunction( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_VOID_PTR __stdcall IPL_PeekProgressCookie( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_VOID_PTR __stdcall IPL_GetInternalProgressFunction( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_CheckLicense( 
    /* [string][full][in] */ const IPL_CHAR *Authentificator,
    /* [string][full][in] */ const IPL_CHAR *PublicKey,
    /* [in] */ IPL_ULONG PublicKeyLength,
    /* [string][full][in] */ const IPL_CHAR *Module,
    /* [full][in] */ const IPL_UCHAR *DataIn,
    /* [in] */ IPL_ULONG DataInSize,
    /* [full][out] */ IPL_UCHAR *DataOut,
    /* [in] */ IPL_ULONG DataOutSize);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_LicenseSerialNumber( 
    /* [string][full][in] */ const IPL_CHAR *Authentificator,
    /* [string][full][in] */ const IPL_CHAR *PublicKey,
    /* [in] */ IPL_ULONG PublicKeySize,
    /* [string][full][out] */ IPL_CHAR *Serial,
    /* [in] */ IPL_ULONG SerialSize);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_Timestamp( 
    /* [string][full][out] */ IPL_CHAR *Stamp);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_Trace( 
    /* [string][full][in] */ const IPL_CHAR *Message);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufLock( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufUnlock( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_LOCK_MODE Mode);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_GetBytesPerItem( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [full][out] */ IPL_ULONG *BytesPerItem);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_IsValidBuffer( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [full][out] */ IPL_BOOL *Valid);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_StoreXML( 
    /* [in] */ IPL_BUFHANDLE Buffer,
    /* [in] */ IPL_COMPRESSION_FLAGS CompressFlags,
    /* [in] */ IPL_SAVE_FLAGS ChildFlags,
    /* [full][out] */ IPL_CHAR **Xml);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufAllocXML( 
    /* [full][out] */ IPL_BUFHANDLE *Buffer,
    /* [full][in] */ const IPL_CHAR *Xml,
    /* [in] */ IPL_BUFHANDLE Parent,
    /* [full][in] */ const IPL_CHAR *Path,
    /* [in] */ IPL_LONG DevHandle);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_FreeXML( 
    /* [full][in] */ IPL_CHAR *Xml);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_CheckForInput( 
    /* [size_is][full][out] */ IPL_BOOL *Valid,
    /* [in] */ IPL_BOOL Block,
    /* [in] */ IPL_BOOL Echo,
    /* [size_is][full][out] */ IPL_CHAR *Character);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_BufWhiteBalance( 
    /* [in] */ IPL_BUFHANDLE hRawImage);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall BASE_CheckLic( void);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall BASE_CheckModule( 
    /* [full][in] */ const IPL_CHAR *Module);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall BASE_GetVersion( 
    /* [full][in] */ const IPL_CHAR *Buffer,
    /* [in] */ IPL_INT Bytes);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall BASE_SetBufferLockTimeout( 
    /* [in] */ IPL_ULONG milliseconds);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall BASE_GetBufferLockTimeout( 
    /* [full][in] */ IPL_ULONG *milliseconds);

/* [helpstring][entry] */ __MIDL_DECLSPEC_DLLIMPORT IPL_FRESULT __stdcall IPL_SetSystem( 
    /* [in] */ IPL_SYSTEM_PARAM Param,
    /* [full][in] */ IPL_VOID *Value);

#endif /* __vl_base_MODULE_DEFINED__ */
#endif /* __vl_base_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_vl_base_0001_0023 */
/* [local] */ 


#ifdef MVIMPACT_H_ // include guard of the main C++ header
	} // namespace mvIMPACT_C
} // namespace mvIMPACT
#endif // #ifdef MVIMPACT_H_



extern RPC_IF_HANDLE __MIDL_itf_vl_base_0001_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vl_base_0001_0023_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


