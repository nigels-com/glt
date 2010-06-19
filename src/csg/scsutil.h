#ifndef CSG_SCSUTIL_H
#define CSG_SCSUTIL_H

/** \file
 *  \brief   SCS Utility Routines
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <iosfwd>

class CsgProduct;
class CsgOverlapGraph;

/// Export to dot
void exportDot(std::ostream &os,const CsgOverlapGraph &graph,const CsgProduct &prod,const bool artBold,const bool all);

/// Export to LaTeX table
void exportTable(std::ostream &os,const CsgOverlapGraph &graph,const CsgProduct &prod);

#endif

