#include "scsutil.h"

//
// OpenGL CSG Rendering
//
// Nigel Stewart (nigels@nigels.com)
// RMIT Department of Mechanical and Manufacturing Engineering
//
// SCS Utility Routines
//

/** \file
 *  \brief   SCS Utility Routines
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <csg/scs.h>
#include <csg/scsseq.h>
#include <csg/graph.h>
#include <csg/element.h>

#include <iostream>
#include <algorithm>
using namespace std;

//
// Dot tool: http://www.research.att.com/sw/tools/graphviz/
//

void exportDot(ostream &os,const CsgOverlapGraph &graph,const CsgProduct &prod,const bool artBold,const bool all)
{
    //
    // Find articulation points in all sub-graphs
    //

    CsgSubtractionSequence art;

#if 0
    {
        for (int i=0; i<adj.size(); i++)
            adj.articulationPoints(art,i);
    }
#endif

    //
    // Output dot-graph
    //

    os << "Graph G {" << endl;

    os << '\t' << "size = \"3,3\";" << endl;

    for (unsigned int i=0; i<graph.size(); i++)
    {
#if 0
        if (!graph.rowSize(i) && !all)
            continue;
#endif

        const string name = prod.shape(i)->name();

        // Draw articulation points in bold
        if (artBold && find(art.begin(),art.end(),i)!=art.end())
            os << "\t" << name << " [style=bold];" << endl;

        os << name << " -- { ";

        for (unsigned int j=i+1; j<graph.size(); j++)
            if (graph.get(i,j))
                os << prod.shape(j)->name() << ' ';

        os << " }" << endl;
    }

    os << "}" << endl;
}

// Export LaTeX table

/*

    \begin{tabular}{|c|c c c c c|} \hline
        & X         & A         & B         & C         & D         \\ \hline
    X & $\bullet$ & $\bullet$ & $\bullet$ & $\bullet$ & $\bullet$ \\
    A & $\bullet$ & $\bullet$ & $\bullet$ &           &           \\
    B & $\bullet$ & $\bullet$ & $\bullet$ &           &           \\
    C & $\bullet$ &           &           & $\bullet$ & $\bullet$ \\
    D & $\bullet$ &           &           & $\bullet$ & $\bullet$ \\ \hline
    \end{tabular}
*/

void
exportTable(ostream &os,const CsgOverlapGraph &graph,const CsgProduct &prod)
{
    unsigned int i,j;
    const unsigned int n = graph.size();

    // Output tabular header

    os << "\\begin{tabular}{|c|";

    for (i=0; i<n; i++)
    {
        if (i!=0)
            os << ' ';
        os << 'c';
    }

    os << "|}\\hline" << endl;

    // Output first row

    os << "  ";

    for (i=0; i<n; i++)
        os << "& " << prod.shape(i)->name() << ' ';

    os << "\\\\ \\hline" << endl;

    // Output table

    for (i=0; i<n; i++)
    {
        os << prod.shape(i)->name() << ' ';

        for (j=0; j<n; j++)
            os << "& " << (i==j || graph.get(i,j) ? "$\\bullet$ " : "          ");

        os << "\\\\" << endl;
    }

    // Finish up

    os << "\\hline\\end{tabular}" << endl;
}

