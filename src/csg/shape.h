#ifndef CSG_SHAPE_H
#define CSG_SHAPE_H

/** \file
 *  \brief   CSG Shape
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels.com@gmail.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <csg/model.h>
#include <csg/options.h>
#include <csg/info.h>

#include <node/shape.h>
#include <node/field.h>

#include <iosfwd>

///////////////////////////////// CsgShape //////////////////////////////////////////

class CsgShape : public CsgModel, public GltShape
{
public:
    CsgShape();
    ~CsgShape();

    virtual void draw() const;
    virtual std::string description() const;
    virtual bool writePov(std::ostream &os) const;

    //

    typedef enum
    {
        CSG_DRAW_PREVIEW = 0,
        CSG_DRAW_GOLDFEATHER,              // Goldfeather CSG Rendering Algorithm
        CSG_DRAW_GOLDFEATHER_LAYERS,       // Layered Goldfeather CSG Rendering Algorithm
        CSG_DRAW_GOLDFEATHER_LAYERS_IMP,   // Improved Layered Goldfeather CSG Rendering Algorithm
        CSG_DRAW_SCS,                      // SCS Rendering Algorithm

        // Debug and/or informational modes

        CSG_DRAW_DEPTH_COMPLEXITY,
        CSG_DRAW_LAYER,
        CSG_DRAW_GROUP,                   // Subdivide subtracted objects into distinct groups
        CSG_DRAW_WIREFRAME,

        CSG_DRAW_MAX

    } DrawMode;

    static const std::string _drawModeDescription[CSG_DRAW_MAX];

    //

    bool selectTree(const int t);
    bool calculateAdjacency();
    bool calculateAdjacencyFrustum();

          DrawMode    &mode();
          CsgOptions  &options();
          CsgInfo     &info();

    const DrawMode    &mode()    const;
    const CsgOptions  &options() const;
    const CsgInfo     &info()    const;

    GltFieldPtr      settings();

    const GltShapePtr &root() const;

    //

    bool exportOverlap(std::ostream &os) const;
    bool exportDot    (std::ostream &os, bool intersected, bool acyclic, bool artic) const;
    bool exportTable  (std::ostream &os) const;

    //

    const int         products() const;
    const CsgProduct &product(const int n) const;

private:

    GltShapePtr        _root;
    CsgSumOfProducts   _normalised;
    CsgOptions         _options;
    CsgInfo            _info;
    DrawMode           _mode;
};

#endif
