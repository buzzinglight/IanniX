/*
   QTFFmpegWrapper - QT FFmpeg Wrapper Class
   Copyright (C) 2009-2012:
         Daniel Roggen, droggen@gmail.com

   All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __QVideoEncoder_H
#define __QVideoEncoder_H


#include <QIODevice>
#include <QFile>
#include <QImage>

#include "ffmpeg.h"

class QVideoEncoder
{
   protected:
      unsigned Width,Height;
      unsigned Bitrate;
      unsigned Gop;
      bool ok;

      // FFmpeg stuff
      ffmpeg::AVFormatContext *pFormatCtx;
      ffmpeg::AVOutputFormat *pOutputFormat;
      ffmpeg::AVCodecContext *pCodecCtx;
      ffmpeg::AVStream *pVideoStream;
      ffmpeg::AVCodec *pCodec;
      // Frame data
      ffmpeg::AVFrame *ppicture;
      uint8_t *picture_buf;
      // Compressed data
      int outbuf_size;
      uint8_t* outbuf;
      // Conversion
      ffmpeg::SwsContext *img_convert_ctx;
      // Packet
      ffmpeg::AVPacket pkt;

      QString fileName;

      unsigned getWidth();
      unsigned getHeight();
      bool isSizeValid();

      void initVars();
      bool initCodec();

      // Alloc/free the output buffer
      bool initOutputBuf();
      void freeOutputBuf();

      // Alloc/free a frame
      bool initFrame();
      void freeFrame();

      // Frame conversion
      bool convertImage(const QImage &img);
      bool convertImage_sws(const QImage &img);

      virtual int encodeImage_p(const QImage &,bool custompts=false,unsigned pts=0);


   public:
      QVideoEncoder();
      virtual ~QVideoEncoder();

      bool createFile(QString filename,unsigned width,unsigned height,unsigned bitrate,unsigned gop,unsigned fps=25);
      virtual bool close();

      virtual int encodeImage(const QImage &);
      virtual int encodeImagePts(const QImage &,unsigned pts);
      virtual bool isOk();

};




#endif // QVideoEncoder_H
