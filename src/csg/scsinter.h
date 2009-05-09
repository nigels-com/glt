#ifndef CSG_SCSINTER_H
#define CSG_SCSINTER_H

/** \file
 *  \brief   Fast CSG Intersection of Convex Objects
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

class CsgProduct;
class CsgOptions;
class CsgInfo;

// Rendering

void csgRenderConvexIntersection
(
    const CsgProduct &prod,
    const CsgOptions &options,
          CsgInfo    &info
);

void csgRenderConvexIntersectionRGB
(
    const CsgProduct &prod,
    const CsgOptions &options,
          CsgInfo    &info
);

#endif

