UNAME_M := $(shell uname -m)

ifeq ($(UNAME_M),x86_64)
	MVIMPACT_PATH := ../mvIMPACT_acquire-x86_64-2.5.10
	INCS := -I$(MVIMPACT_PATH)
	LIBS := -L$(MVIMPACT_PATH)/lib/x86_64 -lmvDeviceManager -lmvPropHandling -lm -pthread -ljpeg -lzmq
	CXX_FLAGS := -O3 -Wall
	LD_FLAGS := -Wl,-rpath=$(MVIMPACT_PATH)/lib/x86_64
else ifeq ($(UNAME_M),armv7l)
	#MVIMPACT_PATH := ../mvIMPACT_acquire-arm-1.12.56
	MVIMPACT_PATH := ../mvIMPACT_acquire-arm-2.5.4
        ARM_PATH := ..
	INCS := -I$(MVIMPACT_PATH) -I$(ARM_PATH)/armel/include
	LIBS := -L$(MVIMPACT_PATH)/lib/arm -lmvDeviceManager -lmvPropHandling -lm -pthread -L$(ARM_PATH)/armel/lib -ljpeg -lzmq
	CXX_FLAGS := -O3 -Wall -mfloat-abi=softfp
	LD_FLAGS := -Wl,-rpath=$(MVIMPACT_PATH)/lib/arm -Wl,-rpath=$(ARM_PATH)/armel/lib
else
	$(error Architecture not supported)
endif

all: sendData

sendData: sendData.o jpeg_compress.o
	$(CXX) $(CXX_FLAGS) $(INCS) $^ $(LIBS) $(LD_FLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCS) -c $^

%.o: %.cc
	$(CXX) $(CXX_FLAGS) $(INCS) -c $^

clean:
	rm -f *.o sendData
