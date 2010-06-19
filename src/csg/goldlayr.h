#ifndef CSG_GOLDLAYR_H
#define CSG_GOLDLAYR_H

/*! \file
 *  \brief   Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 *
 *  This algorithm is documented in detail in the
 *  following paper:
 *
 *  "An Improved CSG Rendering Algorithm"
 *  N. Stewart, G. Leach, S. John
 *  1998 Eurographics/Siggraph Graphics Hardware Workshop
 *  Lisbon, Portugal.
 *
 */

class CsgSumOfProducts;
class CsgOptions;
class CsgInfo;

/*!
 *  \brief  Layered Goldfeather CSG Rendering Algorithm
 *  \ingroup    CSG
 *  \author Nigel Stewart (nigels.com@gmail.com)
 *  \author RMIT School of Computer Science and Information Technology
 *  \author RMIT Department of Mechanical and Manufacturing Engineering
 *  \param  sumOfProducts  CSG Tree in sum-of-products form
 *  \param  options        Rendering options
 *  \param  info           Runtime statistics info
 */

void csgRenderGoldfeatherLayered
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options,
          CsgInfo          &info
);

#endif
