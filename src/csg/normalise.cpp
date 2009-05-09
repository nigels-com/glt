#include "normalise.h"

#include <cassert>
#include <iostream>
using namespace std;

//#define DEBUG

class CsgNormalisationNode;

class CsgNormalisationNode
{
public:
    CsgNormalisationNode(CsgNodeType type);
    CsgNormalisationNode(const GltShapePtr &shape);
    CsgNormalisationNode(CsgNormalisationNode &node);
    ~CsgNormalisationNode();

    bool                           _primitive;

    // Primitive nodes only

    GltShapePtr                    _shape;

    // Parent nodes only

    CsgNodeType                    _type;

    // We could also use std::auto_ptr, but this would be more delicate
    // in terms of knowing which pointer is going to free the memory.

    typedef ReferenceCountPtr<CsgNormalisationNode> CsgNormalisationNodePtr;

    CsgNormalisationNodePtr _left;
    CsgNormalisationNodePtr _right;

    //
    //
    //

    void normalise();
    CsgSumOfProducts normalised();

private:

    bool rule1();
    bool rule2();
    bool rule3();
    bool rule4();
    bool rule5();
    bool rule6();
    bool rule7();
    bool rule8();

    bool isType(CsgNodeType type) const;
    bool rightIsType(CsgNodeType type) const;
    bool leftIsType(CsgNodeType type) const;
};

CsgNormalisationNode::CsgNormalisationNode(CsgNodeType type)
: _primitive(false), _type(type)
{
}

CsgNormalisationNode::CsgNormalisationNode(const GltShapePtr &shape)
{
    assert(shape.get());

    const CsgNode *node = dynamic_cast<const CsgNode *>(shape.get());

    if (!node)
    {
        _primitive = true;
        _shape = shape;
    }
    else
    {
        _primitive = false;
        _type = node->type();

        if (node->left().get())
            _left = CsgNormalisationNodePtr(new CsgNormalisationNode(node->left()));

        if (node->right().get())
            _right = CsgNormalisationNodePtr(new CsgNormalisationNode(node->right()));
    }
}

CsgNormalisationNode::CsgNormalisationNode(CsgNormalisationNode &node)
{
    if (node._primitive)
    {
        _primitive = true;
        _shape = node._shape;
    }
    else
    {
        _primitive = false;
        _type = node._type;
        _left  = CsgNormalisationNodePtr(new CsgNormalisationNode(*node._left));
        _right = CsgNormalisationNodePtr(new CsgNormalisationNode(*node._right));
    }
}

CsgNormalisationNode::~CsgNormalisationNode()
{
}

bool CsgNormalisationNode::isType(CsgNodeType type) const
{
    if (_primitive)
        return false;

    return _type == type;
}

bool CsgNormalisationNode::rightIsType(CsgNodeType type) const
{
    if (_primitive)
        return false;

    if (_right.get())
        return _right->isType(type);

    return false;
}

bool CsgNormalisationNode::leftIsType(CsgNodeType type) const
{
    if (_primitive)
        return false;

    if (_left.get())
        return _left->isType(type);

    return false;
}

// Rule 1  X - (Y + Z)  ->  (X - Y) - Z

bool CsgNormalisationNode::rule1()
{
    if (isType(NODE_DIFFERENCE) && rightIsType(NODE_UNION))
    {
        #ifdef DEBUG
        cout << "Production rule 1" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_DIFFERENCE));

        tmp->_left  = _left;
        tmp->_right = _right->_left;

        _left  = tmp;
        _right = CsgNormalisationNodePtr(_right->_right);

        return true;
    }

    return false;
}

// Rule 2  X . (Y + Z)  ->  (X . Y) + (X . Z)

bool CsgNormalisationNode::rule2()
{
    if (isType(NODE_INTERSECTION) && rightIsType(NODE_UNION))
    {
        #ifdef DEBUG
        cout << "Production rule 2" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_INTERSECTION));

        tmp->_left  = _left;
        tmp->_right = _right->_left;

        _right->_left = CsgNormalisationNodePtr(_left);
        _right->_type = NODE_INTERSECTION;

        _left  = tmp;
        _type = NODE_UNION;

        return true;
    }

    return false;
}

// Rule 3  X - (Y . Z)  ->  (X - Y) + (X - Z)

bool CsgNormalisationNode::rule3()
{
    if (isType(NODE_DIFFERENCE) && rightIsType(NODE_INTERSECTION))
    {
        #ifdef DEBUG
        cout << "Production rule 3" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_DIFFERENCE));

        tmp->_left  = _left;
        tmp->_right = _right->_left;

        _right->_left = CsgNormalisationNodePtr(_left);
        _right->_type = NODE_DIFFERENCE;

        _left = tmp;
        _type = NODE_UNION;

        return true;
    }

    return false;
}

// Rule 4  X . (Y . Z)  ->  (X . Y) . Z

bool CsgNormalisationNode::rule4()
{
    if (isType(NODE_INTERSECTION) && rightIsType(NODE_INTERSECTION))
    {
        #ifdef DEBUG
        cout << "Production rule 4" << endl;
        #endif

        swap(_left,_right);                 // (Y . Z) . X
        swap(_left->_left,_left->_right);   // (Z . Y) . X
        swap(_left->_left,_right);          // (X . Y) . Z

        return true;
    }

    return false;
}

// Rule 5  X - (Y - Z)  ->  (X - Y) + (X . Z)

bool CsgNormalisationNode::rule5()
{
    if (isType(NODE_DIFFERENCE) && rightIsType(NODE_DIFFERENCE))
    {
        #ifdef DEBUG
        cout << "Production rule 5" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_DIFFERENCE));

        tmp->_left  = _left;
        tmp->_right = _right->_left;

        _right->_left = CsgNormalisationNodePtr(_left);
        _right->_type = NODE_INTERSECTION;

        _left = tmp;
        _type = NODE_UNION;

        return true;
    }

    return false;
}

// Rule 6  X . (Y - Z)  ->  (X . Y) - Z

bool CsgNormalisationNode::rule6()
{
    if (isType(NODE_INTERSECTION) && rightIsType(NODE_DIFFERENCE))
    {
        #ifdef DEBUG
        cout << "Production rule 6" << endl;
        #endif

        swap(_left,_right);
        swap(_left->_type,_type);
        swap(_left->_left,_right);          // Put X in right place
        swap(_left->_right,_right);         // Put Y in right place

        return true;
    }

    return false;
}

// Rule 7  (X + Y) - Z  =>  (X - Z) + (Y - Z)

bool CsgNormalisationNode::rule7()
{
    if (leftIsType(NODE_UNION) && isType(NODE_DIFFERENCE))
    {
        #ifdef DEBUG
        cout << "Production rule 7" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_DIFFERENCE));

        tmp->_left  = _left->_right;
        tmp->_right = _right;

        _left->_right = CsgNormalisationNodePtr(_right);
        _left->_type = NODE_DIFFERENCE;

        _right = tmp;
        _type = NODE_UNION;

        return true;
    }

    return false;
}

// Rule 8  (X + Y) . Z  =>  (X . Z) + (Y . Z)

bool CsgNormalisationNode::rule8()
{
    if (leftIsType(NODE_UNION) && isType(NODE_INTERSECTION))
    {
        #ifdef DEBUG
        cout << "Production rule 8" << endl;
        #endif

        CsgNormalisationNodePtr tmp(new CsgNormalisationNode(NODE_INTERSECTION));

        tmp->_left  = _left->_right;
        tmp->_right = _right;

        _left->_right = CsgNormalisationNodePtr(_right);
        _left->_type = NODE_INTERSECTION;

        _right = tmp;
        _type = NODE_UNION;

        return true;
    }

    return false;
}

void
CsgNormalisationNode::normalise()
{
    if (_primitive)
        return;

    assert(_left.get() && _right.get());

    if (_left->_primitive && _right->_primitive)
        return;

    for (;;)
    {

        bool match = true;

        for (;;)
        {
            match |= rule1();
            match |= rule2();
            match |= rule3();
            match |= rule4();
            match |= rule5();
            match |= rule6();

            if (!match)
                break;

            match = false;
        }

        match |= rule7();
        match |= rule8();

        if (_left.get())
            _left->normalise();


        if (isType(NODE_UNION))
            break;

        assert(_right.get());

        if (_right->_primitive && !_left->_primitive && _left->_type!=NODE_UNION)
            break;
    }

    if (_right.get())
        _right->normalise();
}

CsgSumOfProducts
CsgNormalisationNode::normalised()
{
    CsgSumOfProducts sum;

    if (_primitive)
    {
        sum.push_back(CsgProduct());
        sum.back().push_back(CsgElement(_shape,true));
        return sum;
    }

    CsgSumOfProducts left = _left->normalised();
    CsgSumOfProducts right = _right->normalised();

    if (isType(NODE_UNION))
    {
        sum.add(left);
        sum.add(right);
        return sum;
    }

    if (isType(NODE_DIFFERENCE))
    {
        assert(right.size()==1);
        assert(left.size()==1);

        right[0].negate();
        left[0].add(right[0]);
        sum.add(left);
        return sum;
    }

    if (isType(NODE_INTERSECTION))
    {
        assert(right.size()==1);
        assert(left.size()==1);

        left[0].add(right[0]);
        sum.add(left);
        return sum;
    }

    assert(false);

    return sum;
}

CsgSumOfProducts normalise(const GltShapePtr &shape)
{
    CsgNormalisationNode tree(shape);
    tree.normalise();
    return tree.normalised();

}

