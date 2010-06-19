#ifndef CSG_SCSCLIP_H
#define CSG_SCSCLIP_H

/** \file
 *  \brief   Z-Buffer Clipping Against Convex Objects
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

class CsgProduct;

// Rendering

void csgRenderClipZBuffer(const CsgProduct &prod);

#endif

