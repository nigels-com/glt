#include "intersct.h"

//

#include <node/shape.h>
#include <glutm/shape.h>

#include <mesh/mesh.h>

#include <math/vector3.h>
#include <math/matrix4.h>
#include <math/umatrix.h>

#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

//

// Define this for info
//#define DEBUG_INTERSECT

#if defined(NDEBUG) && defined(DEBUG_INTERSECT)
#undef DEBUG_INTERSECT
#endif

bool rayBox(const Vector &a,const Vector &b,const Vector &min,const Vector &max)
{
    const Vector d = b-a;
    const double tol = 1.0e-4;

    double tMin = 0.0;
    double tMax = 1.0;
    double t;

    if (fabs(d.x())>tol)
    {
        const double idx = 1.0/d.x();

        if (d.x()>0.0)
        {
            if ( (t=(max.x()-a.x())*idx) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(min.x()-a.x())*idx) > tMax) return false; tMin = std::max(t,tMin);
        }
        else
        {
            if ( (t=(min.x()-a.x())*idx) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(max.x()-a.x())*idx) > tMax) return false; tMin = std::max(t,tMin);
        }
    }
    else
        if (a.x()<min.x() || a.x()>max.x())
            return false;

    if (fabs(d.y())>tol)
    {
        const double idy = 1.0/d.y();

        if (d.y()>0.0)
        {
            if ( (t=(max.y()-a.y())*idy) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(min.y()-a.y())*idy) > tMax) return false; tMin = std::max(t,tMin);
        }
        else
        {
            if ( (t=(min.y()-a.y())*idy) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(max.y()-a.y())*idy) > tMax) return false; tMin = std::max(t,tMin);
        }
    }
    else
        if (a.y()<min.y() || a.y()>max.y())
            return false;

    if (fabs(d.z())>tol)
    {
        const double idz = 1.0/d.z();

        if (d.z()>0.0)
        {
            if ( (t=(max.z()-a.z())*idz) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(min.z()-a.z())*idz) > tMax) return false; tMin = std::max(t,tMin);
        }
        else
        {
            if ( (t=(min.z()-a.z())*idz) < tMin) return false; tMax = std::min(t,tMax);
            if ( (t=(max.z()-a.z())*idz) > tMax) return false; tMin = std::max(t,tMin);
        }
    }
    else
        if (a.z()<min.z() || a.z()>max.z())
            return false;

    return tMin<tMax;
}


//

CsgIntersectionType intersectShapes
(
    const GltShape &a,
    const GltShape &b,
    const CsgIntersectionType ifUnknown
)
{
    //
    // If both shapes are spheres, we can do an accurate
    // test...
    //

    const GlutSphere *s1 = dynamic_cast<const GlutSphere *>(&a);
    const GlutSphere *s2 = dynamic_cast<const GlutSphere *>(&b);

    if (s1 && s2)
    {
        const Matrix &m1 = s1->transformation();
        const Matrix &m2 = s2->transformation();

        UnMatrix u1 = m1.unmatrix();
        UnMatrix u2 = m2.unmatrix();

        // At the moment we can only cope with uniform
        // scale, rotation and translation - no shear or
        // perspective

        if
        (
            u1.uniformScale()  && u2.uniformScale() &&
            u1.noShear()       && u2.noShear()      &&
            u1.noPerspective() && u2.noPerspective()
        )
        {
            const double r1 = u1[U_SCALEX]*s1->radius();
            const double r2 = u2[U_SCALEX]*s2->radius();

            const Vector c1 = m1*Vector0;
            const Vector c2 = m2*Vector0;

            const bool ret = c1.dist(c2)<sqr(r1+r2);

            #ifdef DEBUG_INTERSECT
            cout << "Sphere-sphere intersection of ";
            cout << s1->name() << " & " << s2->name() << " -> " << ret << endl;
            #endif

            return ret ? INTERSECTION : DISJOINT;
        }
    }

    //
    // If both shapes are cylinders, and no rotation is applied,
    // we can do an accurate test, based on circles
    //

    const GlutCylinder *c1 = dynamic_cast<const GlutCylinder *>(&a);
    const GlutCylinder *c2 = dynamic_cast<const GlutCylinder *>(&b);

    if (c1 && c2)
    {
        const Matrix &m1 = c1->transformation();
        const Matrix &m2 = c2->transformation();

        UnMatrix u1 = m1.unmatrix();
        UnMatrix u2 = m2.unmatrix();

        // At the moment we can only cope with uniform
        // scale, rotation and translation - no shear or
        // perspective

        // TODO - Check for uniform XY scale

        if
        (
//          u1.uniformScale()  && u2.uniformScale() &&
            u1.noRotation()    && u2.noRotation()   &&
            u1.noShear()       && u2.noShear()      &&
            u1.noPerspective() && u2.noPerspective()
        )
        {
            const double r1 = u1[U_SCALEX]*c1->radius();
            const double r2 = u2[U_SCALEX]*c2->radius();

            const Vector s1 = m1*Vector0;
            const Vector s2 = m2*Vector0;

            const Vector e1 = m1*Vector(0,0,c1->height());
            const Vector e2 = m2*Vector(0,0,c2->height());

            const double min1 = std::min(s1.z(),e1.z());
            const double min2 = std::min(s2.z(),e2.z());
            const double max1 = std::max(s1.z(),e1.z());
            const double max2 = std::max(s2.z(),e2.z());

            bool ret = DISJOINT;

            if (max1<min2 || max2<min1)
            {
                // Cylinders don't overlap in z
            }
            else
            {
                // Check that the cylinders actually overlap in z

//              assert(s2.z()>=min1 && s2.z()<=max1 || e2.z()>=min1 && e2.z()<=max1);
//              assert(s1.z()>=min2 && s1.z()<=max2 || e1.z()>=min2 && e1.z()<=max2);

                // Check if circles in XY plane touch

                ret = Vector(s1.x(),s1.y(),0.0).dist(Vector(s2.x(),s2.y(),0.0))<sqr(r1+r2);
            }

            #ifdef DEBUG_INTERSECT
            cout << "Cylinder-cylinder intersection of ";
            cout << c1->name() << " & " << c2->name() << " -> " << ret << endl;
            #endif

            return ret ? INTERSECTION : DISJOINT;
        }
    }

    //
    // If both shapes are convex polyhedral meshes, we can do
    // an accurate test...
    //

    const Mesh *m1 = dynamic_cast<const Mesh *>(&a);
    const Mesh *m2 = dynamic_cast<const Mesh *>(&b);

    if (m1 && m2 && m1->transformation()==m2->transformation())
    {
        // Use bounding boxes for trivial rejection

        if (!a.intersects(b))
            return DISJOINT;

        // Check for shared triangles between m1 and m2

        {
            deque<Triangle>::const_iterator i = m1->triangle().begin();
            for (; i!=m1->triangle().end(); i++)
            {
                deque<Triangle>::const_iterator j = m2->triangle().begin();
                for (; j!=m2->triangle().end(); j++)
                    if (*i==*j)
                        return SHARED_FACE;
            }
        }

        // Check for shared quads between m1 and m2

        {
            deque<Quad>::const_iterator i = m1->quad().begin();
            for (; i!=m1->quad().end(); i++)
            {
                deque<Quad>::const_iterator j = m2->quad().begin();
                for (; j!=m2->quad().end(); j++)
                    if (*i==*j)
                        return SHARED_FACE;
            }
        }

/*
    // Based on face culling
    // REVISIT

        // Check for points of m1 inside of m2

        {
            deque<Point>::const_iterator i = m1->point().begin();
            for (; i!=m1->point().end(); i++)
                if (m2->inside(*i))
                    return INTERSECTION;
        }

        // Check for points of m2 inside of m1
        {
            deque<Point>::const_iterator i = m2->point().begin();
            for (; i!=m2->point().end(); i++)
                if (m1->inside(*i))
                    return INTERSECTION;
        }
*/

        return DISJOINT;
    }

    //
    // If one object is a convex polyhedral mesh,
    // we should use this rather than the bounding
    // box
    //

    if (m1 || m2)
    {
        // Use bounding boxes for trivial rejection

        if (!a.intersects(b))
            return DISJOINT;

        //

        const Mesh     *m = (m1 ? m1 : m2);
        const GltShape *s = (m1 ? &b : &a);

        assert(m);
        assert(s);
        assert(m!=s);

        BoundingBox box;
        s->boundingBox(box);

        assert(box.defined());

        const Vector &min = box.min();
        const Vector &max = box.max();

        // Check for points of box inside of mesh

        {
            if (m->inside(Vector(min.x(),min.y(),min.z()))) return INTERSECTION;
            if (m->inside(Vector(min.x(),min.y(),max.z()))) return INTERSECTION;
            if (m->inside(Vector(min.x(),max.y(),min.z()))) return INTERSECTION;
            if (m->inside(Vector(min.x(),max.y(),max.z()))) return INTERSECTION;
            if (m->inside(Vector(max.x(),min.y(),min.z()))) return INTERSECTION;
            if (m->inside(Vector(max.x(),min.y(),max.z()))) return INTERSECTION;
            if (m->inside(Vector(max.x(),max.y(),min.z()))) return INTERSECTION;
            if (m->inside(Vector(max.x(),max.y(),max.z()))) return INTERSECTION;
        }

        // Check that each triangle is outside of the box

        {
            deque<Triangle>::const_iterator i = m->triangle().begin();
            for (; i!=m->triangle().end(); i++)
            {
                const Triangle &t = *i;
                const Vector a = m->transformation() * *t[0];
                const Vector b = m->transformation() * *t[1];
                const Vector c = m->transformation() * *t[2];

                // Avoid recomputing duplicate rays in opposite
                // directions by comparing pointers.

                if (t[0]<t[1] && rayBox(a,b,min,max)) return INTERSECTION;
                if (t[0]<t[2] && rayBox(a,c,min,max)) return INTERSECTION;
                if (t[1]<t[2] && rayBox(b,c,min,max)) return INTERSECTION;
            }
        }

        return DISJOINT;
    }

    // We don't know, so just return default

    return ifUnknown;
}

