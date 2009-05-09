#include "options.h"

#include <node/fields.h>

CsgOptions::CsgOptions()
:
    zBufferCopy(false),
    sampleDepthComplexity(true),
    cullFaces(true),
    cullBackFaces(true),
    overlapGraph(true),
    layer(-1),
    group(-1),
    groups(-1),
    boundingBoxes(false),
    limitSubtractions(-1),
    nvidiaHardware(true),
    msDriver(true),
    scsSubtraction(true),
    scsZBufferClip(true)
{
}

CsgOptions::~CsgOptions()
{
}

GltFieldPtr
CsgOptions::settings()
{
    GltFields *root = new GltFields("options");
    root->add(zBufferCopy          ,"zBufferCopy");
    root->add(sampleDepthComplexity,"sampleDepthComplexity");
    root->add(cullFaces            ,"cullFaces");
    root->add(cullBackFaces        ,"cullBackFaces");
    root->add(overlapGraph         ,"overlapGraph");
    root->add(layer                ,"layer");
    root->add(group                ,"group");
    root->add(groups               ,"groups");
    root->add(boundingBoxes        ,"boundingBoxes");
    root->add(limitSubtractions    ,"limitSubtractions");
    root->add(nvidiaHardware       ,"nvidiaHardware");
    root->add(msDriver             ,"msDriver");
    root->add(scsSubtraction       ,"scsSubtraction");
    root->add(scsZBufferClip       ,"scsZBufferClip");

    return root;
}
