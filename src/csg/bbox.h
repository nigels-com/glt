#ifndef CSG_BBOX_H
#define CSG_BBOX_H

/** \file
 *  \brief   Bounding box logic and drawing
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

class GltShape;
class CsgProduct;
class CsgOverlapGraph;

void boundingBoxDraw(const GltShape &shape);
bool boundingBoxAdjency(CsgOverlapGraph &graph,const CsgProduct &prod);
bool boundingBoxAdjency(CsgOverlapGraph &graph,const CsgProduct &prod,const unsigned int i);

bool ringAdjency(CsgOverlapGraph &graph,const CsgProduct &prod);

#endif
