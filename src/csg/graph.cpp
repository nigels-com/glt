#include "graph.h"

#include <set>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

CsgOverlapGraph::CsgOverlapGraph(const unsigned int n)
: _n(n), _touching(n,false), _shared(n)
{
}

CsgOverlapGraph::CsgOverlapGraph(const CsgOverlapGraph &graph)
: _n(graph._n), _touching(graph._touching), _shared(graph._shared)
{
}

CsgOverlapGraph::~CsgOverlapGraph()
{
}

CsgOverlapGraph &
CsgOverlapGraph::operator=(const CsgOverlapGraph &graph)
{
    _n        = graph._n;
    _touching = graph._touching;
    _shared   = graph._shared;
    return *this;
}

unsigned int
CsgOverlapGraph::size() const
{
    return _n;
}

bool
CsgOverlapGraph::get(const unsigned int i,const unsigned int j) const
{
    return _touching.get(i,j);
}

void
CsgOverlapGraph::set(const unsigned int i,const unsigned int j,const bool val)
{
    _touching.set(i,j,val);
    _touching.set(j,i,val);
}

void
CsgOverlapGraph::clear()
{
    _touching.clear();
}

void
CsgOverlapGraph::clear(const unsigned int i)
{
    _touching.clear(i);
}

bool
CsgOverlapGraph::orphanNodes(uintv &nodes,boolv &processed) const
{
    assert(processed.size()==_n);

    nodes.clear();
    nodes.reserve(_n);

    // If there are no adjacencies for a row/column it is orphaned

    boolv::iterator j = processed.begin();

    for (unsigned int i=0; i<_n; i++,j++)
        if (!*j && _touching.rowSize(i)==0)
        {
            *j = true;
            nodes.push_back(i);
        }

    return true;
}

bool
CsgOverlapGraph::leafNodes(uintv &nodes,boolv &processed) const
{
    assert(processed.size()==_n);

    nodes.clear();
    nodes.reserve(_n);

    // If there is one adjacency for a row/column it is a leaf

    boolv::iterator j = processed.begin();

    for (unsigned int i=0; i<_n; i++,j++)
        if (!*j && _touching.rowSize(i)==1)
        {
            *j = true;
            nodes.push_back(i);
        }

    return true;
}

bool
CsgOverlapGraph::ringSubgraph(uintv &nodes,boolv &processed) const
{
    assert(processed.size()==_n);

    nodes.clear();
    nodes.reserve(_n);

    // Search for starting node with two adjacencies

    for (unsigned int i=0; i<_n; i++)
        if (!processed[i] && _touching.rowSize(i)==2)
        {
            nodes.clear();                                          // Reset the ring
            nodes.push_back(i);                                     // Push the start position
            nodes.push_back(_touching.getRow(i).begin()->first);    // Push the next position

            unsigned int j=1;

            while (!processed[nodes[j]] && _touching.rowSize(nodes[j])==2)
            {
                // Find the next two choices

                const map<unsigned int,bool>                 &row = _touching.getRow(nodes[j]);
                      map<unsigned int,bool>::const_iterator  k   = row.begin();

                assert(row.size()==2);

                // Select the unvisited node

                if (k->first!=nodes[j-1])
                    nodes.push_back(k->first);
                else
                {
                    ++k;
                    nodes.push_back(k->first);
                }

                // Check if we've found a ring

                if (nodes.front()==nodes.back())
                    break;
                else
                    j++;
            }

            if (nodes.front()==nodes.back())
            {
                // Remove tail entry
                nodes.erase(nodes.end()-1,nodes.end());

                // Mark everything in the ring as processed
                for (unsigned int k=0; k<nodes.size(); k++)
                    processed[nodes[k]] = true;

                return true;
            }
        }

    // Didn't find anything suitable

    nodes.clear();
    return false;
}

bool
CsgOverlapGraph::subgraph(uintv &nodes,boolv &processed) const
{
    assert(processed.size()==_n);
    nodes.clear();
    nodes.reserve(_n);

    //

    list<unsigned int> pending;      // Nodes waiting for processing

    // Look for any unprocessed node

    for (unsigned int i=0; i<_n; i++)
        if (!processed[i])
        {
            // We're going to traverse
            // all nodes connected to the i'th

            pending.push_back(i);

            // Inner Loop: consume queued nodes

            while (pending.size())
            {
                // Pop the front item

                unsigned int j = pending.front();
                pending.erase(pending.begin(),++pending.begin());

                // Stop if it's been visited already

                if (processed[j])
                    continue;

                nodes.push_back(j);
                processed[j] = true;

                // Queue all unprocessed adjacent nodes
                // for traversal

                const map<unsigned int,bool>                 &row = _touching.getRow(j);
                      map<unsigned int,bool>::const_iterator  k   = row.begin();

                while (k!=row.end())
                {
                    const unsigned int &a = k->first;
                    if (!processed[a])
                        pending.push_back(a);
                    k++;
                }
            }

            return true;
        }

    return false;
}

// Based on R. Sedgewick - "Algorithms in C++", page 440

void
CsgOverlapGraph::articulationPoints(uintv &nodes) const
{
    for (unsigned int i=0; i<size(); i++)
        articulationPoints(nodes,i);
}

void
CsgOverlapGraph::articulationPoints(uintv &nodes,const unsigned int i) const
{
    uintv val(size(),0);
    articulationPoints(nodes,val,0,i);
}

unsigned int
CsgOverlapGraph::articulationPoints
(
    uintv &nodes,
    uintv &val,
    const unsigned int id,
    const unsigned int i
) const
{
    bool found = false;
    unsigned int  children = 0;

    unsigned int min = val[i] = id+1;

    // Visit all adjacencies of node i

    const map<unsigned int,bool>                 &row = _touching.getRow(i);
          map<unsigned int,bool>::const_iterator  j   = row.begin();

    for (; j!=row.end(); j++)
    {
        const unsigned int k = j->first;

        if (val[k]!=0)
            min = std::min(min,val[k]);
        else
        {
            children++;
            const unsigned int m = articulationPoints(nodes,val,val[i],k);
            min = std::min(min,m);
            if (m>=val[i])
                found = true;
        }
    }

    // val[i]==1 for the root

    if ((val[i]>1 && found) || (val[i]==1 && children>1))
        if (find(nodes.begin(),nodes.end(),i)==nodes.end())
            nodes.push_back(i);

    return min;
}

void
CsgOverlapGraph::print(ostream &os) const
{
    string str;
    print(str);
    os << str;
}

void
CsgOverlapGraph::print(string &str) const
{
    if (_n==0)
    {
        str = string();
        return;
    }

    // Resize the string to the right size
    str.resize(_n*(_n+1)-1);

    // Use i to iterate through the string
    unsigned int i=0;

    for (unsigned int y=0; y<_n; y++)
    {
        if (y>0)
            str[i++] = '\n';

        for (unsigned int x=0; x<_n; x++)
            if (x==y)
                str[i++]= '.';
            else
                str[i++]= (get(x,y) ? 'X' : '.');
    }

    // Check that we didn't go out of bounds
    assert(i==str.size());
}
