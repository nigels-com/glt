#include "bbox.h"

#include <csg/graph.h>
#include <csg/node.h>
#include <csg/intersct.h>

#include <glt/error.h>
#include <glt/matrix.h>
#include <glt/rgb.h>

#include <node/shape.h>
#include <node/shapes.h>

#include <math/vector3.h>
#include <math/plane.h>

#include <misc/timer.h>

#include <glutm/shape.h>

#include <vector>
#include <iostream>
using namespace std;

//

void boundingBoxDraw(const GltShape &shape)
{
    const GltShapes *shapes = dynamic_cast<const GltShapes *>(&shape);
    const CsgNode   *node   = dynamic_cast<const CsgNode *>  (&shape);

    if (shapes || node)
    {
        // If the shape is a container, draw all children
        // relative to it's transformation.

        GltPushMatrix push(!shape.transformation().isIdentity());
        shape.transformation().glMultMatrix();

        GLERROR

        if (shapes)
            for (unsigned int i=0; i<shapes->size(); i++)
                boundingBoxDraw(*(*shapes)[i].get());

        if (node)
        {
            boundingBoxDraw(*node->left().get());
            boundingBoxDraw(*node->right().get());
        }
    }
    else
    {
        // If the shape is not a container, and a bounding
        // box is available, draw the bounding box in wireframe.

        BoundingBox box;
        shape.boundingBox(box);
        if (box.defined())
        {
            GlutCube cube(false,box.min(),box.max());
            cube.color() = grey70;
            cube.draw();
        }
    }
}

bool boundingBoxAdjency(CsgOverlapGraph &graph,const CsgProduct &prod)
{
    // Output execution time for debugging

    #ifndef NDEBUG
    cout << "boundingBoxAdjency() ";
    Timer timer(cout);
    #endif

    // Size of matrix
    const unsigned int n = prod.size();

    // Resize and reset the adjacency matrix
    graph = CsgOverlapGraph(n);

    // Check every pair of elements in product
    for (unsigned int i=0; i<n; i++)
        for (unsigned int j=i+1; j<n; j++)
        {
            // First check bounding boxes, if they intersect,
            // do specific tests...
            if (prod[i].box().intersects(prod[j].box()))
                if (intersectShapes(*prod.shape(i),*prod.shape(j),INTERSECTION)!=DISJOINT)
                    graph.set(i,j,true);
        }

    return true;
}

bool boundingBoxAdjency(CsgOverlapGraph &graph,const CsgProduct &prod,const unsigned int i)
{
    // Output execution time for debugging

    #ifndef NDEBUG
    cout << "boundingBoxAdjency() i=" << i;
    Timer timer(cout);
    #endif

    // Size of matrix
    const unsigned int n = prod.size();

    // Check that i is in range
    if (i>n || i<0)
        return false;

    // Clear the i'th row and column
    graph.clear(i);

    for (unsigned int j=0; j<n; j++)
        if (i!=j)
            if (prod[i].box().intersects(prod[j].box()))
                if (intersectShapes(*prod.shape(i),*prod.shape(j),INTERSECTION)!=DISJOINT)
                    graph.set(i,j,true);

    return true;
}

bool ringAdjency(CsgOverlapGraph &graph,const CsgProduct &prod)
{
    // Output execution time for debugging

    #ifndef NDEBUG
    cout << "ringAdjency() ";
    Timer timer(cout);
    #endif

    // Size of matrix
    const unsigned int n = prod.size();

    // Resize and reset the adjacency matrix
    graph = CsgOverlapGraph(n);

    // For CSGToolpath.txt from Michele Ribaudo of Twintec
    // a custom adjaceny matrix for testing purposes.

    for (unsigned int i=0; i<n; i++)
    {
        if (i==0)
            for (unsigned int j=i+1; j<n; j++)
                graph.set(i,j,true);
        else
        {
            graph.set(i,i-1,true);
            graph.set(i,(i+1)%(n-1),true);
        }
    }

    return true;
}
