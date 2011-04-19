#ifndef ROLLER_H
#define ROLLER_H

#include "point.h"

#include <iosfwd>

#include <cstdlib>
#include <cstdio>
using namespace std;

//#define ROLLER_NOERROR 0
//#define ROLLER_GLWINDOWCREATION_ERROR 1

/* those ones are exported to be initialized by the parser */

class RollerCoaster
{
public:
    RollerCoaster();
    ~RollerCoaster();

    void ParseRollerFile(char *filename);
    int InitializeRoller(int width, int height, int stereoscopic, float viewAngle, float eyeDist, float focalLength);
    int DrawRoller();
    void ChangeRollerParameters(float viewAngle, float eyeDist, float focalLength);

    bool DrawGLScene0(const float time);
    bool DrawGLScene(const float time);

private:

    float rayonDeCourbure(int i, float t);
    void InitCurve(float longueur_seg);
    void calcTuyau(point *pline, int nbLine, int nbCote, float rayon, float angle, point *pmesh);
    void InitLines();
    void InitLiens(float f);
    void InitNormales();
    void InitCouleurs(point *light_dir);
    void drawEverything();

    //

    int readfile();
    void initinfo();
    void initdefault();
    int parsefile();
    int openfile(char *str);
    int closefile();
    void printerror(char *str, ...);

    int  readchar();
    int  ungetchar(int c);
    void skipwhite();
    void skipcomment();

    int readfloat(float *f);
    int readpositiveinteger(int *i);
    int skipnewline();
    int readpoint(point *p);
    int readname(char *str, int length);
    int readsignedint(int *i);
    int readunsignedint(int *i);
    int readseparator();

    FILE *file;
    int line_number;


    //

    float aperture;  /* field of view angle in degree */
    float near_clip; /* near clip plane coord */
    float far_clip;  /* far clip plane coord */

    int startSegment;           /* index of segment where the train starts */
    int brakeSegment;           /* index of segment where the train starts braking */
    float averageSegmentLength; /* length of segments that the track is made of */
    float twistFactor;          /* amount of tilt when the track tilt in turns */

    int stereo;                /* stereoscopic mode is on if non zero */
    float eye_sep;             /* distance between eyes */
    float focallength;
    int wndWidth, wndHeight;

    int nbPointControle;      // points par lesquelles passe la courbe de Bezier
    int nbLine;               // nombre total de segment du circuit
    int nbCote;               // nombre de cotes du cylindre
    int nbLiens;
    point *ppointcontrole;    /* tableau des points de controle tels qu'ils sont dans le fichier */
    point *pcontrole;         /* tableau des points des courbes de Bezier */
    float *pcourbure;         // courbure de la courbe projetée sur le plan xy
    point *pline;             // tableau des extremites des segments
    point *ppos;              // tableau des vecteurs position par rapport a la courbe
    point *ptraj;
    point *pcyl;              // tableau des coordonnees des vertex du tuyau
    point *pline1,*pline2;
    point *prail1, *prail2;
    point *prail1n, *prail2n, *pcyln; // tableau des normales
    point *pliens;
    point *pnliens;
    point *pliensn;
    point *ptang;               // tangente à la trajectoire en chacun des points

    float *pnorme;              // longueurs des segments (Length of each segment)

    float rayonCyl;
    float rayonLien;
    float longueurLien;

    float maxZ;                 /* maximum z coordinate of the curve             */
    float maxDist;              /* maximum distance of the curve from the origin */
};

#endif
