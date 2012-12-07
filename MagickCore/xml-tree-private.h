/*
  Copyright 1999-2013 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.

  You may not use this file except in compliance with the License.
  obtain a copy of the License at

    http://www.imagemagick.org/MagicksToolkit/script/license.php

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore private xml-tree methods.
*/
#ifndef _MAGICKCORE_XML_TREE_PRIVATE_H
#define _MAGICKCORE_XML_TREE_PRIVATE_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include <MagickCore/exception.h>
#include <MagickCore/splay-tree.h>

extern MagickPrivate char
  *CanonicalXMLContent(const char *,const MagickBooleanType);

extern MagickPrivate const char
  **GetXMLTreeProcessingInstructions(XMLTreeInfo *,const char *);

extern MagickPrivate MagickBooleanType
  GetXMLTreeAttributes(const XMLTreeInfo *,SplayTreeInfo *);

extern MagickPrivate XMLTreeInfo
  *AddPathToXMLTree(XMLTreeInfo *,const char *,const size_t),
  *GetXMLTreeOrdered(XMLTreeInfo *),
  *GetXMLTreePath(XMLTreeInfo *,const char *),
  *InsertTagIntoXMLTree(XMLTreeInfo *,XMLTreeInfo *,const size_t),
  *ParseTagFromXMLTree(XMLTreeInfo *),
  *PruneTagFromXMLTree(XMLTreeInfo *),
  *SetXMLTreeAttribute(XMLTreeInfo *,const char *,const char *);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
