#include "init.h"
#include "psystem.h"

#include <math/random.h>
#include <glt/rgb.h>

InitPosition::InitPosition()
{
}

InitPosition::~InitPosition()
{
}

void
InitPosition::update(ParticleSystem &system) const
{
    if (_options.seed)
        GltRandomLFSRMix::rng = GltRandomLFSRMix(_options.seed);

    if (_options.line)
        initLine(system,_options.a,_options.b);

    if (_options.box)
        initBox(system,_options.a,_options.b);

    if (_options.circle)
        initCircle(system,_options.a,_options.radius);

    if (_options.disk)
        initDisk(system,_options.a,_options.radius);

    if (_options.sphere)
        initSphere(system,_options.a,_options.radius);
}

GltFieldPtr
InitPosition::settings()
{
    GltFields *root = new GltFields("position");
    root->add(_options.line,  "line"    );
    root->add(_options.box,   "box"     );
    root->add(_options.circle,"circle"  );
    root->add(_options.disk,  "disk"    );
    root->add(_options.sphere,"sphere"  );
    root->add(_options.a,     "a"       );
    root->add(_options.b,     "b"       );
    root->add(_options.radius,"radius"  );
    root->add(_options.seed,  "seed"    );
    return root;
}

//

bool InitPosition::initLine(ParticleSystem &system,const Vector &a,const Vector &b)
{
    const int n = system.size();
    int j = 0;

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++,j++)
        i->_position = lerp(a,b,double(j)/double(n-1));

    return true;
}

bool InitPosition::initGrid(ParticleSystem &system,const Vector &a,const Vector &b)
{
    ParticleSystem::iterator i=system.begin();
    const Vector d = b-a;

    // Find the maximum size of 3D grid that
    // can be accomodated

    int s = 1;
    while ((s+1)*(s+1)*(s+1)<system.size())
        s++;

    const double max = s-1;

    // TODO - Adjust size in x, y and z according
    // to ratio of box edges

    for (int z=0; z<s; z++)
    {
        const double dz = double(z)/max;
        for (int y=0; y<s; y++)
        {
            const double dy = double(y)/max;
            for (int x=0; x<s; x++)
            {
                const double dx = double(x)/max;
                i->_position = Vector(a.x()+d.x()*dx,a.y()+d.y()*dy,a.z()+d.z()*dz);
                i++;
            }
        }
    }

    // Remaining particles are expired

    for (;i!=system.end();i++)
        i->_expired = true;

    return true;
}

bool InitPosition::initBox(ParticleSystem &system,const Vector &a,const Vector &b)
{
    const Vector d = b-a;
    GltRandomDouble<> r(0.0,1.0);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        i->_position = a + Vector(r.rand()*d.x(),r.rand()*d.y(),r.rand()*d.z());

    return true;
}

bool InitPosition::initCircle(ParticleSystem &system,const Vector &a,const double radius)
{
    GltRandomDouble<> r(0.0,2*M_PI);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        const double t = r.rand();
        i->_position = Vector(a.x()+radius*cos(t),a.y()+radius*sin(t),a.z());
    }

    return true;
}

bool InitPosition::initDisk(ParticleSystem &system,const Vector &a,const double radius)
{
    GltRandomDouble<> r1(0.0,2*M_PI);
    GltRandomDouble<> r2(0.0,radius);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        const double t = r1.rand();
        const double r = r2.rand();
        i->_position = Vector(a.x()+r*cos(t),a.y()+r*sin(t),a.z());
    }

    return true;
}

bool InitPosition::initSphere(ParticleSystem &system,const Vector &a,const double radius)
{
    GltRandomSphere<> r(radius);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        i->_position = a + radius*r.rand();

    return true;
}

//

InitPosition::InitPositionOptions::InitPositionOptions()
:
    line(false),
    box(false),
    circle(false),
    disk(false),
    sphere(false),
    a(Vector0),
    b(Vector0),
    radius(1.0),
    seed(0)
{
}

///////////////////////////////////////////////////

InitVelocity::InitVelocity()
{
}

InitVelocity::~InitVelocity()
{
}

void
InitVelocity::update(ParticleSystem &system) const
{
    if (_options.seed)
        GltRandomLFSRMix::rng = GltRandomLFSRMix(_options.seed);

    if (_options.circular)
        initVelocityCircular(system,_options.speed);

    if (_options.spherical)
        initVelocitySpherical(system,_options.speed);
}

GltFieldPtr
InitVelocity::settings()
{
    GltFields *root = new GltFields("velocity");
    root->add(_options.circular,  "circular"  );
    root->add(_options.spherical, "spherical" );
    root->add(_options.speed,0.1, "speed"     );
    root->add(_options.seed,      "seed"      );
    return root;
}

bool InitVelocity::initVelocityCircular(ParticleSystem &system,const double speed)
{
    GltRandomDouble<> r(0.0,2*M_PI);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        const double t = r.rand();
        i->_velocity = Vector(speed*cos(t),speed*sin(t),0.0);
    }

    return true;
}

bool InitVelocity::initVelocitySpherical(ParticleSystem &system,const double speed)
{
    GltRandomSphere<> r(speed);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        i->_velocity = r.rand();

    return true;
}

//

InitVelocity::InitVelocityOptions::InitVelocityOptions()
:
    circular(false),
    spherical(false),
    speed(0.0),
    seed(0)
{
}

/////////////////////////////////////////////////////////

InitColor::InitColor()
{
}

InitColor::~InitColor()
{
}

void
InitColor::update(ParticleSystem &system) const
{
    if (_options.blend)
        initColorBlend(system,_options.a,_options.b);

    if (_options.blend3)
        initColorBlend(system,_options.a,_options.b,_options.c);
}

GltFieldPtr
InitColor::settings()
{
    GltFields *root = new GltFields("color");
    root->add(_options.blend, "blend");
    root->add(_options.blend3,"blend3");
    root->add(_options.a,     "a");
    root->add(_options.b,     "b");
    root->add(_options.c,     "c");
    return root;
}

bool
InitColor::initColorBlend(ParticleSystem &system,const GltColor &a,const GltColor &b)
{
    GltRandomDouble<> r(0.0,1.0);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
        i->_color = lerp(a,b,r.rand());

    return true;
}

bool
InitColor::initColorBlend(ParticleSystem &system,const GltColor &a,const GltColor &b,const GltColor &c)
{
    GltColor d1 = b-a;
    GltColor d2 = c-a;

    GltRandomDouble<> r(0.0,1.0);

    for (ParticleSystem::iterator i=system.begin(); i!=system.end(); i++)
    {
        // TODO - We want points uniformly distributed...

        const double t = r.rand();
        const double u = r.rand()*(1.0-t);
        i->_color = a + d1*t + d2*u;
    }

    return true;
}

InitColor::InitColorOptions::InitColorOptions()
:
    blend(false),
    blend3(false),
    a(black),
    b(black),
    c(black)
{
}

