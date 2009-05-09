#include "scsk.h"

#include <glt/gl.h>
#include <glt/error.h>
#include <glt/countsrf.h>

#include <node/shapes.h>

#include <csg/element.h>
#include <csg/options.h>
#include <csg/info.h>

#include <iostream>
using namespace std;

//#define DEBUG_SCS

#if defined(NDEBUG) && defined(DEBUG_SCS)
#undef DEBUG_SCS
#endif

int csgSampleK
(
    const CsgProduct &product,
    const CsgOptions &options,
          CsgInfo    &info
)
{
    Timer timer;
    info.stencilReads++;

    // Find k

    GltShapes shapes;
    for (GLuint i=0; i<product.size(); i++)
        shapes.push_back(product.shape(i));

    if (options.cullFaces)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    #if 0
    const GLuint count = countSurfaces(shapes,COUNT_SURFACES_ALL);
    #else
    countSurfaces(shapes);
    const GLuint count = stencilMax(0,shapes.size());
    #endif

    #ifdef DEBUG_SCS
    cout << "csgSampleK: " << count << endl;
    #endif

    const int k = (options.cullFaces ? count : count>>1);

    info.depthComplexityTime += timer.clock();

    return k;
}

int csgSampleK
(
    const CsgSubtractionSequence &objects,
    const CsgProduct             &product,
    const CsgOptions             &options,
          CsgInfo                &info
)
{
    Timer timer;

    // Find k

    GltShapes shapes;
    for (GLuint i=0; i<objects.size(); i++)
        shapes.push_back(product.shape(objects[i]));

    if (options.cullFaces)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    #if 0
    info.stencilReads++;
    const GLuint count = countSurfaces(shapes,COUNT_SURFACES_ALL);
    #else
    countSurfaces(shapes);
    const GLuint count = stencilMax(0,shapes.size());

    // assert(count==countSurfaces(shapes,COUNT_SURFACES_ALL));
    #endif

    #ifdef DEBUG_SCS
    cout << "csgSampleK: " << count << endl;
    #endif

    const int k = (options.cullFaces ? count : count>>1);

    info.depthComplexityTime += timer.clock();

    return k;
}
