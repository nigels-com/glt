#ifndef CSG_MODEL_H
#define CSG_MODEL_H

/** \file
 *  \brief   Container & parser of CSG trees
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <csg/node.h>
#include <math/matrix4.h>

#include <iosfwd>
#include <vector>

class Vector3;
class GltColor;
class GltMaterial;
class Mesh;
class Triangle;
class Quad;

class CsgModel
{
public:
    CsgModel();
    ~CsgModel();

    const int trees() const;
    GltShapePtr tree(const int i);

    const int primitives() const;
    GltShapePtr primitive(const int i);

    bool read (std::istream &is);
    bool write(std::ostream &os);

    void reset();

protected:
    Matrix _transform;

private:

    static bool matchToken  (const std::string &match, std::istream &is);

           bool readTree    (GltShapePtr &tree,        std::istream &is);
    static bool readToken   (std::string &token,       std::istream &is);
    static bool readShape   (GltShapePtr &shape,       std::istream &is);
    static bool readTriangle(Triangle &val, Mesh &mesh,std::istream &is);
    static bool readQuad    (Quad     &val, Mesh &mesh,std::istream &is);

    static bool read        (int         &val,         std::istream &is);
    static bool read        (float       &val,         std::istream &is);
    static bool read        (double      &val,         std::istream &is);
    static bool read        (Vector3     &vector,      std::istream &is);
    static bool read        (Matrix      &matrix,      std::istream &is);
    static bool read        (Mesh        &val,         std::istream &is);
    static bool read        (GltColor    &color,       std::istream &is);
    static bool read        (GltMaterial &material,    std::istream &is);

    std::vector<GltShapePtr> _trees;
    std::vector<GltShapePtr> _primitives;
};

#endif
