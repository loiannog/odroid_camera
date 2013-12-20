#! /bin/make
##############################################
# common make definitions
# supported CPUs : x86(native and cross on x86_64),
#   ppc (native and cross on ppc64),
#   ppc603e(cross), arm(cross) and x86_64 (native)

include $(SYSTEM_PATH)/version.inc
GLOBAL_PACKAGE_VERSION=$(GPV_MAJOR).$(GPV_MINOR).$(GPV_BUILD)

#-------------------------------------------------
# SYSTEM_PATH will be set in the Makefile.inc
# of each library!
#-------------------------------------------------
include $(SYSTEM_PATH)/config.inc

#-------------------------------------------------
#-------------------------------------------------
# for CYGWIN user
#---------------------------------------------
ifeq ($(OSTYPE),cygwin)
	OTYPEDEF=-D__cygwin__
	TARGET=ppc603e
	TARGET_SYST=$(OSTYPE)
else
	OTYPEDEF=
	TARGET_SYST=$(TARGET)
endif

#---------------------------------------------
GCCPATH=$(GCC_$(HOSTTYPE)X$(TARGET_SYST))


#---------------------------------------------
# when not cross compiling just set these to the standard directories
CROSS_USER_INC_PATH=/usr/include

# This is the default rule but it detects the wrong directory on x86(32bit) systems that happen to have a /usr/lib64 directory.
# However this problem will be corrected for each platform specifically further down the page
CROSS_USER_LIB_PATH=$(shell if [ -h /usr/lib ]; then echo "/usr/lib"; else if [ -e /usr/lib64 ]; then echo "/usr/lib64"; else echo "/usr/lib"; fi; fi)

DISTCC=
CCACHE=

ifeq ($(TARGET),ppc603e)
	CPUTYPEDEF=-D__ppc603e__
	CROSS_USER_INC_PATH=$(GCCPATH)/usr/include
	CROSS_USER_LIB_PATH=$(GCCPATH)/usr/lib

	# for compatibility with older Makefiles
	PPC_USER_INC_PATH=$(CROSS_USER_INC_PATH)
	PPC_USER_LIB_PATH=$(CROSS_USER_LIB_PATH)

	CROSS_USR_INC=-I$(CROSS_USER_INC_PATH)

	CROSS_PREFIX=powerpc-linux-

	DISTCC=$(shell which distcc 2>/dev/null)
	CCACHE=$(shell which ccache 2>/dev/null)

else
	CPUTYPEDEF=
	ifeq ($(TARGET),arm)
	# alternative toolchains
 		CROSS_USER_INC_PATH=$(GCCPATH)/arm-linux/include
 		CROSS_USER_LIB_PATH=$(GCCPATH)/arm-linux/lib
	#
	# Gentoo toolchain
#		CROSS_USER_INC_PATH=/usr/arm-any-linux-gnu/usr/include/
#		CROSS_USER_LIB_PATH=/usr/arm-any-linux-gnu/usr/lib/

		CROSS_USR_INC=-I$(CROSS_USER_INC_PATH)

	# alternative toolchains
		CROSS_PREFIX=arm-linux-

	# Gentoo toolchain
#		CROSS_PREFIX=arm-unknown-linux-gnu-
	else
		ifeq ($(TARGET),x86)
			ifeq ($(HOSTTYPE),x86_64)
				# building for 32 bit on 64 bit system - use 64 bit compiler with -m32 option
				CROSS_USER_INC_PATH=/usr/include
				CROSS_USER_LIB_PATH=/usr/lib32
			else
				ifneq (,$(findstring 86,$(HOSTTYPE)))
					# building for 32 bit on an x86 32 bit system - just use the standard directories
					CROSS_USER_INC_PATH=/usr/include
					CROSS_USER_LIB_PATH=/usr/lib
				endif
			endif
		else
			ifeq ($(TARGET),ppc)
				ifeq ($(HOSTTYPE),ppc64)
					# building for 32 bit on 64 bit system - use 64 bit compiler with -m32 option
					CROSS_USER_INC_PATH=/usr/include
					CROSS_USER_LIB_PATH=/usr/lib
				endif
			else
				ifeq ($(TARGET),ppc_6xx)
					CPUTYPEDEF=-D__ppc_6xx__
					CROSS_USER_INC_PATH=$(GCCPATH)/usr/include
					CROSS_USER_LIB_PATH=$(GCCPATH)/usr/lib
					CROSS_PREFIX=ppc_6xx-
				else
					ifeq ($(TARGET),xcell)
						CPUTYPEDEF=-D__ppc_970__
						CROSS_USER_INC_PATH=/usr/include
						CROSS_USER_LIB_PATH=/usr/lib
					else
						ifeq ($(TARGET),xcell64)
							CPUTYPEDEF=-D__ppc_970__
							CROSS_USER_INC_PATH=/usr/include
							CROSS_USER_LIB_PATH=/usr/lib64
						else
							ifeq ($(TARGET),armv7a)
								CROSS_PREFIX=arm-angstrom-linux-gnueabi-
								CROSS_USER_INC_PATH=$(GCCPATH)/include
								CROSS_USER_LIB_PATH=$(GCCPATH)/lib
								CPUTYPEDEF=-D__armv7a__
								CROSS_USER_FLAGS=-march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \
									-Wl,-rpath-link,$(CROSS_USER_LIB_PATH),--hash-style=gnu \
									-mthumb-interwork -mno-thumb -isystem$(CROSS_USER_INC_PATH) \
									-fexpensive-optimizations -frename-registers -fomit-frame-pointer
							else
								ifeq ($(TARGET),oeppc)
									CROSS_PREFIX=powerpc-angstrom-linux-
									CROSS_USER_INC_PATH=/usr/local/angstrom/powerpc/powerpc-angstrom-linux/usr/include
									CROSS_USER_LIB_PATH=/usr/local/angstrom/powerpc/powerpc-angstrom-linux/usr/lib
								else
									ifeq ($(TARGET),armv6zk)
										CROSS_PREFIX=arm-bcm2708hardfp-linux-gnueabi-
										CROSS_USER_INC_PATH=$(SDK_PATH)/arm-bcm2708hardfp-linux-gnueabi/sysroot/usr/include
										CROSS_USER_LIB_PATH=$(SDK_PATH)/arm-bcm2708hardfp-linux-gnueabi/sysroot/usr/lib
										CPUTYPEDEF=-D__armv6zk__
										CROSS_USER_FLAGS=-mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s \
										-Wl,-rpath-link,$(CROSS_USER_LIB_PATH),--hash-style=gnu \
										-mthumb-interwork -isystem$(CROSS_USER_INC_PATH) \
										-fexpensive-optimizations -frename-registers -fomit-frame-pointer
									endif
								endif
							endif
						endif
					endif
				endif
			endif
		endif
	endif
endif

#---------------------------------------------
ifeq ($(CCACHE),)
	# ccache not found, just use distcc if found
	SPEED_PREFIX = $(DISTCC)

else
	# ccache found, use it
	ifneq ($(DISTCC),)
		# use distcc with ccache if found
		export CCACHE_PREFIX = distcc
	endif

	SPEED_PREFIX = ccache

endif

#-------------------------------------------------
#-------------------------------------------------
GLOBINCFILES=								\
	$(PPC_USR_INC)							\

#---------------------------------------------
#===========================================
# OPT
# ---
# To get debug-info set OPT=-g; with OPT=-O2
# you get the sources optimized; if OPT=-pg
# -a there will be generated a profiling
# file (bb.out).
#
#===========================================
#---------------------------------------------
ifeq ($(OPT),)
	OPT=-O2
	USE_NDEBUG=-DNDEBUG
	ifeq ($(TARGET),armv7a)
		OPT=-O3
	endif
endif

#---------------------------------------------
#===========================================
# compile level options
# -fPIC	 needed for SO
#===========================================
COMP_OPTIONS=				\
	-Wall -W -fPIC -D_REENTRANT -D_GNU_SOURCE	\
	-D_MAJOR_VERSION=$(GPV_MAJOR)				\
	-D_MINOR_VERSION=$(GPV_MINOR)				\
	-D_BUILD_VERSION=$(GPV_BUILD)				\
	-D_BUILD2_VERSION=$(GPV_BUILD2)				\


ifeq ($(findstring xcell,$(TARGET)),xcell) # caches both xcell and xcell64
	COMP_OPTIONS += -mcpu=970
endif

#---------------------------------------------
CPPFLAGS_2=					\
	$(OTYPEDEF)				\
	$(CPUTYPEDEF)			\
	$(INCFILES)				\
	$(CROSS_USR_INC)		\
	$(OPT)					\
	$(COMP_OPTIONS)			\
	$(CPPFLAGS_1)			\
	$(CROSS_USER_FLAGS)	\
	$(USE_NDEBUG)

#-------------------------------------------------
#-------------------------------------------------
ifneq ($(GCCPATH),)
	CC_TOOL_PATH=$(GCCPATH)/bin/$(CROSS_PREFIX)
	TOOLS= $(SPEED_PREFIX) $(CC_TOOL_PATH)
endif

#---------------------------------------------
#===========================================
# modifier for built-in rules
#===========================================
#	CC  = $(TOOLS)gcc
#	CXX = $(TOOLS)g++
##AR	= $(CC_TOOL_PATH)ar
#AR	= ar

#---------------------------------------------
HAVE_GCC := $(shell if [ -x $(CC_TOOL_PATH)gcc ]; then echo "yes"; else echo "no"; fi )

ifeq ($(HAVE_GCC),yes)
	GCC_VERSION        := $(shell $(CC) -dumpversion 2>&1)
	GCC_MAJOR          := $(shell echo $(GCC_VERSION) | cut -d'.' -f1)
	GCC_MINOR          := $(shell echo $(GCC_VERSION) | cut -d'.' -f2)
	# C++ symbol visibility support since version 4.0
	CPP_SYM_VISIBILITY := $(shell if [ $(GCC_MAJOR) -ge 4 ] ; then 	\
								echo "-fvisibility=hidden";			\
							else									\
								echo "";							\
							fi )
	# OpenMP support since gcc version 4.2
	OPENMP             := $(shell if [ $(GCC_MAJOR) -ge 4 ] && [ $(GCC_MINOR) -ge 2 ]; then	\
								echo "-fopenmp";					\
							else									\
								echo "";							\
							fi )
	# static libstdc++ link support since gcc version 4.5
	CPP_STATIC_LINK    := $(shell if [ $(GCC_MAJOR) -ge 4 ] && [ $(GCC_MINOR) -ge 5 ]; then	\
								echo "-static-libgcc -static-libstdc++";			\
							else									\
								echo "";							\
							fi )
endif

ifeq ($(CPP_SYM_VISIBLE),y)
else
	CPPFLAGS_2 += $(CPP_SYM_VISIBILITY)
endif
# uncomment following line to re-enable OpenMP
#CPPFLAGS_2 += $(OPENMP)

#---------------------------------------------
#---------------------------------------------
.PHONY: new default info build $(TARGET)
#===========================================
default:	all

#-------------------------------------------
build: clean_mod all

#-------------------------------------------
new: clean_mod strip

#-------------------------------------------
$(TARGET_SYST):
#	mkdir -p $(TARGET)

#-------------------------------------------
$(TARGET_SYST)/%.o:	%.c
	$(CC) -c $(CPPFLAGS)	-o $@ $<

#-------------------------------------------
$(TARGET_SYST)/%.o:	%.cpp
	$(CXX)	-c $(CPPFLAGS) -o $@ $<

#-------------------------------------------
info:
	@echo "==================================================="
	@echo -n "PWD            =" ; pwd
	@echo "OTSYPE         =" $(OSTYPE)
	@echo "HOSTTYPE       =" $(HOSTTYPE)
	@echo "TARGET         =" $(TARGET)
	@echo "ROOT_PATH      =" $(ROOT_PATH)
	@echo "SYSTEM_PATH    =" $(SYSTEM_PATH)
	@echo "IPP_REPLACEMENT_OBJ    =" $(IPP_REPLACEMENT_OBJ)
	@echo "INTEL_IPP_LIBS =" $(INTEL_IPP_LIBS)
	@echo "TOOLS          =" $(TOOLS)
	@echo "INCFILES       =" $(INCFILES)
	@echo "CC             =" $(CC)
	@echo "CXX            =" $(CXX)
	@echo "CPPFLAGS       =" $(CPPFLAGS)
	@echo "LDOPT          =" $(LDOPT)
	@echo "LDFLAGS        =" $(LDFLAGS)
	@echo "TARGET_SYST    =" $(TARGET_SYST)
	@echo "GCCPATH        =" $(GCCPATH)
	@echo "CROSS_USER_LIB_PATH" = $(CROSS_USER_LIB_PATH)
	@echo "CROSS_USER_INC_PATH" = $(CROSS_USER_INC_PATH)
	@echo "USER_AR_LIB_LIST" = $(USER_AR_LIB_LIST)
	@echo "DISTCC         =" $(DISTCC)
	@echo "CCACHE         =" $(CCACHE)
	@echo "GCC_VERSION    =" $(GCC_VERSION)
	@echo "OPENMP         =" $(OPENMP)
	@echo "CCACHE_PREFIX  =" $(CCACHE_PREFIX)
	@echo "CC_TOOL_PATH   =" $(CC_TOOL_PATH)
	@echo "WX_CONF_PATH   =" $(WX_CONF_PATH)
	@echo "WX_CONF_TOOL   =" $(WX_CONF_TOOL)
	@echo "==================================================="

#-------------------------------------------------
#------------------------------ vim: filetype=make
