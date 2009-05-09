#include "node.h"

#include <string>
using namespace std;

CsgNode::CsgNode()
{
}

CsgNode::~CsgNode()
{
}

void
CsgNode::draw() const
{
    if (_left.get())
        _left->draw();

    if (_right.get())
        _right->draw();
}

GltShapePtr &CsgNode::left()  { return _left;  }
GltShapePtr &CsgNode::right() { return _right; }

const GltShapePtr &CsgNode::left()  const { return _left;  }
const GltShapePtr &CsgNode::right() const { return _right; }

      CsgNodeType &CsgNode::type()       { return _type; }
const CsgNodeType &CsgNode::type() const { return _type; }

string
CsgNode::description() const
{
    string tmp;

    if (_left.get() && _right.get())
    {
        const CsgNode *l = dynamic_cast<const CsgNode *>(_left.get());
        const CsgNode *r = dynamic_cast<const CsgNode *>(_right.get());

        tmp += "(";
        tmp += (l ? l->description() : _left->name());

        switch (_type)
        {
        case NODE_UNION:            tmp += "+"; break;
        case NODE_INTERSECTION:     tmp += "."; break;
        case NODE_DIFFERENCE:       tmp += "-"; break;
        }

        tmp += (r ? r->description() : _right->name());
        tmp += ")";
    }

    return tmp;
}
