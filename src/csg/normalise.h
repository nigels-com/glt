#ifndef CSG_NORMALIS_H
#define CSG_NORMALIS_H

/** \file
 *  \brief   CSG Tree Normalisation
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <csg/node.h>
#include <csg/element.h>

CsgSumOfProducts normalise(const GltShapePtr &shape);

#endif
