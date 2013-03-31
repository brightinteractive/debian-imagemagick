/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%           AAA   N   N  N   N   OOO   TTTTT   AAA   TTTTT  EEEEE             %
%          A   A  NN  N  NN  N  O   O    T    A   A    T    E                 %
%          AAAAA  N N N  N N N  O   O    T    AAAAA    T    EEE               %
%          A   A  N  NN  N  NN  O   O    T    A   A    T    E                 %
%          A   A  N   N  N   N   OOO     T    A   A    T    EEEEE             %
%                                                                             %
%                                                                             %
%                   MagickCore Image Annotation Methods                       %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
%                                                                             %
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
%
% Digital Applications (www.digapp.com) contributed the stroked text algorithm.
% It was written by Leonard Rosenthol.
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/annotate.h"
#include "magick/channel.h"
#include "magick/client.h"
#include "magick/semaphore.h"
#include "magick/xwindow-private.h"
#include "magick/exception.h"
#include "magick/exception-private.h"
#include "magick/gem.h"
#include "magick/geometry.h"
#include "magick/image-private.h"
#include "magick/log.h"
#include "magick/quantum.h"
#include "magick/quantum-private.h"
#include "magick/pixel-accessor.h"

extern SemaphoreInfo *annotate_semaphore;

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   R e n d e r X 1 1                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  RenderX11() renders text on the image with an X11 font.  It also returns the
%  bounding box of the text relative to the image.
%
%  The format of the RenderX11 method is:
%
%      MagickBooleanType RenderX11(Image *image,DrawInfo *draw_info,
%        const PointInfo *offset,TypeMetric *metrics)
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o draw_info: the draw info.
%
%    o offset: (x,y) location of text relative to image.
%
%    o metrics: bounding box of text.
%
*/
#if defined(MAGICKCORE_X11_DELEGATE)
MagickExport MagickBooleanType magickcore_annotate_RenderX11_WITHX(Image *image,const DrawInfo *draw_info,
  const PointInfo *offset,TypeMetric *metrics)
{
  MagickBooleanType
    status;

  static DrawInfo
    cache_info;

  static Display
    *display = (Display *) NULL;

  static XAnnotateInfo
    annotate_info;

  static XFontStruct
    *font_info;

  static XPixelInfo
    pixel;

  static XResourceInfo
    resource_info;

  static XrmDatabase
    resource_database;

  static XStandardColormap
    *map_info;

  static XVisualInfo
    *visual_info;

  size_t
    height,
    width;

  if (annotate_semaphore == (SemaphoreInfo *) NULL)
    AcquireSemaphoreInfo(&annotate_semaphore);
  LockSemaphoreInfo(annotate_semaphore);
  if (display == (Display *) NULL)
    {
      const char
        *client_name;

      ImageInfo
        *image_info;

      /*
        Open X server connection.
      */
      display=XOpenDisplay(draw_info->server_name);
      if (display == (Display *) NULL)
        {
          UnlockSemaphoreInfo(annotate_semaphore);
          ThrowXWindowException(XServerError,"UnableToOpenXServer",
            draw_info->server_name);
          return(MagickFalse);
        }
      /*
        Get user defaults from X resource database.
      */
      (void) XSetErrorHandler(XError);
      image_info=AcquireImageInfo();
      client_name=GetClientName();
      resource_database=XGetResourceDatabase(display,client_name);
      XGetResourceInfo(image_info,resource_database,client_name,&resource_info);
      resource_info.close_server=MagickFalse;
      resource_info.colormap=PrivateColormap;
      resource_info.font=AcquireString(draw_info->font);
      resource_info.background_color=AcquireString("#ffffffffffff");
      resource_info.foreground_color=AcquireString("#000000000000");
      map_info=XAllocStandardColormap();
      if (map_info == (XStandardColormap *) NULL)
        {
          UnlockSemaphoreInfo(annotate_semaphore);
          ThrowXWindowException(ResourceLimitError,"MemoryAllocationFailed",
            image->filename);
          return(MagickFalse);
        }
      /*
        Initialize visual info.
      */
      visual_info=XBestVisualInfo(display,map_info,&resource_info);
      if (visual_info == (XVisualInfo *) NULL)
        {
          UnlockSemaphoreInfo(annotate_semaphore);
          ThrowXWindowException(XServerError,"UnableToGetVisual",
            image->filename);
          return(MagickFalse);
        }
      map_info->colormap=(Colormap) NULL;
      pixel.pixels=(unsigned long *) NULL;
      /*
        Initialize Standard Colormap info.
      */
      XGetMapInfo(visual_info,XDefaultColormap(display,visual_info->screen),
        map_info);
      XGetPixelPacket(display,visual_info,map_info,&resource_info,
        (Image *) NULL,&pixel);
      pixel.annotate_context=XDefaultGC(display,visual_info->screen);
      /*
        Initialize font info.
      */
      font_info=XBestFont(display,&resource_info,MagickFalse);
      if (font_info == (XFontStruct *) NULL)
        {
          UnlockSemaphoreInfo(annotate_semaphore);
          ThrowXWindowException(XServerError,"UnableToLoadFont",
            draw_info->font);
          return(MagickFalse);
        }
      if ((map_info == (XStandardColormap *) NULL) ||
          (visual_info == (XVisualInfo *) NULL) ||
          (font_info == (XFontStruct *) NULL))
        {
          UnlockSemaphoreInfo(annotate_semaphore);
          XFreeResources(display,visual_info,map_info,&pixel,font_info,
            &resource_info,(XWindowInfo *) NULL);
          ThrowXWindowException(XServerError,"UnableToLoadFont",
            image->filename);
          return(MagickFalse);
        }
      cache_info=(*draw_info);
    }
  UnlockSemaphoreInfo(annotate_semaphore);
  /*
    Initialize annotate info.
  */
  XGetAnnotateInfo(&annotate_info);
  annotate_info.stencil=ForegroundStencil;
  if (cache_info.font != draw_info->font)
    {
      /*
        Type name has changed.
      */
      (void) XFreeFont(display,font_info);
      (void) CloneString(&resource_info.font,draw_info->font);
      font_info=XBestFont(display,&resource_info,MagickFalse);
      if (font_info == (XFontStruct *) NULL)
        {
          ThrowXWindowException(XServerError,"UnableToLoadFont",
            draw_info->font);
          return(MagickFalse);
        }
    }
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(AnnotateEvent,GetMagickModule(),
      "Font %s; pointsize %g",draw_info->font != (char *) NULL ?
      draw_info->font : "none",draw_info->pointsize);
  cache_info=(*draw_info);
  annotate_info.font_info=font_info;
  annotate_info.text=(char *) draw_info->text;
  annotate_info.width=(unsigned int) XTextWidth(font_info,draw_info->text,
    (int) strlen(draw_info->text));
  annotate_info.height=(unsigned int) font_info->ascent+font_info->descent;
  metrics->pixels_per_em.x=(double) font_info->max_bounds.width;
  metrics->pixels_per_em.y=(double) font_info->ascent+font_info->descent;
  metrics->ascent=(double) font_info->ascent+4;
  metrics->descent=(double) (-font_info->descent);
  metrics->width=annotate_info.width/ExpandAffine(&draw_info->affine);
  metrics->height=font_info->ascent+font_info->descent;
  metrics->max_advance=(double) font_info->max_bounds.width;
  metrics->bounds.x1=0.0;
  metrics->bounds.y1=metrics->descent;
  metrics->bounds.x2=metrics->ascent+metrics->descent;
  metrics->bounds.y2=metrics->ascent+metrics->descent;
  metrics->underline_position=(-2.0);
  metrics->underline_thickness=1.0;
  if (draw_info->render == MagickFalse)
    return(MagickTrue);
  if (draw_info->fill.opacity == TransparentOpacity)
    return(MagickTrue);
  /*
    Render fill color.
  */
  width=annotate_info.width;
  height=annotate_info.height;
  if ((draw_info->affine.rx != 0.0) || (draw_info->affine.ry != 0.0))
    {
      if (((draw_info->affine.sx-draw_info->affine.sy) == 0.0) &&
          ((draw_info->affine.rx+draw_info->affine.ry) == 0.0))
        annotate_info.degrees=(180.0/MagickPI)*
          atan2(draw_info->affine.rx,draw_info->affine.sx);
    }
  (void) FormatLocaleString(annotate_info.geometry,MaxTextExtent,
    "%.20gx%.20g%+.20g%+.20g",(double) width,(double) height,
    ceil(offset->x-0.5),ceil(offset->y-metrics->ascent-metrics->descent+
    draw_info->interline_spacing-0.5));
  pixel.pen_color.red=ScaleQuantumToShort(draw_info->fill.red);
  pixel.pen_color.green=ScaleQuantumToShort(draw_info->fill.green);
  pixel.pen_color.blue=ScaleQuantumToShort(draw_info->fill.blue);
  status=XAnnotateImage(display,&pixel,&annotate_info,image);
  if (status == 0)
    {
      ThrowXWindowException(ResourceLimitError,"MemoryAllocationFailed",
        image->filename);
      return(MagickFalse);
    }
  return(MagickTrue);
}
#endif
