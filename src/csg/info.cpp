#include "info.h"

#include <misc/string.h>

#include <cstdio>
using namespace std;

CsgInfo::CsgInfo()
{
    reset();
}

CsgInfo::~CsgInfo()
{
}

void
CsgInfo::reset()
{
    startFrame();

    subtractions.reset();
    intersections.reset();
    layerClips.reset();
    depthComplexity.reset();
    depthComplexityFront.reset();
    depthComplexityBack.reset();
    stencilBufferKBits.reset();
    depthBits.reset();
    depthClears.reset();
    depthReads.reset();
    depthWrites.reset();
    stencilBits.reset();
    stencilClears.reset();
    stencilReads.reset();
    stencilWrites.reset();
    depthComplexityTime.reset();
    encodeTime.reset();
    drawTime.reset();
    totalTime.reset();
}

void
CsgInfo::startFrame()
{
    if (subtractions.defined())         subtractions = 0;
    if (intersections.defined())        intersections = 0;
    if (layerClips.defined())           layerClips = 0;
    if (depthComplexity.defined())      depthComplexity = 0;
    if (depthComplexityFront.defined()) depthComplexityFront = 0;
    if (depthComplexityBack.defined())  depthComplexityBack = 0;
    if (stencilBufferKBits.defined())   stencilBufferKBits = 0;
    if (depthBits.defined())            depthBits = 0;
    if (depthClears.defined())          depthClears = 0;
    if (depthReads.defined())           depthReads = 0;
    if (depthWrites.defined())          depthWrites = 0;
    if (stencilBits.defined())          stencilBits = 0;
    if (stencilClears.defined())        stencilClears = 0;
    if (stencilReads.defined())         stencilReads = 0;
    if (stencilWrites.defined())        stencilWrites = 0;
    if (depthComplexityTime.defined())  depthComplexityTime = 0;
    if (encodeTime.defined())           encodeTime = 0;
    if (drawTime.defined())             drawTime = 0;
    if (totalTime.defined())            totalTime = 0;
}

void
CsgInfo::endFrame()
{
    subtractions.update();
    intersections.update();
    layerClips.update();
    depthComplexity.update();
    depthComplexityFront.update();
    depthComplexityBack.update();
    stencilBufferKBits.update();
    depthBits.update();
    depthClears.update();
    depthReads.update();
    depthWrites.update();
    stencilBits.update();
    stencilClears.update();
    stencilReads.update();
    stencilWrites.update();
    depthComplexityTime.update();
    encodeTime.update();
    drawTime.update();
    totalTime.update();
}

std::string
CsgInfo::str() const
{
    string tmp;

    if (!totalTime.samples())
        return tmp;

    const float time = float(totalTime.mean())/Timer::clockPerSec();
    const float fps  = float(Timer::clockPerSec())/totalTime.mean();

    sprintf
    (
        tmp,
        "%-27s %7d\n%-27s %7d\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n%-27s %s\n\n%-27s %7.3f %s\n%-27s %6.2f  %s",
        "Samples:",               drawTime.samples(),
        "Timer Precision:",       (unsigned int) Timer::clockPerSec(),
        "Subtractions:",          subtractions.str().c_str(),
        "Intersections:",         intersections.str().c_str(),
        "Layer clips:",           layerClips.str().c_str(),
        "Depth Complexity:",      depthComplexity.str().c_str(),
        "Front Depth Complexity:",depthComplexityFront.str().c_str(),
        "Back  Depth Complexity:",depthComplexityBack.str().c_str(),
        "Stencil Buffer K-Bits:", stencilBufferKBits.str().c_str(),
        "Depth   Buffer Bits:",   depthBits.str().c_str(),
        "Depth   Buffer Clears:", depthClears.str().c_str(),
        "Depth   Buffer Reads:",  depthReads.str().c_str(),
        "Depth   Buffer Writes:", depthWrites.str().c_str(),
        "Stencil Buffer Bits:",   stencilBits.str().c_str(),
        "Stencil Buffer Clears:", stencilClears.str().c_str(),
        "Stencil Buffer Reads:",  stencilReads.str().c_str(),
        "Stencil Buffer Writes:", stencilWrites.str().c_str(),
        "kSample Time:",          depthComplexityTime.str().c_str(),
        "Encode Time:",           encodeTime.str().c_str(),
        "Draw Time:",             drawTime.str().c_str(),
        "Total Time:",            totalTime.str().c_str(),
        "Average Time:",          time, " sec",
        "Average Frame Rate:",    fps,  " frame/sec"
    );

    return tmp;
}
