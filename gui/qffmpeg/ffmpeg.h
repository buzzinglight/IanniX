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
/*
   Wraps the ffmpeg includes in a namespace and ensures extern "C"
*/

#ifndef _FFMPEG_H
#define _FFMPEG_H

namespace ffmpeg {
extern "C" {

/*#define INT64_C

#define __STDC_CONSTANT_MACROS

#include <stdint.h>*/



#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
//#include "libavformat/riff.h"
//#include "libavformat/metadata.h"
//#include "libavformat/utils.h"
#include "libavcodec/opt.h"
#include "libavutil/rational.h"
//#include "options.h"
#include "libavutil/avstring.h"
//#include "libavutil/internal.h"
#include "libswscale/swscale.h"
}
}

/*
#ifndef INT64_MIN
#define INT64_MIN       (-0x7fffffffffffffffLL-1)
#endif

#ifndef INT64_MAX
#define INT64_MAX 9223372036854775807LL
#endif*/


/*#ifndef INT64_C
#define INT64_C(value) __CONCAT(value, LL)
#endif*/


#endif // _FFMPEG_H
