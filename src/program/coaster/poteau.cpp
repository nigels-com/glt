#include <glt/gl.h>
#include <glt/texture.h>
#include <math/real.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "poteau.h"
#include "point.h"

point* ppoteau;
point* plien;
point* ppoteau_coul;
point* plien_coul;
int nbPoteau;
int nbLien;

int nbCotePoteau = 6;
int nbCoteLien = 4;

float rayonPoteau = 0.02f;
static float rayonLien = 0.015f;

float distPoteau = 0.4;
float hauteurLien = 0.1;

point light_dir = {1.0f,-0.5f,2.0f};
point lightAmbient = {0.4f,0.4f,0.4f};
point lightDiffuse = {1.0f,0.9f,1.0f};
point light = {1.0f,0.5f,1.0f};

FILE *file;


void cylinder(point* a, point* b, point* v, int nbcote, float rayon, point *buf, point* bufn){
    int i,k;
    point p1,p2,p4;
    sub(&p1,a,b);
    normalize(&p1);
    p4 = *v;
    add_mult(&p4,prod_scal(v,&p1)/norme2(&p1),&p1);
    normalize(&p4);
    mult(&p4,rayon,&p4);
    k = 0;
    for(i=0 ; i<nbcote ; i++){
        rotate(&p2,&p1,(float)i*2.0f*M_PI/(float)nbcote,&p4);
        add(&buf[k++],a,&p2);
        add(&buf[k++],b,&p2);
    }
    k = 0;
    for(i=0 ; i<nbcote ; i++){
        sub(&p1,&buf[k],a);
        normalize(&p1);
        bufn[k++] = p1;
        sub(&p1,&buf[k],b);
        normalize(&p1);
        bufn[k++] = p1;
    }
}


void calc_coul(int nb, point* r, point* amb, point* dif, point* lig, point* normale)
{
    int i;
    float f;
    for(i=0 ; i<nb ; i++){
        f = prod_scal(&light_dir,&normale[i]);
        if(f<=0.0f) f = 0.0f;
        r[i].x = dif->x * f + lig->x * amb->x;
        r[i].y = dif->y * f + lig->y * amb->y;
        r[i].z = dif->z * f + lig->z * amb->z;
    }
}


// p est un point de la trajectoire
// v est la tangente à la trajectoire en ce point
void create_poteau(point* p1, point* p2, point* v, point* buf, point* bufc){
    point a,b;
    int i;
    a = *p1;
    a.z = 0.0f;
    b = *p2;
    b.z = 0.0f;
    if(v->z < 0.0f)
    {
        a.z = b.z = -v->z;
        v->z = 0.0f;
    }
    cylinder(p1,&a,v,nbCotePoteau,rayonPoteau,buf,bufc);
    i = nbCotePoteau * 2;
    bufc[i].x = 0.0f; bufc[i].y = 0.0f; bufc[i].z = 1.0f;
    buf[i] = *p1;
    buf[i++].z += rayonPoteau;
    cylinder(p2,&b,v,nbCotePoteau,rayonPoteau,&buf[i],&bufc[i]);
    i += nbCotePoteau * 2;
    bufc[i].x = 0.0f; bufc[i].y = 0.0f; bufc[i].z = 1.0f;
    buf[i] = *p2;
    buf[i++].z += rayonPoteau;
    calc_coul(4*nbCotePoteau+2,bufc,&lightAmbient,&lightDiffuse,&light,bufc);
}


void create_lien(point* p, point* p1, point* p2, point* buf, point* bufc){
    point a;
    float z1, z2;
    z1 = p1->z;
    z2 = p2->z;
    p1->z = p->z - hauteurLien;
    p2->z = p->z - hauteurLien;
    a.x = 0.0f; a.y = 0.0f; a.z = 1.0f;
    cylinder(p,p1,&a,nbCoteLien,rayonLien,buf,bufc);
    cylinder(p,p2,&a,nbCoteLien,rayonLien,&buf[nbCoteLien*2],&bufc[nbCoteLien*2]);
    calc_coul(4*nbCoteLien,bufc,&lightAmbient,&lightDiffuse,&light,bufc);
    p1->z = z1;
    p2->z = z2;
}


void draw_poteau(int nb, point *buf, point *bufc){
    int i,j;
    nb *= 2;
    for(i=0 ; i<nb ; i++){
        glBegin(GL_QUAD_STRIP);
        for(j=0 ; j<2*nbCotePoteau ; j++){
            glColor3fv((float*)&bufc[j+i*(2*nbCotePoteau+1)]);
            glVertex3fv((float*)&buf[j+i*(2*nbCotePoteau+1)]);
        }
        glColor3fv((float*)&bufc[i*(2*nbCotePoteau+1)]);
        glVertex3fv((float*)&buf[i*(2*nbCotePoteau+1)]);
        glColor3fv((float*)&bufc[i*(2*nbCotePoteau+1)+1]);
        glVertex3fv((float*)&buf[i*(2*nbCotePoteau+1)+1]);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
        glColor3fv((float*)&bufc[(i+1)*(2*nbCotePoteau+1)-1]);
        glVertex3fv((float*)&buf[(i+1)*(2*nbCotePoteau+1)-1]);
        for(j=0 ; j<2*nbCotePoteau ; j+=2){
            glColor3fv((float*)&bufc[j+i*(2*nbCotePoteau+1)]);
            glVertex3fv((float*)&buf[j+i*(2*nbCotePoteau+1)]);
        }
        glColor3fv((float*)&bufc[i*(2*nbCotePoteau+1)]);
        glVertex3fv((float*)&buf[i*(2*nbCotePoteau+1)]);
        glEnd();
    }
}


void draw_lien(int nb, point *buf, point *bufc){
    int i,j;
    nb *= 2;
    for(i=0 ; i<nb ; i++){
        glBegin(GL_QUAD_STRIP);
        for(j=0 ; j<2*nbCoteLien ; j++){
            glColor3fv((float*)&bufc[j+i*(2*nbCoteLien)]);
            glVertex3fv((float*)&buf[j+i*(2*nbCoteLien)]);
        }
        glColor3fv((float*)&bufc[i*(2*nbCoteLien)]);
        glVertex3fv((float*)&buf[i*(2*nbCoteLien)]);
        glColor3fv((float*)&bufc[i*(2*nbCoteLien)+1]);
        glVertex3fv((float*)&buf[i*(2*nbCoteLien)+1]);
        glEnd();
    }
}


int est_relie(point* r, point* p, point* p1, point* p2, int i, point* pline, int nbLine){
    point v,n,z;
    float t;
    sub(&v,p1,p2);
    z.x = 0.0f; z.y = 0.0f; z.z = 1.0f;
    prod_vect(&n,&v,&z);
    sub(&v,&pline[(i+1)%nbLine],&pline[i]);
    if(!intersection(r,&pline[i],&v,p1,&n)) return 0;
    sub(&z,p1,&pline[i]);
    t = prod_scal(&z,&n) / prod_scal(&v,&n);
    if(t<0.0f || t>=1.0f) return 0;
    sub(&v,r,p);
    v.z = 0.0f;
    if(norme(&v)>0.3f) return 0;
    return 1;
}


void create_support(point* p, point* v, point* pline, int nbLine){
    point a,b,r;
    point p1, p2;
    int i;
    int flag_last_i=0;
    float zmax;
    a = *v;
    a.z = 0.0f;
    normalize(&a);
    if(a.x*a.x>0.0001f){
        a.x = -a.y / a.x;
        a.y = 1.0f;
    }
    else{ //a.y non nul
        a.y = -a.x / a.y;
        a.x = 1.0f;
    }
    normalize(&a);
    mult(&a,distPoteau/2.0f,&a);
    b = *p;
    add(&p1,&b,&a);
    sub(&p2,&b,&a);
    zmax = -1.0f;
    for(i=0 ; i<nbLine ; i++){
        if(est_relie(&r,p,&p1,&p2,i,pline,nbLine)){
            if(!flag_last_i && ((p->z*p->z)<0.0001f || p->z > r.z) && r.z-hauteurLien>-v->z){
                create_lien(&r,&p1,&p2,&plien[nbLien*4*nbCoteLien],&plien_coul[nbLien*4*nbCoteLien]);
                nbLien++;
                flag_last_i = 1;
                if(r.z > zmax) zmax = r.z;
            }
            else flag_last_i = 0;
        }
        else flag_last_i = 0;
    }
    if(zmax > -0.5f){
        p1.z = p2.z = zmax;
        if(v->z > 0.001f){
            panneauPosition = *p;
            panneauPosition.z = v->z;
            p1.z = p2.z = v->z; v->z = 0.0f;
            panneauDirection = *v;
        }
        create_poteau(&p1,&p2,v,&ppoteau[nbPoteau*(4*nbCotePoteau+2)],&ppoteau_coul[nbPoteau*(4*nbCotePoteau+2)]);
        nbPoteau++;
    }
}

//****************** fonctions exportées *******************


point *ppoteaucoord; /* coordinates were pillars have to be placed */
int *ppoteauabsc;    /* abscisses on the track from the start were pillars have to be placed */
int nbPoteauCoord = 0;
int nbPoteauAbsc = 0;

point *ptree;
int nbTree;

int poteau_init(point *pline, int nbLine, point* ptang){
    point p,v;
    int i;
    int taille_tab;
    point *tab;
    int taille_tab1;
    int *tab1;

    taille_tab = nbPoteauCoord;
    tab = ppoteaucoord;
    taille_tab1 = nbPoteauAbsc;
    tab1 = ppoteauabsc;
    nbPoteau = taille_tab + taille_tab1;
    nbLien = nbPoteau*10;  /******** Here we assume that the maximum is 10 liens for 1 poteau ********/
    normalize(&light_dir);
    ppoteau = (point*)malloc(nbPoteau*(4*nbCotePoteau+2)*sizeof(point));
    ppoteau_coul = (point*)malloc(nbPoteau*(4*nbCotePoteau+2)*sizeof(point));
    plien = (point*)malloc(nbLien*(4*nbCoteLien)*sizeof(point));
    plien_coul = (point*)malloc(nbLien*(4*nbCoteLien)*sizeof(point));
    nbPoteau = nbLien = 0;
    for(i=0 ; i<taille_tab ; i++) create_support(&tab[2*i],&tab[2*i+1],pline,nbLine);
    for(i=0 ; i<taille_tab1 ; i++){
        p = pline[tab1[i]];
        v = ptang[tab1[i]];
        p.z = v.z = 0.0f;
        create_support(&p,&v,pline,nbLine);
    }
    return 1;
}

void poteau_draw()
{
    draw_poteau(nbPoteau,ppoteau,ppoteau_coul);
    draw_lien(nbLien,plien,plien_coul);
}
