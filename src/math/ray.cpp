#include "ray.h"

/*! \file
    \brief   3D Ray Class
    \ingroup Math
*/

#include <math/plane.h>

#include <iostream>
using namespace std;

////////////////////////// Ray /////////////////////////////////

Ray::Ray()
: _origin(Vector0), _direction(Vector0)
{
}

Ray::Ray(const Vector &origin,const Vector &direction)
: _origin(origin), _direction(direction)
{
}

Ray::Ray(const Ray &ray)
{
    if (this!=&ray)
    {
        _origin    = ray._origin;
        _direction = ray._direction;
    }
}

Ray::~Ray()
{
}

      Vector &Ray::origin()          { return _origin; }
const Vector &Ray::origin()    const { return _origin; }
      Vector &Ray::direction()       { return _direction; }
const Vector &Ray::direction() const { return _direction; }

bool Ray::operator==(const Ray &r) const
{
    return _origin==r.origin() && _direction==r.direction();
}

std::ostream &
operator<<(std::ostream &os, const Ray &r)
{
    cout << "Origin: " << r.origin() << ", direction: " << r.direction();
    return cout;
}

bool
intersection(Vector &pos,const Ray &a,const Ray &b)
{
    Vector c = xProduct(a.direction(),b.direction());

    if (c.length()==0.0)
        return false;

    const Plane ac(a.origin(),xProduct(c,a.direction()));
    const Plane bc(b.origin(),xProduct(c,b.direction()));

    Vector ap = bc.intersectPosition(a.origin(),a.origin()+a.direction());
    Vector bp = ac.intersectPosition(b.origin(),b.origin()+b.direction());

    if ((ap-bp).length()<1.0e-3)
    {
        pos = ap;
        return true;
    }

    return false;
}
