#ifndef CSG_INTERSCT_H
#define CSG_INTERSCT_H

/** \file
 *  \brief   Intersection test for two GltShapes
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

class GltShape;

typedef enum
{
    DISJOINT = 0,
    INTERSECTION,
    SHARED_FACE
}
CsgIntersectionType;

CsgIntersectionType intersectShapes
(
    const GltShape &a,
    const GltShape &b,
    const CsgIntersectionType ifUnknown = INTERSECTION
);

#endif
