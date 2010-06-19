#ifndef CSG_GOLDLAY2_H
#define CSG_GOLDLAY2_H

/*! \file
 *  \brief   Improved Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *
 *  Based on the the Layered Goldfeather algorithm,
 *  stencil buffers are saved of intermediate parity
 *  testing results, rather than clipped z-buffer
 *  surfaces which are later merged.
 *
 *  "General Purpose Z-Buffer CSG Rendering with
 *  Consumer Level Hardware"
 *  G. Erhart, R. F. Tobler
 *  VRVis Technical Report 2000 003
 *  VRVis Zentrum für Virtual Reality und Visualisierung Forschungs-GmbH
 *
 *  \ingroup CSG
 */

class CsgSumOfProducts;
class CsgOptions;
class CsgInfo;

/*!
 *  \brief  Improved Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup    CSG
 *  \author Nigel Stewart (nigels.com@gmail.com)
 *  \param  sumOfProducts  CSG Tree in sum-of-products form
 *  \param  options        Rendering options
 *  \param  info           Runtime statistics info
 */

void csgRenderGoldfeatherLayeredImproved
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &info
);

#endif
