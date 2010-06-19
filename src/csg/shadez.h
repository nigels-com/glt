#ifndef CSG_SHADEZ_H
#define CSG_SHADEZ_H

/** \file
 *  \brief   Z-Buffer Shading and Lighting
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

class CsgOptions;
class CsgProduct;
class CsgSumOfProducts;

void csgRenderLightShadeZBuffer
(
    const CsgProduct &product,
    const CsgOptions &options
);

void csgRenderLightShadeZBuffer
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options
);

#endif

