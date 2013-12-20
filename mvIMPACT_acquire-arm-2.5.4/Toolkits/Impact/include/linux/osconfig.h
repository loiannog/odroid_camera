
#ifndef __osconfig_h__
#define __osconfig_h__

// osconfig.h
// platform specific configuration for MVtitan / TriMedia

// this define compiles the ipl libraries without multithreading
// uncomment, if you need multithreading
#define NO_THREADS

// this define compiles the ipl libraries without tracing
// uncomment, if you need tracing support
#define NO_TRACING

// this define compiles the ipl libraries without licensing
// uncomment, if you need licensing support
//#define NO_LICENSING

// this define compiles the ipl libraries without progress control
// uncomment, if you need progress control support
#define NO_PROGRESS

// this define compiles the ipl libraries without typelibs
// uncomment, if you need typelibs
#define NO_TYPELIB

// this define compiles the ipl libraries without bigimage support
// uncomment, if you need bigimage support
#define NO_BIGIMAGE

// disk based buffer
#define NO_DISK_BASED_BUFFER

// disable autolink pragma
#define NO_VL_DISPLAY_AUTOLINK
#define NO_VL_FILE_AUTOLINK
#define NO_VL_BASE_AUTOLINK
#define NO_VL_OCR_AUTOLINK
#define NO_VL_DEVICE_AUTOLINK
#define NO_VL_IPL_AUTOLINK
#define NO_VL_AUTOFOCUS_AUTOLINK
#define NO_VL_PAT_AUTOLINK
#define NO_VL_AUTOREG_AUTOLINK
#define NO_VL_AUTOTRACE_AUTOLINK
#define NO_VL_BLOB_AUTOLINK
#define NO_VL_COLOR_AUTOLINK
#define NO_VL_GAUGE_AUTOLINK
#define NO_VL_SLICE_AUTOLINK
#define NO_VL_BARCODE_AUTOLINK
#define NO_VL_DUMMY_AUTOLINK
#define NO_VL_DEFECT_AUTOLINK
#define NO_VL_COMPRESS_AUTOLINK
#define NO_VL_GMM_AUTOLINK
#define NO_VL_CR1D_AUTOLINK
#define NO_VL_CR2D_AUTOLINK
#define NO_VL_CAMCAL_AUTOLINK
#define NO_VL_MATH_AUTOLINK
#define NO_VL_TIME_AUTOLINK
#define NO_VL_BLOBLOC_AUTOLINK

#endif // __osconfig_h__
