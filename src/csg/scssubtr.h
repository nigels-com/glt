#ifndef CSG_SCSSUBTR_H
#define CSG_SCSSUBTR_H

/** \file
 *  \brief   CSG Subtraction of Convex Objects
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <csg/scsseq.h>

class CsgProduct;
class CsgOptions;
class CsgInfo;

void csgRenderConvexSubtraction
(
    const CsgProduct             &prod,
    const CsgSubtractionSequence &seq,
    const CsgOptions             &options,
          CsgInfo                &info
);

#endif

