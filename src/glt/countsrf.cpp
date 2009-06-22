#include "countsrf.h"

/*! \file
    \ingroup GLT

    $Id: countsrf.cpp,v 2.3 2009/06/22 05:03:21 nigels Exp $
*/

#include <glt/rgb.h>
#include <glt/zplane.h>
#include <glt/error.h>

#include <node/shape.h>

#include <iostream>
using namespace std;

//#define DEBUG_BINARY_SEARCH 1

////////////////////////////////////////////////////////////////////////////////////////

void
countSurfaces(const GltShape &shape)
{
    GLERROR

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Ensure stencil buffer is fully zero

        glClearStencil(0);
        glStencilMask(~0);
        glClear(GL_STENCIL_BUFFER_BIT);

        // Disable z buffer test & update

        glDepthMask(GL_FALSE);
        glDepthFunc(GL_ALWAYS);

        // Use stencil test to count surfaces

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS,0,~0);
        glStencilOp(GL_INCR,GL_INCR,GL_INCR);

        // Disable updates to colour buffer

        glDisable(GL_LIGHTING);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        // Draw all objects
        shape.draw();

    glPopAttrib();

    GLERROR
}

GLubyte
countSurfaces
(
    const GltShape &shape,
    const countSurfacesMode mode
)
{
    countSurfaces(shape);

    GLERROR

    // Get stencil buffer histogram

    GLuint histogram[256];
    GLuint pixels = stencilHistogram(histogram);

    GLubyte max = 0;

    switch (mode)
    {
        case COUNT_SURFACES_ALL:
            {
                for (GLuint p=0; p<256; p++)
                    if (histogram[p]>0)
                        max = p;
            }
            break;

        case COUNT_SURFACES_99TH_PERCENTILE:
            {
                GLuint accum = 0;
                for (GLuint p=0; p<256; p++)
                {
                    accum += histogram[p];
                    if ((double) accum / pixels >= 0.999)
                    {
                        max = p;
                        break;
                    }
                }
            }
            break;
    }

    #ifdef DEBUG
    GLint stencilSize = 0;
    glGetIntegerv(GL_STENCIL_BITS,&stencilSize);

    if ( GLubyte(GLubyte(1)<<stencilSize) == max+1 )
        cout << "WARNING: Stencil Buffer may be too small for countSurfaces" << endl;
    #endif

    GLERROR

    return max;
}

////////////////////////////////////////////////////////////////////////////////////////

/// Number of colors used for stencil buffer color coding
static const GLuint maxColors=15;

/// Colors used for stencil buffer color coding
static const GltColor *surfaceColor[maxColors] =
{
    &red,
    &green,
    &blue,
    &yellow,
    &cyan,
    &magenta,
    &orange,
    &limeGreen,
    &darkGreen,
    &black,
    &grey0,
    &grey20,
    &grey40,
    &grey60,
    &grey80
};

GLubyte
countSurfacesVisualise(const GltShape &shape)
{
    glPushAttrib( GL_ENABLE_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

        GLubyte layers = countSurfaces(shape,COUNT_SURFACES_ALL);

        glEnable(GL_STENCIL_TEST);
        glStencilMask(~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
        glDepthMask(GL_FALSE);

        glDisable(GL_LIGHTING);

        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

        for (GLuint l=0; l<layers && l<maxColors; l++)
        {
            if (l<layers)
            {
                glStencilFunc(GL_EQUAL,l+1,~0);
                surfaceColor[l%(maxColors-1)]->glColor();
            }
            else
            {
                glStencilFunc(GL_GEQUAL,l+1,~0);
                surfaceColor[maxColors-1]->glColor();
            }

            drawZnear();
        }

    glPopAttrib();

    return layers;
}

////////////////////////////////////////////////////////////////////////////////////////

GLuint
stencilHistogram(GLuint histogram[256])
{
    // Get the viewport dimensions

    GLuint viewport[4];
    glGetIntegerv(GL_VIEWPORT,(GLint *) viewport);

    // Allocate enough memory to get a copy of the stencil buffer

    GLuint   pixels = viewport[2] * viewport[3];
    GLubyte *pixel  = new GLubyte[pixels];

    // Read the stencil buffer

    glPixelStorei(GL_PACK_ALIGNMENT,sizeof(GLubyte));
    glReadPixels(viewport[0],viewport[1],viewport[2],viewport[3],GL_STENCIL_INDEX,GL_UNSIGNED_BYTE,pixel);

    // Initialise Histogram

    GLuint x;

    for (x=0;x<256;x++)
        histogram[x] = 0;

    // Build Histogram

    for (x=0;x<pixels;x++)
        histogram[pixel[x]]++;

    // Free allocated memory

    delete [] pixel;

    return pixels;
}

GLuint
stencilMax(const GLuint min, const GLuint max)
{
    // Get the viewport dimensions

    GLuint viewport[4];
    glGetIntegerv(GL_VIEWPORT,(GLint *) viewport);

    //

    GLuint size = viewport[2]*viewport[3];

    //

    GLuint begin = min;
    GLuint end   = std::min<GLuint>(max,255);

    //

    GLuint *pixels = new GLuint[end+1];
    glGenQueriesARB(end+1,pixels);

    glPushAttrib( GL_ENABLE_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);

        glDisable(GL_LIGHTING);

        glStencilMask(0);
        glDepthMask(GL_FALSE);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        for (;;)
        {
            GLuint mid = (begin+end)>>1;

            if (mid==begin || mid==end)
                break;

            glStencilFunc(GL_GEQUAL,mid,~0);

            glBeginQueryARB(GL_SAMPLES_PASSED_ARB,pixels[mid]);
            drawZnear();
            glEndQueryARB(GL_SAMPLES_PASSED_ARB);

            GLuint count;
            glGetQueryObjectuivARB(pixels[mid],GL_QUERY_RESULT_ARB,&count);

            #ifdef DEBUG_BINARY_SEARCH
            cout << begin << " " << mid << " " << end << " -> " << count << endl;
            #endif

            if (count<size)
                begin = mid;
            else
                end = mid;
        }

    glPopAttrib();

    glDeleteQueriesARB(end+1,pixels);
    delete [] pixels;

    #ifdef DEBUG_BINARY_SEARCH
    cout << end << endl;
    #endif

    return end;
}
