#ifndef GLT_RASTER_BAR
#define GLT_RASTER_BAR

#include <glt/color.h>

class GltRasterBar
{
public:
    GltRasterBar(const GltColor &edge,const GltColor &middle);

    void draw();

    double &height();
    double &pos();

private:

    GltColor _edge;
    GltColor _middle;

    double _height;
    double _pos;
};

#endif
