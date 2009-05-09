#ifndef CSG_GRAPH_H
#define CSG_GRAPH_H

/** \file
 *  \brief   Adjacency graph class
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 *  \todo    Make use of matrix, sparse and symmetric
 */

#include <csg/sparse.h>
#include <math/plane.h>

#include <vector>
#include <iosfwd>
#include <string>

class CsgOverlapGraph
{
public:
    //
    // Constructor/Destructor
    //

    CsgOverlapGraph(const unsigned int n = 0);
    CsgOverlapGraph(const CsgOverlapGraph &graph);
    ~CsgOverlapGraph();

    CsgOverlapGraph &operator=(const CsgOverlapGraph &graph);

    unsigned int size() const;
    bool get(const unsigned int i,const unsigned int j) const;
    void set(const unsigned int i,const unsigned int j,const bool val);
    void clear();
    void clear(const unsigned int i);

    template<class I>
    void clear(const I &begin,const I &end)
    {
        _touching.clear(begin,end);
    }

    typedef std::vector<unsigned int> uintv;
    typedef std::vector<bool>         boolv;

    /// Locate subgraphs of one node (no adjacencies)
    bool orphanNodes (uintv &nodes,boolv &processed) const;

    /// Search for nodes with only one adjacency
    bool leafNodes   (uintv &nodes,boolv &processed) const;

    /// Search for nodes connected as a ring
    bool ringSubgraph(uintv &nodes,boolv &processed) const;

    /// Search for connected subgraph
    bool subgraph    (uintv &nodes,boolv &processed) const;

    /// Articulation points
    void articulationPoints(uintv &nodes) const;

    /// Print table
    void print(std::ostream &os) const;

    /// Print table (string version)
    void print(std::string &str) const;

protected:

    void         articulationPoints(uintv &nodes,const unsigned int i) const;
    unsigned int articulationPoints(uintv &nodes,uintv &val,const unsigned int id,const unsigned int i) const;

private:
    unsigned int _n;

    sparse_matrix<bool>  _touching;
    sparse_matrix<Plane> _shared;
};

#endif
