/** \file
 * CSG Rendering Demo
 *
 * This program renders saved csg tree files,
 * or pre-canned models available from the
 * menu.
 *
 * http://www.nigels.com/research/
 *
 * \author  Nigel Stewart (nigels@nigels.com)
 * \author  RMIT Dept. Mechanical and Manufacturing Engineering, Australia
 */

#include <glt/gl.h>
#include <glt/light.h>
#include <glt/material.h>
#include <glt/lightm.h>
#include <glt/frame.h>
#include <glt/fontasci.h>
#include <glt/info.h>
#include <glt/color.h>
#include <glt/buffer.h>
#include <glt/frame.h>
#include <glt/zplane.h>
#include <glt/error.h>
#include <glt/matrix.h>
#include <glt/rgb.h>

#include <node/text.h>
#include <node/histogrm.h>
#include <node/fields.h>
#include <node/registry.h>
#include <node/fieldmen.h>
#include <node/interp.h>
#include <node/skyspher.h>

#include <misc/file.h>

#include <glutm/main.h>
#include <glutm/winexam.h>

#include <csg/trees.h>
#include <csg/trees2.h>
#include <csg/trees3.h>
#include <csg/test.h>
#include <csg/shape.h>
#include <csg/histogrm.h>
#include <csg/capture.h>

#include <fonts/fonts.h>

#include <math/random.h>

#include <misc/compress.h>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

#include <mcheck.h>

// Define for debug info
// #define DEBUG_CSG

static const GltString info =
  "OpenGL CSG Rendering                \n\n"
  "Nigel Stewart                       \n"
  "RMIT School of Computer Science & IT\n"
  "3rd August 2007                    \n\n"
  "Left mouse button for menu.         ";

static const GltString banner =
  "                                                                   \n"
  " OpenGL CSG Rendering                                              \n"
  "                                                                   \n"
  " Nigel Stewart (nigels@nigels.com)                                 \n"
  " RMIT School of Computer Science & IT                              \n"
  " 3rd August 2007                                                   \n"
  "                                                                   \n"
  " Left mouse button for menu.                                       \n"
  "                                                                   \n"
  "         Right mouse for rotation.                                 \n"
  " SHIFT + Right mouse for panning.                                  \n"
  " CTRL  + Right mouse for zooming.                                  \n"
  "                                                                   \n"
  " Keypress                Action                                    \n"
  " -------------------------------------------------                 \n"
  "       1,2,3..           Select tree                               \n"
  " SHIFT 1,2,3..           Help page                                 \n"
  " i,o                     Zoom In/Out                               \n"
  " a,z,x,c                 Rotate                                    \n"
  " g,b,n,m                 Pan                                       \n"
  " f,v                     Forward and back                          \n"
  " p ;                     Save dot, table                           \n"
  " .                       Toggle real-time                          \n"
  " ?                       Object-space subtraction sequence         \n"
  " /                       Sample K subtraction sequence             \n"
  " + -                     Adjust maximum subtracted objects         \n"
  " [ ] { }                 Scale, translate frustrum in z            \n"
  "                                                                   \n"
  " F9                      Save RGB image                            \n"
  " F10                     Save stencil buffer                       \n"
  " F11                     Save z-buffer                             \n"
  "                                                                   \n"
  " q                       Quit                                      \n"
  " -------------------------------------------------                 \n";

static const GltString args =
    "Command line arguments:\n\n" \
    "filename                CSG model input file.\n" \
    "-size width height      Width and height of the window.\n" \
    "-fullscreen             Display full-screen.\n" \
    "-ini filename           File for internal settings.\n" \
    "-set name:value         Internal setting.\n" \
    "-quiet                  Suppress startup messages.\n" \
    "+keys                   List of keyboard events for processing.\n";

////////////////////////////////////////////////////////////////

class CsgDemo : public GlutWindowExaminer
{
public:
    CsgDemo(const int width,const int height,const string &set = std::string(),const string &iniFile = std::string());
    virtual ~CsgDemo();

    void OnOpen();
    void OnClose();
    void OnIdle();
    void OnDisplay();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
    void OnMenu(int value);
    void OnMouse(int button, int state, int x, int y);
    void OnReshape(int w, int h);
    void OnOrient(const Matrix &viewing,const Matrix &inverse);

    bool loadModel(istream &is);
    bool loadModel(const char *);

    typedef enum
    {
        MODEL_DEFAULT = 10000,
        MODEL_ROW,
        MODEL_GRID,
        MODEL_HOLLOW,
        MODEL_BOXSPHERE,
        MODEL_HELIX,
        MODEL_CONVEX_HELIX,
        MODEL_STEP_TOOL,
        MODEL_SWISS_CHEESE,
        MODEL_SWISS_CHEESE2,
        MODEL_PIPE,
        MODEL_DEGENERATE,
        MODEL_TRICKLE,
        MODEL_CSG_NORMALIS,

        MODEL_GSCS_ACYCLIC,
        MODEL_GSCS_RING4,
        MODEL_GSCS_RING5,
        MODEL_GSCS_SPIRAL,
        MODEL_GSCS_RING,

        MODEL_GSCS_CASE0,
        MODEL_GSCS_CASE1,
        MODEL_GSCS_CASE2,
        MODEL_GSCS_CASE3,
        MODEL_GSCS_CASE4,
        MODEL_GSCS_CASE5,
        MODEL_GSCS_CASE6,
        MODEL_GSCS_CASE7,
        MODEL_GSCS_CASE8,

        MODEL_CYLINDERS_2,
        MODEL_CYLINDERS_3,
        MODEL_CYLINDERS_4,
        MODEL_CYLINDERS_5,
        MODEL_CYLINDERS_6,
        MODEL_CYLINDERS_8,
        MODEL_CYLINDERS_10,
        MODEL_CYLINDERS_15,
        MODEL_CYLINDERS_20,
        MODEL_CYLINDERS_50,
        MODEL_CYLINDERS_100,

        MODEL_CHEESE_10,
        MODEL_CHEESE_20,
        MODEL_CHEESE_30,
        MODEL_CHEESE_40,
        MODEL_CHEESE_50,
        MODEL_CHEESE_60,
        MODEL_CHEESE_70,
        MODEL_CHEESE_80,
        MODEL_CHEESE_90,
        MODEL_CHEESE_100,

        // Graphite models

        MODEL_GRAPHITE_CHEESE25,
        MODEL_GRAPHITE_CHEESE50,
        MODEL_GRAPHITE_CHEESE75,
        MODEL_GRAPHITE_CHEESE100,
        MODEL_GRAPHITE_CHEESE125,
        MODEL_GRAPHITE_CHEESE150,
        MODEL_GRAPHITE_CHEESE175,
        MODEL_GRAPHITE_CHEESE200,

        MODEL_GRAPHITE_3AXIS25,
        MODEL_GRAPHITE_3AXIS50,
        MODEL_GRAPHITE_3AXIS75,
        MODEL_GRAPHITE_3AXIS100,
        MODEL_GRAPHITE_3AXIS125,
        MODEL_GRAPHITE_3AXIS150,
        MODEL_GRAPHITE_3AXIS175,
        MODEL_GRAPHITE_3AXIS200,

        //

        BACKGROUND_WHITE,
        BACKGROUND_GREY,
        BACKGROUND_BLACK,

        SAVE_OVERLAP,
        SAVE_DOT,
        SAVE_TABLE,
        SAVE_POVRAY,

        MODE_COPY,
        MODE_DEGRADE,
        MODE_BOUNDINGBOX,
        MODE_ADJACENCY,
        MODE_SAMPLEK,
        MODE_OVERLAP_GRAPH,
//        MODE_BSP,
        MODE_CULLFACE,
        MODE_BENCHMARK,
        MODE_REALTIME,
        MODE_ZHISTOGRAM,

        MODE_SPIN_STOP,
        MODE_SPIN_SLOW,
        MODE_SPIN_FAST,

        MODE_MAX
    }
    MenuCallbacks;

    //

    typedef enum
    {
        INFO_HIDDEN = 0,
        INFO_INTRO,
        INFO_OPENGL,
        INFO_CSG,
        INFO_NORMALISED,
        INFO_OVERLAP,
        INFO_FRAME_RATE,
        INFO_MENU,

        INFO_MAX

    } InfoMode;

    static const std::string _infoModeDescription[INFO_MAX];

    //

    void keyboardCommands(const std::string &keys);

protected:

    GltFontAscii                        _font;
    GltLight                            _light0;
    GltMaterial                         _material;
    GltLightModel                       _lightModel;
    GltColor                            _background;
    GltSkySphere                        _sphere;
    Matrix                              _spinMatrix;
    GltInterpolatorRotation             _spin;
    ReferenceCountPtr<GltTextOverlay>   _text[INFO_MAX];

    CsgShape                            _shape;
    int                                 _currentTree;

    InfoMode                            _infoMode;
    CsgHistograms                       _histograms;

    //
    // Drawing options
    //

    bool          _degrade;           // use a faster method for mouse manipulation
    bool          _benchmark;         // in benchmark mode, draw as fast as possible
    bool          _realTime;          // in real-time mode, use the real clock
    bool          _randomOrient;      // Randomise the orientation
    int           _samples;           // Number of samples before shutdown

    GltRandomOrientation<> _orient;     // RNG for orientations
    int                    _orientSeed; // RNG Seed

    GltBufferCapture _capture;
    bool             _captureExit;

    //

    bool          _zFurthest;
    bool          _nBehind;

    //

    GltFieldPtr       settings();
    GltRegistry      _settings;
    GltRegistryMenu  _menu;

    //

    bool selectTree(const int t = -1);
    void updateMenus();

    void enableFrustum(const bool enable);

private:

    bool _recalcAdjacency;

    GltFrameRate _frameRate;

    std::string              _iniFile;
    bool                     _iniSave;
    std::string              _modelFile;
    bool                     _modelSave;
    static const std::string _registryKey;

    static const int         _drawModeOffset;
    static const int         _infoModeOffset;

    std::string _keyCommands;
};

//////////////////////////////////////////////////////////////////////////

const std::string CsgDemo::_registryKey("Software\\CsgDemo");
const int         CsgDemo::_drawModeOffset = 1100;
const int         CsgDemo::_infoModeOffset = 1200;

const string CsgDemo::_infoModeDescription[INFO_MAX] =
{
    "Hidden",
    "Intro",
    "OpenGL",
    "CSG",
    "Adjacent",
    "Frame Rate",
    "Menu"
};

CsgDemo::CsgDemo(const int width,const int height,const string &set,const string &iniFile)
: GlutWindowExaminer("OpenGL CSG Demo",width,height),
  _light0(GL_LIGHT0),
  _material(GL_FRONT_AND_BACK),
  _background(grey),
  _spin(_spinMatrix),
  _currentTree(0),
  _infoMode(INFO_INTRO),
  _degrade(true),
  _benchmark(false),
  _realTime(true),
  _randomOrient(false),
  _samples(-1),
  _orientSeed(25101974),
  _capture(*this),
  _captureExit(false),
  _zFurthest(false),
  _nBehind(false),
  _menu(_settings),
  _recalcAdjacency(false),
  _frameRate(7),
  _iniFile("csgdemo.ini"),
  _iniSave(true),
  _modelFile("csgdemo.dat"),
  _modelSave(true),
  _keyCommands("")
{
    _viewMatrix = matrixScale(0.1);

    _settings.set(settings());

    for (int i=0; i<INFO_MAX; i++)
    {
        _text[i] = new GltTextOverlay(_font,_viewport),
        _text[i]->color() = white;
        _text[i]->fadeColor() = black;
        _text[i]->fadeColor().alpha() = 0.3;
        _text[i]->shadow() = true;
        _text[i]->alignHorizontal() = GLT_ALIGN_LEFT;
        _text[i]->alignVertical()   = GLT_ALIGN_TOP;
    }

    _text[INFO_INTRO]->text() = info;

    _text[INFO_FRAME_RATE]->alignHorizontal()   = GLT_ALIGN_RIGHT;
    _text[INFO_FRAME_RATE]->alignVertical()     = GLT_ALIGN_BOTTOM;
    _text[INFO_FRAME_RATE]->border() = false;
    _text[INFO_FRAME_RATE]->fadeColor().alpha() = 0.25;

    _material.ambient()   = black;
    _material.diffuse()   = black;
    _material.specular()  = white;
    _material.shininess() = 40.0;

    _light0.ambient()  = GltColor(0.1, 0.1, 0.1, 1.0);
    _light0.diffuse()  = GltColor(1.0, 1.0, 1.0, 0.0);
    _light0.specular() = GltColor(0.5, 0.5, 0.5, 0.0);
    _light0.position() = Vector(0.2, 0.5, 10.0);
//    _light0.position() = Vector(50.0, 50.0, 10.0);

    _light0.enabled()  = true;

    //

    _ortho.zNear() =  10.0;
    _ortho.zFar()  = -10.0;

    // Read settings from INI file, if specified

    if (iniFile.size())
    {
        _iniFile = iniFile;
        _settings.read(_iniFile);
    }
    else
    {
        #ifdef GLT_WIN32
        _settings.readRegistry(_registryKey);
        #else
        _settings.read(_iniFile);
        #endif
    }

    _settings.set(set);

    _orient.base().seed(_orientSeed);

    // Read CSG model from saved file, if possible
    // Otherwise use the default CSG model

    if (isFile(_modelFile))
    {
        cout << "Reading " << _modelFile << "..." << endl;
        ifstream fin(_modelFile.c_str());
        loadModel(fin);
    }
    else
        loadModel(defaultTree);
}

CsgDemo::~CsgDemo()
{
}

void
CsgDemo::OnOpen()
{
    glewInit();

    mouseMode() = MODE_MOUSE_RIGHT;

    //

    _lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    _lightModel.setLocalViewer(GL_FALSE);
    _lightModel.setTwoSide(GL_TRUE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DITHER);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    //

    _sphere.clear();
    _sphere.map().addEntry(M_PI*0.0,blue);
    _sphere.map().addEntry(M_PI*0.1,blue);
    _sphere.map().addEntry(M_PI*0.4,lightBlue);
    _sphere.map().addEntry(M_PI*0.5,white);
    _sphere.map().addEntry(M_PI*0.6,lightGrey);
    _sphere.map().addEntry(M_PI*0.9,black);
    _sphere.map().addEntry(M_PI*1.0,black);

    //

    postRedisplay();

    _menu.reset();

    _spin.loop() = true;
    _spin.realTime() = true;

    //

    _menu.reset();
    _text[INFO_OPENGL]->text() = GltSystemInfo() + "\n\n" + GltInfo();
    setIdle(_benchmark);

    _font.init(mac8Font);

    //

    updateMenus();
}

void
CsgDemo::OnClose()
{
    if (_iniSave)
    {
        if (_iniFile.size())
            _settings.write(_iniFile);

        #ifdef GLT_WIN32
        else
            _settings.writeRegistry(_registryKey);
        #endif
    }

    _menu.reset();
}

void
CsgDemo::OnIdle()
{
    // Benchmark mode

    if (_benchmark)
        postRedisplay();

    // Capture frame-buffer

    _capture.capture();

    if (_captureExit && _capture.finished())
        close();

    // Non real-time mode

    if (!_realTime)
    {
        // Update clock

        Timer::advance(40); // 25 frames/sec
    }

    _spin.draw();
}

void CsgDemo::OnDisplay()
{
//  glFrontFace(GL_CCW);

    GLERROR;

    _material.set();

    glPushMatrix();
    glLoadIdentity();
    _light0.set();
    glPopMatrix();

    glPushMatrix();

    if (_randomOrient)
        _orient.rand().glMultMatrix();

    _spinMatrix.glMultMatrix();

    glClearDepth(1.0);
    _background.glClearColor();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    _sphere.draw();

    const CsgShape::DrawMode mode  = _shape.mode();
    const bool               solid = _shape.solid();

    if (_degrade && mousePressed())
    {
        if
        (
            mode==CsgShape::CSG_DRAW_GOLDFEATHER ||
            mode==CsgShape::CSG_DRAW_GOLDFEATHER_LAYERS ||
            mode==CsgShape::CSG_DRAW_GOLDFEATHER_LAYERS_IMP ||
            mode==CsgShape::CSG_DRAW_SCS
        )
            _shape.solid() = false;
    }
    else
        if (_recalcAdjacency)
        {
            Timer timer;
            _shape.calculateAdjacencyFrustum();
            _recalcAdjacency = false;
        }

    if (_zFurthest || _nBehind)
    {
        glClearDepth(0.0);
        glClear(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_GREATER);

        _shape.mode() = CsgShape::CSG_DRAW_PREVIEW;
    }

    GLERROR;

    _shape.draw();

    GLERROR;

    if (_nBehind)
    {
        glPushAttrib(~0);

        glEnable(GL_STENCIL_TEST);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
        glDisable(GL_LIGHTING);
        glStencilMask(~0);
        glStencilFunc(GL_ALWAYS,0,~0);
        glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
        glCullFace(GL_FRONT);
        glDepthMask(GL_FALSE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);

        _shape.draw();

        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
        glDepthFunc(GL_ALWAYS);
        glDisable(GL_CULL_FACE);

        glStencilFunc(GL_EQUAL,1,~0);
        red.glColor();
        drawZnear();

        glStencilFunc(GL_EQUAL,2,~0);
        green.glColor();
        drawZnear();

        glPopAttrib();
    }

    _shape.mode() = mode;
    _shape.solid() = solid;

    glPopMatrix();

    GLERROR;

    // Normalisation information

    _text[INFO_NORMALISED]->text() = _shape.description();

    if (_menu.active())
    {
        _text[INFO_MENU]->text() = _menu.menu();
        _text[INFO_MENU]->draw();
    }
    else
        _text[_infoMode]->draw();

    GLERROR;

    // Consume keyboard commands

    {
        static bool here = false;

        if (!here)
        {
            here = true;
            string::size_type i;

            for (i=0; i<_keyCommands.size(); )
            {
                OnKeyboard(_keyCommands[i],0,0);
                if (_keyCommands[i++]=='.')
                {
                    postRedisplay();
                    break;
                }
            }

            _keyCommands = _keyCommands.substr(i);
            here = false;
        }
    }

    GLERROR;

    _histograms.draw();

    GLERROR;

    // Frame rate

    ++_frameRate;

    if (_infoMode==INFO_FRAME_RATE)
    {
            sprintf
            (
                _text[INFO_FRAME_RATE]->text(),
                "%s %s%s%5.1f fps",
                CsgShape::_drawModeDescription[_shape.mode()].c_str(),
                _shape.options().overlapGraph          ? "overlap " : "",
                _shape.options().sampleDepthComplexity ? "sampleK " : "",
                float(_frameRate.frameRate())
            );
    }

    // CSG runtime info

    _text[INFO_CSG]->text() = _shape.info().str();

    GLERROR;

    // Check if we're finished sampling

    if (_samples>=0)
    {
        _samples--;
        if (_samples==0)
        {
            _samples = -1;  // Disable sampling next time

            cout << endl << GltSystemInfo() << endl << GltInfo() << endl;
            cout << endl << _shape.info().str() << endl;

            close();        // Close the window
        }
    }

    GLERROR;
}

void CsgDemo::OnKeyboard(unsigned char key, int x, int y)
{
    if (_menu.OnKeyboard(key,x,y))
    {
        postRedisplay();
        return;
    }

    switch (key)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            selectTree(int(key-'0'));
            break;

        case '!': _infoMode = INFO_INTRO;         break;
        case '@': _infoMode = INFO_OPENGL;        break;
        case '#': _infoMode = INFO_CSG;           break;
        case '$': _infoMode = INFO_NORMALISED;    break;
        case '%': _infoMode = INFO_OVERLAP;       break;
        case '^': _infoMode = INFO_FRAME_RATE;    break;
        case '&': _infoMode = INFO_HIDDEN;        break;

        case 'P':  OnMenu(SAVE_DOT);              return;
        case ';':  OnMenu(SAVE_TABLE);            return;
        case ' ':  OnMenu(MODE_BENCHMARK);        return;
        case '.':  OnMenu(MODE_REALTIME);         return;
        case '?':  OnMenu(MODE_OVERLAP_GRAPH);    return;
        case '/':  OnMenu(MODE_SAMPLEK);          return;

        case 'r':  _randomOrient = !_randomOrient; break;

        case '-':  _shape.options().limitSubtractions--; break;
        case '+':  _shape.options().limitSubtractions++; break;

        // Scale the frustrum in z

        case '[':
            _ortho.zNear() *= 1.25;
            _ortho.zFar()  *= 1.25;
            OnReshape(getWidth(),getHeight());
            break;

        case ']':
            _ortho.zNear() *= 0.8;
            _ortho.zFar()  *= 0.8;
            OnReshape(getWidth(),getHeight());
            break;

        // Translate the frustum in z

        case '{':
            {
                const double delta = (_ortho.zFar()-_ortho.zNear())*0.02;
                _ortho.zNear() += delta;
                _ortho.zFar()  += delta;
                OnReshape(getWidth(),getHeight());
                break;
            }

        case '}':
            {
                const double delta = (_ortho.zFar()-_ortho.zNear())*0.02;
                _ortho.zNear() -= delta;
                _ortho.zFar()  -= delta;
                OnReshape(getWidth(),getHeight());
                break;
            }

        // Adjust current layer for display

        case 'l': _shape.options().layer++; break;
        case 'L': _shape.options().layer--; break;

        // Randomise color of objects

        case 'R':
            {
                GltRandomDouble<> randHue(0.0,360.0);

                for (int32 i=0; i<_shape.primitives(); i++)
                {
                    real hue = randHue.rand();
                    real sat = 1.0;
                    real val = 1.0;
                    _shape.primitive(i)->color().fromHSV(hue,sat,val);
                }

                break;
            }

        case '|':
            _settings.write(_iniFile);
            break;

        // Inherited keybindings

        default:
            GlutWindowExaminer::OnKeyboard(key,x,y);
            return;
    }

    postRedisplay();

    // Reset the gathered statistics whenever
    // the configuration changes

    _shape.info().reset();
}

void
CsgDemo::OnSpecial(int key, int x, int y)
{
    if (_menu.OnSpecial(key,x,y))
    {
        postRedisplay();
        return;
    }

    GlutWindowExaminer::OnSpecial(key,x,y);
}

#define STATUS(x) cout << '\t' << #x << " -> " << x << endl;
#define TOGGLE(x) ((x) = !(x)); STATUS(x)

void CsgDemo::OnMenu(int value)
{
    GlutWindowExaminer::OnMenu(value);

    if (!selectTree(value))
    {
        if
        (
            value>=_drawModeOffset && value<(CsgShape::CSG_DRAW_MAX+_drawModeOffset)
        )
        {
            const int mode = value-_drawModeOffset;

            if (mode>0 && mode<CsgShape::CSG_DRAW_MAX)
                _shape.mode() = CsgShape::DrawMode(mode);
            else
                _shape.mode() = CsgShape::CSG_DRAW_PREVIEW;

            _shape.solid() = true;
        }

        else

        switch (value)
        {
            case MODEL_DEFAULT:         loadModel(defaultTree);         break;
            case MODEL_ROW:             loadModel(rowTree);             break;
            case MODEL_GRID:            loadModel(gridTree);            break;
            case MODEL_HOLLOW:          loadModel(hollowTree);          break;
            case MODEL_BOXSPHERE:       loadModel(boxSphereTree);       break;
            case MODEL_HELIX:           loadModel(helixTree);           break;
            case MODEL_CONVEX_HELIX:    loadModel(segmentedHelixTree);  break;

            case MODEL_STEP_TOOL:
                {
                    string tmp;
                    decompress(tmp,stepToolTree);
                    loadModel(tmp.c_str());
                }
                break;

            case MODEL_SWISS_CHEESE:    loadModel(swissCheeseTree);      break;
            case MODEL_SWISS_CHEESE2:   loadModel(swissCheeseTree2);     break;
            case MODEL_PIPE:            loadModel(pipeTree);             break;
            case MODEL_DEGENERATE:      loadModel(degenerateTree);       break;
            case MODEL_TRICKLE:         loadModel(trickleTree);          break;
            case MODEL_CSG_NORMALIS:    loadModel(csgNormalisationTest); break;

            case MODEL_GSCS_ACYCLIC:    loadModel(gscsAcyclicTree);     break;
            case MODEL_GSCS_RING4:      loadModel(gscsRing4Tree);       break;
            case MODEL_GSCS_RING5:      loadModel(gscsRing5Tree);       break;
            case MODEL_GSCS_SPIRAL:     loadModel(gscsSpiral);          break;
            case MODEL_GSCS_RING:       loadModel(gscsRing);            break;

            case MODEL_GSCS_CASE0:      loadModel(gscsCase0);           break;
            case MODEL_GSCS_CASE1:      loadModel(gscsCase1);           break;
            case MODEL_GSCS_CASE2:      loadModel(gscsCase2);           break;
            case MODEL_GSCS_CASE3:      loadModel(gscsCase3);           break;
            case MODEL_GSCS_CASE4:      loadModel(gscsCase4);           break;
            case MODEL_GSCS_CASE5:      loadModel(gscsCase5);           break;
            case MODEL_GSCS_CASE6:      loadModel(gscsCase6);           break;
            case MODEL_GSCS_CASE7:      loadModel(gscsCase7);           break;
            case MODEL_GSCS_CASE8:      loadModel(gscsCase8);           break;

            case MODEL_CYLINDERS_2:     loadModel(cylinder2Tree);       break;
            case MODEL_CYLINDERS_3:     loadModel(cylinder3Tree);       break;
            case MODEL_CYLINDERS_4:     loadModel(cylinder4Tree);       break;
            case MODEL_CYLINDERS_5:     loadModel(cylinder5Tree);       break;
            case MODEL_CYLINDERS_6:     loadModel(cylinder6Tree);       break;
            case MODEL_CYLINDERS_8:     loadModel(cylinder8Tree);       break;
            case MODEL_CYLINDERS_10:    loadModel(cylinder10Tree);      break;
            case MODEL_CYLINDERS_15:    loadModel(cylinder15Tree);      break;
            case MODEL_CYLINDERS_20:    loadModel(cylinder20Tree);      break;
            case MODEL_CYLINDERS_50:    loadModel(cylinder50Tree);      break;
            case MODEL_CYLINDERS_100:   loadModel(cylinder100Tree);     break;

            case MODEL_CHEESE_10:       loadModel(cheese10Tree);    break;
            case MODEL_CHEESE_20:       loadModel(cheese20Tree);    break;
            case MODEL_CHEESE_30:       loadModel(cheese30Tree);    break;
            case MODEL_CHEESE_40:       loadModel(cheese40Tree);    break;
            case MODEL_CHEESE_50:       loadModel(cheese50Tree);    break;
            case MODEL_CHEESE_60:       loadModel(cheese60Tree);    break;
            case MODEL_CHEESE_70:       loadModel(cheese70Tree);    break;
            case MODEL_CHEESE_80:       loadModel(cheese80Tree);    break;
            case MODEL_CHEESE_90:       loadModel(cheese90Tree);    break;
            case MODEL_CHEESE_100:      loadModel(cheese100Tree);   break;

            case MODEL_GRAPHITE_CHEESE25:   loadModel(cheeseGraphite25Tree);    break;
            case MODEL_GRAPHITE_CHEESE50:   loadModel(cheeseGraphite50Tree);    break;
            case MODEL_GRAPHITE_CHEESE75:   loadModel(cheeseGraphite75Tree);    break;
            case MODEL_GRAPHITE_CHEESE100:  loadModel(cheeseGraphite100Tree);   break;
            case MODEL_GRAPHITE_CHEESE125:  loadModel(cheeseGraphite125Tree);   break;
            case MODEL_GRAPHITE_CHEESE150:  loadModel(cheeseGraphite150Tree);   break;
            case MODEL_GRAPHITE_CHEESE175:  loadModel(cheeseGraphite175Tree);   break;
            case MODEL_GRAPHITE_CHEESE200:  loadModel(cheeseGraphite200Tree);   break;

            case MODEL_GRAPHITE_3AXIS25:    loadModel(threeAxisGraphite25Tree);  break;
            case MODEL_GRAPHITE_3AXIS50:    loadModel(threeAxisGraphite50Tree);  break;
            case MODEL_GRAPHITE_3AXIS75:    loadModel(threeAxisGraphite75Tree);  break;
            case MODEL_GRAPHITE_3AXIS100:   loadModel(threeAxisGraphite100Tree); break;
            case MODEL_GRAPHITE_3AXIS125:   loadModel(threeAxisGraphite125Tree); break;
            case MODEL_GRAPHITE_3AXIS150:   loadModel(threeAxisGraphite150Tree); break;
            case MODEL_GRAPHITE_3AXIS175:   loadModel(threeAxisGraphite175Tree); break;
            case MODEL_GRAPHITE_3AXIS200:   loadModel(threeAxisGraphite200Tree); break;

            case BACKGROUND_WHITE:      _background = white;            break;
            case BACKGROUND_GREY:       _background = grey;             break;
            case BACKGROUND_BLACK:      _background = black;            break;

            case MODE_COPY:             _shape.options().zBufferCopy = !_shape.options().zBufferCopy; break;
            case MODE_DEGRADE:          _degrade = !_degrade;                      break;
            case MODE_BOUNDINGBOX:      _shape.options().boundingBoxes = !_shape.options().boundingBoxes;  break;
            case MODE_ADJACENCY:        selectTree();                              break;

            case MODE_BENCHMARK:
                _benchmark = !_benchmark;
                setIdle(_benchmark);
                STATUS(_benchmark);
                break;

            case MODE_REALTIME:
                _realTime = !_realTime;
                if (_realTime)
                    Timer::unFreeze();
                else
                {
                    Timer::freeze();
                    _spin.restart();
                    setIdle(true);
                    return;             // Don't post a redisplay, wait for idle
                }
                STATUS(_realTime);
                break;

            case MODE_SAMPLEK:       TOGGLE(_shape.options().sampleDepthComplexity); break;
            case MODE_OVERLAP_GRAPH: TOGGLE(_shape.options().overlapGraph);          break;
            case MODE_CULLFACE:      TOGGLE(_shape.options().cullFaces);             break;
            case MODE_ZHISTOGRAM:    TOGGLE(_histograms.zBuffer());                  break;

            case MODE_SPIN_STOP:    _spin.stop();           setIdle(_benchmark);    break;
            case MODE_SPIN_SLOW:    _spin.start(10.0,true); setIdle(_benchmark);    break;
            case MODE_SPIN_FAST:    _spin.start( 1.0,true); setIdle(_benchmark);    break;

            case _infoModeOffset+INFO_HIDDEN:     _infoMode = INFO_HIDDEN;          break;
            case _infoModeOffset+INFO_INTRO:      _infoMode = INFO_INTRO;           break;
            case _infoModeOffset+INFO_OPENGL:     _infoMode = INFO_OPENGL;          break;
            case _infoModeOffset+INFO_CSG:        _infoMode = INFO_CSG;             break;
            case _infoModeOffset+INFO_NORMALISED: _infoMode = INFO_NORMALISED;      break;
            case _infoModeOffset+INFO_OVERLAP:    _infoMode = INFO_OVERLAP;         break;
            case _infoModeOffset+INFO_FRAME_RATE: _infoMode = INFO_FRAME_RATE;      break;

            case SAVE_OVERLAP:
                {
                    const string filename(nextFilename()+".txt");
                    #ifdef DEBUG_CSG
                    cout << "Writing " << filename << "..." << endl;
                    #endif
                    ofstream os(filename.c_str());
                    _shape.exportOverlap(os);
                }
                break;

            case SAVE_DOT:
                {
                    const string filename(nextFilename()+".dot");
                    #ifdef DEBUG_CSG
                    cout << "Writing " << filename << "..." << endl;
                    #endif
                    ofstream os(filename.c_str());
                    _shape.exportDot(os,false,true,false);
                }
                break;

            case SAVE_TABLE:
                {
                    const string filename(nextFilename()+".txt");
                    #ifdef DEBUG_CSG
                    cout << "Writing " << filename << "..." << endl;
                    #endif
                    ofstream os(filename.c_str());
                    _shape.exportTable(os);
                }
                break;

            case SAVE_POVRAY:
                {
                    const string filename(nextFilename()+".pov");
                    #ifdef DEBUG_CSG
                    cout << "Writing " << filename << "..." << endl;
                    #endif
                    ofstream os(filename.c_str());

                    os << "// Exported from csgdemo" << endl;
                    os << "// OpenGL CSG Rendering" << endl;
                    os << "// Nigel Stewart, RMIT" << endl;
                    os << "// http://www.nigels.com/research" << endl;
                    os << endl;
                    os << "global_settings { assumed_gamma 1.0 }" << endl;
                    os << "#include \"colors.inc\"" << endl;
                    os << "#include \"skies.inc\"" << endl;

                    GltClearColor col(true);
                    os << "background { color rgb ";
                    col.writePov(os);
                    os << "}" << endl;

                    os << "//sphere { <0,0,0>, 100.0 pigment { P_Cloud2 } finish { ambient 0.5  diffuse 0.0 specular 0.0 } hollow }"<< endl;
                    os << "#default { finish { ambient 0.05 diffuse 0.8 specular 0.5 brilliance 10 roughness 0.0001 phong 0.05 } }" << endl;

                    os << "camera { orthographic location z*-10 right 2*x*(4/3) up 2*y direction z }" << endl;
                    os << "light_source { <-1,2, -10> color rgb <1,1,1>*0.5 }" << endl;
                    os << "light_source { < 3,1, -10> color rgb <1,1,1>*0.5 }" << endl;
                    os << endl;

                    os << "union { " << endl;
                    _shape.writePov(os);

                    // Apply the OpenGL modelview (viewing) matrix

                    os << endl << "// OpenGL modelview matrix" << endl;
                    _viewMatrix.writePov(os);

                    // Apply the OpenGL projection (camera) matrix

                    os << endl << "// OpenGL projection matrix" << endl;
                    Matrix proj(GL_PROJECTION_MATRIX);
                    proj.writePov(os);

                    os << "}" << endl;
                }
                break;

            default: return;
        }
    }

    postRedisplay();

    // Reset the gathered statistics whenever
    // the configuration changes

    _shape.info().reset();
}

void
CsgDemo::OnMouse(int button, int state, int x, int y)
{
    GlutWindowExaminer::OnMouse(button,state,x,y);
    if (_degrade && !mousePressed())
        postRedisplay();
}

void
CsgDemo::OnReshape(int w, int h)
{
    GlutWindowExaminer::OnReshape(w,h);
}

void
CsgDemo::OnOrient(const Matrix &viewing, const Matrix &inverse)
{
}

GltFieldPtr
CsgDemo::settings()
{
    GltFields *root = new GltFields("csgdemo");

        GltFields *spin    = new GltFields("spin");
        spin->add(_spin.active(),       "active");
        spin->add(_spin.duration(),10.0,"duration");
        spin->add(_spin.center(),       "origin");
        spin->add(_spin.axis(),         "axis");
        spin->add(_spinMatrix,          "matrix");

        GltFields *display = new GltFields("display");
        display->add((int &)_infoMode,INFO_MAX,_infoModeDescription,"info");
        display->add(_degrade          ,"degrade");
        display->add(_benchmark        ,"benchmark");
        display->add(_randomOrient     ,"randomOrientation");
        display->add(spin);
        display->add(_histograms.rBuffer(),"rHistogram");
        display->add(_histograms.gBuffer(),"gHistogram");
        display->add(_histograms.bBuffer(),"bHistogram");
        display->add(_histograms.zBuffer(),"zHistogram");

        GltFields *window = new GltFields("window");
        window->add(_background,"background");
        window->add(_ortho     ,"ortho");
        window->add(_light0,"light0");
        window->add(_material,"material");
        window->add(_sphere.settings(),"skySphere");

        GltFields *viewing = new GltFields("viewing");
        viewing->add(_viewMatrix       ,"viewMatrix");
        viewing->add(_viewMatrixInverse,"viewMatrixInv");

        GltFields *capture = new GltFields("frame");
        capture->add(_fileIndex,     "file");
        capture->add(_captureExit,   "captureExit");
        capture->add(_capture.settings());
        capture->add(_orientSeed,    "orientSeed");

    root->add(display);
    root->add(window);
    root->add(viewing);
    root->add(capture);
    root->add(_samples,"samples");
    root->add(_shape.settings());

    root->add(_iniSave,"iniSave");
    root->add(_iniFile,"iniFile");

    root->add(_modelSave,"modelSave");
    root->add(_modelFile,"modelFile");

    return root;
}

bool
CsgDemo::selectTree(const int t)
{
    Timer timer;

    int tree;

    if (t==-1)
        tree = _currentTree;
    else
        tree = t;

    bool ok = false;

    if (_shape.selectTree(tree))
    {
        _currentTree = tree;
        postRedisplay();

        #ifdef DEBUG_CSG
        cout << "Init Tree       : " << timer.elapsed() << " sec" << endl;
        #endif

        ok = true;
    }

    // Print overlap graphics into overlay

    string matrix,tmp;
    for (int i=0; i<_shape.products(); i++)
    {
        if (i>0 && tmp.size())
            tmp += "\n\n";

        _shape.product(i).graph().print(matrix);
        tmp +=  matrix;
    }
    assert(_text[INFO_OVERLAP].get());
    _text[INFO_OVERLAP]->text() = tmp;

    return ok;
}

void
CsgDemo::updateMenus()
{
    if (!getOpen())
        return;

    _leftButtonMenu.detach();
    _leftButtonMenu.reset();

    GlutMenu &model = _leftButtonMenu.subMenu();

        //
        // WSCG 2000
        //

        GlutMenu &wscg2000 = model.subMenu();
        wscg2000.addEntry("Gadget"      ,MODEL_DEFAULT);
        wscg2000.addEntry("Grid"        ,MODEL_GRID);
        wscg2000.addEntry("Hollow"      ,MODEL_HOLLOW);
        wscg2000.addEntry("Swiss Cheese",MODEL_SWISS_CHEESE);
        wscg2000.addEntry("Pipe"        ,MODEL_PIPE);

        //
        // WSCG 2002
        //

        GlutMenu &wscg2002 = model.subMenu();

            GlutMenu &cylinders = model.subMenu();
            cylinders.addEntry("2",  MODEL_CYLINDERS_2);
            cylinders.addEntry("3",  MODEL_CYLINDERS_3);
            cylinders.addEntry("4",  MODEL_CYLINDERS_4);
            cylinders.addEntry("5",  MODEL_CYLINDERS_5);
            cylinders.addEntry("6",  MODEL_CYLINDERS_6);
            cylinders.addEntry("8",  MODEL_CYLINDERS_8);
            cylinders.addEntry("10", MODEL_CYLINDERS_10);
            cylinders.addEntry("15", MODEL_CYLINDERS_15);
            cylinders.addEntry("20", MODEL_CYLINDERS_20);
            cylinders.addEntry("50", MODEL_CYLINDERS_50);
            cylinders.addEntry("100",MODEL_CYLINDERS_100);

            GlutMenu &cheese = model.subMenu();
            cheese.addEntry("10",  MODEL_CHEESE_10);
            cheese.addEntry("20",  MODEL_CHEESE_20);
            cheese.addEntry("30",  MODEL_CHEESE_30);
            cheese.addEntry("40",  MODEL_CHEESE_40);
            cheese.addEntry("50",  MODEL_CHEESE_50);
            cheese.addEntry("60",  MODEL_CHEESE_60);
            cheese.addEntry("70",  MODEL_CHEESE_70);
            cheese.addEntry("80",  MODEL_CHEESE_80);
            cheese.addEntry("90",  MODEL_CHEESE_90);
            cheese.addEntry("100", MODEL_CHEESE_100);

        wscg2002.addEntry("Cylinders",cylinders);
        wscg2002.addEntry("Cheese",cheese);

        //
        // GRAPHITE 2003
        //

        GlutMenu &graphite2003 = model.subMenu();
        graphite2003.addEntry("Fig 1. External"     ,MODEL_GSCS_CASE1);
        graphite2003.addEntry("Fig 2. Leaf Nodes"   ,MODEL_GSCS_CASE3);
        graphite2003.addEntry("Fig 3. Ring Graph"   ,MODEL_GSCS_CASE4);
        graphite2003.addEntry("Fig 4. Disconnected" ,MODEL_GSCS_CASE8);
        graphite2003.addEntry("Fig 5. Cyclic"       ,MODEL_GSCS_CASE5);

            GlutMenu &fig7 = model.subMenu();
            fig7.addEntry(" 25",MODEL_GRAPHITE_CHEESE25);
            fig7.addEntry(" 50",MODEL_GRAPHITE_CHEESE50);
            fig7.addEntry(" 75",MODEL_GRAPHITE_CHEESE75);
            fig7.addEntry("100",MODEL_GRAPHITE_CHEESE100);
            fig7.addEntry("125",MODEL_GRAPHITE_CHEESE125);
            fig7.addEntry("150",MODEL_GRAPHITE_CHEESE150);
            fig7.addEntry("175",MODEL_GRAPHITE_CHEESE175);
            fig7.addEntry("200",MODEL_GRAPHITE_CHEESE200);

            GlutMenu &fig9 = model.subMenu();
            fig9.addEntry(" 25",MODEL_GRAPHITE_3AXIS25);
            fig9.addEntry(" 50",MODEL_GRAPHITE_3AXIS50);
            fig9.addEntry(" 75",MODEL_GRAPHITE_3AXIS75);
            fig9.addEntry("100",MODEL_GRAPHITE_3AXIS100);
            fig9.addEntry("125",MODEL_GRAPHITE_3AXIS125);
            fig9.addEntry("150",MODEL_GRAPHITE_3AXIS150);
            fig9.addEntry("175",MODEL_GRAPHITE_3AXIS175);
            fig9.addEntry("200",MODEL_GRAPHITE_3AXIS200);

            GlutMenu &misc1 = graphite2003.subMenu();
            misc1.addEntry("Two Subtractions"    ,MODEL_GSCS_CASE2);
            misc1.addEntry("Two Subgraphs"       ,MODEL_GSCS_CASE6);
            misc1.addEntry("Articulation Points" ,MODEL_GSCS_CASE7);

        graphite2003.addEntry("Fig 7. Swiss Cheese"   ,fig7);
        graphite2003.addEntry("Fig 9. 3-Axis Drilling",fig9);
        graphite2003.addEntry("Misc",misc1);

        //
        // HELIX
        //

        GlutMenu &helix = model.subMenu();
        helix.addEntry("Helix"        ,MODEL_HELIX);
        helix.addEntry("Convex Helix" ,MODEL_CONVEX_HELIX);

        //
        // MISC
        //

        GlutMenu &misc = model.subMenu();
        misc.addEntry("Normalise"      ,MODEL_CSG_NORMALIS);
        misc.addEntry("Row"            ,MODEL_ROW);
        misc.addEntry("Swiss Cheese II",MODEL_SWISS_CHEESE2);
        misc.addEntry("Degenerate"     ,MODEL_DEGENERATE);
        misc.addEntry("GSCS Acyclic"   ,MODEL_GSCS_ACYCLIC);
        misc.addEntry("GSCS Ring4"     ,MODEL_GSCS_RING4);
        misc.addEntry("GSCS Ring5"     ,MODEL_GSCS_RING5);
        misc.addEntry("BoxSphere"      ,MODEL_BOXSPHERE);
        misc.addEntry("StepTool"       ,MODEL_STEP_TOOL);
        misc.addEntry("TrickleBoxes"   ,MODEL_TRICKLE);
        misc.addEntry("NoOverlap"      ,MODEL_GSCS_CASE0);
        misc.addEntry("Spiral"         ,MODEL_GSCS_SPIRAL);
        misc.addEntry("Ring"           ,MODEL_GSCS_RING);

    model.addEntry("WSCG 2000",  wscg2000);
    model.addEntry("WSCG 2002",  wscg2002);
    model.addEntry("Graphite 2003",  graphite2003);
    model.addEntry("Helix",      helix);
    model.addEntry("Misc",       misc);

    _leftButtonMenu.addEntry("Model"    ,model);

    //
    // Build menus for Tree and Primitive
    //

    int index = 0;

    if (_shape.trees()>0)
    {
        GlutMenu &tree = _leftButtonMenu.subMenu();

        for (int t=0; t<_shape.trees(); t++)
            tree.addEntry(_shape.tree(t)->description().substr(0,50),index++);

         _leftButtonMenu.addEntry("Tree"     ,tree);
   }

    if (_shape.primitives()>0)
    {
        GlutMenu &primitive = _leftButtonMenu.subMenu();

        for (int t=0; t<_shape.primitives(); t++)
            primitive.addEntry(_shape.primitive(t)->name(),index++);

        _leftButtonMenu.addEntry("Primitive",primitive);
    }

    //
    // Algorithm Menu
    //

    GlutMenu &algorithm = _leftButtonMenu.subMenu();
    algorithm.addEntry("Preview"            ,_drawModeOffset+CsgShape::CSG_DRAW_PREVIEW);
    algorithm.addEntry("Wireframe"          ,_drawModeOffset+CsgShape::CSG_DRAW_WIREFRAME);
    algorithm.addEntry("Layer"              ,_drawModeOffset+CsgShape::CSG_DRAW_LAYER);
    algorithm.addEntry("Group"              ,_drawModeOffset+CsgShape::CSG_DRAW_GROUP);
    algorithm.addEntry("Depth Complexity"   ,_drawModeOffset+CsgShape::CSG_DRAW_DEPTH_COMPLEXITY);
    algorithm.addEntry("Goldfeather"        ,_drawModeOffset+CsgShape::CSG_DRAW_GOLDFEATHER);
    algorithm.addEntry("Layered Goldfeather",_drawModeOffset+CsgShape::CSG_DRAW_GOLDFEATHER_LAYERS);
    algorithm.addEntry("Imp. L. Goldfeather",_drawModeOffset+CsgShape::CSG_DRAW_GOLDFEATHER_LAYERS_IMP);
    algorithm.addEntry("SCS"                ,_drawModeOffset+CsgShape::CSG_DRAW_SCS);

    _leftButtonMenu.addEntry("Algorithm",algorithm);

    //
    // Options sub-menu
    //

    GlutMenu &options = _leftButtonMenu.subMenu();

    // Display sub-menu

        GlutMenu &display = options.subMenu();
        display.addEntry("Fast Manipulation"    ,MODE_DEGRADE);
        display.addEntry("Bounding Boxes"       ,MODE_BOUNDINGBOX);
        display.addEntry("Z Histogram"          ,MODE_ZHISTOGRAM);
        display.addEntry("Benchmark Mode"       ,MODE_BENCHMARK);

        // Background sub-menu

            GlutMenu &background = display.subMenu();
            background.addEntry("White",BACKGROUND_WHITE);
            background.addEntry("Grey" ,BACKGROUND_GREY);
            background.addEntry("Black",BACKGROUND_BLACK);

        display.addEntry("Background",background);

        // Spin sub-menu

            GlutMenu &spin = display.subMenu();
            spin.addEntry("Stop",MODE_SPIN_STOP);
            spin.addEntry("Slow",MODE_SPIN_SLOW);
            spin.addEntry("Fast",MODE_SPIN_FAST);

        display.addEntry("Spin",spin);

    options.addEntry("Display",display);

    // Information sub-menu

        GlutMenu &info = options.subMenu();
        info.addEntry("Introduction"         ,_infoModeOffset+INFO_INTRO);
        info.addEntry("OpenGL Driver"        ,_infoModeOffset+INFO_OPENGL);
        info.addEntry("CSG Information"      ,_infoModeOffset+INFO_CSG);
        info.addEntry("Normalised"           ,_infoModeOffset+INFO_NORMALISED);
        info.addEntry("Overlap"              ,_infoModeOffset+INFO_OVERLAP);
        info.addEntry("Frame Rate"           ,_infoModeOffset+INFO_FRAME_RATE);
        info.addEntry("Hide"                 ,_infoModeOffset+INFO_HIDDEN);

    options.addEntry("Info",info);

    // CSG sub-menu

        GlutMenu &csgOptions = options.subMenu();

        csgOptions.addEntry("Copy/Draw"            ,MODE_COPY);
        csgOptions.addEntry("Sample K"             ,MODE_SAMPLEK);
        csgOptions.addEntry("Overlap Graph"        ,MODE_OVERLAP_GRAPH);
//        csgOptions.addEntry("BSP Overlap"          ,MODE_BSP);
        csgOptions.addEntry("Cull Faces"           ,MODE_CULLFACE);
        csgOptions.addEntry("Calculate Adjacency"  ,MODE_ADJACENCY);

    options.addEntry("CSG Rendering",csgOptions);

    //

    _leftButtonMenu.addEntry("Options",options);


    GlutMenu &save = _leftButtonMenu.subMenu();
    save.addEntry("RGB"             ,MENU_CAPTURE_RGB);
    save.addEntry("Stencil Buffer"  ,MENU_CAPTURE_STENCIL);
    save.addEntry("Z-Buffer"        ,MENU_CAPTURE_ZBUFFER);
    save.addEntry("Overlap (Data)"  ,SAVE_OVERLAP);
    save.addEntry("Overlap (LaTeX)" ,SAVE_TABLE);
    save.addEntry("Overlap (dot)"   ,SAVE_DOT);
    save.addEntry("Povray"          ,SAVE_POVRAY);

    _leftButtonMenu.addEntry("Save",save);

    _leftButtonMenu.addEntry("Close",MENU_CLOSE);

    _leftButtonMenu.attach();
}

bool
CsgDemo::loadModel(istream &is)
{
    if (!is.good())
        return false;

    if (!_shape.read(is))
    {
        cerr << "Error loading CSG model." << endl;
        return false;
    }

    selectTree(0);
    updateMenus();

    return true;
}

bool
CsgDemo::loadModel(const char *tree)
{
    // Save a copy to the model file,
    // if necessary.

    if (_modelSave)
    {
        ofstream of(_modelFile.c_str());
        of << tree << endl;
    }

    istringstream fin(tree);
    return loadModel(fin);
}

void
CsgDemo::keyboardCommands(const std::string &keys)
{
    _keyCommands += keys;
}

/////////////////////////////////////////

bool GlutMain(const std::vector<std::string> &args)
{
#if 0
    mtrace();
#endif

    string inputFile;
    string iniFile;
    string commands;
    string settings;
    int width  = 300;
    int height = 300;
    bool fullscreen = false;
    bool quiet = false;

    for (uint32 i=1; i<args.size(); i++)
    {
        const string &arg = args[i];

        if (arg.size()>0 && arg[0]=='+')
        {
            commands = arg.substr(1);
            continue;
        }

        if (arg=="-size")
        {
            if (i+2<args.size())
            {
                width  = atoi(args[++i]);
                height = atoi(args[++i]);
            }

            continue;
        }

        if (arg=="-set")
        {
            if (i+1<args.size())
                settings = settings + (settings.size()>0 ?"\n" : "") + args[++i];
            continue;
        }

        if (arg=="-ini")
        {
            if (i+1<args.size())
                iniFile = args[++i];
            continue;
        }

        if (arg=="-fullscreen")
        {
            fullscreen = true;
            continue;
        }

        if (arg=="-quiet")
        {
            quiet = true;
            continue;
        }

        inputFile = arg;
    }

    if (!quiet)
    {
        cout << ::banner << endl;
        cout << ::args << endl;
    }

    static CsgDemo *demo = new CsgDemo(width,height,settings,iniFile);
    demo->open();
    if (fullscreen)
        demo->enterGameMode();

    if (inputFile.size())
    {
        if (inputFile=="-")
            demo->loadModel(cin);
        else
        {
            ifstream is(inputFile.c_str());
            demo->loadModel(is);
        }
    }

    demo->keyboardCommands(commands);

    #ifdef DEBUG_CSG
    cout << GltInfo() << endl << endl;
    #endif

#if 0
    glutSetOption(GLUT_PRINT_TRACE,1);
    glutSetOption(GLUT_PRINT_WARNING,1);
    glutSetOption(GLUT_PRINT_INFORMATION,1);
#endif

    return true;
}
