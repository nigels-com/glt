#include "window.h"

#include <glutm/shape.h>

#include <misc/string.h>

#include <glt/gl.h>
#include <glt/fontasci.h>
#include <glt/error.h>
#include <glt/light.h>
#include <glt/lightm.h>
#include <glt/matrix.h>
#include <glt/project.h>
#include <glt/rgb.h>
#include <glt/zplane.h>

#include <fonts/fonts.h>
#include <node/tiled.h>
#include <math/random.h>
#include <math/vector4.h>
#include <math/matrix4.h>
#include <misc/compress.h>

#include "document.h"
#include "examples.h"

#include "textures.h"
#include "project.h"

#include "gravity.h"
#include "lorenz.h"
#include "rossler.h"
#include "project.h"
#include "hockey.h"

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

//////////////////////

Grips::DisplayOptions::DisplayOptions()
:
    animation(true),
    steps(1),
    wait(20),
    info(false),
    logo(true),
    formula(true),
    options(false),
    editVal(false),
    particles(true),
    points(false),
    trail(false),
    accel(false),
    center(false),
    follow(false),
    box(false),
    floor(false),
    lighting(true),
    ortho(true),
    reflections(false),
    shadows(false),
    stencil(false),
    selfShadows(false),
    shadowVolumes(false),
    slices(12),
    stacks(12),
    orthoConfig()
{
}

///////////////

Grips::Grips(int width,int height,int x,int y)
:
    GlutWindowExaminer("GRIPS",width,height,x,y,GLUT_DOUBLE|GLUT_DEPTH|GLUT_STENCIL|GLUT_RGBA),
    _document(new Document()),
    _radiusScale(1.0),
    _light0(GL_LIGHT0),
    _light1(GL_LIGHT1),
    _light2(GL_LIGHT2),
    _axesSize(1.0),
    _field(8.0,0.06,0.30),
    _spinInterp(_spin),
    _current(-1),

    tileX(1),
    tileY(1),
    tileN(0),

    _info(_font,_viewport),
    _textureCurrent(0),
    _material(GL_FRONT_AND_BACK),
    _filename("settings.dat"),
    _maxTime(0.0),

    _server(*this),
    _client(*this),
    _settingsClient(*this),

    _menu(_settings)
{
    //

    _info.color() = white;
    _info.fadeColor().alpha() = 0.3;
    _info.shadow() = true;
    _info.shadowColor() = black;

    //

    const double size = 10.0;

    _center.points().push_back(-VectorX*size);
    _center.points().push_back( VectorX*size);
    _center.points().push_back( Vector0);

    _center.points().push_back(-VectorY*size);
    _center.points().push_back( VectorY*size);
    _center.points().push_back( Vector0);

    _center.points().push_back(-VectorZ*size);
    _center.points().push_back( VectorZ*size);

    _center.color() = grey;

    _axes.visible() = false;

    _viewMatrix = matrixScale(0.003);

    //

    _quad.point().push_back(Point(Vector(-1,-1,0),VectorZ,Vector(0,0,0)));
    _quad.point().push_back(Point(Vector( 1,-1,0),VectorZ,Vector(1,0,0)));
    _quad.point().push_back(Point(Vector( 1, 1,0),VectorZ,Vector(1,1,0)));
    _quad.point().push_back(Point(Vector(-1, 1,0),VectorZ,Vector(0,1,0)));

    _quad.quad().push_back(Quad(&_quad.point()[0],&_quad.point()[1],&_quad.point()[2],&_quad.point()[3]));
    _quad.inheritColor() = true;

    //

    _light0.ambient()  = grey10;
    _light0.diffuse()  = grey50;
    _light0.specular() = white;
    _light0.position() = Vector4(0,0,10.0,0.0);
    _light0.enabled()  = true;

    _light1.ambient()  = black;
    _light1.diffuse()  = GltColor(0.5,0.5,0.7);
    _light1.specular() = white;
    _light1.position() = Vector4(15,5,2,1.0);
    _light1.enabled()  = true;

    _light2.ambient()  = black;
    _light2.diffuse()  = GltColor(0.5,0.5,0.7);
    _light2.specular() = white;
    _light2.position() = Vector4(-15,10,1,1.0);
    _light2.enabled()  = true;

    _material.ambient()   = black;
    _material.diffuse()   = black;
    _material.specular()  = white;
    _material.shininess() = 40.0;

    //

    observe(*_document);
    _document->init();
}

Grips::~Grips()
{
    forget(*_document);
    delete _document;
}

void
Grips::OnOpen()
{
    //

    _font.init(vga8Font);

    // Logo textures

    _eScience.init(escienceTexture);
    _rmit.init(rmitTexture);
    _vpac.init(vpacTexture);
//    _star.init(starTexture);

    // Planet textures

//  _earth.init(earthTexture);  // TODO - Use texture maps for particles
//    _blob.init(blobTexture);

    //

    setAnimation(_display.animation);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glDisable(GL_DITHER);
    glCullFace(GL_BACK);
    glClearDepth(1.0);
    glDepthRange(0.0,1.0);
    glLoadIdentity();

    GLERROR

    black.glClearColor();

    GltLightModel lightModel;
    lightModel.setAmbient(0.0, 0.0, 0.0, 0.0);
    lightModel.setLocalViewer(GL_FALSE);
    lightModel.setTwoSide(GL_TRUE);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    //

    _texture[0].init(starTexture);
    _texture[1].init(blobTexture);
    _texture[2].init(dropletTexture);

//  _sprite.init(handTexture,false);

}

void
Grips::OnClose()
{
    _font.init(NULL);
    _formula.clear();
    _eScience.clear();
    _rmit.clear();
    _vpac.clear();

    _texture[0].clear();
    _texture[1].clear();
    _texture[2].clear();

    _settings.clear();
    _menu.reset();
}

GltFieldPtr
Grips::settings()
{
    GltFields *root = new GltFields("grips");

            GltFields *opengl = new GltFields("opengl");
            opengl->add(_display.lighting   ,"lighting"    );
            opengl->add(_material           ,"material"    );
            opengl->add(_display.ortho      ,"ortho"       );
            opengl->add(_display.orthoConfig,"orthoCamera" );
            opengl->add(_light0             ,"light0"      );
            opengl->add(_light1             ,"light1"      );
            opengl->add(_light2             ,"light2"      );
            opengl->add(_viewMatrix         ,"transform"   );
            opengl->add(_viewMatrixInverse  ,"transformInv");

            GltFields *tile = new GltFields("tile");
            tile->add(tileX,"width");
            tile->add(tileY,"height");
            tile->add(tileN,"index");

            GltFields *spin = new GltFields("spin");
            spin->add(_spinInterp.active(),  "active");
            spin->add(_spinInterp.duration(),"duration");
            spin->add(_spinInterp.loop(),    "loop");
            spin->add(_spinInterp.axis(),    "axis");
            spin->add(_spinInterp.center(),  "center");
            spin->add(new GltFieldFunc<GltInterpolatorRotation>(_spinInterp,&GltInterpolatorRotation::stop,"stop"));
            spin->add(new GltFieldFunc<GltInterpolatorRotation>(_spinInterp,&GltInterpolatorRotation::restart,"restart"));
            spin->add(_spin,                 "matrix");

            GltFields *follow = new GltFields("follow");
            follow->add(_display.follow     ,"follow");
            follow->add(_current            ,"current");

            GltFields *window = new GltFields("window");
            window->add(_background,        "background"  );
            window->add(_info.color(),      "info"        );
            window->add(_info.fadeColor(),  "fade"        );
            window->add(_info.shadow(),     "shadowEnable");
            window->add(_info.border(),     "borderEnable");
            window->add(_info.borderColor(),"border"      );

        GltFields *display = new GltFields("display");

            GltFields *particles = new GltFields("particles");
            particles->add(_display.particles,  "enable");
            particles->add(_display.slices,     "slices");
            particles->add(_display.stacks,     "stacks");
            particles->add(_display.points,     "points");
            particles->add(_textureCurrent,     "texture");
            particles->add(_display.accel,      "acceleration");
            particles->add(_display.trail,      "trail");
            particles->add(_radiusScale,0.2    ,"radiusScale");

            GltFields *shadows = new GltFields("shadows");
            shadows->add(_display.shadows,      "shadows"     );
            shadows->add(_display.reflections,  "reflections" );
            shadows->add(_display.stencil,      "stencil"     );
            shadows->add(_display.selfShadows , "selfShadows" );
            shadows->add(_display.shadowVolumes,"shadowVolumes");

        display->add(particles);

        display->add(_display.center     ,"center"      );
        display->add(_display.box        ,"box"         );
        display->add(_display.floor      ,"floor"       );
        display->add(_axes.visible()     ,"axes"        );
        display->add(_axesSize, 1.0      ,"axesSize"    );
        display->add(_grid.settings());
        display->add(_display.logo       ,"logo"        );
        display->add(_display.formula    ,"formula"     );
        display->add(_display.info       ,"info"        );

        display->add(shadows);
        display->add(opengl);
        display->add(tile);
        display->add(spin);
        display->add(follow);
        display->add(_field.settings());
        display->add(window);
        display->add(new GltFieldFunc<Grips>(*this,&Grips::enterGameMode,"fullscreen"));
        display->add(new GltFieldFunc<Grips>(*this,&Grips::leaveGameMode,"windowed"));

    if (_document)
        root->add(_document->settings());
    root->add(display);
    root->add(_display.animation,"animation");
    root->add(_display.steps    ,"steps");
    root->add(_display.wait     ,"wait");

        GltFields *network = new GltFields("network");

        network->add(_server.settings());
        network->add(_client.settings());
        network->add(_settingsClient.settings());

    root->add(network);

    return root;
}

void
Grips::read(istream &is)
{
//    _settings.reset();
    _settings.read(is);

    // Synchronise clients
    _server.sendState(*this);
    _server.sendTile();

    postRedisplay();
}

void
Grips::read(const void *data)
{
    string tmp;
    if (decompress(tmp,data))
        read(tmp);
}

void
Grips::read(const std::string &str)
{
    istringstream is(str);
    read(is);
}

void
Grips::write(ostream &os,const std::string &prefix) const
{
    _settings.write(os,prefix);
}

void Grips::step()
{
    if (!_document)
        return;

    // In slave mode, wait for sync signals
    // from master node

    if (_client.connected())
        return;

    // Send sync signal to slave

    _server.sendSync();

    //

    _document->iterate(_display.steps);

    ParticleSystem &particles = _document->particles();

    if (_maxTime!=0.0 && particles._t>_maxTime)
        close();

    postRedisplay();
}

void Grips::OnTick()
{
    if (_display.animation)
        step();
}

void Grips::drawLogo(
    const GltViewport &viewport,
    const GltTexture  &texture,
    const GltHorizontalAlignment &alignH,
    const GltVerticalAlignment   &alignV,
    const bool                    blend,
    const GltColor               &color)
{
    if (texture.width()<=0 && texture.height()<=0)
        return;

    glPushAttrib(GL_VIEWPORT_BIT);

        GltViewport v;
        v.resize(texture);
        v.align(alignH,viewport);
        v.align(alignV,viewport);
        v.set();

        GltTextureViewport t(texture,false,blend);
        t.color() = color;
        t.draw();

    glPopAttrib();
}

void
Grips::drawReflections() const
{
    GLERROR

    if (_document && _display.reflections)
    {
        // Draw bodies as spheres

        GlutSphere sphere(true);

        sphere.slices() = _display.slices;
        sphere.stacks() = _display.stacks;
        sphere.inheritColor() = true;

        //

        glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        glPushMatrix();

            matrixMirror(-10*VectorZ,VectorZ).glMultMatrix();

            _light0.set();
            _light1.set();
            _light2.set();

            drawParticles();

        glPopMatrix();
        glPopAttrib();
    }

    GLERROR
}

void
Grips::drawShadows() const
{
    GLERROR

    if (_document && _display.shadows && _display.particles)
    {
        ParticleSystem &particles  = _document->particles();

        GlutSphere   sphere(true);
        sphere.slices() = _display.slices;
        sphere.stacks() = _display.stacks;
        sphere.color()  = black;
        sphere.color().alpha() = 0.6;

        glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

            Vector4 plane(0,0,1,10);
            matrixShadow(plane,_light0.position()).glMultMatrix();

            glDepthFunc(GL_ALWAYS);
            glDisable(GL_LIGHTING);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

            for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                if (i->_visible)
                {
                    const Particle &a = *i;
                    sphere.position(a._position,_radiusScale*a._radius);
                    sphere.draw();
                }

        glPopMatrix();
        glPopAttrib();
    }

    GLERROR
}

void
Grips::drawGrid() const
{
    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_LIGHTING);
        glDepthFunc(GL_ALWAYS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        _grid.draw();

    glPopAttrib();
}

void
Grips::drawParticles() const
{
    GLERROR

    if (_document && _display.particles)
    {
        ParticleSystem &particles  = _document->particles();

        GlutSphere sphere(true);
        sphere.slices()       = _display.slices;
        sphere.stacks()       = _display.stacks;
        sphere.inheritColor() = true;

        for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
            if (i->_visible)
            {
                  const Particle &a = *i;

                  a._color.glColor();

                  if (!_display.points)
                  {
                     sphere.position(a._position,_radiusScale*a._radius);
                     sphere.draw();
                  }
            }
    }

    GLERROR
}

void
Grips::drawShadowVolumes() const
{
    GLERROR

    if (_document)
    {
        ParticleSystem &particles  = _document->particles();

        GlutCylinder cyl(true);
        cyl.slices() = _display.slices;
        cyl.stacks() = _display.stacks;
        cyl.inheritColor() = true;

        for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
            if (i->_visible)
            {
                const Particle &a = *i;

                GltColor col = a._color;
                col.alpha() = 0.2;
                col.glColor();

                if (!_display.points)
                {
                 cyl.position(a._position,a._position-Vector3(_light0.position())*10.0,_radiusScale*a._radius);
                 cyl.draw();
                }
            }
    }

    GLERROR
}

void
Grips::drawFloor() const
{
    GLERROR

    Integrator *integrator = _document->integrator();

    if (_display.floor && integrator && integrator->_boundingBox.defined())
    {
        BoundingBox &box = integrator->_boundingBox;

        glPushAttrib(GL_ENABLE_BIT);

            glDisable(GL_LIGHTING);
            white.glColor();
            glBegin(GL_LINE_LOOP);
            Vector(box.max().x(),box.max().y(),box.min().z()).glVertex();
            Vector(box.max().x(),box.min().y(),box.min().z()).glVertex();
            Vector(box.min().x(),box.min().y(),box.min().z()).glVertex();
            Vector(box.min().x(),box.max().y(),box.min().z()).glVertex();
            glEnd();

        glPopAttrib();
    }

    GLERROR
}

void
Grips::drawBox() const
{
    GLERROR

    if (!_document)
        return;

    Integrator *integrator = _document->integrator();

    if (_display.box && integrator && integrator->_boundingBox.defined())
    {
        glPushAttrib(GL_ENABLE_BIT);
            glDisable(GL_LIGHTING);
            GlutCube box(false);
            box.position(integrator->_boundingBox.min(),integrator->_boundingBox.max());
            box.color() = white;
            box.draw();
        glPopAttrib();
    }

    GLERROR
}

void Grips::OnDisplay()
{
    // Clear Screen

    _background.glClearColor();

    glClearStencil(0);
    glStencilMask(~0);

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (_display.ortho)
    {
//        GltOrtho proj;
        _display.orthoConfig.set(getWidth(),getHeight());

//        GltOrtho tile;
//        proj.tile(tile,tileX,tileY,tileN);
//        tile.set();
    }
    else
    {
        GltPerspective proj;
        proj.zFar() = 30;
        proj.zNear() = 0.1;
        proj.mult(getWidth(),getHeight());
    }

//    else
//    {
#if 0
        GltFrustum proj;
        proj.set(getWidth(),getHeight());

        GltFrustum tile;
        proj.tile(tile,tileX,tileY,tileN);
        tile.set();
//#else

    glMatrixMode(GL_MODELVIEW);



/*

        GltPerspective proj;
        proj.zFar() =  40.0;
        proj.zNear() = 0.01;
        proj.mult(getWidth(),getHeight());
*/

    if (tileN>=0)
    {
        GltOrtho proj;
//      proj.set(getWidth(),getHeight());

        GltOrtho tile;
        proj.tile(tile,tileX,tileY,tileN);
        tile.mult();
    }

    glTranslatef(0,0,-15);
    referencePoint() = VectorZ*-15;

    {
    //  GltFrustum proj;
        GltPerspective proj;
        proj.zFar() = 30;
        proj.zNear() = 0.1;
        proj.mult(getWidth(),getHeight());
    }

//        GltPerspective tile;
//        proj.tile(tile,tileX,tileY,tileN);
//        tile.set();
#endif
//    }


    GLERROR

    //

    _material.set();
//    _light0.set();

    if (_document)
    {
        ParticleSystem &particles  = _document->particles();
        Integrator     *integrator = _document->integrator();

        _spinInterp.draw();

        glPushMatrix();

            // Follow
            if (_display.follow && _current>=0 && _current<particles.size())
                glTranslate(-particles[_current]._position);

            // Spin
            _spin.glMultMatrix();

            // OpenGL Configuration

            if (_display.lighting)
                glEnable(GL_LIGHTING);
            else
                glDisable(GL_LIGHTING);

            _light0.set();
            _light1.set();
            _light2.set();


            // Draw trails first

            glPushAttrib(GL_ENABLE_BIT|GL_DEPTH_BUFFER_BIT);

                glDisable(GL_LIGHTING);
                glEnable(GL_LINE_SMOOTH);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                glLineWidth(1.2);
                glDepthFunc(GL_ALWAYS);
                glDepthMask(GL_FALSE);

                if (_document)
                    _document->_video.draw();

    /*
                glPushMatrix();
                    glDisable(GL_CULL_FACE);
                    glRotatef(90.0,1,0,0);
                    const real sf = 8.0/64;
                    glScalef(sf,sf,sf);
                    _sprite.draw();
                glPopMatrix();
    */
                // Draw trails

                if (_display.trail)
                   for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                      if (i->_visible)
                      {
                         i->_color.glColor();
                         i->_trail.draw();
                      }

                glDepthMask(GL_TRUE);
                glDepthFunc(GL_LESS);

                // Draw field

                if (_document && integrator)
                    _field.draw(particles,*integrator);

                // Draw points

                if (_display.points)
                {
    #if 1
                    glPushAttrib(GL_ENABLE_BIT);
                        glDisable(GL_LIGHTING);
                        glDisable(GL_NORMALIZE);
                        glDisable(GL_DEPTH_TEST);
                        glDisable(GL_CULL_FACE);
                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                        glEnable(GL_TEXTURE_2D);

                        _texture[clamp(_textureCurrent,0,2)].set();

                        for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                           if (i->_visible)
                           {
                                i->_color.glColor();

                                glPushMatrix();
                                glTranslate(i->_position);
                                glScale(_radiusScale*i->_radius);
                                glRotatef(90,1,0,0);
                                _quad.draw();
                                glPopMatrix();
                             }

                    glPopAttrib();

    #else
                    glBegin(GL_POINTS);
                    for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                      if (i->_visible)
                          {
                             i->_color.glColor();
                             i->_position.glVertex();
                          }
                    glEnd();
    #endif
                }

           glPopAttrib();


            // Create stencil mask

            if (_display.stencil)
            {
                glEnable(GL_STENCIL_TEST);
                glStencilFunc(GL_ALWAYS,1,1);
                glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
                glStencilMask(1);
                glDepthMask(GL_FALSE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
                _grid.drawQuad();

                glStencilFunc(GL_EQUAL,1,1);
                glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                glStencilMask(1);
                glDepthMask(GL_TRUE);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
            }

            // Draw reflections, grid and then shadows

            GLERROR

            drawReflections();

            if (_display.stencil)
            {
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                glDisable(GL_STENCIL_TEST);
            }

            drawFloor();
            drawGrid();

            if (_display.stencil)
            {
                glEnable(GL_STENCIL_TEST);
                glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);
            }

            drawShadows();

            GLERROR

            if (_display.stencil && _display.selfShadows)
            {
                // In 1st pass, form z-buffer

                glDisable(GL_STENCIL_TEST);
                glDisable(GL_LIGHT0);
                glEnable(GL_LIGHT1);
                glEnable(GL_LIGHT2);
                drawParticles();

                // In 2nd pass, form stencil buffer

                glStencilMask(~0);
                glClear(GL_STENCIL_BUFFER_BIT);

                glEnable(GL_STENCIL_TEST);
                glDepthMask(GL_FALSE);
                glDisable(GL_CULL_FACE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

                ParticleSystem &particles  = _document->particles();

                GlutCylinder cyl(true);
                cyl.slices() = _display.slices;
                cyl.stacks() = _display.stacks;

                for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                    if (i->_visible)
                    {
                        const Particle &a = *i;

                        glStencilFunc(GL_ALWAYS,2,2);
                        glStencilOp(GL_KEEP,GL_KEEP,GL_INVERT);
                        glStencilMask(2);

                        cyl.position(a._position,a._position-Vector3(_light0.position())*10.0,_radiusScale*a._radius);
                        cyl.draw();

                        glStencilFunc(GL_EQUAL,2,6);
                        glStencilOp(GL_KEEP,GL_KEEP,GL_INVERT);
                        glStencilMask(6);
                        drawZnear();

                        glStencilMask(2);
                        glClear(GL_STENCIL_BUFFER_BIT);
                    }

                // In 3rd pass, draw with z-equal and stencil test

                glStencilFunc(GL_EQUAL,0,4);
                glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                glEnable(GL_LIGHT0);
                glEnable(GL_LIGHT1);
                glEnable(GL_LIGHT2);
                glDepthFunc(GL_EQUAL);
                glEnable(GL_CULL_FACE);
                drawParticles();

                glDepthFunc(GL_LESS);
                glDepthMask(GL_TRUE);
                glDisable(GL_STENCIL_TEST);
            }
            else
            {
                glDisable(GL_STENCIL_TEST);
                drawParticles();
            }

            drawBox();

            if (_display.shadowVolumes)
            {
                glPushAttrib(GL_ENABLE_BIT);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                    glCullFace(GL_BACK);
                    drawShadowVolumes();

                glPopAttrib();
            }

            GLERROR

            // Draw bodies as spheres

            GlutCylinder accel(true);
            accel.inheritColor() = true;

            for (ParticleSystem::const_iterator i=particles.begin(); i!=particles.end(); i++)
                if (i->_visible)
                {
                      const Particle &a = *i;

                      a._color.glColor();

                      Vector f = a._mass * a._acceleration;
                      if (_display.accel && f.norm()>1e-6)
                      {
                         f.normalize();
                         accel.position(a._position,a._position+f*a._radius*2.0,a._radius*0.2);
                         accel.draw();
                      }

                      // Draw trail

                      if (_display.trail)
                      {
                         glPushAttrib(GL_ENABLE_BIT);
                            glDisable(GL_LIGHTING);
                            a._trail.draw();
                         glPopAttrib();
                      }
                }

    /*
            // Draw center of mass

            if (_display.center)
            {
                _center.transformation() = matrixTranslate(_particles._centerOfMass);
                _center.draw();
            }
    */
            // Draw axes

            glPushMatrix();
                glScale(_axesSize);
                _axes.draw();
            glPopMatrix();

            //


        glPopMatrix();

        // Draw forumula

        if (_display.formula)
            drawLogo(_viewport,_formula ,GLT_ALIGN_RIGHT  ,GLT_ALIGN_TOP   ,true ,white);

        if (_display.logo)
        {
            drawLogo(_viewport,_rmit    ,GLT_ALIGN_LEFT   ,GLT_ALIGN_BOTTOM,true ,white);
            drawLogo(_viewport,_vpac    ,GLT_ALIGN_HCENTER,GLT_ALIGN_BOTTOM,true ,white);
            drawLogo(_viewport,_eScience,GLT_ALIGN_RIGHT  ,GLT_ALIGN_BOTTOM,true ,white);
        }

        if (_document)
        {
            GltViewport v(true);
            GltViewport tmp(true);
            tmp.shrink(32);
            tmp.height() /= 2;
            tmp.set();
            _document->_histogramVx.draw();
            _document->_histogramVy.draw();
            _document->_histogramVz.draw();
            _document->_histogramSpeed.draw();
            v.set();
        }

        // Draw text overlay

        if (_menu.active())
        {
            _info.text() = _menu.menu();
            _info.draw();
        }
        else if (_display.options)
        {
            _info.text() = _options;
            _info.draw();
        }
        else if (_display.info)
        {
            ostringstream os;
            os.setf(ios::fixed|ios::showpoint);
            os.precision(3);

            if (integrator)
                integrator->print(os);

            os << '\0';

            _info.text() = os.str();
            _info.draw();
        }
    }

    setAnimation(_display.animation);
}

void
Grips::OnMenu(int value)
{
    switch (value)
    {

    case NBODY_STEP:                OnTick(); break;
    case NBODY_ANIMATE:     setAnimation(!_display.animation);          break;

    case NBODY_DISPLAY_INFO:    _display.info     = !_display.info; break;
    case NBODY_DISPLAY_POINTS:  _display.points   = !_display.points;   break;
    case NBODY_DISPLAY_ACCEL:   _display.accel    = !_display.accel;    break;
    case NBODY_DISPLAY_CENTER:  _display.center   = !_display.center;   break;
    case NBODY_DISPLAY_FOLLOW:  _display.follow   = !_display.follow;   break;
    case NBODY_DISPLAY_LIGHTING:    _display.lighting = !_display.lighting; break;

//  case NBODY_DISPLAY_FORCE_FIELD:     _showForceField = !_showForceField;         break;
//  case NBODY_DISPLAY_FORCE_FIELD_MORE:    _field._size *= 0.75;               break;
//  case NBODY_DISPLAY_FORCE_FIELD_LESS:    _field._size *= 1.5;                break;

    default:
        GlutWindowExaminer::OnMenu(value);
    }

   postRedisplay();
}

void
Grips::OnKeyboard(unsigned char key, int x, int y)
{
    if (_menu.OnKeyboard(key,x,y))
    {
        postRedisplay();
        return;
    }

    // Use the top row on the keyboard for selecting built-in
    // examples.

    const string exampleKeys = "`1234567890-=\\~!@#$%^&*()_+|";

    if (exampleKeys.find(key)!=string::npos)
    {
        // Count the number of available examples

        int n=0;
        for (int i=0;examples[i]!=NULL;i++)
            n++;

        //  Select the j'th example, if in range

        const int j = exampleKeys.find(key);

        if (j>=0 && j<n)
            read(examples[j]);

        return;
    }

    switch (key)
    {
        case 's': OnMenu(NBODY_ANIMATE);            break;
        case ' ': OnMenu(NBODY_STEP);               break;
//      case '.': OnMenu(NBODY_FASTER);             break;
//      case ',': OnMenu(NBODY_SLOWER);             break;
//      case 'r': OnMenu(NBODY_REVERSE);            break;

        case 't': OnMenu(NBODY_TRAIL);              break;
        case '<': OnMenu(NBODY_TRAIL_SHORTER);          break;
        case '>': OnMenu(NBODY_TRAIL_LONGER);           break;

//      case 'I': OnMenu(NBODY_INTEGRATOR);         break;
        case 'i': OnMenu(NBODY_DISPLAY_INFO);           break;
        case 'a': OnMenu(NBODY_DISPLAY_ACCEL);          break;
        case 'c': OnMenu(NBODY_DISPLAY_CENTER);         break;
        case 'x': OnMenu(NBODY_DISPLAY_AXES);           break;
        case 'v': OnMenu(NBODY_DISPLAY_FORCE_FIELD);        break;
        case '+': OnMenu(NBODY_DISPLAY_FORCE_FIELD_MORE);   break;
        case '-': OnMenu(NBODY_DISPLAY_FORCE_FIELD_LESS);   break;
        case 'f': OnMenu(NBODY_DISPLAY_FOLLOW);         break;
        case 'l': OnMenu(NBODY_DISPLAY_LIGHTING);       break;
        case 'p': OnMenu(NBODY_DISPLAY_POINTS);         break;

        case '?':
            {
                ofstream os(_filename.c_str());
                write(os);
                break;
            }

        case '/':
            {
                ifstream is(_filename.c_str());
                read(is);
                break;
            }

        case ':':
            {
                _server.sendState(*this);
                _server.sendTile();
                break;
            }

        case '!':   if (_document) _document->init(); break;

        default:
            GlutWindowExaminer::OnKeyboard(key,x,y);
    }

    postRedisplay();
}

void
Grips::OnSpecial(int key, int x, int y)
{
    if (_menu.OnSpecial(key,x,y))
    {
        postRedisplay();
        return;
    }

    switch (key)
    {
        default:
            GlutWindowExaminer::OnSpecial(key,x,y);
    }

    postRedisplay();
}

void
Grips::OnMouse(int button, int state, int x, int y)
{
    GlutWindowExaminer::OnMouse(button,state,x,y);

    _server.sendState(*this,"grips.display.opengl.transform");
    _server.sendState(*this,"grips.display.opengl.transformInv");
}

void
Grips::OnMotion(int x, int y)
{
    GlutWindowExaminer::OnMotion(x,y);

    _server.sendState(*this,"grips.display.opengl.transform");
    _server.sendState(*this,"grips.display.opengl.transformInv");
}

void
Grips::setAnimation(const bool animate)
{
    if (_display.animation = animate)
        setTick(_display.wait>0 ? _display.wait : 1);
    else
        setTick(0);
}

void
Grips::OnNotify(const Document *subject)
{
 //   cout << "Grips::OnNotify" << endl;

    assert(subject==_document);

    // Set an appropriate formula texture for
    // top-right of viewport.

    if (getOpen())
    {
        const Integrator *integrator = subject->integrator();

        if (dynamic_cast<const EngineLorenz *>(integrator))
            _formula.init(lorenzfTexture);
        else
            if (dynamic_cast<const EngineRossler *>(integrator))
                _formula.init(rosslerfTexture);
            else
                if (dynamic_cast<const EngineGravity *>(integrator))
                    _formula.init(gravityfTexture);
                else
                    if (dynamic_cast<const EngineProjectile *>(integrator))
                        _formula.init(projectfTexture);
                    else
                        _formula.init(NULL);
    }

    // Update the field heirachy

    _settings.set(settings());
    _menu.reset();
}

const string Grips::help =
"GRIPS - GRand Integrated Particle System      \n" \
"RMIT School of Computer Science and IT        \n" \
"Email: nigels@cs.rmit.edu.au                  \n" \
"\n";
