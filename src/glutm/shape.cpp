#include "shape.h"

/*! \file
    \ingroup GlutMaster
*/

#include <glutm/glut.h>

#include <glt/error.h>

#include <math/plane.h>
#include <math/vector3.h>
#include <math/matrix4.h>
#include <math/volume.h>

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

////////////////////

GlutSphere::GlutSphere(const bool solid,const GLdouble radius,const GLint slices,const GLint stacks)
: GltShape(solid), _radius(radius), _slices(slices), _stacks(stacks)
{
}

GlutSphere::~GlutSphere()
{
}

void
GlutSphere::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidSphere(_radius,_slices,_stacks);
        else
            glutWireSphere(_radius,_slices,_stacks);
    glPopMatrix();

    GLERROR;
}

GLdouble
GlutSphere::volume() const
{
    return sphereVolume(_radius);
}

bool
GlutSphere::inside(const Vector &pos) const
{
    const Vector p = transformation().inverse()*pos;
    return (p*p)<_radius*_radius;
}

bool
GlutSphere::povrayExport(ostream &os) const
{
    os << "sphere { ";
    Vector0.writePov(os) << ", " << _radius << endl;


    os << "pigment { color rgb ";
    color().writePov(os) << '}' << endl;

    transformation().writePov(os) << endl;

    os << "}" << endl;

    return true;
}

void
GlutSphere::boundingBox(BoundingBox &box) const
{
    vector<Vector> p;
    p.reserve(8);
    p.push_back(Vector( _radius, _radius, _radius));
    p.push_back(Vector( _radius, _radius,-_radius));
    p.push_back(Vector( _radius,-_radius, _radius));
    p.push_back(Vector( _radius,-_radius,-_radius));
    p.push_back(Vector(-_radius, _radius, _radius));
    p.push_back(Vector(-_radius, _radius,-_radius));
    p.push_back(Vector(-_radius,-_radius, _radius));
    p.push_back(Vector(-_radius,-_radius,-_radius));
    transformPoints(p);

    box.reset();
    box += p;
}

void
GlutSphere::position(const Vector &pos,const double radius)
{
    _radius = radius;
    transformation() = matrixTranslate(pos);
}

/*
bool
GlutSphere::intersects(const GltShape &shape) const
{
    // Find the bounding box of the other shape

    Vector min,max;
    if (!shape.boundingBox(min,max))
        return false;

    // Transform the verticies of bounding box
    // to be relative to this sphere on the origin

    vector<Vector> p;
    boundingPoints(min,max,p);

    Matrix mat = transformation().inverse();
    for (int i=0; i<p.size(); i++)
        p[i] = mat * p[i];

    // Find a new bounding box, relative to
    // this sphere, untransformed.

    if (!GltShape::boundingBox(min,max,p))
        return false;

    // Quick check against the bounding box of the sphere

    if (min[0]>_radius || min[1]>_radius || min[2]>_radius)
        return false;

    if (max[0]<-_radius || max[1]<-_radius || max[2]<-_radius)
        return false;

    // More exacting check

    boundingPoints(min,max,p);
    for (i=0; i<p.size(); i++)
    {
        // Form a plane on the surface
        // of the sphere between the origin
        // and the point on the box.  If
        // all points on the box are on the
        // "outside" of the plane, then the
        // box doesn't intersect the sphere.

        const Vector n = p[i];
        const double l = n.norm();

        // If a point of the box is inside the
        // circle, then there is an intersection.

        if (l<_radius)
            return true;

        Plane plane(n/l*_radius,n);

        bool allOutside = true;
        for (int j=0; j<p.size(); j++)
            if (!plane.inside(p[j]))
            {
                allOutside =false;
                break;
            }

        if (allOutside)
            return false;
    }

    return true;
}
*/

      GLdouble &GlutSphere::radius()       { return _radius; }
      GLint    &GlutSphere::slices()       { return _slices; }
      GLint    &GlutSphere::stacks()       { return _stacks; }

const GLdouble &GlutSphere::radius() const { return _radius; }
const GLint    &GlutSphere::slices() const { return _slices; }
const GLint    &GlutSphere::stacks() const { return _stacks; }


/////////////

GlutCube::GlutCube(const bool solid,const GLdouble size)
: GltShape(solid), _size(size)
{
}

GlutCube::GlutCube(const bool solid,const Vector &min,const Vector &max)
: GltShape(solid), _size(1.0)
{
    position(min,max);
}

GlutCube::~GlutCube()
{
}

void
GlutCube::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidCube(_size);
        else
            glutWireCube(_size);
    glPopMatrix();

    GLERROR;
}

GLdouble
GlutCube::volume() const
{
    return boxVolume(_size,_size,_size);
}

void
GlutCube::boundingBox(BoundingBox &box) const
{
    const real size = _size*0.5;

    vector<Vector> p;
    p.reserve(8);
    p.push_back(Vector( size, size, size));
    p.push_back(Vector( size, size,-size));
    p.push_back(Vector( size,-size, size));
    p.push_back(Vector( size,-size,-size));
    p.push_back(Vector(-size, size, size));
    p.push_back(Vector(-size, size,-size));
    p.push_back(Vector(-size,-size, size));
    p.push_back(Vector(-size,-size,-size));
    transformPoints(p);

    box.reset();
    box += p;
}

bool
GlutCube::povrayExport(ostream &os) const
{
    os << "box { ";
    (Vector1*_size* 0.5).writePov(os) << ", ";
    (Vector1*_size*-0.5).writePov(os) << endl;

    os << "pigment { color rgb ";
    color().writePov(os) << '}' << endl;

    transformation().writePov(os) << endl;

    os << "}" << endl;

    return true;
}

void
GlutCube::position(const Vector &min,const Vector &max)
{
    _size = 1.0;

    const Vector center = (min+max)*0.5;
    Vector size = max-min;
    size.abs();

    transformation() = matrixScale(size) * matrixTranslate(center);
}

void
GlutCube::position(const Vector &pos,const real width,const real height,const real depth)
{
    _size = 1.0;
    Vector size(width,height,depth);
    size.abs();
    size *= 0.5;

    transformation() =
        matrixScale(size) *
        matrixTranslate(pos);
}

      GLdouble &GlutCube::size()       { return _size; }
const GLdouble &GlutCube::size() const { return _size; }

////////////////////

GlutCylinder::GlutCylinder(const bool solid,const GLdouble radius,const GLdouble height,const GLint slices,const GLint stacks,const GLint loops)
: GltShape(solid), _radius(radius), _height(height), _slices(slices), _stacks(stacks), _loops(loops)
{
}

GlutCylinder::~GlutCylinder()
{
}

void
GlutCylinder::draw() const
{
    // Well, GLUT doesn't have cylinder, so we resort
    // to glu quadric

    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        #ifdef GLUTM_FREEGLUT
        if (solid())
            glutSolidCylinder(_radius, _height, _slices, _stacks);
        else
            glutWireCylinder(_radius, _height, _slices, _stacks);
        #else
        GLUquadricObj *quadObj = gluNewQuadric();
        gluQuadricDrawStyle(quadObj, (GLenum) (solid() ? GLU_FILL : GLU_SILHOUETTE));
        gluQuadricNormals(quadObj, (GLenum) GLU_SMOOTH);
        gluQuadricOrientation(quadObj, (GLenum) GLU_OUTSIDE);
        gluCylinder(quadObj, _radius, _radius, _height, _slices,_stacks);
        if (solid())
        {
            gluQuadricOrientation(quadObj, (GLenum) GLU_INSIDE);
            gluDisk(quadObj,0.0,_radius,_slices,_loops);
            glTranslatef(0.0,0.0,_height);
            glRotatef(180,0.0,1.0,0.0);
            gluDisk(quadObj,0.0,_radius,_slices,_loops);
        }
        gluDeleteQuadric(quadObj);
        #endif
    glPopMatrix();

    GLERROR;
}

GLdouble
GlutCylinder::volume() const
{
    return cylinderVolume(_radius,_height);
}

void
GlutCylinder::boundingBox(BoundingBox &box) const
{
    vector<Vector> p;
    p.reserve(8);
    p.push_back(Vector( _radius, _radius, 0));
    p.push_back(Vector( _radius,-_radius, 0));
    p.push_back(Vector(-_radius, _radius, 0));
    p.push_back(Vector(-_radius,-_radius, 0));
    p.push_back(Vector( _radius, _radius, _height));
    p.push_back(Vector( _radius,-_radius, _height));
    p.push_back(Vector(-_radius, _radius, _height));
    p.push_back(Vector(-_radius,-_radius, _height));
    transformPoints(p);

    box.reset();
    box += p;
}

bool
GlutCylinder::povrayExport(ostream &os) const
{
    os << "cylinder { ";
    Vector0          .writePov(os) << ", ";
    (VectorZ*_height).writePov(os) << ", " << _radius << endl;

    os << "pigment { color rgb ";
    color().writePov(os) << '}' << endl;

    transformation().writePov(os) << endl;

    os << "}" << endl;

    return true;
}

void
GlutCylinder::position(const Vector &begin,const Vector &end,const double radius)
{
    Vector dir  = end - begin;

    _radius = radius;
    _height = dir.length();
    dir.normalize();

    // Create new co-ordinate system
    // with [0,0,1] in direction of end,
    // [1,0,0] and [0,1,0] mutually orthogonal.

    if (fabs(dir.z())>0.8)
    {
        const Vector a = xProduct(dir,VectorY);
        const Vector b = xProduct(dir,a);
        transformation() = matrixOrient(a/a.length(),b/b.length(),dir);
    }
    else
    {
        const Vector a = xProduct(dir,VectorZ);
        const Vector b = xProduct(dir,a);
        transformation() = matrixOrient(a/a.length(),b/b.length(),dir);
    }

    transformation() = transformation() * matrixTranslate(begin);
}

      GLdouble &GlutCylinder::radius()       { return _radius; }
      GLdouble &GlutCylinder::height()       { return _height; }
      GLint    &GlutCylinder::slices()       { return _slices; }
      GLint    &GlutCylinder::stacks()       { return _stacks; }
      GLint    &GlutCylinder::loops()        { return _loops; }

const GLdouble &GlutCylinder::radius() const { return _radius; }
const GLdouble &GlutCylinder::height() const { return _height; }
const GLint    &GlutCylinder::slices() const { return _slices; }
const GLint    &GlutCylinder::stacks() const { return _stacks; }
const GLint    &GlutCylinder::loops()  const { return _loops;  }

////////////////////

GlutCone::GlutCone
(
    const bool solid,
    const GLdouble base,
    const GLdouble height,
    const GLint slices,
    const GLint stacks,
    const bool closed
)
: GltShape(solid),
  _base(base),
  _height(height),
  _slices(slices),
  _stacks(stacks),
  _closed(closed)
{
}

GlutCone::~GlutCone()
{
}

void
GlutCone::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidCone(_base,_height,_slices,_stacks);
        else
            glutWireCone(_base,_height,_slices,_stacks);

        #ifndef GLUTM_FREEGLUT
        if (solid() && _closed)
        {
            GLUquadricObj *quadObj = gluNewQuadric();
            gluQuadricDrawStyle(quadObj, (GLenum) (solid() ? GLU_FILL : GLU_SILHOUETTE));
            gluQuadricNormals(quadObj, (GLenum) GLU_SMOOTH);
            gluQuadricOrientation(quadObj, (GLenum) GLU_OUTSIDE);
            gluQuadricOrientation(quadObj, (GLenum) GLU_INSIDE);
            gluDisk(quadObj,0.0,_base,_slices,_stacks);
            gluDeleteQuadric(quadObj);
        }
        #endif

    glPopMatrix();

    GLERROR;
}

GLdouble
GlutCone::volume() const
{
    return coneVolume(_base,_height);
}

void
GlutCone::boundingBox(BoundingBox &box) const
{
    vector<Vector> p;
    p.reserve(8);
    p.push_back(Vector( _base, _base, 0));
    p.push_back(Vector( _base,-_base, 0));
    p.push_back(Vector(-_base, _base, 0));
    p.push_back(Vector(-_base,-_base, 0));
    p.push_back(Vector(     0,     0, _height));
    transformPoints(p);

    box.reset();
    box += p;
}

      GLdouble &GlutCone::base()         { return _base;   }
      GLdouble &GlutCone::height()       { return _height; }
      GLint    &GlutCone::slices()       { return _slices; }
      GLint    &GlutCone::stacks()       { return _stacks; }
      bool     &GlutCone::closed()       { return _closed; }

const GLdouble &GlutCone::base()   const { return _base;   }
const GLdouble &GlutCone::height() const { return _height; }
const GLint    &GlutCone::slices() const { return _slices; }
const GLint    &GlutCone::stacks() const { return _stacks; }
const bool     &GlutCone::closed() const { return _closed; }

////////////////////

GlutTorus::GlutTorus(const bool solid,const GLdouble innerRadius,const GLdouble outerRadius,const GLint nsides,const GLint rings)
: GltShape(solid), _innerRadius(innerRadius), _outerRadius(outerRadius), _nsides(nsides), _rings(rings)
{
}

GlutTorus::~GlutTorus()
{
}

void
GlutTorus::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidTorus(_innerRadius,_outerRadius,_nsides,_rings);
        else
            glutWireTorus(_innerRadius,_outerRadius,_nsides,_rings);
    glPopMatrix();

    GLERROR;
}

      GLdouble &GlutTorus::innerRadius()       { return _innerRadius; }
      GLdouble &GlutTorus::outerRadius()       { return _outerRadius; }
      GLint    &GlutTorus::nsides()            { return _nsides;      }
      GLint    &GlutTorus::rings()             { return _rings;       }

const GLdouble &GlutTorus::innerRadius() const { return _innerRadius; }
const GLdouble &GlutTorus::outerRadius() const { return _outerRadius; }
const GLint    &GlutTorus::nsides()      const { return _nsides;      }
const GLint    &GlutTorus::rings()       const { return _rings;       }

////////////////////

GlutDodecahedron::GlutDodecahedron(const bool solid)
: GltShape(solid)
{
}

GlutDodecahedron::~GlutDodecahedron()
{
}

void
GlutDodecahedron::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidDodecahedron();
        else
            glutWireDodecahedron();
    glPopMatrix();

    GLERROR;
}

////////////////////

GlutOctahedron::GlutOctahedron(const bool solid)
: GltShape(solid)
{
}

GlutOctahedron::~GlutOctahedron()
{
}

void
GlutOctahedron::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidOctahedron();
        else
            glutWireOctahedron();
    glPopMatrix();

    GLERROR;
}

////////////////////

GlutTetrahedron::GlutTetrahedron(const bool solid)
: GltShape(solid)
{
}

GlutTetrahedron::~GlutTetrahedron()
{
}

void
GlutTetrahedron::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidTetrahedron();
        else
            glutWireTetrahedron();
    glPopMatrix();

    GLERROR;
}

////////////////////

GlutIcosahedron::GlutIcosahedron(const bool solid)
: GltShape(solid)
{
}

GlutIcosahedron::~GlutIcosahedron()
{
}

void
GlutIcosahedron::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidIcosahedron();
        else
            glutWireIcosahedron();
    glPopMatrix();

    GLERROR;
}

/////////////

GlutTeapot::GlutTeapot(const bool solid,const GLdouble size)
: GltShape(solid), _size(size)
{
}

GlutTeapot::~GlutTeapot()
{
}

void
GlutTeapot::draw() const
{
    GLERROR;

    glPushMatrix();
        transformation().glMultMatrix();
        glColor();
        if (solid())
            glutSolidTeapot(_size);
        else
            glutWireTeapot(_size);
    glPopMatrix();

    GLERROR;
}

      GLdouble &GlutTeapot::size()       { return _size; }
const GLdouble &GlutTeapot::size() const { return _size; }

