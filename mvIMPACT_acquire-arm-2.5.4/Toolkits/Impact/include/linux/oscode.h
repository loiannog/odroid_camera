
#ifndef __oscode_h__
#define __oscode_h__

// linux/oscode.h

#ifndef FIELD_OFFSET
#define FIELD_OFFSET(type, field)    ((IPL_LONG)(INT_PTR)&(((type *)0)->field))
#endif

typedef int INT_PTR;

#ifndef NO_THREADS

struct CRITICAL_SECTION
{
	int dummy;
};

// #define EnterCriticalSection(cs)
// #define LeaveCriticalSection(cs)
// #define InitializeCriticalSection(cs)
// #define DeleteCriticalSection(cs)

void InitializeCriticalSection(CRITICAL_SECTION*);
void DeleteCriticalSection(CRITICAL_SECTION*);
void EnterCriticalSection(CRITICAL_SECTION*);
void LeaveCriticalSection(CRITICAL_SECTION*);

const DWORD DLL_PROCESS_ATTACH = 0;
const DWORD DLL_PROCESS_DETACH = 1;
const DWORD DLL_THREAD_ATTACH = 2;
const DWORD DLL_THREAD_DETACH = 3;

#else
struct CThreadSafe
{
#ifdef __cplusplus
	CThreadSafe(int, int) { };
#endif	// __cplusplus
};
#endif // NO_THREADS

void* GlobalAllocPtr(int, int);
void* GlobalReAllocPtr(void*, int, int);
void GlobalUnlockPtr(void*);
void GlobalFree(void*);
void* GlobalPtrHandle(void*);

#define UNUSED( __i )	(( __i ) = ( __i ))
#define Sleep		sleep

inline static int IsBadReadPtr(const void __attribute__((unused)) * BufHandle, int __attribute__((unused)) size)	{ return FALSE; }
inline static int IsBadWritePtr(void __attribute__((unused)) * BufHandle, int __attribute__((unused)) size)		{ return FALSE; }
inline static int IsBadStringPtr(const char __attribute__((unused)) * msg, unsigned int __attribute__((unused)) size)	{ return FALSE; }
inline static int IsBadCodePtr(void __attribute__((unused)) * Value)							{ return FALSE; }

//typedef void (__stdcall *FARPROC)();
typedef void *FARPROC;

#define GMEM_MOVEABLE 0
#define GMEM_ZEROINIT 0

#include <errno.h>

inline static long GetLastError()		{ return errno ; }
inline static void SetLastError(long e)		{ errno = e ; }

unsigned long TlsAlloc();
int TlsSetValue(unsigned long, void*);
void* TlsGetValue(unsigned long);
int TlsFree(unsigned long);

#define IPL_CPP_CALLTYPE
typedef unsigned int UINT_PTR;

#ifdef __cplusplus

void CloseHandle(unsigned int);

inline int __min ( int a, int b ) { return a < b ? a : b ; }
inline int __max ( int a, int b ) { return a > b ? a : b ; }

inline int min ( int a, int b ) { return a < b ? a : b ; }
inline int max ( int a, int b ) { return a > b ? a : b ; }

inline unsigned int min ( unsigned int a, unsigned int b ) { return a < b ? a : b ; }
inline unsigned int max ( unsigned int a, unsigned int b ) { return a > b ? a : b ; }

inline unsigned long min ( unsigned long a, unsigned long b ) { return a < b ? a : b ; }
inline unsigned long max ( unsigned long a, unsigned long b ) { return a > b ? a : b ; }

inline long min ( long a, long b ) { return a < b ? a : b ; }
inline long max ( long a, long b ) { return a > b ? a : b ; }

inline float min ( float a, float b ) { return a < b ? a : b ; }
inline float max ( float a, float b ) { return a > b ? a : b ; }

inline double min ( double a, double b ) { return a < b ? a : b ; }
inline double max ( double a, double b ) { return a > b ? a : b ; }

inline double __min ( double a, double b ) { return a < b ? a : b ; }
inline double __max ( double a, double b ) { return a > b ? a : b ; }

#endif	// __cplusplus

inline static long __min ( long a, long b ) { return a < b ? a : b ; }
inline static long __max ( long a, long b ) { return a > b ? a : b ; }



#endif // __oscode_h__
