#ifndef CSG_INFO_H
#define CSG_INFO_H

/** \file
 *  \brief   CSG Rendering Runtime Info
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <csg/summary.h>
#include <misc/timer.h>

class CsgInfo
{
public:

    #if defined(linux) && defined(i386)
    typedef uint64                    intType;
    #else
    typedef uint32                    intType;
    #endif

    typedef summary<intType> summaryType;

    CsgInfo();
    ~CsgInfo();

    void reset();

    void startFrame();
    void endFrame();

    std::string str() const;

    // Summaries

    summaryType subtractions;           ///< Number of subtractions computed
    summaryType intersections;          ///< Number of intersections computed
    summaryType layerClips;             ///< Number of layer clipping operations

    summaryType depthComplexity;
    summaryType depthComplexityFront;
    summaryType depthComplexityBack;

    summaryType stencilBufferKBits;

    summaryType depthBits;
    summaryType depthClears;
    summaryType depthReads;
    summaryType depthWrites;

    summaryType stencilBits;
    summaryType stencilClears;
    summaryType stencilReads;
    summaryType stencilWrites;

    summaryType depthComplexityTime;
    summaryType encodeTime;
    summaryType drawTime;
    summaryType totalTime;
};

#endif

