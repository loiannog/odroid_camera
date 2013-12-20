//----------------------------------------------------------------------
//----------------------------------------------------------------------
/*
        mvIMPACT - operating system dependent global definitions
                    *** LINUX version ***
*/
//----------------------------------------------------------------------
//----------------------------------------------------------------------
#ifndef __system_h__
#define __system_h__

//----------------------------------------------------------------------
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

#ifdef __USE_CURSES__
    #include <curses.h>
#endif    // __USE_CURSES__

#include <unistd.h>

//----------------------------------------------------------------------
#define __cdecl
#define __declspec(exp)
#define __stdcall

#define WINAPI
#define FAR
#define CALLBACK

//#define _MAX_EXT 256    // TODO : (td) under windows in stdlib.h

#define MV_MOD_API(type)    extern type
#define M_SQRT_2            (M_SQRT2/2.0)

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif    // __cplusplus

//---------------------------------
//change td(18.04.02)
#ifndef FALSE
#define FALSE                0
#endif    // FALSE

#ifndef TRUE
#define TRUE                1 //(!FALSE)
#endif    // TRUE

//---------------------------------
#define GCCUNUSED            __attribute__((__unused__))

//---------------------------------
#define VOID                void


typedef int                    INT ;
typedef int                    BOOL ;
typedef void                *PVOID ;
typedef unsigned char        BYTE ;
typedef unsigned short        WORD ;
typedef unsigned long        DWORD ;
typedef unsigned int        UINT;
typedef signed long            LONG;
typedef char FAR*            LPSTR;
typedef LPSTR                LPTSTR;
typedef const char FAR*        LPCSTR;
typedef const char FAR*        LPCTSTR;
typedef BYTE FAR*            LPBYTE;
typedef int FAR*            LPINT;
typedef WORD FAR*            LPWORD;
typedef long FAR*            LPLONG;
typedef DWORD FAR*            LPDWORD;
typedef void FAR*            LPVOID;
typedef LPINT                LRESULT;
typedef DWORD                ACCESS_MASK;

typedef void                *MSG ;


#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)((UINT)(w) >> 8))

#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))

#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))

#define _snprintf           snprintf
#define _stricmp(s1,s2)        strcasecmp(s1,s2)
#define stricmp(s1,s2)        strcasecmp(s1,s2)
#define _getcwd(ch,i)       getcwd(ch, i);

// TODO : in File.cpp no ref ?? (td)
EXTERN_C int _access( const char *path, int mode );
EXTERN_C void   __cdecl _splitpath(const char *, char *, char *, char *, char *);
EXTERN_C void   __cdecl _makepath(char *, const char *, const char *, const char *, const char *);

// TODO : inline _itoa
#define _itoa(i,s,b)        sprintf(s, b==10?"%ld":"%lx", i )

typedef unsigned long   SYSTEMTIME ;
typedef unsigned long   IID ;

typedef void            *HWND ;
typedef void            *HDC ;
typedef void            *HMENU ;
typedef void            *HKEY ;
typedef unsigned long   COLORREF ;
typedef void            *HICON ;
typedef void            *HCURSOR ;
typedef void            *HINSTANCE ;
typedef void            *HMODULE ;

typedef void            *HANDLE ;
typedef HANDLE          HDRAWDIB;
typedef HANDLE          HBITMAP;
typedef HANDLE          HPALETTE;
typedef HANDLE          HPEN;
typedef HANDLE          HBRUSH;
typedef HANDLE          HFONT;
typedef HANDLE          HRGN;

// API declaration
typedef struct tagPOINT
{ // pt
    LONG x;
    LONG y;
} POINT;

typedef struct _RECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

typedef RECT*            LPRECT;

typedef struct tagLOGBRUSH
{
    UINT lbStyle;
    COLORREF lbColor;
    LONG lbHatch;
}
LOGBRUSH;

typedef struct tagSIZE
{
    LONG cx;
    LONG cy;
} SIZE;

#define LF_FACESIZE        32
typedef char    TCHAR;

typedef struct tagLOGFONT
{
    LONG lfHeight;
    LONG lfWidth;
    LONG lfEscapement;
    LONG lfOrientation;
    LONG lfWeight;
    BYTE lfItalic;
    BYTE lfUnderline;
    BYTE lfStrikeOut;
    BYTE lfCharSet;
    BYTE lfOutPrecision ;
    BYTE lfClipPrecision ;
    BYTE lfQuality ;
    BYTE lfPitchAndFamily ;
    TCHAR lfFaceName[LF_FACESIZE] ;
}
LOGFONT;

////////////////////////////////////////////

#include <oscode.h>

////////////////////////////////////////////
#if 0
#define RGB(r,g,b) ((COLORREF)(( (((DWORD)(r))<<24) | (((DWORD)(g))<<16) | (((WORD)(b))<<8))))

#define PALETTERGB(r,g,b) (0x02 | RGB(r,g,b))
#else
#define RGB(r,g,b) ((COLORREF)(( (((DWORD)(r))<<16) | (((DWORD)(g))<<8) | (((WORD)(b))))))
#define PALETTERGB(r,g,b) RGB(r,g,b)

#endif

#define _pack __attribute__ ((packed))

#ifdef __BIG_ENDIAN__    // PPC ...

typedef struct { BYTE b0, b1, b2, b3; } _pack miDWORD ;
typedef struct { BYTE b0, b1, b2, b3; } _pack miLONG ;

typedef struct { 
  BYTE b0, b1;         
  inline operator miLONG()
    {
      miLONG l1;
      l1.b0 = b0;
      l1.b1 = b1;
      l1.b2 = 0;
      l1.b3 = 0;
      return l1;
    }
 } _pack miWORD ;

inline static WORD  mdWord  ( miWORD w )
    {
        return ( ((WORD)w.b1) << 8 ) | w.b0 ;
    }

inline static WORD mnWord  ( miWORD w )
    {
        return (( ((WORD)w.b0) << 8 ) | (WORD)w.b1 );
    }

inline static LONG  mdLong  ( miLONG l )
    {
        miLONG l1 ;
        l1.b0 = l.b3 ;
        l1.b1 = l.b2 ;
        l1.b2 = l.b1 ;
        l1.b3 = l.b0 ;
        return *(LONG *)&l1 ;
    }

inline static DWORD mdDWord ( miDWORD d )
    {
        miDWORD d1 ;
        d1.b0 = d.b3 ;
        d1.b1 = d.b2 ;
        d1.b2 = d.b1 ;
        d1.b3 = d.b0 ;
        return *(DWORD *)&d1 ;
    }

inline static miWORD  miWord  ( WORD w )
    {
        miWORD w1;
        w1.b0 = ((miWORD *)&w)->b1;
        w1.b1 = ((miWORD *)&w)->b0;
        return w1;
    }

inline static miLONG  miLong  ( LONG l )
    {
        miLONG l1 ;
        l1.b0 = ((miLONG *)&l)->b3 ;
        l1.b1 = ((miLONG *)&l)->b2 ;
        l1.b2 = ((miLONG *)&l)->b1 ;
        l1.b3 = ((miLONG *)&l)->b0 ;
        return l1 ;
    }

inline static miDWORD miDWord ( DWORD d )
    {
        miDWORD d1 ;
        d1.b0 = ((miDWORD *)&d)->b3 ;
        d1.b1 = ((miDWORD *)&d)->b2 ;
        d1.b2 = ((miDWORD *)&d)->b1 ;
        d1.b3 = ((miDWORD *)&d)->b0 ;
        return d1 ;
    }



size_t  diFread(  void *ptr, size_t size, size_t nmemb, FILE *stream ) ;
size_t  diFwrite(  void *ptr, size_t size, size_t nmemb, FILE *stream ) ;

#else
#define mdWord(w)    (w)
#define mnWord(w)    (w)
#define mdLong(l)    (l)
#define mdDWord(d)    (d)

#define miWord(w)    (w)
#define miLong(l)    (l)
#define miDWord(d)    (d)

typedef WORD  miWORD ;
typedef LONG  miLONG  ;
typedef DWORD miDWORD ;

#define  diFread(p,s,n,f)    fread(p,s,n,f)
#define  diFwrite(p,s,n,f)    fwrite(p,s,n,f)

//#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

//#define PALETTERGB(r,g,b) (0x02000000 | RGB(r,g,b))
#endif

typedef struct tagPAINTSTRUCT {
    HDC         hdc;
    BOOL        fErase;
    RECT        rcPaint;
    BOOL        fRestore;
    BOOL        fIncUpdate;
    BYTE        rgbReserved[32];
} __attribute__ ((packed)) PAINTSTRUCT;

typedef struct tagBITMAPCOREHEADER {
        miDWORD   bcSize;                 /* used to get to color table */
        miWORD    bcWidth;
        miWORD    bcHeight;
        miWORD    bcPlanes;
        miWORD    bcBitCount;
} __attribute__ ((packed)) BITMAPCOREHEADER;


// TODO : BITMAPINFOHEADER windows specific
// td
typedef struct tagBITMAPINFOHEADER{ // bmih
    miDWORD  biSize;
       miLONG   biWidth;
    miLONG   biHeight;
    miWORD   biPlanes;
       miWORD   biBitCount;
    miDWORD  biCompression;
    miDWORD  biSizeImage;
       miLONG   biXPelsPerMeter;
    miLONG   biYPelsPerMeter;
    miDWORD  biClrUsed;
       miDWORD  biClrImportant;
} __attribute__ ((packed)) BITMAPINFOHEADER;

typedef BYTE    LPBITMAPINFOHEADER;

typedef struct tagRGBQUAD { // rgbq
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} __attribute__ ((packed)) RGBQUAD;

typedef struct tagBITMAPINFO { // bmi
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];
} __attribute__ ((packed)) BITMAPINFO;

typedef struct tagBITMAPFILEHEADER { // bmfh
    miWORD    bfType;
    miDWORD   bfSize;
    miWORD    bfReserved1;
    miWORD    bfReserved2;
    miDWORD   bfOffBits;
} __attribute__ ((packed)) BITMAPFILEHEADER;


//----------------------------------------------------------------------
//----------------------------------------------------------------------
/* constants for the biCompression field */
#define BI_RGB                0L
#define BI_RLE8                1L
#define BI_RLE4                2L
#define BI_BITFIELDS        3L
#define BI_JPEG                4L
#define BI_PNG                5L

//----------------------------------------------------------------------
//----------------------------------------------------------------------
#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define FILE_ATTRIBUTE_READONLY         0x00000001
#define FILE_ATTRIBUTE_HIDDEN           0x00000002
#define FILE_ATTRIBUTE_SYSTEM           0x00000004
#define FILE_ATTRIBUTE_DIRECTORY        0x00000010
#define FILE_ATTRIBUTE_ARCHIVE          0x00000020
#define FILE_ATTRIBUTE_NORMAL           0x00000080
#define FILE_ATTRIBUTE_TEMPORARY        0x00000100

/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */
#ifndef _MAC

#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

#define GENERIC_READ                (0x80000000) /* from WINNT.H */
#define GENERIC_WRITE               (0x40000000) /* from WINNT.H */
#define FILE_SHARE_READ             (0x00000001) /* from WINNT.H */
#define FILE_SHARE_WRITE            (0x00000002) /* from WINNT.H */

#define INVALID_HANDLE_VALUE        ((HANDLE)NULL)

#define FILE_BEGIN                  SEEK_SET
#define FILE_CURRENT                SEEK_CUR
#define FILE_END                    SEEK_END


typedef void *LPSECURITY_ATTRIBUTES, *LPOVERLAPPED ;

extern DWORD SetFilePointer( HANDLE hFile,
                             LONG   lDistanceToMove,
                             LONG   *lpDistanceToMoveHigh,
                             DWORD  dwMoveMethod ) ;


extern HANDLE CreateFile(  LPCSTR lpFileName,
                           DWORD  dwDesiredAccess,       // access (read-write) mode : GENERIC_READ, GENERIC_WRITE
                           DWORD  dwShareMode,
                           LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                           DWORD dwCreationDisposition,
                           DWORD dwFlagsAndAttributes,
                           HANDLE hTemplateFile ) ;

extern BOOL CloseHandle ( HANDLE hFile ) ;

extern BOOL ReadFile ( HANDLE hFile,
                       LPVOID lpBuffer,
                       DWORD nNumberOfBytesToRead,
                       LPDWORD lpNumberOfBytesRead,
                       LPOVERLAPPED lpOverlapped ) ;

extern BOOL WriteFile( HANDLE  hFile,
                       LPVOID  lpBuffer,
                       DWORD   nNumberOfBytesToWrite,
                       LPDWORD lpNumberOfBytesWritten,
                       LPOVERLAPPED lpOverlapped ) ;

extern HDC GetDC( HDC hdc );
extern HANDLE GetProcessHeap( );
extern BOOL HeapFree( HANDLE hHeap, DWORD dwFlags, LPVOID lpMem );
extern int ReleaseDC(
  HWND hWnd,  // handle to window
  HDC hDC     // handle to DC
);

#else   /* def _MAC */

#define _MAX_PATH   256 /* max. length of full pathname */
#define _MAX_DIR    32  /* max. length of path component */
#define _MAX_FNAME  64  /* max. length of file name component */

#endif  /* _MAC */



// TODO : use inline for min & max, check types, int ??
#if 0
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#endif


//----------------------------------------------------------------------
//----------------------------------------------------------------------
#ifndef _T
#define _T( s )        s
#endif

#define _tcsnset( buf, val, size)            memset( buf, val, size)

#define _tcslen( str )                        strlen( str )

#define _tcsicmp( str1, str2 )                strcmp( str1, str2 )
#define _tcsncmp( str1, str2, len )            strncmp( str1, str2, len )

#define _tcscpy( dest, src )                strcpy( dest, src )
#define _tcsncpy( dest, src, len )            strncpy( dest, src, len )

#define _tcstok( s, delim )                 strtok( s, delim )

#define _stscanf( t, s, val )                sscanf( t, s, val )

//----------------------------------------------------------------------
//typedef char TCHAR;
//----------------------------------------------------------------------

#ifdef __cplusplus
int _stprintf( char *buf, const char *s, char *arg );
int _stprintf( char *buf, const char *s );
#endif    // __cplusplus
int _stprintf( char *buf, const char *s, int arg );

//----------------------------------------------------------------------
// events for Linux
//----------------------------------------------------------------------
//#ifndef NO_THREADS
    //#include <semaphore.h>
    //#include <mvs_semaph.h>

//#endif    // NO_THREADS

//----------------------------------------------------------------------
void InvalidateRect( HWND hwnd, const RECT *lpRect, BOOL bErase );

#define SB_VERT                0
#define SB_HORZ                1
int GetScrollPos( HWND hWindow, int nBar );

BOOL InflateRect( LPRECT lprc, int dx, int dy );

#ifdef USE_SYS_KBHIT
int _kbhit( void );    /* moved to conio.cpp */
#else
#include <conio.h>
#endif    // USE_SYS_KBHIT

//----------------------------------------------------------------------
// 4 debugs
//----------------------------------------------------------------------
#define _stmt( stmt )        do { stmt ; } while( 0 )

//#ifndef LOCAL_DEBUG
//    #define LOCAL_DEBUG        1
//#endif

#ifdef _DEBUG
    #define DEBUG
#endif    // _DEBUG

#ifdef DEBUG
    #define dprintf( p )    _stmt( printf p; )
    //#define dprintf( p )    _stmt( if( Debug & LOCAL_DEBUG ) printf p; )
#else
    #define dprintf( p )    do { } while( 0 )
#endif


//----------------------------------------------------------------------
//----------------------------------------------------------------------
#endif // __system_h__

