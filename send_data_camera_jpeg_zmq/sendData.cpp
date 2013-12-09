// ContinuousCaptureAllDevicesLIN.cpp
// Capture continuously from all found MATRIX VISION devices
//
// *** LINUX VERSION ***
//
// No display. Uses Linux threads.
//
#ifndef linux
#error This file is only for Linux
#endif

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <list>

#include <assert.h>
#include <zmq.h>

// Camera
#include "mvIMPACT_CPP/mvIMPACT_acquire.h"

using namespace std;
using namespace mvIMPACT::acquire;

#define PRESS_A_KEY getchar()

//#define ZMQ_TRANSPORT "tcp://192.168.1.100:12345"
#define ZMQ_TRANSPORT "tcp://127.0.0.1:12345"
static void *zmq_context;
static void *publisher;

//-----------------------------------------------------------------------------
class ThreadParameter
//-----------------------------------------------------------------------------
{
  Device*      m_pDev;
  volatile bool  m_boTerminateThread;
 public:
  ThreadParameter( Device* pDev ) : m_pDev(pDev), m_boTerminateThread(false) {}
  Device*  device( void ) const { return m_pDev; }
  bool  terminated( void ) const { return m_boTerminateThread; }
  void  terminateThread( void ) { m_boTerminateThread = true; }
};

//-----------------------------------------------------------------------------
static unsigned int thread_func( void* pData )
  //-----------------------------------------------------------------------------
{
  ThreadParameter* pThreadParameter = reinterpret_cast<ThreadParameter*>(pData);

  try
  {
    pThreadParameter->device()->open();
  }
  catch( const ImpactAcquireException& e )
  {
    // this e.g. might happen if the same device is already opened in another process...
    cout << "An error occurred while opening the device " << pThreadParameter->device()->serial.read()
        << "(error code: " << e.getErrorCode() << "(" << e.getErrorCodeAsString() << ")). Terminating thread." << endl
        << "Press [ENTER] to end the application..."
        << endl;
    PRESS_A_KEY;
    return 0;
  }
  // establish access to the statistic properties
  Statistics statistics( pThreadParameter->device() );
  // create an interface to the device found
  FunctionInterface fi( pThreadParameter->device() );

  // Set Properties ----------------------------------------------------------------
  mvIMPACT::acquire::SettingsBlueFOX settings(pThreadParameter->device());

  settings.cameraSetting.restoreDefault();
  // Binning
  //settings.cameraSetting.binningMode.write(cbmBinningHV);
  settings.cameraSetting.binningMode.write(cbmOff);

  // Gain
  settings.cameraSetting.autoGainControl.write(agcOff);
  settings.cameraSetting.gain_dB.write(0.0);
  //settings.cameraSetting.autoGainControl.write(agcOn);

  // Exposure
  settings.cameraSetting.autoExposeControl.write(aecOff);
  settings.cameraSetting.expose_us.write(20000);
  //settings.cameraSetting.autoExposeControl.write(aecOn);

  //settings.cameraSetting.pixelFormat.write(ibpfMono8);

  // HDR
  //settings.cameraSetting.getHDRControl().HDRMode.write(cHDRmFixed0);
  //settings.cameraSetting.getHDRControl().HDREnable.write(bTrue);

  // Color
  //settings.imageDestination.pixelFormat.write(idpfRaw);
  //settings.imageDestination.pixelFormat.write(idpfMono8);
  settings.imageDestination.pixelFormat.write(idpfRGB888Packed);

  // Set request queue length, prefer 1 to avoid delay
  SystemSettings ss(pThreadParameter->device());
  ss.requestCount.write(1);
  // Set Properties ----------------------------------------------------------------

  // run thread loop
  const Request* pRequest = 0;
  const unsigned int timeout_ms = 200;   // USB 1.1 on an embedded system needs a large timeout for the first image
  int requestNr = INVALID_ID;
  unsigned int cnt = 0;
  // Request image
  //fi.imageRequestSingle();

  // Prefill buffers. Note: This introduces delay since the buffer contains a slightly older image while the current
  // image is being captured
  int requestCount = 0;

  while(fi.imageRequestSingle() == DMR_NO_ERROR)
  {
    ++requestCount;
  }
  cout << requestCount << " buffers requested" << std::endl;

  while(!pThreadParameter->terminated())
  {
    // wait for results from the default capture queue
	requestNr = fi.imageRequestWaitFor( timeout_ms );  
if( fi.isRequestNrValid( requestNr ) )
    {
      pRequest = fi.getRequest(requestNr);
      if( fi.isRequestOK(pRequest) )
      {
        const int width  = pRequest->imageWidth.read();
        const int height = pRequest->imageHeight.read();
        const int bits_per_channel = pRequest->imageChannelBitDepth.read();
        const int channels = pRequest->imageChannelCount.read();
        const uint8_t *im = (const uint8_t *)pRequest->imageData.read();
        //std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << ", Bits per channel: " << bits_per_channel << std::endl;

        ++cnt;
        // here we can display some statistical information every 100th image
        if(cnt%100 == 0)
        {
          cout << cnt << ": Info from " << pThreadParameter->device()->serial.read()
              << ": " << statistics.framesPerSecond.name() << ": " << statistics.framesPerSecond.readS()
              << ", " << statistics.errorCount.name() << ": " << statistics.errorCount.readS()
              << ", " << statistics.captureTime_s.name() << ": " << statistics.captureTime_s.readS() << " Image count: " << cnt
              << " (dimensions: " << pRequest->imageWidth.read() << "x" << pRequest->imageHeight.read() << ", format: " << pRequest->imagePixelFormat.readS();
          if(pRequest->imageBayerMosaicParity.read() != bmpUndefined)
          {
            cout << ", " << pRequest->imageBayerMosaicParity.name() << ": " << pRequest->imageBayerMosaicParity.readS();
          }
          cout << "), line pitch: " << pRequest->imageLinePitch.read() << endl;
        }

        zmq_send(publisher, im, width*height*channels, 0);
      }
      else
      {
        cout << "Error: " << pRequest->requestResult.readS() << endl;
      }

      // Unlock request handler
      fi.imageRequestUnlock(requestNr);
      // send a new image request into the capture queue
      fi.imageRequestSingle();
      //usleep(1000);
    }
    else
    {
      fi.imageRequestUnlock(requestNr);
      // If the error code is -2119(DEV_WAIT_FOR_REQUEST_FAILED), the documentation will provide
      // additional information under TDMR_ERROR in the interface reference (
      cout << "imageRequestWaitFor failed (" << requestNr << ", " <<
          ImpactAcquireException::getErrorCodeAsString( requestNr ) << ", device "
          << pThreadParameter->device()->serial.read() << ")"
          << ", timeout value too small?" << endl;
    }
  }

  // free the last potential locked request
  if( fi.isRequestNrValid( requestNr ) )
  {
    fi.imageRequestUnlock( requestNr );
  }
  // clear the request queue
  fi.imageRequestReset( 0, 0 );

  return 0;
}

//-----------------------------------------------------------------------------
static void* liveThread( void* pData )
  //-----------------------------------------------------------------------------
{
  thread_func( pData );
  return NULL;
}

//-----------------------------------------------------------------------------
//int main(int /*argc*/, char* /*argv*/[])
  //-----------------------------------------------------------------------------
/*{
  zmq_context = zmq_ctx_new();
  publisher = zmq_socket(zmq_context, ZMQ_PUB);
  const int queue_size = 1;
  int rc = zmq_setsockopt(publisher, ZMQ_SNDHWM, &queue_size, sizeof(queue_size));
  assert(rc == 0);

  rc = zmq_bind(publisher, ZMQ_TRANSPORT);
  assert(rc == 0);

  // Camera
  DeviceManager devMgr;
  const unsigned int devCnt = devMgr.deviceCount();
  if( devCnt == 0 )
  {
    cout << "No MATRIX VISION device found! Unable to continue!" << endl;
    return 0;
  }
  pthread_t* pHandles = new pthread_t[devCnt];
  pthread_attr_t* pAttrs = new pthread_attr_t[devCnt];
  // store all device infos in a vector
  // and start the execution of a 'live' thread for each device.
  vector<ThreadParameter*> threadParams;
  for( unsigned int i=0; i<devCnt; i++ )
  {
    threadParams.push_back( new ThreadParameter(devMgr[i]) );
    cout << devMgr[i]->family.read() << "(" << devMgr[i]->serial.read() << ")" << endl;
  }
  // start live threads
  for( unsigned int j=0; j<devCnt; j++ )
  {
    pthread_attr_init( &pAttrs[j] );
    // you can set the stack size like this: pthread_attr_setstacksize (&pAttrs[j], 1024*1024);
    pthread_create( &pHandles[j], &pAttrs[j], liveThread, (void *)threadParams[j] );
  }
  // now all threads will start running...
  cout << "Press return to end the acquisition( the initialisation of the devices might take some time )" << endl;

  PRESS_A_KEY;

  // stop all threads again
  cout << "Terminating live threads..." << endl;
  size_t vSize = threadParams.size();
  for( unsigned int k=0; k<vSize; k++ )
  {
    cout << "Terminating thread " << k << "." << endl;
    threadParams[k]->terminateThread();
  }

  // wait until each live thread has terminated.
  for( unsigned int j=0; j<devCnt; j++ )
  {
    cout << "Waiting for thread " << j << " to terminate." << endl;
    pthread_join (pHandles[j], NULL);
  }
  cout << "All capture threads terminated." << endl;

  // free resources
  for( unsigned int l=0; l<vSize; l++ )
  {
    delete threadParams[l];
    cout << "thread parameter " << l << " removed." << endl;
  }
  delete [] pHandles;
  cout << "All thread handles removed." << endl;

  delete [] pAttrs;
  cout << "All thread atributes removed." << endl;
  return 0;
}*/

int main(int argc, char* argv[])
{
  zmq_context = zmq_ctx_new();
  publisher = zmq_socket(zmq_context, ZMQ_PUB);
  const int queue_size = 1;
  int rc = zmq_setsockopt(publisher, ZMQ_SNDHWM, &queue_size, sizeof(queue_size));
  assert(rc == 0);

  rc = zmq_bind(publisher, ZMQ_TRANSPORT);
  assert(rc == 0);

  // Camera
  DeviceManager dev_mgr;
  const unsigned int dev_cnt = dev_mgr.deviceCount();
  if(dev_cnt == 0)
  {
    cout << "No MATRIX VISION device found! Unable to continue!" << endl;
    return 0;
  }
  else if(dev_cnt > 1)
  {
    cout << dev_cnt << " devices found, using only the first one" << endl;
  }

  pthread_t thread_handle;
  ThreadParameter thread_params(dev_mgr[0]);
  cout << dev_mgr[0]->family.read() << "(" << dev_mgr[0]->serial.read() << ")" << endl;

  // start live thread
  pthread_create(&thread_handle, NULL, liveThread, (void *)&thread_params);

  // now the thread will start running...
  cout << "Press return to end the acquisition( the initialisation of the device might take some time )" << endl;

  PRESS_A_KEY;

  // stop the threads
  cout << "Terminating live thread..." << endl;
  thread_params.terminateThread();

  // wait until the live thread has terminated.
  cout << "Waiting for thread to terminate." << endl;
  pthread_join(thread_handle, NULL);
  cout << "Capture thread terminated." << endl;

  return 0;
}