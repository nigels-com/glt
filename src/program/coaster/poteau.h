#ifndef _POTEAU_HEADER
#define _POTEAU_HEADER

#include "point.h"

int poteau_init(point *pline, int nbLine, point* ptang);
void poteau_draw();
void drawtree();

void calc_coul(int nb, point* r, point* amb, point* dif, point* lig, point* normale);

/* those ones are exported to be initialized by the parser */

extern point *ppoteaucoord;
extern int *ppoteauabsc;
extern int nbPoteauCoord;
extern int nbPoteauAbsc;

extern point *ptree;
extern int nbTree;

extern point panneauPosition;
extern point panneauDirection;

extern float metalLength;
extern float metalAngle;
extern point metalPosition;

#endif /* _POTEAU_HEADER */
