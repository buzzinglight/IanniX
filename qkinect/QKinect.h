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
/// @file QKinect.h
/// @brief a Qt wrapper for the OpenKinect project a lot of the code has been modified from
/// this project source here https://github.com/OpenKinect/libfreenect
//----------------------------------------------------------------------------------------------------------------------

#ifndef __QKINECT_H__
#define __QKINECT_H__
#include <QObject>
#include <QThread>
#include <stdexcept>
#include <QMutex>
#include <QMutexLocker>
#include <vector>
#include <libfreenect.h>

#define   FREENECT_FRAME_W   640
#define   FREENECT_FRAME_H   480
#define   FREENECT_FRAME_PIX      (FREENECT_FRAME_H*FREENECT_FRAME_W) //width*height pixels in the image
#define   FREENECT_VIDEO_RGB_SIZE (FREENECT_FRAME_PIX*3) //3 bytes per pixel

//----------------------------------------------------------------------------------------------------------------------
/// @class QKinectProcessEvents "QKinect.h"
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/12/10 Inital commit
/// @brief this is the process event thread class
/// it needs to be a class so we can use the Qt thread system
//----------------------------------------------------------------------------------------------------------------------

class QKinectProcessEvents : public QThread
{
public :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief ctor where we pass in the context of the kinect
	/// @param [in] _ctx the context of the current kinect device
	//----------------------------------------------------------------------------------------------------------------------
	inline QKinectProcessEvents(
															freenect_context *_ctx
														 )
															{m_ctx=_ctx;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief sets the thread active this will loop the run thread
	/// with a while(m_active) setting this will end the thread loop
	//----------------------------------------------------------------------------------------------------------------------
	inline void setActive(){m_active=true;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief sets the thread active must call QThread::start again to make this
	/// work if the thread has been de-activated
	//----------------------------------------------------------------------------------------------------------------------
	inline void setInActive(){m_active=false;}
protected :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the actual thread main loop, this is not callable and the
	/// QThread::start method of QThread must be called to activate the loop
	//----------------------------------------------------------------------------------------------------------------------
	void run();

private :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief a flag to indicate if the loop is to be active
	/// set true in the ctor
	//----------------------------------------------------------------------------------------------------------------------
	bool m_active;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the context of the kinect device, this must
	/// be set before the thread is run with QThread::start
	//----------------------------------------------------------------------------------------------------------------------
	freenect_context *m_ctx;

};

//----------------------------------------------------------------------------------------------------------------------
/// @class QKinect "QKinect.h"
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/12/10 Inital commit
/// @brief this class wraps the libfreenect library as a QObject
/// this allows us to use singals and slots to communicate with the class
/// from other Qt GUI elements. This class uses the Singleton pattern so must
/// be accessed via the instance method
//----------------------------------------------------------------------------------------------------------------------

class QKinect : public QObject
{
// must include this macro so we inherit all the core QT features such as singnals and slots
Q_OBJECT
public :

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief get the instance of the QKinect object this will call the
	/// init method of the class if the instance doesn't exist. This is because
	/// this class will construct some threads so we need to create an instance
	/// first then pass that to the other classes in the thread
	/// @returns an instance of the QKinect object
	//----------------------------------------------------------------------------------------------------------------------
	static QKinect *instance();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief we can set the user device number here by default it will be 1
	/// @param[in] _m the number we wish to set
	//----------------------------------------------------------------------------------------------------------------------
	inline void setUserDeviceNumber(
																	int _m
																 )
																	{m_userDeviceNumber=_m;}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief method to shutdown our device and close
	//----------------------------------------------------------------------------------------------------------------------
	void shutDownKinect();

public slots :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to change the angle of the Kinect
	/// @param[in] _angle the angle to set will be constrained to -/+ 30.0
	//----------------------------------------------------------------------------------------------------------------------
	void setAngle(
								double _angle
							 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to turn off the led
	//----------------------------------------------------------------------------------------------------------------------
	void setLedOff();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to enable the red LED
	//----------------------------------------------------------------------------------------------------------------------
	void setRedLed();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to enable the green LED
	//----------------------------------------------------------------------------------------------------------------------
	void setGreenLed();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to enable the yellow LED
	//----------------------------------------------------------------------------------------------------------------------
	void setYellowLed();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to flash the red led
	//----------------------------------------------------------------------------------------------------------------------
	void setRedLedFlash();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to flash the green led
	//----------------------------------------------------------------------------------------------------------------------
	void setGreenLedFlash();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to flash the yellow led
	//----------------------------------------------------------------------------------------------------------------------
	void setYellowLedFlash();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief slot to set the video mode
	/// @brief param _mode the video mode as an int index
	/// FREENECT_VIDEO_RGB = 0,
	/// FREENECT_VIDEO_YUV_RGB = 1,
	/// FREENECT_VIDEO_IR_8BIT = 2,

	//----------------------------------------------------------------------------------------------------------------------
	void setVideoMode(
										int _mode
									 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief reset the tilt angle
	//----------------------------------------------------------------------------------------------------------------------
	void resetAngle();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief getDepth buffer and convert it to an RGB colour representation
	/// this code is based on the sample implementation glview.c / cppview.cpp
	/// @param[out] o_buffer the buffer to fill
	//----------------------------------------------------------------------------------------------------------------------
	bool getDepth(
								std::vector<uint8_t> &o_buffer
							 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief getDepth buffer as the raw values converted to uint8_t not sure if this will
	/// be much use but have used it in some tracking examples
	/// @param[out] o_buffer the buffer to fill
	//----------------------------------------------------------------------------------------------------------------------
	bool getDepthRaw(
									 std::vector<uint8_t> &o_buffer
									);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief getDepth buffer as the raw 16 Bit values
	/// this is useful for generating point cloud renders as we have the full depth range
	/// @param[out] o_buffer the buffer to fill
	//----------------------------------------------------------------------------------------------------------------------
	bool getDepth16Bit(
										 std::vector<uint16_t> &o_buffer
										);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief get the RGB buffer
	/// @param [out] o_buffer the rgb values
	//----------------------------------------------------------------------------------------------------------------------
	bool getRGB(
							std::vector<uint8_t> &o_buffer
						 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief start the Depth buffer grabbing subsystem
	//----------------------------------------------------------------------------------------------------------------------
	void startDepth();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief stop the Depth buffer grabbing subsystem
	//----------------------------------------------------------------------------------------------------------------------
	void stopDepth();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief start the Video buffer grabbing subsystem
	//----------------------------------------------------------------------------------------------------------------------
	void startVideo();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief stop the Depth buffer grabbing subsystem
	//----------------------------------------------------------------------------------------------------------------------
	void stopVideo();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief convenience method to toggle the video mode  with a bool to indicate
	/// mode, useful for connecting to buttons
	//----------------------------------------------------------------------------------------------------------------------
	void toggleVideoState(
												bool _mode
											 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief convenience method to toggle the depth mode  with a bool to indicate
	/// mode, useful for connecting to buttons
	//----------------------------------------------------------------------------------------------------------------------
	void toggleDepthState(
												bool _mode
											 );
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief return a pointer to the active device context
	/// @returns the current active contects
	//----------------------------------------------------------------------------------------------------------------------
	inline freenect_context *getContext(){return m_ctx;}

private :
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief private ctor as we are a singleton class
	//----------------------------------------------------------------------------------------------------------------------
  QKinect();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief private dtor as we are a singleton class
	//----------------------------------------------------------------------------------------------------------------------
	~QKinect();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief private copy ctor as we are a singleton class
	//----------------------------------------------------------------------------------------------------------------------
	Q_DISABLE_COPY(QKinect)
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief private init method, this makes the instance method thread safe
	/// as all the initialisations will be done here
	//----------------------------------------------------------------------------------------------------------------------
	void init();
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our instance of the Kinect device
	//----------------------------------------------------------------------------------------------------------------------
	static QKinect *s_instance;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the contex for the device
	//----------------------------------------------------------------------------------------------------------------------
	freenect_context *m_ctx;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our device pointer
	//----------------------------------------------------------------------------------------------------------------------
	freenect_device *m_dev;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief user device number
	//----------------------------------------------------------------------------------------------------------------------
	int m_userDeviceNumber;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief function for depth callback this hooks into the libfreenect callback system
	/// @param[in] _dev the device we are querying
	/// @param[out] the actual depth data returned from the device
	/// @param _timestamp the time stamp for the grab (not used at present)
	//----------------------------------------------------------------------------------------------------------------------
	void depthFunc(
								  freenect_device *_dev,
									void *o_depth,
									uint32_t _timestamp
								);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief function for Video callback this hooks into the libfreenect callback system
	/// @param[in] _dev the device we are querying
	/// @param[out] o_rgb the actual video data returned from the device
	/// @param _timestamp the time stamp for the grab (not used at present)
	//----------------------------------------------------------------------------------------------------------------------
	void rgbFunc(
								freenect_device *_dev,
								void *o_rgb,
								uint32_t _timestamp
							);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our depth buffer for the current depth frames will be filled
	/// from the depth callback, this data is converted into an RGB representation
	/// with Red being closest and blue far away, this is done via a gamma table
	/// and converting the depth from 16 bit to 8 bit RGB useful for OpenCV like
	/// motion tracking
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<uint8_t> m_bufferDepth;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our video buffer for the current rgb video frames will be filled
	/// from the rgb callback
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<uint8_t> m_bufferVideo;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our depth buffer for the current depth frames will be filled
	/// from the depth callback this is the unaltered data converted to 8 bit
	/// not really useful so may get rid of at a later date just legacy from
	/// testing the other examples
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<uint8_t> m_bufferDepthRaw;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the 16Bit raw depth values, this is good for voxel rendering of the
	/// data
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<uint16_t> m_bufferDepthRaw16;

	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our gamma table this is filled in the ctor and used in the depth
	/// callbacks, this is taken from the sample code glview.c cppview.cpp
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<uint16_t> m_gamma;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if there is a new rgb frame
	//----------------------------------------------------------------------------------------------------------------------
	bool m_newRgbFrame;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if there is a new depth frame
	//----------------------------------------------------------------------------------------------------------------------
	bool m_newDepthFrame;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if we need to stop the device
	//----------------------------------------------------------------------------------------------------------------------
	bool m_stopDevice;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if the device is active
	//----------------------------------------------------------------------------------------------------------------------
	bool m_deviceActive;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief pointer to our thread process used to process the events
	//----------------------------------------------------------------------------------------------------------------------
	QKinectProcessEvents *m_process;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief our mutex used for the threaded processes, for ease we use a
	/// QMutexLocker to automagically control our mutex state
	//----------------------------------------------------------------------------------------------------------------------
	QMutex m_mutex;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief method to grab the depth passed to the depthCallback function
	/// as we are hooking into a C lib we need to do it this way as the callback
	/// functions must be static (see below)
	/// @param[out] _depth the depth data
	/// @param[in] _timestamp the timestamp of the operation (not used)
	//----------------------------------------------------------------------------------------------------------------------
	void grabDepth(
									void *_depth,
									uint32_t timestamp
								);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief method to grab the Video passed to the depthCallback function
	/// as we are hooking into a C lib we need to do it this way as the callback
	/// functions must be static (see below)
	/// @param[out] _video the depth data
	/// @param[in] _timestamp the timestamp of the operation (not used)
	//----------------------------------------------------------------------------------------------------------------------
	void grabVideo(
								  void *_video,
									uint32_t timestamp
								);
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief this hooks into the feenet callback system an is the main way of
	/// getting the data from the kinect this is not called directly
	/// @param[in] _dev this is not used as we use the class m_dev
	/// @param[out] _video the depth data
	/// @param[in] _timestamp the timestamp of the operation (not used)
	//----------------------------------------------------------------------------------------------------------------------
	static inline void depthCallback(
																	 freenect_device *_dev,
																	 void *_depth,
																	 uint32_t _timestamp=0
																	)
	{
		/// get an instance of our device
		QKinect *kinect=QKinect::instance();
		/// then call the grab method to fill the depth buffer and return it
		kinect->grabDepth(_depth,_timestamp);
	}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief this hooks into the feenet callback system an is the main way of
	/// getting the data from the kinect this is not called directly
	/// @param[in] _dev this is not used as we use the class m_dev
	/// @param[out] _video the depth data
	/// @param[in] _timestamp the timestamp of the operation (not used)
	//----------------------------------------------------------------------------------------------------------------------

	static inline void videoCallback(
																	 freenect_device *_dev,
																	 void *_video,
																	 uint32_t _timestamp=0
																	)
	{
		/// get an instance of our device
		QKinect *kinect=QKinect::instance();
		/// then fill the video buffer
		kinect->grabVideo(_video, _timestamp);
	}

};



#endif
