#include "chaos.h"

#include <glt/gl.h>

GltRandomDouble<GltRandomLCG> ChaosSystem::_random(-1.2,1.2);
GltRandomDouble<GltRandomLCG> ChaosSystem::_mutate(-1.0,1.0);

ChaosSystem::ChaosSystem()
: _lastSeed(0)
{
}

void ChaosSystem::advancexy(const double x,const double y,double &xn,double &yn) const
{
    xn = _a[0] + _a[1]*x + _a[2]*x*x + _a[3]*x*y + _a[ 4]*y + _a[ 5]*y*y;
    yn = _a[6] + _a[7]*x + _a[8]*x*x + _a[9]*x*y + _a[10]*y + _a[11]*y*y;
}

void ChaosSystem::mutate(const double m)
{
    for (int i=0; i<12; i++)
        _a[i] += m*_mutate.rand();

    findSize();
}

void ChaosSystem::set(const std::string &id)
{
    if (id.size()!=13)
        return;

    int i=0;

    for (i=0; i<12; i++)
        _a[i] = (id[i+1]-'A')*0.1 - 1.2;

    findSize();
}

void ChaosSystem::findSize()
{
    _x = _y = 0.0;

    double xmin = 0.0;
    double xmax = 0.0;
    double ymin = 0.0;
    double ymax = 0.0;

    const int n = 4000;

    for (int i=0; i<n; i++)
    {
        advancexy(_x,_y,_x,_y);

        if (i==100)
        {
            xmin = xmax = _x;
            ymin = ymax = _y;
        }
        else
        {
            xmin = std::min(_x,xmin);
            xmax = std::max(_x,xmax);
            ymin = std::min(_y,ymin);
            ymax = std::max(_y,ymax);
        }
    }

    const double limit = 10000;

    xmin = std::min( limit,xmin);
    xmax = std::max(-limit,xmax);
    ymin = std::min( limit,ymin);
    ymax = std::max(-limit,ymax);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScaled(0.9,0.9,1.0);
    glOrtho(xmin,xmax,ymin,ymax,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void ChaosSystem::set(const uint32 seed)
{
    const int n    = 4000;
    bool found     = false;
    bool firstTime = true;

    while (!found)
    {
        _x = _y = 0.0;

        if (seed && firstTime)
            _random.base().seed(_lastSeed = seed);
        else
            _lastSeed = _random.base().rand();

        firstTime = false;

        {
            for (int i=0; i<12; i++)
                _a[i] = _random.rand();
        }

        // Inverse displacement between two samples
        const double epsilon = 1e6;

        double xe = 1.0/epsilon;
        double ye = 0.0;

        double lsum = 0.0;

        double xmin = 0.0;
        double xmax = 0.0;
        double ymin = 0.0;
        double ymax = 0.0;

        for (int i=0; i<n; i++)
        {
            advancexy(_x,_y,_x,_y);
            advancexy(xe,ye,xe,ye);

            const double dx = xe - _x;
            const double dy = ye - _y;

            const double d2 = dx*dx+dy*dy;
            const double df = epsilon * d2;
            const double rs = 1.0 / df*df;

            xe = _x + rs*(xe-_x);
            ye = _y + rs*(ye-_y);

            lsum += log(df);

            if (i==100)
            {
                xmin = xmax = _x;
                ymin = ymax = _y;
            }
            else
            {
                xmin = std::min(_x,xmin);
                xmax = std::max(_x,xmax);
                ymin = std::min(_y,ymin);
                ymax = std::max(_y,ymax);
            }

            found = false;

            if (fabs(_x) + fabs(_y) > 1e6)
                break;

            if (i>100 && 0.721348*lsum/double(i+1) < 0.005)
                break;

            found = true;
        }

        if (!found)
            continue;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glScaled(0.9,0.9,1.0);
        glOrtho(xmin,xmax,ymin,ymax,-1.0,1.0);
        glMatrixMode(GL_MODELVIEW);
        break;
    }
}

void
ChaosSystem::draw(const uint32 n)
{
    glBegin(GL_POINTS);

    for (uint32 i=0; i<n; i++)
    {
        advancexy(_x,_y,_x,_y);
        glVertex2f(_x,_y);
    }

    glEnd();
}

ChaosSystem &
ChaosSystem::operator=(const ChaosSystem &sys)
{
    _x = sys._x;
    _y = sys._y;
    memcpy(_a,sys._a,sizeof(_a));
    _lastSeed = sys._lastSeed;
    return *this;
}

uint32
ChaosSystem::lastSeed() const
{
    return _lastSeed;
}

