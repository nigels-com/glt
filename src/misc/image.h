#ifndef MISC_IMAGE_H
#define MISC_IMAGE_H

/*

  GLT OpenGL C++ Toolkit (LGPL)
  Copyright (C) 2000-2004 Nigel Stewart


  WWW:    http://www.nigels.com/glt/
  Forums: http://sourceforge.net/forum/?group_id=36869

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*! \file
    \brief   Image utility routines
    \author  Nigel Stewart, RMIT (nigels.com@gmail.com)
    \ingroup Misc
    \todo    Image test program(s)

    These routines are not intended as a general-purpose
    image viewing, output or image-processing package.
    The priority here is to support image formats that
    are most likely to be used in the context of OpenGL
    texture mapping.

    Here are a few notes about the relative advantages
    of each type of image encoding.

    PPM is simple to read and write - greyscale and
    RGB variants are useful for input and output,
    commonly used on the UNIX platform.  PPM's are
    not compressed, and are not lossy.

    TGA come in uncompressed or compressed variants,
    and support indexed, greyscale, or 16/24/32 bit
    RGB and RGBA pixel data.  TGA's support an
    alpha (transparency) channel.

    BMP is the standard image format for the Windows
    platform.  The structure of BMP files is
    relatively convoluted, but similar to TGA.
*/

#include <glt/config.h>
#include <misc/config.h>

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include <string>
#include <iosfwd>
#include <vector>

//
// Image Processing
//

/*!
    \brief      Is an RGB buffer greyscale?
    \ingroup    Misc
    \param      rgb     RGB image buffer
*/
bool isGreyscale(const std::string &rgb);

/*!
    \brief      Is an RGB buffer 256 colors or less?
    \ingroup    Misc
    \param      rgb     RGB image buffer
*/
bool is256Colors(const std::string &rgb);

/*!
    \brief      Extract channel from image buffer
    \ingroup    Misc
    \param      dest    Destination buffer
    \param      src     Source buffer in any format
    \param      size    Number of channels in source buffer
    \param      channel Channel to be extracted
*/
bool getChannel(std::string &dest,const std::string &src,const uint32 size,const uint32 channel);

/*!
    \brief      Convert RGB data to indexed
    \ingroup    Misc
    \note       Image data should be pre-quantised
    \note       Only the first 256 colors will be maintained
    \param      dest    Destination buffer
    \param      rgb     RGB source buffer
*/
void rgb2Indexed(std::string &dest,const std::string &rgb);

/*!
    \brief      Convert indexed data to RGB
    \ingroup    Misc
    \param      dest    RGB Destination buffer
    \param      indexed Indexed source buffer
*/
void indexed2rgb(std::string &dest,const std::string &indexed);

/*!
    \brief      Flip image vertically
    \ingroup    Misc
    \param      dest     Destination buffer
    \param      src      Source buffer
    \param      width    Width of image  (pixels)
    \param      height   Height of image (pixels)
*/
void flipImage(std::string &dest,const std::string &src,const uint32 width,const uint32 height);

/*!
    \brief      Mirror image horizontally
    \ingroup    Misc
    \param      dest     Destination buffer
    \param      src      Source buffer
    \param      width    Width of image  (pixels)
    \param      height   Height of image (pixels)
*/
void mirrorImage(std::string &dest,const std::string &src,const uint32 width,const uint32 height);

/*!
    \brief      Adjust image gamma
    \ingroup    Misc
    \param      image    Image
    \param      gamma    Gamma co-efficient
*/
void adjustGamma(std::string &image,const double gamma);

/*!
    \brief      Adjust image hue, saturation and brightness
    \ingroup    Misc
    \param      image      Image
    \param      width      Width of image  (pixels)
    \param      height     Height of image (pixels)
    \param      hue        Hue adjustment
    \param      saturation Saturation adjustment
    \param      value      Value adjustment
*/
void adjustHSV(std::string &image,const int width,const int height,const real hue,const real saturation,const real value);

/*!
    \brief      Stitch tiled images
    \ingroup    Misc
*/
bool stitchImages(std::string &image,const int dx,const int dy,const std::vector<std::string> &src,const int lineSize);

/*!
    \brief      Synthesise Perlin Noise image
    \ingroup    Misc
*/
bool noiseImage(std::string &image,const uint32 width,const uint32 height,const uint32 fractionalBits);

//
// Image decoding
//

/*!
    \brief      Decode image data from PPM, BMP, TGA, PNG and JPEG
    \ingroup    Misc
    \param      width    Image width
    \param      height   Image height
    \param      image    Raw image data
    \param      data     Source data buffer
*/
bool decode(uint32 &width,uint32 &height,std::string &image,const std::string &data);

/*!
    \brief      Decode image data from PPM
    \ingroup    Misc
    \param      type     Type of PPM, P5 for PGM, P6 for PPM
    \param      width    Width of PPM
    \param      height   Height of PPM
    \param      image    Destination RGB or Greyscale buffer
    \param      data     Source data buffer
    \todo       Only P6 and P5 variants (binary RGB and Grey) recognised
    \todo       Implement text PPM support
*/
bool decodePPM(std::string &type,uint32 &width,uint32 &height,std::string &image,const std::string &data);

/*!
    \brief      Decode image data from BMP
    \ingroup    Misc
    \param      width    Width of BMP
    \param      height   Height of BMP
    \param      image    Destination RGB buffer
    \param      data     Source data buffer
    \todo       Windows BMP import limited to RGB images
*/
bool decodeBMP(uint32 &width,uint32 &height,std::string &image,const std::string &data);

/*!
    \brief      Decode image data from TGA
    \ingroup    Misc
    \param      width    Width of BMP
    \param      height   Height of BMP
    \param      image    Destination RGB buffer
    \param      data     Source data buffer
    \todo       TGA import limited to uncompressed RGB or RGBA images
*/
bool decodeTGA(uint32 &width,uint32 &height,std::string &image,const std::string &data);

#ifdef GLT_PNG

/*!
    \brief      Decode image data from PNG
    \ingroup    Misc
    \param      width    Width of PNG image
    \param      height   Height of PNG image
    \param      image    Destination RGB buffer
    \param      data     Source data buffer
*/
bool decodePNG(uint32 &width,uint32 &height,std::string &image,const std::string &data);

#endif

#ifdef GLT_JPEG

/*!
    \brief      Decode image data from JPG
    \ingroup    Misc
    \param      width    Width of JPG image
    \param      height   Height of JPG image
    \param      image    Destination RGB buffer
    \param      data     Source data buffer
*/
bool decodeJPG(uint32 &width,uint32 &height,std::string &image,const std::string &data);

#endif

//
// Image Encoding
//

/*!
    \brief      Encode image data as RGB unix PPM or PGM
    \ingroup    Misc
    \param      data     PPM output buffer
    \param      width    Image width
    \param      height   Image height
    \param      image    Input image buffer
*/
bool encodePPM(std::string &data,const uint32 width,const uint32 height,const std::string &image);

/*!
    \brief      Encode image data as RGB Windows BMP
    \ingroup    Misc
    \param      data     BMP output buffer
    \param      width    Image width
    \param      height   Image height
    \param      image    Input image buffer
    \todo       Not yet implemented
*/
bool encodeBMP(std::string &data,const uint32 width,const uint32 height,const std::string &image);

/*!
    \brief      Encode image data as RGB TGA
    \ingroup    Misc
    \param      data     TGA output buffer
    \param      width    Image width
    \param      height   Image height
    \param      image    Input image buffer
    \todo       TGA RGBA alpha channel export
*/
bool encodeTGA(std::string &data,const uint32 width,const uint32 height,const std::string &image);

#ifdef GLT_PNG

/*!
    \brief      Encode image data as RGB PNG
    \ingroup    Misc
    \param      data     PNG output buffer
    \param      width    Image width
    \param      height   Image height
    \param      image    Input image buffer
*/
bool encodePNG(std::string &data,const uint32 &width,const uint32 &height,const std::string &image);

#endif

#ifdef GLT_JPEG

/*!
    \brief      Encode image data as JPG
    \ingroup    Misc
    \param      data     JPG output buffer
    \param      width    Image width
    \param      height   Image height
    \param      image    Input image buffer
    \param      quality  JPG output quality, 0 to 100
*/
bool encodeJPG(std::string &data,const uint32 &width,const uint32 &height,const std::string &image,const uint32 quality = 97);

#endif

#endif
