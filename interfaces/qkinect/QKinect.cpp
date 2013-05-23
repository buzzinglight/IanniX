/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2010 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

//----------------------------------------------------------------------------------------------------------------------
/// @file QKinect.cpp
/// @brief a Qt wrapper for the OpenKinect project a lot of the code has been modified from
/// this project source here https://github.com/OpenKinect/libfreenect
//----------------------------------------------------------------------------------------------------------------------

#include "QKinect.h"
#include <QDebug>
#include <cstdlib>
#include <cmath>
#include <cassert>

//----------------------------------------------------------------------------------------------------------------------
QKinect *QKinect::s_instance = 0;// initialize pointer
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
void QKinectProcessEvents::run()
{
    // loop while we are active and process the kinect event queue
    while(m_active)
    {
        if(freenect_process_events(m_ctx) < 0)
        {
            throw std::runtime_error("Cannot process freenect events");
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
/// @brief Destructor ---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
QKinect::~QKinect()
{
    // dtor is not called directly
    if (s_instance)
    {
        delete s_instance;
    }
}
//----------------------------------------------------------------------------------------------------------------------
/// @brief Get instance --------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
QKinect* QKinect::instance()
{
    // this is the main singleton code first check to see if we exist
    if (s_instance==0 )
    {
        // we do so create an instance (this will validate the pointer so other
        // methods called in the init function will have a valid pointer to use)
        s_instance = new QKinect;
        // now setup the actual class (with a valid pointer)
        /// \note this could be made nicer to make it fully thread safe
        s_instance->init();
    }
    // otherwise return the existing pointer
    return s_instance;
}


//----------------------------------------------------------------------------------------------------------------------
QKinect::QKinect() : QObject(0)
{
    // nothing to see here we just need a valid object pointer the init
    // method does all the hard work
    qDebug()<<"ctor called \n";
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::init()
{
    // first see if we can init the kinect
    if (freenect_init(&m_ctx, NULL) < 0)
    {
        qDebug()<<"freenect_init() failed\n";
        exit(EXIT_FAILURE);
    }
    /// set loggin level make this programmable at some stage
    freenect_set_log_level(m_ctx, FREENECT_LOG_DEBUG);
    /// see how many devices we have
    int nr_devices = freenect_num_devices (m_ctx);
    qDebug()<<"Number of devices found: "<<nr_devices<<"\n";
    /// now allocate the buffers so we can fill them
    m_userDeviceNumber = 0;
    m_bufferDepth.resize(FREENECT_VIDEO_RGB_SIZE);
    m_bufferVideo.resize(FREENECT_VIDEO_RGB_SIZE);
    m_bufferDepthRaw.resize(FREENECT_FRAME_PIX);
    m_bufferDepthRaw16.resize(FREENECT_FRAME_PIX);
    m_gamma.resize(2048);
    /// open the device at present hard coded to device 0 as I only
    /// have 1 kinect
    if (freenect_open_device(m_ctx, &m_dev, m_userDeviceNumber) < 0)
    {
        qDebug()<<"Could not open device\n";
        exit(EXIT_FAILURE);
    }


    /// build the gamma table used for the depth to rgb conversion
    /// taken from the demo programs
    for (int i=0; i<2048; ++i)
    {
        float v = i/2048.0;
        v = std::pow(v, 3)* 6;
        m_gamma[i] = v*6*256;
    }
    /// init our flags
    m_newRgbFrame=false;
    m_newDepthFrame=false;
    m_deviceActive=true;
    // set our video formats to RGB by default

#ifdef Q_OS_MAC
    freenect_set_video_mode(m_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
    freenect_set_depth_mode(m_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
#else
    freenect_set_video_format(m_dev, FREENECT_VIDEO_RGB);
    freenect_set_depth_format(m_dev, FREENECT_DEPTH_11BIT);
#endif

    /// hook in the callbacks
    freenect_set_depth_callback(m_dev, depthCallback);
    freenect_set_video_callback(m_dev, videoCallback);
    // start the video and depth sub systems
    startVideo();
    startDepth();
    // set the thread to be active and start
    m_process = new QKinectProcessEvents(m_ctx);
    m_process->setActive();
    m_process->start();
}

//----------------------------------------------------------------------------------------------------------------------
void QKinect::shutDownKinect()
{
    /// stop the processing thread
    m_process->setInActive();
    /// stop the video and depth callbacks
    freenect_stop_depth(m_dev);
    freenect_stop_video(m_dev);
    // close down our devices
    freenect_close_device(m_dev);
    freenect_shutdown(m_ctx);

}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setLedOff()
{
    freenect_set_led(m_dev,LED_OFF);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setRedLed()
{
    freenect_set_led(m_dev,LED_RED);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setGreenLed()
{
    freenect_set_led(m_dev,LED_GREEN);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setYellowLed()
{
    freenect_set_led(m_dev,LED_YELLOW);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setRedLedFlash()
{
    freenect_set_led(m_dev,LED_BLINK_RED_YELLOW);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setGreenLedFlash()
{
    freenect_set_led(m_dev,LED_BLINK_GREEN);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setYellowLedFlash()
{
    freenect_set_led(m_dev,LED_YELLOW);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::setVideoMode(
    int _mode
    )
{
    freenect_video_format vm=FREENECT_VIDEO_RGB;
    switch(_mode)
    {
    case 0 : { vm=FREENECT_VIDEO_RGB; break;}
    case 1 : { vm=FREENECT_VIDEO_YUV_RGB; break;}
    case 2 : { vm=FREENECT_VIDEO_IR_8BIT; break;}
        /*
  /// had issues with these modes so sticking to the 3 that work
   case 1 : { vm=FREENECT_VIDEO_BAYER; break;}
  case 2 : { vm=FREENECT_VIDEO_IR_8BIT; break;}
  case 3 : { vm=FREENECT_VIDEO_IR_10BIT; break;}
  case 4 : { vm=FREENECT_VIDEO_IR_10BIT_PACKED; break;}
  case 5 : { vm=FREENECT_VIDEO_YUV_RGB; break;}
  case 6 : { vm=FREENECT_VIDEO_YUV_RAW; break;}
   */
    default : qDebug()<<"index out of bounds for video mode\n";
        vm=FREENECT_VIDEO_RGB;
        break;
    }
    /// stop the video and set to new mode
    freenect_stop_video(m_dev);

#ifdef Q_OS_MAC
    freenect_set_video_mode(m_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, vm));
#else
    freenect_set_video_format(m_dev, vm);
#endif

    freenect_start_video(m_dev);
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::resetAngle()
{
    freenect_set_tilt_degs(m_dev,0);
}

//----------------------------------------------------------------------------------------------------------------------
void QKinect::setAngle(
    double _angle
    )
{
    // constrain the angle from -30 - +30
    if(_angle > 30)
    {
        _angle = 30;
    }
    else if(_angle <-30)
    {
        _angle=-30;
    }
    freenect_set_tilt_degs(m_dev,_angle);
}


//----------------------------------------------------------------------------------------------------------------------
bool QKinect::getRGB(
    std::vector<uint8_t> &o_buffer
    )
{
    /// this grabs the rgb data we first need to lock our mutex
    /// this will be unlocked on destruction of the locker
    QMutexLocker locker( &m_mutex );
    // do we have a new frame?
    if(m_newRgbFrame)
    {
        // if so swap out and fill
        o_buffer.swap(m_bufferVideo);
        m_newRgbFrame = false;
        return true;
    }
    else
    {
	return false;
    }
}


//----------------------------------------------------------------------------------------------------------------------
bool QKinect::getDepth(
    std::vector<uint8_t> &o_buffer
    )
{
    // this fills the depth buffer, first lock our mutex
    QMutexLocker locker( &m_mutex );
    if(m_newDepthFrame)
    {
        // swap data
        o_buffer.swap(m_bufferDepth);
        m_newDepthFrame = false;
        return true;
    }
    else
    {
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------
bool QKinect::getDepth16Bit(
    std::vector<uint16_t> &o_buffer
    )
{
    /// fill the 16 Bit data value first lock mutex
    QMutexLocker locker( &m_mutex );
    if(m_newDepthFrame)
    {
        // fill our buffer if avaliable
        o_buffer.swap( m_bufferDepthRaw16 );
        m_newDepthFrame = false;
        return true;
    }
    else
    {
        return false;
    }
}


//----------------------------------------------------------------------------------------------------------------------
bool QKinect::getDepthRaw(
    std::vector<uint8_t> &o_buffer
    )
{
    QMutexLocker locker( &m_mutex );
    if(m_newDepthFrame)
    {
        o_buffer.swap(m_bufferDepthRaw);
        m_newDepthFrame = false;
        return true;
    }
    else
    {
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::grabDepth(
    void *_depth,
    uint32_t
    )
{
    // this method fills all the different depth buffers at once
    // modifed from the sample code glview and cppview.cpp
    /// lock our mutex
    QMutexLocker locker( &m_mutex );
    // cast the void pointer to the unint16_t the data is actually in
    uint16_t* depth = static_cast<uint16_t*>(_depth);

    // now loop and fill data buffers
    for( unsigned int i = 0 ; i < FREENECT_FRAME_PIX ; ++i)
    {
	// first our two raw buffers the first will lose precision and may well
	// be removed in the next iterations
	m_bufferDepthRaw[i]=depth[i];
	m_bufferDepthRaw16[i]=depth[i];
	// now get the index into the gamma table
	int pval = m_gamma[depth[i]];
	// get the lower bit
	int lb = pval & 0xff;
	// shift right by 8 and determine which colour value to fill the
	// array with based on the position
	switch (pval>>8)
	{
	case 0:
            m_bufferDepth[3*i+0] = 255;
            m_bufferDepth[3*i+1] = 255-lb;
            m_bufferDepth[3*i+2] = 255-lb;
            break;
	case 1:
            m_bufferDepth[3*i+0] = 255;
            m_bufferDepth[3*i+1] = lb;
            m_bufferDepth[3*i+2] = 0;
            break;
	case 2:
            m_bufferDepth[3*i+0] = 255-lb;
            m_bufferDepth[3*i+1] = 255;
            m_bufferDepth[3*i+2] = 0;
            break;
	case 3:
            m_bufferDepth[3*i+0] = 0;
            m_bufferDepth[3*i+1] = 255;
            m_bufferDepth[3*i+2] = lb;
            break;
	case 4:
            m_bufferDepth[3*i+0] = 0;
            m_bufferDepth[3*i+1] = 255-lb;
            m_bufferDepth[3*i+2] = 255;
            break;
	case 5:
            m_bufferDepth[3*i+0] = 0;
            m_bufferDepth[3*i+1] = 0;
            m_bufferDepth[3*i+2] = 255-lb;
            break;
	default:
            m_bufferDepth[3*i+0] = 0;
            m_bufferDepth[3*i+1] = 0;
            m_bufferDepth[3*i+2] = 0;
            break;
	}
    }
    // flag we have a new frame
    m_newDepthFrame = true;
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::grabVideo(
    void *_video,
    uint32_t
    )
{
    // lock our mutex and copy the data from the video buffer
    QMutexLocker locker( &m_mutex );
    uint8_t* rgb = static_cast<uint8_t*>(_video);
    std::copy(rgb, rgb+FREENECT_VIDEO_RGB_SIZE, m_bufferVideo.begin());
    m_newRgbFrame = true;
}

//----------------------------------------------------------------------------------------------------------------------
void QKinect::startVideo()
{
    if(freenect_start_video(m_dev) < 0)
    {
        throw std::runtime_error("Cannot start RGB callback");
    }
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::stopVideo()
{
    if(freenect_stop_video(m_dev) < 0)
    {
        throw std::runtime_error("Cannot stop RGB callback");
    }
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::startDepth()
{
    if(freenect_start_depth(m_dev) < 0)
    {
        throw std::runtime_error("Cannot start depth callback");
    }
}

//----------------------------------------------------------------------------------------------------------------------
void QKinect::stopDepth()
{
    if(freenect_stop_depth(m_dev) < 0)
    {
        throw std::runtime_error("Cannot stop depth callback");
    }
}

//----------------------------------------------------------------------------------------------------------------------
void QKinect::toggleVideoState(bool _mode)
{
    if(_mode ==true)
    {
        startVideo();
    }
    else
    {
        stopVideo();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void QKinect::toggleDepthState(bool _mode)
{
    if(_mode == true)
    {
        startDepth();
    }
    else
    {
        stopDepth();
    }
}
//----------------------------------------------------------------------------------------------------------------------
