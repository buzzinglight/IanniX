/*
	QTFFmpegWrapper - QT FFmpeg Wrapper Class
	Copyright (C) 2009,2010:
			Daniel Roggen, droggen@gmail.com

	All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __QVIDEODECODER_H
#define __QVIDEODECODER_H


#include <QIODevice>
#include <QFile>
#include <QImage>

#include "ffmpeg.h"

class QVideoDecoder
{
   protected:
      // Basic FFmpeg stuff
      ffmpeg::AVFormatContext *pFormatCtx;
      int videoStream;
      ffmpeg::AVCodecContext  *pCodecCtx;
      ffmpeg::AVCodec         *pCodec;
      ffmpeg::AVFrame         *pFrame;
      ffmpeg::AVFrame         *pFrameRGB;
      ffmpeg::AVPacket        packet;
      ffmpeg::SwsContext      *img_convert_ctx;
      uint8_t                 *buffer;
      int                     numBytes;

      // State infos for the wrapper
      bool ok;
      QImage LastFrame;
      int LastFrameTime,LastLastFrameTime,LastLastFrameNumber,LastFrameNumber;
      int DesiredFrameTime,DesiredFrameNumber;
      bool LastFrameOk;                // Set upon start or after a seek we don't have a frame yet

      // Initialization functions
      virtual bool initCodec();
      virtual void InitVars();

      // Helpers
      virtual void dumpFormat(ffmpeg::AVFormatContext *ic,int index,const char *url,int is_output);
      virtual void saveFramePPM(ffmpeg::AVFrame *pFrame, int width, int height, int iFrame);

      // Seek
      virtual bool decodeSeekFrame(int after);

   public:
      // Public interface
      QVideoDecoder();
      QVideoDecoder(QString file);
      virtual ~QVideoDecoder();

      virtual bool openFile(QString file);
      virtual void close();

      virtual bool getFrame(QImage&img,int *effectiveframenumber=0,int *effectiveframetime=0,int *desiredframenumber=0,int *desiredframetime=0);
      virtual bool seekNextFrame();
      virtual bool seekMs(int ts);
      virtual bool seekFrame(int64_t frame);
      virtual int getVideoLengthMs();


      virtual bool isOk();
};

#endif // __QVIDEODECODER_H
