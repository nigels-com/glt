#ifndef RasterSaver_H
#define RasterSaver_H

// RasterSaver.h
// James Ward 02/10/01 (espresso@crema.co.uk)
//
// Screen Saver Implementation
//

#include <vector>
#include <string>
using namespace std;

#include <glt/texture.h>
#include <misc/timer.h>
#include <math/random.h>
#include <node/dlist.h>
#include <glutm/window.h>

#include "Model.h"

class RasterSaver : public GlutWindow
{
public:
    RasterSaver();
    virtual ~RasterSaver();

    void OnOpen();
    void OnClose();
    void OnDisplay();

private: // initialisation & saver scenes
    void SetupModels();
    void SetupTextures();

    bool drawScene1();
    bool drawScene2();
    bool drawScene3();

private: // various drawing functions

    static void drawBar(float x, float y, float w, float h);
    static void drawSphere(float Radius, int Slices, int Stacks, bool Wire=false);
    static void drawBars(float time, float x, float y, float w, float h, int num);

    void drawKana    (float x, float y, float h, int kana=0);
    void drawCode    (float x, float y, float w, float h, float scroll=0);
    void drawTimecode(float time, int w, int h) const;
    void drawRasters (float time, int w, int h) const;

    void myNumString(const char *str, float x, float y, float s) const;

    void drawSnow(
        float Time, float x, float y, int Width, int Height,
        bool loseSync=true, int Image=0
    ) const;


    // Constants

    const static real jitterAmp;        // vertical jitter amplitude
    const static real jitterRate;       // vertical jitter rate
    const static real jitterRotation;   // strength of rotation jitter

    const static real fadeAmp;          // amplitude of raster fade effect (0..1)
    const static real fadeRate;     // raster fade cycle rate

private:

    bool   _bRasters;   // draw rasters?
    bool   _bSnow;      // draw snowy CRTs?
    Timer  _timer;
    int    _scene;      // Current scene
    bool   _done;       // Ready to change scenese?

    GltRandomDouble<> _rng;

    // OpenGL textures

    GltTexture _crt;
    GltTexture _kana;
    GltTexture _code;
    GltTexture _numbers;
    GltTexture _snow;
    GltTexture _raster;

    // OpenGL display lists

    vector<GltDisplayList> _sphere;
    vector<Model>          _building;
};

#endif
