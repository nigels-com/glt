#ifndef GRIPS_WINDOW_H
#define GRIPS_WINDOW_H

#include <glutm/winexam.h>
#include <glutm/axes.h>

#include <glt/color.h>
#include <glt/fontasci.h>
#include <glt/texture.h>
#include <glt/material.h>
#include <glt/light.h>

#include <node/text.h>
#include <node/line.h>
#include <node/fields.h>
#include <node/fieldmen.h>
#include <node/registry.h>
#include <node/interp.h>
#include <node/sprite.h>

#include <math/matrix4.h>

#include <misc/observer.h>

#include <mesh/mesh.h>

#include "trail.h"
#include "field.h"
#include "grid.h"

#include "network.h"

#include <vector>
#include <string>
#include <iosfwd>

class Document;
class GripsMaster;
class GripsSlave;

////////////////////////////////////////

class Grips : public GlutWindowExaminer, GltObserver<Document>
{
    friend class GripsServer;
    friend class GripsClient;

public:
    Grips
    (
        int width                = widthDefault,
        int height               = heightDefault,
        int x                    = xDefault,
        int y                    = yDefault
    );

    ~Grips();

    void OnOpen();
    void OnClose();
    void OnDisplay();
    void OnTick();
    void OnMenu(int value);
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMouse(int button, int state, int x, int y);
    void OnMotion(int x, int y);

    void read(std::istream &is);
    void read(const std::string &str);
    void read(const void *data);
    void write(std::ostream &os,const std::string &prefix = "") const;

    void OnNotify(const Document *subject);

    //

    static const std::string help;

protected:

    void step();

    void setAnimation(const bool animate);

    void drawLogo(
        const GltViewport &viewport,
        const GltTexture  &texture,
        const GltHorizontalAlignment &alignH,
        const GltVerticalAlignment   &alignV,
        const bool blend,
        const GltColor &color);

    void drawReflections() const;
    void drawShadows() const;
    void drawGrid() const;
    void drawParticles() const;
    void drawFloor() const;
    void drawBox() const;
    void drawShadowVolumes() const;

private:

    // Display options

    class DisplayOptions
    {
    public:
        DisplayOptions();

        bool animation;
        int  steps;
        int  wait;
        bool info;
        bool logo;
        bool formula;
        bool options;
        bool editVal;
        bool particles;
        bool points;
        bool billboard;
        bool trail;
        bool accel;
        bool center;
        bool follow;
        bool box;
        bool floor;
        bool lighting;
        bool ortho;
        bool reflections;
        bool shadows;
        bool stencil;
        bool selfShadows;
        bool shadowVolumes;

        Vector4 shadowPlane;

        int32 slices;
        int32 stacks;

        GltOrtho orthoConfig;
    };

    //

    Document              *_document;

    DisplayOptions _display;

    // Display settings

    double      _radiusScale;

    GltColor    _background;
    GltLight    _light0;
    GltLight    _light1;
    GltLight    _light2;

    GlutAxes     _axes;
    double       _axesSize;
    GltGrid      _grid;

//  GltSprite    _sprite;

    Field       _field;

    Matrix                  _spin;
    GltInterpolatorRotation _spinInterp;

    int         _current;

    // Temp

    int tileX;
    int tileY;
    int tileN;

    // OpenGL helpers

    GltFontAscii    _font;
    GltTextOverlay  _info;

    GltTexture      _formula;
    GltTexture      _eScience;
    GltTexture      _rmit;
    GltTexture      _vpac;

    GltLine         _center;

//    GltTexture  _earth;             // TODO - Use texture maps for particles
//    GltTexture  _blob;
//    GltTexture  _star;

    //
    GltTexture _texture[3];
    int        _textureCurrent;

    GltMaterial _material;
    Mesh        _quad;

    // Misc

    std::string _filename;
    std::string _options;

    double          _maxTime;

    // Networking

    GripsServer     _server;
    GripsClient     _client;
    GripsHttpClient _settingsClient;

    // Registry

    GltFieldPtr      settings();

    GltRegistry      _settings;
    GltRegistryMenu  _menu;

    typedef enum
    {
        NBODY_STEP,
        NBODY_ANIMATE,

        NBODY_TRAIL,
        NBODY_TRAIL_RESET,
        NBODY_TRAIL_LONGER,
        NBODY_TRAIL_SHORTER,

        NBODY_DISPLAY_INFO,
        NBODY_DISPLAY_POINTS,
        NBODY_DISPLAY_ACCEL,
        NBODY_DISPLAY_CENTER,
        NBODY_DISPLAY_FORCE_FIELD,
        NBODY_DISPLAY_FORCE_FIELD_MORE,
        NBODY_DISPLAY_FORCE_FIELD_LESS,
        NBODY_DISPLAY_AXES,
        NBODY_DISPLAY_FOLLOW,
        NBODY_DISPLAY_LIGHTING

    } MenuCallbacks;
};

#endif
