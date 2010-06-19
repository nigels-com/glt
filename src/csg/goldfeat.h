#ifndef CSG_GOLDFEAT_H
#define CSG_GOLDFEAT_H

/** \file
 *  \brief   Goldfeather CSG Rendering Algorithm
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

/** \brief Goldfeather CSG Rendering Algorithm
 *
 *  This module is an OpenGL/C++ implementation
 *  of the following journal article:
 *
 *  "Near Real-Time CSG Rendering Using Tree Normalisation
 *  "and Geometric Pruning", Jack Goldfeather, et. al.
 *  IEEE Computer Graphics and Applications, May 1989, pp 20-28
 *
 *  \ingroup Goldfeather
 *  \param sum  CSG Tree in sum-of-products form
 *  \param copy Z-Buffer management strategy
 */

class CsgSumOfProducts;
class CsgOptions;
class CsgInfo;

void csgRenderGoldfeather
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &info
);

#endif
