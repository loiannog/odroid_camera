
#ifndef __ostypes_h__
#define __ostypes_h__

// ostypes.h
// type definitions for linux

#include <osconfig.h>
#include <system.h>
#ifdef __ppc603e__
	#include <picogui.h>
#endif	// __ppc603e__

typedef long            LONG_PTR;

typedef long            _IPL_FRESULT;
typedef char            _IPL_CHAR;
typedef unsigned char   _IPL_UCHAR;
typedef short           _IPL_SHORT;
typedef unsigned short  _IPL_USHORT;
typedef int             _IPL_INT;
typedef unsigned int    _IPL_UINT;
typedef long            _IPL_LONG;
typedef unsigned long   _IPL_ULONG;
typedef float           _IPL_FLOAT;
typedef double          _IPL_DOUBLE;
typedef char            _IPL_STRING;
typedef void            _IPL_VOID;
typedef void*           _IPL_VOID_PTR;
typedef const void*     _IPL_CONST_VOID_PTR;
typedef unsigned short  _IPL_WORD;
typedef unsigned int    _IPL_DWORD;
typedef _IPL_LONG       _IPL_BUFHANDLE;
typedef _IPL_LONG       _IPL_ERRORID;

typedef _IPL_LONG       _IPL_TIME; //SYSTEMTIME
typedef int             _IPL_BOOL;
typedef int             _IPL_FILE_HANDLE;

typedef _IPL_DWORD      _IPL_PROCESS_ID;
typedef _IPL_DWORD      _IPL_THREAD_ID;
typedef _IPL_ULONG      _IPL_HFILE;

#define _inline			inline

#ifdef __cplusplus

	#define AUTOTYPECONVERT(ipltype, orgtype, member)	\
		ipltype() 										\
			{ member = 0; } 							\
		ipltype(orgtype r) 								\
			{ member = (ipltype)r; } 					\
		operator orgtype() 								\
			{ return (orgtype)member; }

#else

	#define AUTOTYPECONVERT(ipltype, orgtype, member)

#endif

typedef _IPL_LONG		_IPL_HWND;
#ifdef __ppc603e__
	typedef pgcontext		_IPL_HDC;
#else
	typedef void*		_IPL_HDC;
#endif	// __ppc603e__
typedef _IPL_LONG		_IPL_COLOR;

struct _IPL_HMENU
{
	_IPL_VOID* menu;
	AUTOTYPECONVERT(_IPL_HMENU, HMENU, menu)
};
typedef struct _IPL_HMENU _IPL_HMENU;

struct _IPL_HKEY
{
	_IPL_VOID* key;
	AUTOTYPECONVERT(_IPL_HKEY, HKEY, key)
};
typedef struct _IPL_HKEY _IPL_HKEY;


struct _IPL_HTHREAD
{
	_IPL_VOID* thread;
	AUTOTYPECONVERT(_IPL_HTHREAD, HANDLE, thread)
};
typedef struct _IPL_HTHREAD _IPL_HTHREAD;

struct _IPL_HICON
{
	_IPL_VOID* icon;
	AUTOTYPECONVERT(_IPL_HICON, HICON, icon)
};
typedef struct _IPL_HICON _IPL_HICON;

struct _IPL_HCURSOR
{
	_IPL_VOID* cursor;
	AUTOTYPECONVERT(_IPL_HCURSOR, HCURSOR, cursor)
};
typedef struct _IPL_HCURSOR _IPL_HCURSOR;

struct _IPL_HDLL
{
	_IPL_VOID* instance;
	AUTOTYPECONVERT(_IPL_HDLL, HINSTANCE, instance)

// td	_IPL_HDLL(int i) { };
//	operator IPL_VOID_PTR() { return 0 ; }
};
typedef struct _IPL_HDLL _IPL_HDLL;

struct _IPL_HMODULE
{
	_IPL_VOID* instance;
	AUTOTYPECONVERT(_IPL_HMODULE, HMODULE, instance)

// td	_IPL_HMODULE(int i) { };
//	operator IPL_VOID_PTR() { return 0 ; }
};
typedef struct _IPL_HMODULE _IPL_HMODULE;



//**************************************************************

// ... vl_blob ...
typedef _IPL_LONG _BL_BUFHANDLE;

// ... vl_blobloc ...
typedef _IPL_LONG _BLOC_BUFHANDLE;
typedef _IPL_LONG _BLOC_HANDLE;

// ... vl_device ...
typedef _IPL_LONG _DEV_HANDLE;

// ... vl_display ...
typedef _IPL_LONG _DISP_OOIHANDLE;
typedef _IPL_LONG _DISP_OOISETHANDLE;

// ... vl_gauge ...
typedef _IPL_LONG _GAU_BUFHANDLE;

// ... vl_pat ...
typedef _IPL_LONG _PAT_BUFHANDLE;

// ... vl_cr1d ...
typedef _IPL_LONG _CR1D_BUFHANDLE;

// ... vl_cr2d ...
typedef _IPL_LONG _CR2D_BUFHANDLE;

#endif // __ostypes_h__

