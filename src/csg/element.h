#ifndef CSG_ELEMENT_H
#define CSG_ELEMENT_H

/** \file
 *  \brief   CSG Element, Product and Sum of Products
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <csg/graph.h>

#include <vector>
#include <string>
#include <iosfwd>

#include <node/shapes.h>
#include <node/dlist.h>
#include <math/vector3.h>
#include <math/bbox.h>

class CsgElement;
class CsgProduct;
class CsgSumOfProducts;

class CsgElement
{
    friend class CsgProduct;

public:
    CsgElement();
    CsgElement(GltShapePtr shape,bool positive);
    ~CsgElement();


    //

    void drawFront() const;
    void drawBack()  const;

    //

    void updateBox();

    const BoundingBox &box() const;

    //

    std::string toString() const;

    bool operator==(const CsgElement &) const;

private:

    GltShapePtr    _shape;          // Actual shape for drawing
    bool           _positive;       // Intersected or subtracted
    BoundingBox    _box;            // Bounding box info
};

class CsgProduct : public std::vector<CsgElement>
{
public:
    CsgProduct();
    ~CsgProduct();

    std::string toString() const;

    void negate();
    void add(CsgProduct &);
    void remove(const CsgProduct &);

    void optimise();
    bool contains(const CsgProduct &other) const;
    bool split(CsgProduct &intersect,CsgProduct &subtract) const;
    bool split(GltShapes  &intersect,GltShapes  &subtract) const;

    //
    // Get
    //

    const GltShapePtr &shape   (const int i) const;
    const bool        &positive(const int i) const;

    const CsgOverlapGraph &graph() const;
          CsgOverlapGraph &graph();

    std::vector<bool> intersected() const;

private:

    CsgOverlapGraph          _graph;
};

class CsgSumOfProducts : public std::vector<CsgProduct>
{
public:
    CsgSumOfProducts();
    ~CsgSumOfProducts();

    void optimise();

    std::string toString() const;
    bool writePov(std::ostream &os) const;

    void add(CsgSumOfProducts &);
};

#endif

