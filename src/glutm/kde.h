//-----------------------------------------------------------------------------
//
// kmorph3d - port of "morph3d" from xlock
//

#ifndef GLUTM_KDE_H
#define GLUTM_KDE_H

#include <glutm/config.h>

#if defined(GLUTM_SAVER) && defined(GLT_UNIX)

//#include <kglobal.h>
//#include <qt.h>
#include <qtimer.h>

#include <X11/Xlib.h>

// Adapted from kmorph3d

class GlutMasterKdeSaver : public QObject
{
    Q_OBJECT
public:
    GlutMasterKdeSaver( Drawable drawable );
    virtual ~GlutMasterKdeSaver();

protected:
    void readSettings();

protected slots:
    void slotTimeout();

protected:
    Drawable    _mDrawable;
    GC          _mGc;
    unsigned    _mWidth;
    unsigned    _mHeight;
    QTimer      _timer;
    int         _colorContext;
};

#endif
#endif

