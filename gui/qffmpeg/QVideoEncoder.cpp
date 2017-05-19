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

#include <QPainter>
#include "QVideoEncoder.h"
#include "ffmpeg.h"



/******************************************************************************
*******************************************************************************
* QVideoEncoder   QVideoEncoder   QVideoEncoder   QVideoEncoder   QVideoEncoder
*******************************************************************************
******************************************************************************/


/******************************************************************************
* PUBLIC   PUBLIC   PUBLIC   PUBLIC   PUBLIC   PUBLIC   PUBLIC   PUBLIC   PUBLIC
******************************************************************************/

/**
  gop: maximal interval in frames between keyframes
**/
QVideoEncoder::QVideoEncoder()
{
   initVars();
   initCodec();
}

QVideoEncoder::~QVideoEncoder()
{
   close();
   /*if(Initmodefile)
   {
      writeFooter();
      Outdev->close();
      delete Outdev;
      Outdev=0;
   }
   else
   {
      // nothing to do
   }*/
}

bool QVideoEncoder::createFile(QString fileName,unsigned width,unsigned height,unsigned bitrate,unsigned gop,unsigned fps)
{
   // If we had an open video, close it.
   close();

   Width=width;
   Height=height;
   Gop=gop;
   Bitrate=bitrate;

   if(!isSizeValid())
   {
      qDebug("Invalid size\n");
      return false;
   }

   pOutputFormat = ffmpeg::av_guess_format(NULL, fileName.toStdString().c_str(), NULL);
   if (!pOutputFormat) {
      qDebug("Could not deduce output format from file extension: using MPEG.\n");
      pOutputFormat = ffmpeg::av_guess_format("mpeg", NULL, NULL);
   }

   pFormatCtx=ffmpeg::avformat_alloc_context();
   if(!pFormatCtx)
   {
      qDebug("Error allocating format context\n");
      return false;
   }
   pFormatCtx->oformat = pOutputFormat;
   snprintf(pFormatCtx->filename, sizeof(pFormatCtx->filename), "%s", fileName.toStdString().c_str());


   // Add the video stream

   pVideoStream = av_new_stream(pFormatCtx,0);
   if(!pVideoStream )
   {
      qDebug("Could not allocate stream\n");
      return false;
   }


   pCodecCtx=pVideoStream->codec;
   pCodecCtx->codec_id = pOutputFormat->video_codec;
   pCodecCtx->codec_type = ffmpeg::AVMEDIA_TYPE_VIDEO;

   pCodecCtx->bit_rate = Bitrate;
   pCodecCtx->width = getWidth();
   pCodecCtx->height = getHeight();
   pCodecCtx->time_base.den = fps;
   pCodecCtx->time_base.num = 1;
   pCodecCtx->gop_size = Gop;
   pCodecCtx->pix_fmt = ffmpeg::PIX_FMT_YUV420P;


   avcodec_thread_init(pCodecCtx, 10);

   //if (c->codec_id == CODEC_ID_MPEG2VIDEO)
   //{
      //c->max_b_frames = 2;  // just for testing, we also add B frames
   //}

   // some formats want stream headers to be separate
   if(pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
      pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;


   if (av_set_parameters(pFormatCtx, NULL) < 0)
   {
      qDebug("Invalid output format parameters\n");
      return false;
   }

   ffmpeg::dump_format(pFormatCtx, 0, fileName.toStdString().c_str(), 1);

   // open_video
   // find the video encoder
   pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
   if (!pCodec)
   {
      qDebug("codec not found\n");
      return false;
   }
   // open the codec
   if (avcodec_open(pCodecCtx, pCodec) < 0)
   {
      qDebug("could not open codec\n");
      return false;
   }

   // Allocate memory for output
   if(!initOutputBuf())
   {
      qDebug("Can't allocate memory for output bitstream\n");
      return false;
   }

   // Allocate the YUV frame
   if(!initFrame())
   {
      qDebug("Can't init frame\n");
      return false;
   }

   if (url_fopen(&pFormatCtx->pb, fileName.toStdString().c_str(), URL_WRONLY) < 0)
   {
      qDebug( "Could not open '%s'\n", fileName.toStdString().c_str());
      return false;
   }

   av_write_header(pFormatCtx);



   ok=true;

   return true;
}

/**
   \brief Completes writing the stream, closes it, release resources.
**/
bool QVideoEncoder::close()
{
   if(!isOk())
      return false;

   av_write_trailer(pFormatCtx);

   // close_video

   avcodec_close(pVideoStream->codec);
   freeFrame();
   freeOutputBuf();


   /* free the streams */

   for(int i = 0; i < pFormatCtx->nb_streams; i++)
   {
      av_freep(&pFormatCtx->streams[i]->codec);
      av_freep(&pFormatCtx->streams[i]);
   }

   // Close file
   url_fclose(pFormatCtx->pb);

   // Free the stream
   av_free(pFormatCtx);

   initVars();
   return true;
}


/**
   \brief Encode one frame

   The frame must be of the same size as specified in the createFile call.

   This is the standard method to encode videos with fixed frame rates.
   Each call to encodeImage adds a frame, which will be played back at the frame rate
   specified in the createFile call.
**/
int QVideoEncoder::encodeImage(const QImage &img)
{
   return encodeImage_p(img);
}
/**
   \brief Encode one frame

   The frame must be of the same size as specified in the createFile call.

   This mehtod allows to specify the presentation time stamp (pts) of the frame.
   pts is specified in multiples of 1/framerate, where framerate was specified in the createFile call
   E.g. to encode frames with a 1ms resolution: set the frame rate to 1000, and pts is the presentation
   time in milliseconds.
   pts must be monotonously increasing.
   The first frame ought to have a pts of 0 to be immediately displayed.
**/
int QVideoEncoder::encodeImagePts(const QImage &img,unsigned pts)
{
   return encodeImage_p(img,true,pts);
}


/******************************************************************************
* INTERNAL   INTERNAL   INTERNAL   INTERNAL   INTERNAL   INTERNAL   INTERNAL
******************************************************************************/

void QVideoEncoder::initVars()
{
   ok=false;
   pFormatCtx=0;
   pOutputFormat=0;
   pCodecCtx=0;
   pVideoStream=0;
   pCodec=0;
   ppicture=0;
   outbuf=0;
   picture_buf=0;
   img_convert_ctx=0;
}


/**
   \brief Register the codecs
**/
bool QVideoEncoder::initCodec()
{
   ffmpeg::avcodec_init();
   ffmpeg::av_register_all();

   qDebug("License: %s\n",ffmpeg::avformat_license());
   qDebug("AVCodec version %d\n",ffmpeg::avformat_version());
   qDebug("AVFormat configuration: %s\n",ffmpeg::avformat_configuration());

   return true;
}

/**
   \brief Encode one frame - internal function
   custompts: true if a custom presentation time stamp  is used
   pts: presentation time stamp in milliseconds
**/
int QVideoEncoder::encodeImage_p(const QImage &img,bool custompts, unsigned pts)
{
   if(!isOk())
      return -1;

   //convertImage(img);       // Custom conversion routine
   convertImage_sws(img);     // SWS conversion



   if(custompts)                             // Handle custom pts
         pCodecCtx->coded_frame->pts = pts;  // Set the time stamp

   int out_size = ffmpeg::avcodec_encode_video(pCodecCtx,outbuf,outbuf_size,ppicture);
   //qDebug("Frame size: %d\n",out_size);


   if(custompts)                             // Handle custom pts (must set it again for the rest of the processing)
         pCodecCtx->coded_frame->pts = pts;  // Set the time stamp

   if (out_size > 0)
   {

      av_init_packet(&pkt);

      //if (pCodecCtx->coded_frame->pts != AV_NOPTS_VALUE)
      if (pCodecCtx->coded_frame->pts != (0x8000000000000000LL))
         pkt.pts= av_rescale_q(pCodecCtx->coded_frame->pts, pCodecCtx->time_base, pVideoStream->time_base);
      if(pCodecCtx->coded_frame->key_frame)
         pkt.flags |= AV_PKT_FLAG_KEY;

      //qDebug("c %d. pts %d. codedframepts: %ld pkt.pts: %ld\n",custompts,pts,pCodecCtx->coded_frame->pts,pkt.pts);

      pkt.stream_index= pVideoStream->index;
      pkt.data= outbuf;
      pkt.size= out_size;
      int ret = av_interleaved_write_frame(pFormatCtx, &pkt);
      //qDebug("Wrote %d\n",ret);
      if(ret<0)
         return -1;
   }
   return out_size;
}



/**
  Ensures sizes are some reasonable multiples
**/
bool QVideoEncoder::isSizeValid()
{
   if(getWidth()%8)
      return false;
   if(getHeight()%8)
      return false;
   return true;
}

unsigned QVideoEncoder::getWidth()
{
   return Width;
}
unsigned QVideoEncoder::getHeight()
{
   return Height;
}
bool QVideoEncoder::isOk()
{
   return ok;
}

/**
  Allocate memory for the compressed bitstream
**/
bool QVideoEncoder::initOutputBuf()
{
   outbuf_size = getWidth()*getHeight()*3;        // Some extremely generous memory allocation for the encoded frame.
   outbuf = new uint8_t[outbuf_size];
   if(outbuf==0)
      return false;
   return true;
}
/**
  Free memory for the compressed bitstream
**/
void QVideoEncoder::freeOutputBuf()
{
   if(outbuf)
   {
      delete[] outbuf;
      outbuf=0;
   }
}

bool QVideoEncoder::initFrame()
{
   ppicture = ffmpeg::avcodec_alloc_frame();
   if(ppicture==0)
      return false;

   int size = avpicture_get_size(pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
   picture_buf = new uint8_t[size];
   if(picture_buf==0)
   {
      av_free(ppicture);
      ppicture=0;
      return false;
   }

   // Setup the planes
   avpicture_fill((ffmpeg::AVPicture *)ppicture, picture_buf,pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);

   return true;
}
void QVideoEncoder::freeFrame()
{
   if(picture_buf)
   {
      delete[] picture_buf;
      picture_buf=0;
   }
   if(ppicture)
   {
      av_free(ppicture);
      ppicture=0;
   }
}

/**
  \brief Convert the QImage to the internal YUV format

  Custom conversion - not very optimized.

**/

bool QVideoEncoder::convertImage(const QImage &img)
{
   // Check if the image matches the size
   if(img.width()!=getWidth() || img.height()!=getHeight())
   {
      qDebug("Wrong image size!\n");
      return false;
   }
   if(img.format()!=QImage::Format_RGB32	&& img.format() != QImage::Format_ARGB32)
   {
      qDebug("Wrong image format\n");
      return false;
   }

   // RGB32 to YUV420

   int size = getWidth()*getHeight();
   // Y
   for(unsigned y=0;y<getHeight();y++)
   {

      unsigned char *s = (unsigned char*)img.scanLine(y);
      unsigned char *d = (unsigned char*)&picture_buf[y*getWidth()];
      //qDebug("Line %d. d: %p. picture_buf: %p\n",y,d,picture_buf);

      for(unsigned x=0;x<getWidth();x++)
      {
         unsigned int r=s[2];
         unsigned int g=s[1];
         unsigned int b=s[0];

         unsigned Y = (r*2104 + g*4130 + b*802 + 4096 + 131072) >> 13;
         if(Y>235) Y=235;

         *d = Y;

         d+=1;
         s+=4;
      }
   }

   // U,V
   for(unsigned y=0;y<getHeight();y+=2)
   {
      unsigned char *s = (unsigned char*)img.scanLine(y);
      unsigned int ss = img.bytesPerLine();
      unsigned char *d = (unsigned char*)&picture_buf[size+y/2*getWidth()/2];

      //qDebug("Line %d. d: %p. picture_buf: %p\n",y,d,picture_buf);

      for(unsigned x=0;x<getWidth();x+=2)
      {
         // Cr = 128 + 1/256 * ( 112.439 * R'd -  94.154 * G'd -  18.285 * B'd)
         // Cb = 128 + 1/256 * (- 37.945 * R'd -  74.494 * G'd + 112.439 * B'd)

         // Get the average RGB in a 2x2 block
         int r=(s[2] + s[6] + s[ss+2] + s[ss+6] + 2) >> 2;
         int g=(s[1] + s[5] + s[ss+1] + s[ss+5] + 2) >> 2;
         int b=(s[0] + s[4] + s[ss+0] + s[ss+4] + 2) >> 2;

         int Cb = (-1214*r - 2384*g + 3598*b + 4096 + 1048576)>>13;
         if(Cb<16)
            Cb=16;
         if(Cb>240)
            Cb=240;

         int Cr = (3598*r - 3013*g - 585*b + 4096 + 1048576)>>13;
         if(Cr<16)
            Cr=16;
         if(Cr>240)
            Cr=240;

         *d = Cb;
         *(d+size/4) = Cr;

         d+=1;
         s+=8;
      }
   }
   return true;
}

/**
  \brief Convert the QImage to the internal YUV format

  SWS conversion

   Caution: the QImage is allocated by QT without guarantee about the alignment and bytes per lines.
   It *should* be okay as we make sure the image is a multiple of many bytes (8 or 16)...
   ... however it is not guaranteed that sws_scale won't at some point require more bytes per line.
   We keep the custom conversion for that case.

**/

bool QVideoEncoder::convertImage_sws(const QImage &img)
{
   // Check if the image matches the size
   if(img.width()!=getWidth() || img.height()!=getHeight())
   {
      qDebug("Wrong image size!\n");
      return false;
   }
   if(img.format()!=QImage::Format_RGB32	&& img.format() != QImage::Format_ARGB32)
   {
      qDebug("Wrong image format\n");
      return false;
   }

   img_convert_ctx = ffmpeg::sws_getCachedContext(img_convert_ctx,getWidth(),getHeight(),ffmpeg::PIX_FMT_BGRA,getWidth(),getHeight(),ffmpeg::PIX_FMT_YUV420P,SWS_BICUBIC, NULL, NULL, NULL);
   //img_convert_ctx = ffmpeg::sws_getCachedContext(img_convert_ctx,getWidth(),getHeight(),ffmpeg::PIX_FMT_BGRA,getWidth(),getHeight(),ffmpeg::PIX_FMT_YUV420P,SWS_FAST_BILINEAR, NULL, NULL, NULL);
   if (img_convert_ctx == NULL)
   {
      qDebug("Cannot initialize the conversion context\n");
      return false;
   }

   uint8_t *srcplanes[3];
   srcplanes[0]=(uint8_t*)img.bits();
   srcplanes[1]=0;
   srcplanes[2]=0;

   int srcstride[3];
   srcstride[0]=img.bytesPerLine();
   srcstride[1]=0;
   srcstride[2]=0;


   ffmpeg::sws_scale(img_convert_ctx, srcplanes, srcstride,0, getHeight(), ppicture->data, ppicture->linesize);

   return true;
}

