#ifndef CSG_OPTIONS_H
#define CSG_OPTIONS_H

#include <node/field.h>

/*!
    \file
    \brief   CSG Rendering Options
    \ingroup CSG
*/

class CsgOptions
{
public:
    CsgOptions();
    ~CsgOptions();

    GltFieldPtr settings();

    bool    zBufferCopy;                ///< Use z-buffer copying, or read/draw pixels
    bool    sampleDepthComplexity;      ///< Sample depth complexity, or assume k==n
    bool    cullFaces;                  ///< Use face culling
    bool    cullBackFaces;              ///< Cull back faces, otherwise front faces
    bool    overlapGraph;               ///< Use object-space subtraction sequence encoding

    int     layer;                      ///< Selected layer
    int     group;                      ///< Currently selected group
    int     groups;                     ///< Number of groups
    bool    boundingBoxes;              ///< Draw bounding boxes
    int     limitSubtractions;          ///< Limit number of subtractions, -1 for all

    bool    nvidiaHardware;             ///< NVIDIA hardware has certain bugs/features
    bool    msDriver;                   ///< Microsoft driver has certain bugs/features

    // SCS-specific options

    bool    scsSubtraction;             ///< Enable subtraction phase
    bool    scsZBufferClip;             ///< Enable z-buffer clipping
};

#endif
