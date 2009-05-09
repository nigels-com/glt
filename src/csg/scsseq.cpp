#include "scsseq.h"

/** \file
 *  \brief SCS (Sequenced Convex Subtraction) Sequence Generation
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 *  \author  RMIT School of Computer Science and Information Technology, Australia
 */

#include <csg/element.h>
#include <csg/graph.h>
#include <csg/scs.h>
#include <csg/scsk.h>
#include <csg/options.h>
#include <csg/info.h>

#include <node/shape.h>
#include <node/shapes.h>

#include <misc/timer.h>

#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

// Define this for info
//#define DEBUG_SCS

// Define this to print subtraction sequences
//#define DEBUG_SCS_SEQUENCE

//

#if defined(NDEBUG) && defined(DEBUG_SCS)
#undef DEBUG_SCS
#endif

#if defined(NDEBUG) && defined(DEBUG_SCS_SEQUENCE)
#undef DEBUG_SCS_SEQUENCE
#endif

//
//
//
//   S   E   Q   U   E   N   C   E    G  E  N  E  R  A  T  I  O  N
//
//
//

//
// Internal routines
//

/// Generate subtraction for ring topology, given n and k
CsgSubtractionSequence gscsSequenceRing(const unsigned int n, const unsigned int k = -1);

/// Generate subtraction sequence from cyclic adjacency table
CsgSubtractionSequence gscsSequenceCyclic(const CsgOverlapGraph &adj);


//
// Generate subtraction sequence, given n and k
//
// Length of this subtraction sequence in the worst case is n^2 - n + 1
//

CsgSubtractionSequence gscsSequence(const unsigned int n, const unsigned int k)
{
    // Best known subtraction sequences

    static const uint32 bestSequences = 8;
    static const char *bestSequence[bestSequences][bestSequences] =
    {
        { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },  // n=0
        { NULL, "a",  NULL, NULL, NULL, NULL, NULL, NULL },  // n=1
        { NULL, "ab", "aba",NULL, NULL, NULL, NULL, NULL },  // n=2

        // n=3
        {
            NULL,
            "abc",
            "abcab",
            "abcabac",
            NULL, NULL, NULL, NULL
        },

        // n=4
        {
            NULL,
            "abcd",
            "abcdabc",
            "abcdabcabd",
            "abcdabcadbac",
            NULL, NULL, NULL
        },

        // n=5
        {
            NULL,
            "abcde",
            "abcdeabcd",
            "abcdeabcdabce",
            "abcdeabcdabecabd",
            "abcdeabcdaebcadbcea",
            NULL, NULL
        },

        // n=6
        {
            NULL,
            "abcdef",
            "abcdefabcde",
            "abcdefabcdefabcd",
            NULL, NULL, NULL, NULL
        },

        // n=7
        {
            NULL,
            "abcdefg",
            "abcdefgabcdef",
            NULL, NULL, NULL, NULL, NULL
        }
    };

    // Check sanity of parameters.

    assert(k<=n);
    assert(n>=0);
    assert(k>=0);

    // Use the best-known sequence if available

    if (n<bestSequences && k<bestSequences && bestSequence[n][k])
    {
        CsgSubtractionSequence tmp;
        for (const char *i = bestSequence[n][k]; *i!='\0'; i++)
            tmp.push_back(*i-'a');
        return tmp;
    }

    // Use Galbiati if possible

    if (n>=4 && k==n)
        return gscsSequenceGalbiati(n);

    // Use Savage, if possible

    if (n>=3 && k>=3)
        return gscsSequenceSavage(n,k);

    // Use n^2-n+1 sequence if necessary

    CsgSubtractionSequence tmp;
    tmp.reserve(n*n-n+1);

    //

    for (unsigned int i=0; i<k; i++)
        for (unsigned int j=0; j<n; j++)
            if (i==0 || j>0)
                tmp.push_back( (i%2)==0 ? j : n-1-j );

    return tmp;
}

//
// Length of this subtraction sequence is n^2 - 2n + 4
//
// L. Adleman, Short Permutation Strings,
// Discrete Mathematics, Vol. 10, 1974, pp. 197-200
//

CsgSubtractionSequence gscsSequenceAdleman(const unsigned int n)
{
    // n must be at least 3
    assert(n>=3);
    if (n<3)
        return CsgSubtractionSequence();

    // Storage for generated sequence.

    CsgSubtractionSequence tmp;
    tmp.reserve(n*n-2*n+4);

    // The sequence begins with the n'th symbol
    tmp.push_back(n-1);

    // Repeat the string abcd..abcd..
    // With the n'th symbol inserted after
    // the i'th occurance of the symbol n-i
    // where 1 <= i <= n-2

    const unsigned int size = n*n-3*n+4;

    unsigned int k=n-2;
    for (unsigned int i=0; i<size; i++)
    {
        const unsigned int j = i%(n-1);
        tmp.push_back(j);

        // Insert the n'th symbol

        if (j==k && k>0)
        {
            tmp.push_back(n-1);
            k--;
        }
    }

    // The sequence ends with the n'th symbol
    tmp.push_back(n-1);

    return tmp;
}

//
// Length of this subtraction sequence is n^2 - 2n + 4
//
// G. Galbiati, F.P. Preparata, On Permutation-Embedding Sequences,
// SIAM J. Appl. Math., Vol. 30, No. 3, May 1976, pp. 421-423
//

CsgSubtractionSequence gscsSequenceGalbiati(const unsigned int n)
{
     // n must be at least 4

    assert(n>=4);
    if (n<4)
        return CsgSubtractionSequence();

    // Storage for generated sequence.

    CsgSubtractionSequence tmp;
    tmp.reserve(n*n-2*n+4);

    // Galbiati uses four arbitrary elements: 1,2,3,4
    // We use zero as base: 0,1,2,3

    tmp.push_back(1);
    tmp.push_back(0);
    tmp.push_back(2);

    // Append each segment

    const unsigned int V[3] = { 1,2,3 };
    unsigned int v = 2;

    for (unsigned int i=0; i<n-1; i++)
    {
        // Append U

        for (unsigned int j=4; j<n; j++)
            tmp.push_back(j);

        // Append next element in V
        tmp.push_back(V[v++%3]);
        tmp.push_back(0);
        tmp.push_back(V[v++%3]);
    }

    return tmp;
}

//
// Length of this subtraction sequence is kn - 2k + 4
//
// Short Strings Containing all k-element Permutations,
// Carla Savage, Discrete Mathematics, Vol. 42, 1982, pp. 281-285
//

CsgSubtractionSequence gscsSequenceSavage(const unsigned int n, const unsigned int k)
{
    // n and k must be at least 3

    assert(n>=3 && k>=3);
    if (n<3 || k<3)
        return CsgSubtractionSequence();

    // Storage for generated sequence.

    CsgSubtractionSequence tmp;
    tmp.reserve(k*n-2*k+4);

    // The n elements are partitioned into two
    // sets: A = ab..x_{k-1}, B = x_{k}..x_{n}

    // The sequence begins with B
    unsigned int m;
    for (m=k-1; m<n; m++)
        tmp.push_back(m);

    // Repeat the string AA..
    // With the B symbol inserted after
    // the i'th occurance of the symbol n-i
    // where 1 <= i <= k-2

    const unsigned int size = k*k-3*k+4;

    unsigned int p=k-2;
    for (unsigned int i=0; i<size; i++)
    {
        const unsigned int j = i%(k-1);
        tmp.push_back(j);

        // Insert B

        if (j==p && p>0)
        {
            for (m=k-1; m<n; m++)
                tmp.push_back(m);
            p--;
        }
    }

    // The sequence ends with B
    for (m=k-1; m<n; m++)
        tmp.push_back(m);

    return tmp;
}

CsgSubtractionSequence gscsSequenceRing(const unsigned int n, const unsigned int k)
{
    static const uint32 ringSequences = 11;

    static const char *ringSequence[ringSequences] =
    {
                                                    // n
        "",                                         // 0
        "a",                                        // 1
        "aba",                                      // 2
        "abcabca",                                  // 3
        "abcdcbadbc",                               // 4
        "abcdedcbaedbcd",                           // 5
        "abcbdaefdcebabecdf",                       // 6
        "abcdbaefgfedabcbadfegf",                   // 7
        "abcdedcbafghagdfbcedcbfahg",               // 8
        "abcdefgedcbhiaibhcgdfedcbfgaih",           // 9
        "abcdefghgfiedcbajaighfedcbacdjefhgi",      // 10
    };

    // Limitations: Depth complexity information not utilised

    CsgSubtractionSequence tmp;

    if (n<ringSequences)
    {
        // Use the best-known sequence if available

        #ifdef DEBUG_SCS
        if (n>1)
        {
            cout << "Using ring sequence for n=" << n;
            cout << ": " << ringSequence[n] << endl;
        }
        #endif

        for (const char *i = ringSequence[n]; *i!='\0'; i++)
            tmp.push_back(*i-'a');
    }
    else
    {
        // Create 4n-2 subtraction sequence, as needed

        uint32 i;
        for (i=0; i<n+n-1; i++)
            tmp.push_back(i%n);
        for (i=3; i<n+n-1; i++)
            tmp.push_back((2*n-i)%n);
    }

    return tmp;

}

//
// Generate subtraction sequence, given an adjacency graph
//

CsgSubtractionSequence gscsSequence
(
    const CsgProduct &prod,
    const CsgOptions &options,
          CsgInfo    &info
)
{
    // Collect sequence encoding time

    Timer timer;

    // Create a working copy of the adjacency graph
    // for further processing.

    CsgOverlapGraph graph = prod.graph();

    assert(graph.size());

    // Elements that have been processed are flagged

    vector<bool> processed;

    //
    // P H A S E   1  -  P R E P A R E   G R A P H
    //

    {
        const vector<bool> intersected = prod.intersected();

        processed = intersected;

        //
        // Check that all intersected objects intersect each other
        // If not, the CSG result will be empty
        //

        {
            for (unsigned int i=0; i<prod.size(); i++)
                for (unsigned int j=i+1; j<prod.size(); j++)
                    if (intersected[i] && intersected[j] && !graph.get(i,j))
                        return CsgSubtractionSequence();
        }

        //
        // Subtracted objects that don't touch all intersected
        // objects can be omitted.
        //

        {
            #ifdef DEBUG_SCS
            bool first = true;
            #endif

            // For each subtracted object, i

            for (unsigned int i=0; i<prod.size(); i++)
            {
                if (intersected[i])
                    continue;

                // For each intersected object, j

                for (unsigned int j=0; j<prod.size(); j++)
                    if (intersected[j] && !graph.get(i,j))
                    {
                        // If i is not touching j then
                        // erase i from graph and mark
                        // it as processed

                        graph.clear(i);
                        processed[i] = true;

                        // For debugging, list omitted
                        // objects

                        #ifdef DEBUG_SCS
                        if (first)
                        {
                            first = false;
                            cout << "Omitting ";
                        }
                        cout << prod.shape(i)->name() << ' ';
                        #endif

                        // Break out of loop of intersected objects

                        break;
                    }
            }

            // For debugging, end list of omitted
            // objects

            #ifdef DEBUG_SCS
            if (!first)
                cout << endl;
            #endif
        }

        //
        // Remove intersected objects from the graph
        // Subtraction sequences do not involve the
        // non-subtracted items.
        //

        {
            for (unsigned int i=0; i<prod.size(); i++)
                if (intersected[i])
                    graph.clear(i);
        }


        // Debugging feature: limit number of subtractions
        // by erasing subsequent non-intersected items.
        // If maxSubtract is -1, all subtractions will be
        // considered

        if (options.limitSubtractions>=0)
        {
            unsigned int i = 0;
            unsigned int j = 0;

            // Skip the allowed subtractions

            for (; i<prod.size() && j<(unsigned int)(options.limitSubtractions); i++)
                if (!intersected[i] && !processed[i])
                    j++;

            // Disable subsequent subtractions

            for (;i<prod.size(); i++)
                if (!intersected[i])
                {
                    graph.clear(i);
                    processed[i] = true;
                }
        }
    }

    //
    // P H A S E   2  -  S E Q U E N C E  E N C O D I N G
    //

    // LEAF NODES
    //
    // Identify leaf nodes in the graph until there are no
    // more.  Leaf nodes are those with only one edge.
    // Nodes trimmed in one pass may uncover further leaves
    // for subsequent passes.

    CsgSubtractionSequence leaf;
    leaf.reserve(graph.size());

    for(;;)
    {
        // Query graph for leaf nodes

        CsgSubtractionSequence trim;
        graph.leafNodes(trim,processed);

        // Give up if no (more) leaves found

        if (!trim.size())
            break;

        // Remove leaf nodes from graph

        graph.clear(trim.begin(),trim.end());

        // Combine leaf nodes into list from outside to inside

        leaf.insert(leaf.end(),trim.begin(),trim.end());

        #ifdef DEBUG_SCS
        cout << "Found " << trim.size() << " leaf nodes." << endl;
        #endif
    }

    // RING SUBGRAPHS
    //
    // Identify ring subgraphs until there are no more.

    CsgSubtractionSequence ringSequence;
    ringSequence.reserve(graph.size());

    for(;;)
    {
        // Query graph for ring subgraph

        CsgSubtractionSequence ring;
        graph.ringSubgraph(ring,processed);

        // Give up if no (more) ring subgraphs found

        if (!ring.size())
            break;

        // Remove ring nodes from graph

        graph.clear(ring.begin(),ring.end());

        // Encode each ring subgraph and remap it according to
        // the inolved nodes

        CsgSubtractionSequence seq = gscsSequenceRing(ring.size(),ring.size());
        gscsRemapSequence(seq,ring);

        // Combine encoded ring sequences

        ringSequence.insert(ringSequence.end(),seq.begin(),seq.end());

        #ifdef DEBUG_SCS
        cout << "Found ring of size " << ring.size() << endl;
        #endif
    }

    // SUBGRAPHS
    //
    // Identify subgraphs until there are no more.

    CsgSubtractionSequence subgraphSequence;
    subgraphSequence.reserve(graph.size());

    for(;;)
    {
        // Query graph for subgraph

        CsgSubtractionSequence subgraph;
        graph.subgraph(subgraph,processed);

        // Give up if no (more) subgraphs found

        if (subgraph.size()==0)
            break;

        #ifdef DEBUG_SCS
        cout << "Subgraph of size " << subgraph.size() << endl;
        #endif

        // Remove subgraph nodes from graph

        graph.clear(subgraph.begin(),subgraph.end());

        // Sample depth complexity k, if necessary

        unsigned int k = subgraph.size();
        if (options.sampleDepthComplexity && subgraph.size()>1)
        {
            info.encodeTime += timer.clock();

            #ifdef DEBUG_SCS
            cout << " encodeTime += " << timer.clock() << " -> " << info.encodeTime << endl;
            #endif

            k = csgSampleK(subgraph,prod,options,info);

            timer.start();
        }

        // Sometimes we'll get k>n because of stray
        // (incorrect) pixels in depth complexity
        // sampling algorithm.  Make sure k is n at
        // most.

        k = clamp<unsigned int>(k,0,subgraph.size());

        #ifdef DEBUG_SCS
        cout << "  k = " << k << endl;
        #endif

        // Encode each subgraph according to O(kn)
        // subtraction sequence

        CsgSubtractionSequence seq = gscsSequence(subgraph.size(),k);
        gscsRemapSequence(seq,subgraph);

        // Combine encoded subgraph sequences

        subgraphSequence.insert(subgraphSequence.end(),seq.begin(),seq.end());

        // Do some debugging

        #ifdef DEBUG_SCS_SEQUENCE
        cout << "Subgraph sequence:" << seqenceString(subgraphSequence,prod) << endl;
        #endif
    }

    // Check that everything has been processed

    #ifndef NDEBUG
    for (unsigned int i=0; i<graph.size(); i++)
        assert(processed[i]==true);
    #endif

    //
    // P H A S E   3  -  C O M B I N E D  S E Q U E N C E
    //

    CsgSubtractionSequence seq;
    seq.insert(seq.end(),leaf.begin()            ,leaf.end()            );
    seq.insert(seq.end(),ringSequence.begin()    ,ringSequence.end()    );
    seq.insert(seq.end(),subgraphSequence.begin(),subgraphSequence.end());

    reverse(leaf.begin(),leaf.end());
    seq.insert(seq.end(),leaf.begin()            ,leaf.end()            );

    seq = gscsSequenceOptimise(seq);

    #ifdef DEBUG_SCS
    cout << "Subtraction sequence size: " << seq.size() << endl;
    #endif

    // Record the total encoding time

    info.encodeTime += timer.clock();

    #ifdef DEBUG_SCS
    cout << " encodeTime += " << timer.clock()   << endl;
    cout << " encodeTime  = " << info.encodeTime << endl;
    #endif

    return seq;
}

CsgSubtractionSequence gscsSequenceCyclic(const CsgOverlapGraph &adj)
{
    CsgSubtractionSequence seq;
    return seq;
}

//
// Remap sequence
//

bool gscsRemapSequence(CsgSubtractionSequence &sequence,const std::vector<unsigned int> &remap)
{
    for (unsigned int i=0; i<sequence.size(); i++)
    {
        if (sequence[i]<0 || sequence[i]>=remap.size())
            return false;

        sequence[i] = remap[sequence[i]];
    }

    return true;
}

bool gscsRemapSequence(CsgSubtractionSequence &sequence,const CsgProduct &product)
{
    vector<unsigned int> remap;

    for (unsigned int i=0; i<product.size(); i++)
        if (!product.positive(i))
            remap.push_back(i);

    return gscsRemapSequence(sequence,remap);
}

bool gscsNormalise(CsgSubtractionSequence &sequence)
{
    unsigned int n=0;

    for (unsigned int i=0; i<sequence.size(); i++)
        n = std::max(n,sequence[i]);

    vector<bool>          seen(n+1,false);
    vector<unsigned int>  remap(n+1);
    n = 0;

    for (unsigned int j=0; j<sequence.size(); j++)
    {
        unsigned int &x = sequence[j];

        if (!seen[x])
        {
            remap[x] = n++;
            seen[x] = true;
        }

        x = remap[x];
    }

    return true;
}

CsgSubtractionSequence gscsSequenceOptimise(const CsgSubtractionSequence &sequence)
{
    CsgSubtractionSequence tmp;
    tmp.reserve(sequence.size());

    for (unsigned int i=0; i<sequence.size(); i++)
    {
        if (i>0 && sequence[i]==sequence[i-1])
            continue;

        tmp.push_back(sequence[i]);
    }

    return tmp;
}

//
// Write sequence to stream
//

string seqenceString(const CsgSubtractionSequence &seq,const CsgProduct &prod)
{
    string tmp;

    char buffer[1024];
    sprintf(buffer,"%d: ",int(seq.size()));
    tmp += buffer;

    for (unsigned int i=0; i<seq.size(); i++)
        tmp += prod.shape(seq[i])->name() + ' ';

    return tmp;
}

string seqenceString(const CsgSubtractionSequence &seq)
{
    string tmp;
    tmp.resize(seq.size()+1);

    for (unsigned int i=0; i<seq.size(); i++)
        if (seq[i]<'z'-'a')
            tmp[i] = seq[i]+'a';
        else
            tmp[i] = '?';

    return tmp;
}
