/*
%              Stubs for Xwindows
%
%  Copyright 1999-2013 ImageMagick Studio LLC, a non-profit organization      %
%  dedicated to making software imaging solutions freely available.           %
%                                                                             %
%  You may not use this file except in compliance with the License.  You may  %
%  obtain a copy of the License at                                            %
%                                                                             %
%    http://www.imagemagick.org/script/license.php                            %
%                                                                             %
%  Unless required by applicable law or agreed to in writing, software        %
%  distributed under the License is distributed on an "AS IS" BASIS,          %
%  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   %
%  See the License for the specific language governing permissions and        %
%  limitations under the License.                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#include "magick/magick-config.h"
#include "magick/studio.h"
#include "magick/utility.h"
#include "magick/image.h"
#include "magick/annotate.h"
#include "magick/log.h"


/* TODO compile inconditionnaly when xplugin is done */
#if !defined(MAGICKCORE_X11_DELEGATE)
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D i s p l a y I m a g e s                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DisplayImages() displays an image sequence to any X window screen.  It
%  returns a value other than 0 if successful.  Check the exception member
%  of image to determine the reason for any failure.
%
%  The format of the DisplayImages method is:
%
%      MagickBooleanType DisplayImages(const ImageInfo *image_info,
%        Image *images)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o image: the image.
%
*/
static MagickBooleanType DisplayImages_NOX(const ImageInfo *image_info,
  Image *image)
{
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  (void) ThrowMagickException(&image->exception,GetMagickModule(),
    MissingDelegateError,"DelegateLibrarySupportNotBuiltIn","`%s' (X11)",
    image->filename);
  return(MagickFalse);
}
#else
extern MagickBooleanType DisplayImages_WITHX(const ImageInfo *image_info,
					     Image *image);
#endif

/* TODO use symbols alias if possible */
#if defined(MAGICKCORE_X11_DELEGATE)
MagickExport MagickBooleanType DisplayImages(const ImageInfo *image_info,Image *image)
{
  return DisplayImages_WITHX(image_info,image);
}
#else /* !defined(MAGICKCORE_X11_DELEGATE) */
MagickExport MagickBooleanType DisplayImages(const ImageInfo *image_info,Image *image)
{
  return DisplayImages_NOX(image_info,image);
}
#endif /* defined(MAGICKCORE_X11_DELEGATE) */



/* TODO compile inconditionnaly when xplugin is done */
#if !defined(MAGICKCORE_X11_DELEGATE)
/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   R e m o t e D i s p l a y C o m m a n d                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RemoteDisplayCommand() encourages a remote display program to display the
%  specified image filename.
%
%  The format of the RemoteDisplayCommand method is:
%
%      MagickBooleanType RemoteDisplayCommand(const ImageInfo *image,
%        const char *window,const char *filename,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image_info: the image info.
%
%    o window: Specifies the name or id of an X window.
%
%    o filename: the name of the image filename to display.
%
%    o exception: return any errors or warnings in this structure.
%
*/
static MagickBooleanType RemoteDisplayCommand_NOX(const ImageInfo *image_info,
  const char *window,const char *filename,ExceptionInfo *exception)
{
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(filename != (char *) NULL);
  (void) window;
  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",filename);
  (void) ThrowMagickException(exception,GetMagickModule(),MissingDelegateError,
    "DelegateLibrarySupportNotBuiltIn","`%s' (X11)",image_info->filename);
  return(MagickFalse);
}
#else
extern MagickBooleanType RemoteDisplayCommand_WITHX(const ImageInfo *image_info,
					      const char *window,const char *filename,ExceptionInfo *exception);
#endif

/* TODO use symbols alias if possible */
#if defined(MAGICKCORE_X11_DELEGATE)
MagickExport MagickBooleanType RemoteDisplayCommand(const ImageInfo *image_info,
				       const char *window,const char *filename,ExceptionInfo *exception) {
  return RemoteDisplayCommand_WITHX(image_info,window,filename,exception);
}
#else /* !defined(MAGICKCORE_X11_DELEGATE) */
MagickExport MagickBooleanType RemoteDisplayCommand(const ImageInfo *image_info,
				       const char *window,const char *filename,ExceptionInfo *exception) {
  return RemoteDisplayCommand_NOX(image_info,window,filename,exception);
}
#endif /* defined(MAGICKCORE_X11_DELEGATE) */

/* TODO compile inconditionnaly when xplugin is done */
#if !defined(MAGICKCORE_X11_DELEGATE)
static void XComponentTerminus_NOX(void)
{
}
#else /* defined(MAGICKCORE_X11_DELEGATE) */
extern void XComponentTerminus_WITHX(void);
#endif /* defined(MAGICKCORE_X11_DELEGATE) */

/* TODO use symbols alias if possible */
#if defined(MAGICKCORE_X11_DELEGATE) 
MagickExport void XComponentTerminus(void) {
  XComponentTerminus_WITHX();
}
#else /* !defined(MAGICKCORE_X11_DELEGATE) */
MagickExport void XComponentTerminus(void) {
  XComponentTerminus_NOX();
}
#endif

/* TODO compile inconditionnaly when xplugin is done */
#if !defined(MAGICKCORE_X11_DELEGATE)
static MagickBooleanType XComponentGenesis_NOX(void)
{
  return(MagickTrue);
}
#else /* defined(MAGICKCORE_X11_DELEGATE) */
extern MagickBooleanType XComponentGenesis_WITHX(void);
#endif /* !defined(MAGICKCORE_X11_DELEGATE) */

/* TODO use symbols alias if possible */
#if defined(MAGICKCORE_X11_DELEGATE)
MagickExport MagickBooleanType XComponentGenesis(void) {
  return XComponentGenesis_WITHX();
}
#else /* !defined(MAGICKCORE_X11_DELEGATE) */
MagickExport MagickBooleanType XComponentGenesis(void) {
  return XComponentGenesis_NOX();
}
#endif /* defined(MAGICKCORE_X11_DELEGATE) */

#if !defined(MAGICKCORE_X11_DELEGATE)
static MagickBooleanType magickcore_annotate_RenderX11_NOX(Image *image,const DrawInfo *draw_info,
  const PointInfo *offset,TypeMetric *metrics)
{
  (void) draw_info;
  (void) offset;
  (void) metrics;
  (void) ThrowMagickException(&image->exception,GetMagickModule(),
    MissingDelegateError,"DelegateLibrarySupportNotBuiltIn","`%s' (X11)",
    image->filename);
  return(MagickFalse);
}
#else /* defined(MAGICKCORE_X11_DELEGATE) */
extern MagickBooleanType magickcore_annotate_RenderX11_WITHX(Image *image,const DrawInfo *draw_info,
							     const PointInfo *offset,TypeMetric *metrics);
#endif /* !defined(MAGICKCORE_X11_DELEGATE) */

/* TODO use symbols alias if possible */
#if defined(MAGICKCORE_X11_DELEGATE)
MagickExport MagickBooleanType magickcore_annotate_RenderX11(Image *image,const DrawInfo *draw_info,
							     const PointInfo *offset,TypeMetric *metrics)
{
  return magickcore_annotate_RenderX11_WITHX(image,draw_info,offset,metrics);
}
#else /* !defined(MAGICKCORE_X11_DELEGATE) */
MagickExport MagickBooleanType magickcore_annotate_RenderX11(Image *image,const DrawInfo *draw_info,
							     const PointInfo *offset,TypeMetric *metrics);
  return magickcore_annotate_RenderX11_NOX(image,draw_info,offset,metrics);
}
#endif /* defined(MAGICKCORE_X11_DELEGATE) */
