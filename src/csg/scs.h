#ifndef CSG_SCS_H
#define CSG_SCS_H

/*!
    \file
    \brief   Sequenced Convex Subtraction (SCS) CSG Rendering Algorithm
    \ingroup CSG

    The Sequenced Convex Subtraction CSG Rendering Algorithm is
    described in the following papers:

    "A CSG Rendering Algorithm for Convex Objects"
    N. Stewart, G. Leach, S. John,
    The 8-th International Conference in Central Europe on Computer Graphics,
    Visualisation and Interactive Digital Media '2000 - WSCG 2000,
    Volume II, pp. 369-372

    "Linear-Time CSG Rendering of Intersected Convex Objects"
    N. Stewart, G. Leach, S. John,
    The 10-th International Conference in Central Europe on
    Computer Graphics, Visualization and Computer Vision'2002 - WSCG 2002,
    Volume II, pp. 437-444

   \author  Nigel Stewart (nigels@nigels.com)
*/

#include <csg/scsseq.h>

class CsgSumOfProducts;
class CsgProduct;
class CsgOptions;
class CsgInfo;

/*!
    \brief      Sequenced Convex Subtraction (SCS) CSG Rendering Algorithm
    \ingroup    CSG

    \param      sumOfProducts CSG Tree in sum-of-products form
    \param      options       CSG Rendering configuration options
*/

void csgRenderSequencedConvexSubtraction
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &info
);

void csgRenderSubtractionSequence
(
    const CsgProduct             &product,
    const CsgOptions             &options,
          CsgSubtractionSequence &sequence,
          CsgInfo                &info
);

#endif
