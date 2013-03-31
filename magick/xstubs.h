/*
  Copyright 1999-2013 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.
  
  You may not use this file except in compliance with the License.
  obtain a copy of the License at
  
    http://www.imagemagick.org/script/license.php
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore xwindows stub function
*/

#ifndef _MAGICKCORE_XSTUBS_H
#define _MAGICKCORE_XSTUBS_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include "magick/draw.h"
#include "magick/image.h"

extern MagickExport void XComponentTerminus(void);
extern MagickExport MagickBooleanType XComponentGenesis(void);
extern MagickExport MagickBooleanType DisplayImages(const ImageInfo *image_info,
						    Image *image);
extern MagickExport MagickBooleanType RemoteDisplayCommand(const ImageInfo *image_info,
							   const char *window,const char *filename,ExceptionInfo *exception);

extern MagickExport MagickBooleanType magickcore_annotate_RenderX11(Image *image,const DrawInfo *draw_info,
								    const PointInfo *offset,TypeMetric *metrics);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _MAGICKCORE_XSTUBS_H */
