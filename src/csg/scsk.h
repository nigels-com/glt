#ifndef CSG_SCSK_H
#define CSG_SCSK_H

/** \file
 *  \brief   Depth Complexity Sampling
 *  \ingroup CSG
 *
 */

#include <csg/scsseq.h>

class CsgProduct;
class CsgOptions;
class CsgInfo;

int csgSampleK
(
    const CsgProduct             &product,
    const CsgOptions             &options,
          CsgInfo                &info
);

int csgSampleK
(
    const CsgSubtractionSequence &objects,
    const CsgProduct             &product,
    const CsgOptions             &options,
          CsgInfo                &info
);

#endif
