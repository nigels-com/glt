#include "shadez.h"

#include <csg/element.h>
#include <csg/options.h>

#include <glt/error.h>

#include <iostream>
using namespace std;

void csgRenderLightShadeZBuffer
(
    const CsgProduct &product,
    const CsgOptions &options
)
{
    GLERROR         // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT);

        // Match z-buffer with primitive surfaces

        glDisable(GL_STENCIL_TEST);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_EQUAL);
        glDepthMask(GL_FALSE);

        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

        // Face culling is normally used, but can be
        // disabled at some expense to performance

        if (options.cullFaces)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);

        // Draw front facing surfaces of intersected objects

        GLuint j;

        glCullFace(GL_BACK);
        for (j=0; j<product.size(); j++)
            if (product.positive(j))
                product.shape(j)->draw();

        // Draw back facing surfaces of subtracted objects

        glCullFace(GL_FRONT);
        for (j=0; j<product.size(); j++)
            if (!product.positive(j))
                product.shape(j)->draw();

    glPopAttrib();  // Restore OpenGL state

    GLERROR         // Check for errors
}

void csgRenderLightShadeZBuffer
(
    const CsgSumOfProducts &sumOfProducts,
    const CsgOptions       &options
)
{
    GLERROR         // Check for OpenGL errors

    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT);

        // Match z-buffer with primitive surfaces

        glDisable(GL_STENCIL_TEST);                    // No stencil testing

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_EQUAL);                         // z-equal depth test
        glDepthMask(GL_FALSE);                         // No updates to depth buffer

        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);  // Draw into colour buffer

        // Face culling is normally used, but can be
        // disabled at some expense to performance

        if (options.cullFaces)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);

        // Draw front facing surfaces of intersected objects

        glCullFace(GL_BACK);

        for (GLuint i=0; i<sumOfProducts.size(); i++)
        {
            const CsgProduct &product = sumOfProducts[i];

            for (GLuint j=0; j<product.size(); j++)
                if (product.positive(j))
                    product.shape(j)->draw();
        }

        // Draw back facing surfaces of subtracted objects

        glCullFace(GL_FRONT);

        for (GLuint i=0; i<sumOfProducts.size(); i++)
        {
            const CsgProduct &product = sumOfProducts[i];

            for (GLuint j=0; j<product.size(); j++)
                if (!product.positive(j))
                    product.shape(j)->draw();
        }

    glPopAttrib();  // Restore OpenGL state

    GLERROR         // Check for errors
}
