#ifndef CSG_HISTOGRAMS_H
#define CSG_HISTOGRAMS_H

/** \file
 *  \brief   r,g,b,z Histograms
 *  \ingroup CSG
 *  \author  Nigel Stewart (nigels@nigels.com)
 *  \author  RMIT School of Computer Science and Information Technology
 *  \author  RMIT Department of Mechanical and Manufacturing Engineering
 */

#include <node/shape.h>
#include <node/histogrm.h>

///////////////////////////////// CsgHistograms ///////////////////////////////

class CsgHistograms : public GltShape
{
public:
    CsgHistograms();
    ~CsgHistograms();

    virtual void draw() const;

    bool &rBuffer();
    bool &gBuffer();
    bool &bBuffer();
    bool &zBuffer();

private:

    void updateHistograms();

    GltHistogram    _rBuffer;
    GltHistogram    _gBuffer;
    GltHistogram    _bBuffer;
    GltHistogram    _zBuffer;
    GltHistogram    _stencilBuffer;
};

#endif
