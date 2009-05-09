#ifndef CSG_PARITY_H
#define CSG_PARITY_H

/** \file
 *  \brief   Z-Buffer Parity Test
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <glt/config.h>
#include <glt/gl.h>

class GltShape;

/** \brief Test the parity of a z-buffer surface
 *  \ingroup CSG
 *
 *  Toggle a stencil buffer bit according to the number of
 *  fragments that are closer than the z-buffer at each pixel.
 *
 *  \param shape     CSG Tree in sum-of-products form
 *  \param bit       Stencil buffer bit to toggle
 *  \param depthFunc Z-Buffer test
 */

void parityTest(const GltShape &shape,const GLuint bit,const GLenum depthFunc = GL_LESS);

/** \brief   Perform parity-based intersection
 *  \ingroup CSG
 *  \param   shape     CSG Tree in sum-of-products form
 *  \param   bit       Stencil buffer bit to toggle
 *  \param   mask      Stencil buffer parity mask
 *  \param   depthFunc Z-Buffer test
 */

void parityIntersect(const GltShape &shape,const GLuint bit,GLuint &mask,const GLenum depthFunc = GL_LESS);

/** \brief   Perform parity-based subtraction
 *  \ingroup CSG
 *  \param   shape     CSG Tree in sum-of-products form
 *  \param   bit       Stencil buffer bit to toggle
 *  \param   mask      Stencil buffer parity mask
 *  \param   depthFunc Z-Buffer test
 */

void paritySubtract (const GltShape &shape,const GLuint bit,GLuint &mask,const GLenum depthFunc = GL_LESS);

/** \brief   Apply parity test mask
 *  \ingroup CSG
 *  \param   parityMask     Parity mask
 *  \param   stencilMask    Stencil mask
 */

void parityApply(const GLuint parityMask,const GLuint stencilMask);

#endif
