#ifndef CSG_NODE_H
#define CSG_NODE_H

/** \file
 *  \brief   CSG Tree Nodes
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <node/shape.h>

#include <csg/element.h>
#include <misc/refcount.h>

typedef enum
{
    NODE_UNION = 0,
    NODE_INTERSECTION,
    NODE_DIFFERENCE
} CsgNodeType;

typedef ReferenceCountPtr<GltShape> GltShapePtr;

class CsgNode : public GltShape
{
public:
    CsgNode();
    ~CsgNode();

    void draw() const;

    //

          GltShapePtr &left();
          GltShapePtr &right();
          CsgNodeType &type();

    const GltShapePtr &left()  const;
    const GltShapePtr &right() const;
    const CsgNodeType &type()  const;

    //

    std::string description() const;

private:
    GltShapePtr  _left;
    GltShapePtr  _right;
    CsgNodeType  _type;
};

#endif
