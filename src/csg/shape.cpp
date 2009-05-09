#include "shape.h"

#include <glt/countsrf.h>

#include <csg/goldfeat.h>
#include <csg/goldlayr.h>
#include <csg/goldlay2.h>
#include <csg/scs.h>
#include <csg/scsseq.h>
#include <csg/scsutil.h>
#include <csg/normalise.h>
#include <csg/bbox.h>
#include <csg/util.h>

#include <csg/shadez.h>

#include <node/fields.h>

#include <iomanip>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////

const std::string CsgShape::_drawModeDescription[CSG_DRAW_MAX] =
{
    "Preview",
    "Goldfeather",
    "LayeredGoldfeather",
    "ImprovedLayeredGoldfeather",
    "SCS",

    "DepthComplexity",
    "Layer",
    "Group",
    "Wireframe"
};

CsgShape::CsgShape()
:
  _mode(CSG_DRAW_PREVIEW)
{
}

CsgShape::~CsgShape()
{
}

void
CsgShape::draw() const
{
    if (!_root.get())
        return;

    // Cast away the const in order to collect
    // runtime information

    CsgInfo &info = ((CsgShape *) (this))->info();
    info.startFrame();

    Timer timer;

    //

    if (_options.cullFaces)
    {
        glEnable(GL_CULL_FACE);
        if (_options.cullBackFaces)
            glCullFace(GL_BACK);
        else
            glCullFace(GL_FRONT);
    }
    else
        glDisable(GL_CULL_FACE);


    glPushMatrix();
        transformation().glMultMatrix();
        _transform.glMultMatrix();
        color().glColor();

        if (!solid() || _mode==CSG_DRAW_WIREFRAME)
        {
            glPushAttrib(GL_POLYGON_BIT);
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                _root.get()->draw();
            glPopAttrib();
        }
        else
            switch (_mode)
            {
            default:
            case CSG_DRAW_PREVIEW:

                #if 0
                if (_options.msDriver)
                    massageOpenGLMatrices();
                glDisable(GL_NORMALIZE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
                _root.get()->draw();
                glEnable(GL_NORMALIZE);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                csgRenderLightShadeZBuffer(_normalised,_options);
                #else
                {
                    Timer timer;
                    _root.get()->draw();
                    info.drawTime += timer.clock();
                }
                #endif

                break;

            case CSG_DRAW_GOLDFEATHER:            csgRenderGoldfeather               (_normalised,_options,info);  break;
            case CSG_DRAW_GOLDFEATHER_LAYERS:     csgRenderGoldfeatherLayered        (_normalised,_options,info);  break;
            case CSG_DRAW_GOLDFEATHER_LAYERS_IMP: csgRenderGoldfeatherLayeredImproved(_normalised,_options,info);  break;
            case CSG_DRAW_SCS:                    csgRenderSequencedConvexSubtraction(_normalised,_options,info);  break;

            case CSG_DRAW_DEPTH_COMPLEXITY:
                {
                    Timer timer;
                    info.depthComplexity += countSurfacesVisualise(*_root.get());
                    info.drawTime += timer.clock();
                }
                break;

            case CSG_DRAW_GROUP:
                if (_options.groups>0)
                {
                    const int n = std::abs(_options.groups);
                    const int g = std::abs(_options.group)%n;

                    uint32 k = 0;
                    for (uint32 i=0; i<products(); i++)
                        for (uint32 j=0; j<product(i).size(); j++)
                        {
                            if (k==g)
                                product(i)[j].drawFront();
                            k = (k+1)%n;
                        }
                }
                break;

            case CSG_DRAW_LAYER:
                glPushAttrib(GL_ENABLE_BIT);
                    glDepthFunc(GL_ALWAYS);
                    glDepthMask(GL_TRUE);
                    glEnable(GL_STENCIL_TEST);
                    glStencilOp(GL_INCR,GL_INCR,GL_INCR);
                    glStencilMask(~0);
                    glStencilFunc(GL_EQUAL,_options.layer,~0);
                    #if 1
                    _root.get()->draw();
                    #else
                    for (uint32 i=0; i<products(); i++)
                        for (uint32 j=0; j<product(i).size(); j++)
                            if (product(i).positive(j))
                                product(i)[j].drawFront();
                            else
                                product(i)[j].drawBack();
                    #endif

                glPopAttrib();
                break;
            }

        if (_options.boundingBoxes)
            boundingBoxDraw(*_root.get());

    glPopMatrix();

    info.totalTime = timer.clock();
    info.endFrame();
}

string
CsgShape::description() const
{
    string text;

    if (_root.get())
        text += _root->description();

    if (_normalised.size())
    {
        CsgInfo tmp;

        text += "\n" + _normalised.toString();

        for (uint32 i=0; i<_normalised.size(); i++)
            if (_normalised[i].size()>1)
                text += "\n" + seqenceString(gscsSequence(_normalised[i],_options,tmp),_normalised[i]);
    }

    return text;
}

bool
CsgShape::writePov(ostream &os) const
{
    return _normalised.writePov(os);
}

bool
CsgShape::exportOverlap(ostream &os) const
{
    for (uint32 i=0; i<_normalised.size(); i++)
        if (_normalised[i].size())
        {
            const CsgOverlapGraph &graph = _normalised[i].graph();

            for (unsigned int j=0; j<_normalised[i].size(); j++)
            {
                for (unsigned int k=0; k<_normalised[i].size(); k++)
                    os << (graph.get(k,j) ? 'X' : ' ');
                os << endl;
            }
        }

    return true;
}

bool
CsgShape::exportDot(ostream &os,bool intersected,bool acyclic,bool artic) const
{
    for (uint32 i=0; i<_normalised.size(); i++)
        if (_normalised[i].size())
        {
            CsgOverlapGraph graph = _normalised[i].graph();

            // Remove intersected nodes

            if (!intersected)
                for (unsigned int j=0; j<_normalised[i].size(); j++)
                    if (_normalised[i].positive(j))
                        graph.clear(j);

            if (!acyclic)
            {
                // Remove orphans

                CsgOverlapGraph::boolv processed(graph.size(),false);
                CsgOverlapGraph::uintv nodes;
                graph.orphanNodes(nodes,processed);

                // Remove leaf nodes

                for (;;)
                {
                    CsgOverlapGraph::uintv nodes;
                    graph.leafNodes(nodes,processed);

                    if (nodes.size()==0)
                        break;

                    graph.clear(nodes.begin(),nodes.end());
                }
            }

            ::exportDot(os,graph,_normalised[i],artic,intersected && acyclic);
        }

    return true;
}

bool
CsgShape::exportTable(ostream &os) const
{
    // Output a table for each product

    for (uint32 i=0; i<_normalised.size(); i++)
        if (_normalised[i].size())
            ::exportTable(os,_normalised[i].graph(),_normalised[i]);

    return true;
}

      CsgShape::DrawMode &CsgShape::mode()          { return _mode;    }
      CsgOptions         &CsgShape::options()       { return _options; }
      CsgInfo            &CsgShape::info()          { return _info;    }

const CsgShape::DrawMode &CsgShape::mode()        const { return _mode; }
const CsgOptions         &CsgShape::options()     const { return _options; }
const CsgInfo            &CsgShape::info()        const { return _info;    }

const GltShapePtr        &CsgShape::root()        const { return _root; }

GltFieldPtr
CsgShape::settings()
{
    GltFields *root = new GltFields("shape");
    root->add((int &)_mode,CSG_DRAW_MAX,_drawModeDescription,"mode");
    root->add(solid()            ,"solid");
    root->add(_options.settings());
    return root;
}

bool
CsgShape::selectTree(const int t)
{
    if (t>=0 && t<trees())
    {
        _root = tree(t);
        _normalised = normalise(_root);
        _normalised.optimise();
    }
    else
        if (t>=trees() && t<(trees()+primitives()))
        {
            _root = primitive(t-trees());
            _normalised = normalise(_root);
            _normalised.optimise();
        }
        else
            return false;

    calculateAdjacency();
    _info.reset();

    return true;
}

bool
CsgShape::calculateAdjacency()
{
    // Calculate adjacency information for each product

    #ifdef _DEBUG
    cout << "Adjacency Information" << endl;
    cout << "---------------------" << endl;
    #endif

    for (uint32 i=0; i<_normalised.size(); i++)
        if (_normalised[i].size())
        {
//          ringAdjency(_normalised[i].graph(),_normalised[i]);                            
            boundingBoxAdjency(_normalised[i].graph(),_normalised[i]);

            #ifdef _DEBUG
            cout << "Product " << i << endl;
            if (_normalised[i].size()<=50)
            {
                _normalised[i].graph().print(cout);
                cout << endl;
            }
            #endif
        }

    #ifdef _DEBUG
    cout << "---------------------" << endl;
    #endif

    return true;
}

bool
CsgShape::calculateAdjacencyFrustum()
{
    for (uint32 i=0; i<_normalised.size(); i++)
        if (_normalised[i].size()>1)
        {
            _normalised[i].back().updateBox();
            boundingBoxAdjency(_normalised[i].graph(),_normalised[i],_normalised[i].graph().size()-1);
        }

    return true;
}

const int         CsgShape::products() const           { return _normalised.size(); }
const CsgProduct &CsgShape::product(const int n) const { return _normalised[n]; }
