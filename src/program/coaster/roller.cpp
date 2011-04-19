#include <glt/gl.h>
#include <glt/glu.h>

#include <math/real.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "point.h"
#include "poteau.h"
#include "parser.h"
#include "roller.h"

////////////

void matrix_mult(float *r, float* a, float *b)
{
    {
        for(int i=0 ; i<16 ; i++)
            r[i]=0.0f;
    }

    for (int i=0 ; i<4 ; i++)
    {
        for (int j=0 ; j<4 ; j++)
        {
            r[i+4*j] = a[i]*b[4*j] + a[i+4]*b[4*j+1] + a[i+8]*b[4*j+2] + a[i+12]*b[4*j+3];
        }
    }
}


void mult_vect(point *r, float *m, point *v){
    float w;
    w = m[3]*v->x + m[7]*v->y + m[11]*v->z + m[15];
    r->x = (m[0]*v->x + m[4]*v->y + m[8]*v->z + m[12]) / w;
    r->y = (m[1]*v->x + m[5]*v->y + m[9]*v->z + m[13]) / w;
    r->z = m[2]*v->x + m[6]*v->y + m[10]*v->z + m[14];
}

/////////////

RollerCoaster::RollerCoaster()
:
    file(NULL),
    line_number(1),

    //

    aperture(60.0f),
    near_clip(0.01f),
    far_clip(60.0f),
    startSegment(-5),
    brakeSegment(-20),
    averageSegmentLength(0.15f),
    twistFactor(5.0f),
    stereo(0),
    eye_sep(0.005f),
    focallength(0.05f),
    wndWidth(0),
    wndHeight(0),
    nbPointControle(0),
    nbLine(0),
    nbCote(6),
    nbLiens(0),
    ppointcontrole(NULL),
    pcontrole(NULL),
    pcourbure(NULL),
    pline(NULL),
    ppos(NULL),
    ptraj(NULL),
    pcyl(NULL),
    pline1(NULL),
    pline2(NULL),
    prail1(NULL),
    prail2(NULL),
    prail1n(NULL),
    prail2n(NULL),
    pcyln(NULL),
    pliens(NULL),
    pnliens(NULL),
    pliensn(NULL),
    ptang(NULL),
    pnorme(NULL),
    rayonCyl(0.02f),
    rayonLien(0.01f),
    longueurLien(0.1f),
    maxZ(0.0f),
    maxDist(0.0f)
{
}

RollerCoaster::~RollerCoaster()
{
}



// calcul la longueur d'un patch de Bézier en le discrétisant avec 1000 segments
float longueur_bezier(point *p1, point *p2, point *p3, point *p4){
    point a,b;
    float t,f;
    float d = 1.0f/1000.0f;
    a = *p1;
    f = 0.0f;
    for(t=d ; t<=1.0f ; t+=d){
        mult(&b, (1-t)*(1-t)*(1-t), p1);
        add_mult(&b, 3*t*(1-t)*(1-t), p2);
        add_mult(&b, 3*t*t*(1-t), p3);
        add_mult(&b, t*t*t, p4);
        sub(&a,&b,&a);
        f += norme(&a);
        a = b;
    }
    return f;
}


point *pvitesse;
point *paccel;


/* Calcul l'inverse du rayon de courbure de la courbe de Bézier i (projeté sur le plan xy) à l'abscisse t */
float
RollerCoaster::rayonDeCourbure(int i, float t)
{
    point v,g; /* vitesse et accélération */

    v.z = g.z = 0.0f;
    mult(&v, -3*t*t+6*t-3, &pcontrole[3*i]);
    add_mult(&v, 9*t*t-12*t+3, &pcontrole[3*i+1]);
    add_mult(&v, -9*t*t+6*t, &pcontrole[3*i+2]);
    add_mult(&v, 3*t*t, &pcontrole[3*i+3]);
    mult(&g, -6*t+6, &pcontrole[3*i]);
    add_mult(&g, 18*t-12, &pcontrole[3*i+1]);
    add_mult(&g, -18*t+6, &pcontrole[3*i+2]);
    add_mult(&g, 6*t, &pcontrole[3*i+3]);
    v.z = g.z = 0.0f;


    /* formula : 1/R = det(v,g)/|v|^3 */
    if(norme2(&v) < 0.5f)  /* cas la trajectoire est proche de la verticale */
    {
        return 0.0f;
    }
    return (v.x * g.y - v.y * g.x) / norme2(&v) / norme(&v);
    /* autre façon de calculer l'inverse du rayon de courbure:
     * projeter le vecteur accélération sur un vecteur unitaire orthoganal
     * à la trajectoire (à l'aide d'un produit scalaire). Diviser le résultat
     * par le carré de la longueur du vecteur vitesse.
     * 1 / R = prod_scal(&n,&g) / norme2(&v); où n est orthogonale à v
     */
}


/* longueur_seg est la longueur d'un segment de la courbe */
void
RollerCoaster::InitCurve(float longueur_seg)
{
    int i,j,k;
    point a,b,c;
    float t,d;
    float *pnbsegment;

    /* initialise pcontrole à partir de ppointcontrole */
    pcontrole = (point*) malloc((3*nbPointControle+1)*sizeof(point));
    for(i=0 ; i<nbPointControle ; i++) {
        pcontrole[3*i] = ppointcontrole[2*i];
        pcontrole[3*i+1] = ppointcontrole[2*i+1];
    }
    pcontrole[3*nbPointControle] = pcontrole[0];
    /* calculer les points intermédiaires */
    for(i=0 ; i<3*nbPointControle ; i+=3){
        b = pcontrole[i+1];
        if(i>0) j = i-3; else j = 3*nbPointControle-3;
        if(norme(&b)<=0.1f){
            sub(&b,&pcontrole[i+3],&pcontrole[j]);
        }
        normalize(&b);
        sub(&c,&pcontrole[i+3],&pcontrole[i]);
        if(prod_scal(&b,&c)<0.0f){ b.x = -b.x; b.y = -b.y; b.z = -b.z; }
        mult(&a,norme(&c)*M_PI/5.5f/1.41421f,&b);
        add(&pcontrole[i+1],&pcontrole[i],&a);
        b.x = -b.x; b.y = -b.y; b.z = -b.z;
        sub(&c,&pcontrole[i],&pcontrole[j]);
        mult(&a,norme(&c)*M_PI/5.5f/1.41421f,&b);
        if(i>0) k = i-1; else k = 3*nbPointControle-1;
        add(&pcontrole[k],&pcontrole[i],&a);
    }
    /* calculer le nombre de segments pour chaque patch de Bézier */
    pnbsegment = (float *) malloc(nbPointControle*sizeof(float));
    nbLine = 0;
    for(i=0 ; i<nbPointControle ; i++){
        j = i * 3;
        t = longueur_bezier(&pcontrole[j],&pcontrole[j+1],&pcontrole[j+2],&pcontrole[j+3]);
        pnbsegment[i] = t / longueur_seg;
        if(!pnbsegment[i])
            pnbsegment[i] = 1.0f;
        nbLine += (int) floor(pnbsegment[i] + 1);
    }
    /* faire la discrétisation pour tout les patchs */
    pline = (point*)malloc(nbLine*sizeof(point));
/*  pcourbure = (float*)malloc(nbLine*sizeof(float)); */
    k = 0;
    for(i=0 ; i<nbPointControle ; i++){
        a = pcontrole[3*i];
        pline[k++] = a;
        d = 1.0f / (pnbsegment[i]+1.0f);
        for(j=1,t=d ; j<pnbsegment[i] ; j++,t+=d){
            mult(&b, (1-t)*(1-t)*(1-t), &pcontrole[3*i]);
            add_mult(&b, 3*t*(1-t)*(1-t), &pcontrole[3*i+1]);
            add_mult(&b, 3*t*t*(1-t), &pcontrole[3*i+2]);
            add_mult(&b, t*t*t, &pcontrole[3*i+3]);
            pline[k] = b;
            if(b.z > maxZ) maxZ = b.z;
            if(b.x * b.x + b.y * b.y > maxDist) maxDist = b.x * b.x + b.y * b.y;
/*          pcourbure[k] = - rayonDeCourbure(i,t); */
            k++;
        }
    }
    maxDist = sqrt(maxDist);
    free(pnbsegment);
}


/* intersection du cylindre d'axe v avec le plan passant par p de normal n */
void calcCercle(point *p, point *z, point *v, int nbCote, float rayon, float angle, point *n, point *pmesh){
    point r;
    int i;
    for(i=0 ; i<nbCote ; i++){
        rotate(&r, v, (angle+(float)i)*2.0f*M_PI/(float)nbCote, z);
        normalize(&r);
        mult(&r,rayon,&r);
        add(&r,p,&r);
        intersection(&r,&r,v,p,n);
        pmesh[i] = r;
    }
}


void
RollerCoaster::calcTuyau(point *pline, int nbLine, int nbCote, float rayon, float angle, point *pmesh)
{
    point a,b,c;
    point v,p;
    int i;
    a = pline[nbLine-1];
    for(i=0 ; i<nbLine ; i++)
    {
        b = pline[i];
        c = pline[(i+1)%nbLine];
        sub(&v,&b,&a);
        normalize(&v);
        sub(&c,&c,&b);
        normalize(&c);
        add(&p,&v,&c);
        c = ppos[i];
        calcCercle(&b, &c, &v, nbCote, rayon, angle+pcourbure[i], &p, &pmesh[i*nbCote]);
        a = b;
    }
}


void moyenne(float *tab, int nbelem, int nbmoy_pred, int nbmoy_succ)
{
    float *buf;
    int i,j,k;
    float tot,f,m;
    buf = (float*)malloc(nbelem*sizeof(float));
    for(i=0 ; i<nbelem ; i++) buf[i] = tab[i];
    for(i=0 ; i<nbelem ; i++){
        k = i;
        tot = 0.0f;
        m = 0.0f;
        for(j=0 ; j<nbmoy_pred ; j++){
            f = (float)j / nbmoy_pred;
            f = 1.0f - f*f;
            m += f;
            tot += f * buf[k];
            k = (k-1+nbelem) % nbelem;
        }
        k = (i+1) % nbelem;
        for(j=1 ; j<nbmoy_succ ; j++){
            f = (float)j / nbmoy_succ;
            f = 1.0f - f*f;
            m += f;
            tot += f * buf[k];
            k = (k+1) % nbelem;
        }
        tab[i] = tot / m;
    }
    free(buf);
}

void
RollerCoaster::InitLines()
{
    int i,j,k;
    float t;
    point a,b,c;
    point p,v;
    /* initialisation de pcourbure et pnorme */
    pcourbure   = (float*)malloc(nbLine*sizeof(float));
    pnorme      = (float*)malloc(nbLine*sizeof(float));

    k=0;
    for(i=0 ; i<nbLine ; i++)
    {
        sub(&p,&pline[i],&pline[(i-1+nbLine)%nbLine]);
        sub(&v,&pline[(i+1)%nbLine],&pline[i]);
        pnorme[i] = norme(&p);
        normalize(&p);
        normalize(&v);
        p.z = v.z = 0;
        prod_vect(&a,&v,&p);
        pcourbure[i] = twistFactor * asin(a.z);
/*      pcourbure[i] = pcourbure[i] / 1.8f; */
    }
    moyenne(pcourbure,nbLine,7,5);
    /* initialisation de ppos */
    ppos = (point*) malloc(nbLine*sizeof(point));
    c.x = 0.0f; c.y = 0.0f; c.z = 1.0f;
    /************** at point j, curve's upward vector must be +z ************/
    j = 0;
    for(i=0 ; i<nbLine ; i++){
        a = pline[(j+i-1+nbLine)%nbLine];
        b = pline[(j+i)%nbLine];
        sub(&p,&b,&a);
        normalize(&p);
        t = -prod_scal(&p,&c)/* / prod_scal(&p,&p)*/;
        add_mult(&c,t,&p);
        normalize(&c);
        prod_vect(&a,&p,&c);
        if(a.z != 0.0f){
            a.z = 0.0f;
            prod_vect(&c,&a,&p);
            normalize(&c);
        }
        ppos[(i+j)%nbLine] = c;
    }
    /* initialisation de ptraj et ptang */
    ptraj = (point*) malloc(nbLine*sizeof(point));
    ptang = (point*) malloc(nbLine*sizeof(point));
    a = pline[nbLine-1];
    for(i=0 ; i<nbLine ; i++){
        b = pline[i];
        c = pline[(i+1)%nbLine];
        sub(&p,&b,&a);
        normalize(&p);
        sub(&c,&c,&b);
        normalize(&c);
        add(&v,&p,&c);
        ptang[i] = v;
        normalize(&ptang[i]);
        add(&c,&ppos[i],&b);
        intersection(&a,&c,&p,&b,&v);
        sub(&a,&a,&b);
        normalize(&a);
        ptraj[i] = a;
        a = b;
    }
    /* initialisation de pcyl */
    pcyl = (point*) malloc(nbLine*4*sizeof(point));
    calcTuyau(pline,nbLine,4,rayonCyl,0.0f,pcyl);
    /* initialisation de pline1 et pline2 */
    pline1 = (point*) malloc(nbLine*sizeof(point));
    pline2 = (point*) malloc(nbLine*sizeof(point));
    a = pline[nbLine-1];
    for(i=0 ; i<nbLine ; i++){
        b = pline[i];
        c = pline[(i+1)%nbLine];
        sub(&p,&b,&a);
        normalize(&p);
        sub(&v,&c,&b);
        normalize(&v);
        t = pcourbure[i];
        add(&p,&v,&p);
        normalize(&p);
        v = ptraj[i];
        rotate(&c,&p,t+1.0f*M_PI/3.0f,&v);
        mult(&c,longueurLien,&c);
        add(&pline1[i],&c,&b);
        rotate(&c,&p,t-1.0f*M_PI/3.0f,&v);
        mult(&c,longueurLien,&c);
        add(&pline2[i],&c,&b);
        a = b;
    }
    /* initialisation de prail1 */
    prail1 = (point*) malloc(nbLine*nbCote*sizeof(point));
    calcTuyau(pline1,nbLine,nbCote,rayonCyl,0.0f,prail1);
    /* initialisation de prail2 */
    prail2 = (point*) malloc(nbLine*nbCote*sizeof(point));
    calcTuyau(pline2,nbLine,nbCote,rayonCyl,0.0f,prail2);
}


void
RollerCoaster::InitLiens(float f)
{ // f est la distance entre 2 liens consécutif souhaitée
    point a,a1,a2,p,p1,p2,b,v,n;
    float longueur,l;
    int i;
    int ia,ib;
    float distLien;
    float t,t1,t2;
    longueur = 0.0f;
    for(i=0 ; i<nbLine ; i++){
        longueur += pnorme[i];
    }
    nbLiens = (int)floor(longueur / f);
    pliens = (point*)malloc(nbLiens*12*sizeof(point));
    pnliens = (point*)malloc(nbLiens*3*sizeof(point));
    distLien = longueur / (float)nbLiens;
    l = 0.0f;
    ia = nbLine-1;
    ib = 0;
    sub(&p,&pline[ib],&pline[ia]);
    sub(&p1,&pline1[ib],&pline1[ia]);
    sub(&p2,&pline2[ib],&pline2[ia]);
    for(i=0 ; i<nbLiens ; i++){
        while(l > pnorme[ib]){
            l -= pnorme[ib];
            ia = (ia + 1) % nbLine;
            ib = (ib + 1) % nbLine;
            sub(&p,&pline[ib],&pline[ia]);
            sub(&p1,&pline1[ib],&pline1[ia]);
            sub(&p2,&pline2[ib],&pline2[ia]);
        }
        t = l / pnorme[ib];
        a = pline[ia];
        add_mult(&a,t,&p);
        pnliens[i*3] = a;
        a1 = pline1[ia];
        sub(&v,&a,&a1);
        t1 = prod_scal(&v,&p) / prod_scal(&p1,&p);
        add_mult(&a1,t1,&p1);
        pnliens[i*3+1] = a1;
        a2 = pline2[ia];
        sub(&v,&a,&a2);
        t2 = prod_scal(&v,&p) / prod_scal(&p2,&p);
        add_mult(&a2,t2,&p2);
        pnliens[i*3+2] = a2;
        sub(&n,&a1,&a2);
        normalize(&n);
        sub(&v,&a1,&a);
        normalize(&v);
        prod_vect(&b,&v,&p);
        normalize(&b);
        calcCercle(&a,&b,&v,4,rayonLien,0.0f,&n,&pliens[i*12]);       // lien avec le rail central
        calcCercle(&a1,&b,&v,4,rayonLien,0.0f,&n,&pliens[i*12+4]);
        sub(&v,&a,&a2);
        normalize(&v);
        prod_vect(&b,&v,&p);
        normalize(&b);
        calcCercle(&a2,&b,&v,4,rayonLien,0.0f,&n,&pliens[i*12+8]);
        l += distLien;
    }
}

void
RollerCoaster::InitNormales()
{
    int i;
    prail1n = (point*)malloc(nbLine*nbCote*sizeof(point));
    for(i=0 ; i<nbLine*nbCote ; i++){
        sub(&prail1n[i],&prail1[i],&pline1[i/nbCote]);
        normalize(&prail1n[i]);
    }
    prail2n = (point*)malloc(nbLine*nbCote*sizeof(point));
    for(i=0 ; i<nbLine*nbCote ; i++){
        sub(&prail2n[i],&prail2[i],&pline2[i/nbCote]);
        normalize(&prail2n[i]);
    }
    pcyln = (point*)malloc(nbLine*4*sizeof(point));
    for(i=0 ; i<nbLine*4 ; i++){
        sub(&pcyln[i],&pcyl[i],&pline[i/4]);
        normalize(&pcyln[i]);
    }
    pliensn = (point*)malloc(nbLiens*12*sizeof(point));
    for(i=0 ; i<nbLiens*3 ; i++){
        sub(&pliensn[i*4],&pliens[i*4],&pnliens[i]);
        normalize(&pliensn[i*4]);
        sub(&pliensn[i*4+1],&pliens[i*4+1],&pnliens[i]);
        normalize(&pliensn[i*4+1]);
        sub(&pliensn[i*4+2],&pliens[i*4+2],&pnliens[i]);
        normalize(&pliensn[i*4+2]);
        sub(&pliensn[i*4+3],&pliens[i*4+3],&pnliens[i]);
        normalize(&pliensn[i*4+3]);
    }
}

void
RollerCoaster::InitCouleurs(point *light_dir)
{
    int i;
    float f;
    static GLfloat LightAmbient[] = {0.4f,0.4f,0.4f,1.0f};
    static GLfloat LightDiffuse[] = {1.1f,0.8f,1.1f,1.0f};
    /* static GLfloat LightSpecular[] = {1.0f,1.0f,1.0f,1.0f}; */
    /* static GLfloat LightPosition[] = {-1.0f,1.0f,0.0f,1.0f}; */

    normalize(light_dir);
    for(i=0 ; i<nbLine*nbCote ; i++){
        f = prod_scal(light_dir,&prail1n[i]);
        if(f<=0.0f) f = 0.0f;
        prail1n[i].x = LightDiffuse[0] * f + LightAmbient[0];
        prail1n[i].y = LightDiffuse[1] * f + 0.0f * LightAmbient[1];
        prail1n[i].z = LightDiffuse[2] * f + LightAmbient[2];
        f = prod_scal(light_dir,&prail2n[i]);
        if(f<=0.0f) f = 0.0f;
        prail2n[i].x = LightDiffuse[0] * f + LightAmbient[0];
        prail2n[i].y = LightDiffuse[1] * f + 0.0f * LightAmbient[1];
        prail2n[i].z = LightDiffuse[2] * f + LightAmbient[2];
    }
    for(i=0 ; i<nbLine*4 ; i++){
        f = prod_scal(light_dir,&pcyln[i]);
        if(f<=0.0f) f = 0.0f;
        pcyln[i].x = LightDiffuse[0] * f + LightAmbient[0];
        pcyln[i].y = LightDiffuse[1] * f + 0.0f * LightAmbient[1];
        pcyln[i].z = LightDiffuse[2] * f + LightAmbient[2];
    }
    for(i=0 ; i<nbLiens*12 ; i++){
        f = prod_scal(light_dir,&pliensn[i]);
        if(f<=0.0f) f = 0.0f;
        pliensn[i].x = LightDiffuse[0] * f + LightAmbient[0];
        pliensn[i].y = LightDiffuse[1] * f + 0.0f * LightAmbient[1];
        pliensn[i].z = LightDiffuse[2] * f + LightAmbient[2];
    }
}


void drawTuyau0(point *ptuyau, point *pnorm, int nbLine, int nbCote, float *mat, point *pline){
    int i0,i,j,k;
    point v;
    int flag1,flag2;
    int index;
    mult_vect(&v,mat,&pline[0]);
    flag1 = (v.x<-1.1f || v.x>1.1f || v.y<-1.2f || v.y>1.1f || v.z>0.0f);
    i0 = 0;
    for(i=0 ; i<nbLine ; i++){
        mult_vect(&v,mat,&pline[(i+1)%nbLine]);
        flag2 = (v.x<-1.1f || v.x>1.1f || v.y<-1.2f || v.y>1.1f || v.z>0.0f);
        if(flag1 && flag2){i0 = (i+1)%nbLine; continue;}
        glBegin(GL_QUAD_STRIP);
        for(j=0 ; j<=nbCote ; j++){
            k = j % nbCote;
            index = ((i+1)%nbLine)*nbCote+k;
            glColor3fv((float*)&pnorm[index]);
            glVertex3fv((float*)&ptuyau[index]);
            index = i0*nbCote+k;
            glColor3fv((float*)&pnorm[index]);
            glVertex3fv((float*)&ptuyau[index]);
        }
        glEnd();
        i0 = (i+1)%nbLine;
        flag1 = flag2;
        if((v.z < -2.0f) && i<(nbLine-2) && (i%2)==0) i++;
    }
}


void drawTuyau(point *ptuyau, point *pnorm, int nbLine, int nbCote, float *mat, point *pline){
    int i0,i,j,k;
    point v;
    int flag1,flag2;
    int shl,shl0;
    int index;
    mult_vect(&v,mat,&pline[0]);
    flag1 = (v.x<-1.1f || v.x>1.1f || v.y<-1.2f || v.y>1.1f || v.z>0.0f);
    i0 = 0;
    shl0 = 0;
    for(i=0 ; i<nbLine ; i++){
        mult_vect(&v,mat,&pline[(i+1)%nbLine]);
        flag2 = (v.x<-1.1f || v.x>1.1f || v.y<-1.2f || v.y>1.1f || v.z>0.0f);
        if(flag1 && flag2){i0 = (i+1)%nbLine; continue;}
        if((v.z >= -2.0f)||(i==nbLine-1)) shl = 0; else shl = 1;
        if(shl && shl0){
            glBegin(GL_QUAD_STRIP);
            for(j=0 ; j<=nbCote ; j+=2){
                k = j % nbCote;
                index = ((i+1)%nbLine)*nbCote+k;
                glColor3fv((float*)&pnorm[index]);
                glVertex3fv((float*)&ptuyau[index]);
                index = i0*nbCote+k;
                glColor3fv((float*)&pnorm[index]);
                glVertex3fv((float*)&ptuyau[index]);
            }
            glEnd();
        }
        else{
            if(shl && !shl0){
                for(j=0 ; j<nbCote ; j+=2){
                    glBegin(GL_TRIANGLE_STRIP);
                    k = (j+2) % nbCote;
                    index = i0*nbCote+k;
                    glColor3fv((float*)&pnorm[index]);
                    glVertex3fv((float*)&ptuyau[index]);
                    index = ((i+1)%nbLine)*nbCote+k;
                    glColor3fv((float*)&pnorm[index]);
                    glVertex3fv((float*)&ptuyau[index]);
                    k = j+1;
                    index = i0*nbCote+k;
                    glColor3fv((float*)&pnorm[index]);
                    glVertex3fv((float*)&ptuyau[index]);
                    k = j;
                    index = ((i+1)%nbLine)*nbCote+k;
                    glColor3fv((float*)&pnorm[index]);
                    glVertex3fv((float*)&ptuyau[index]);
                    index = i0*nbCote+k;
                    glColor3fv((float*)&pnorm[index]);
                    glVertex3fv((float*)&ptuyau[index]);
                    glEnd();
                }
            }
            else{
                if(!shl && shl0){
                    for(j=0 ; j<nbCote ; j+=2){
                        glBegin(GL_TRIANGLE_STRIP);
                        k = j;
                        index = ((i+1)%nbLine)*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        index = i0*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        k = j+1;
                        index = ((i+1)%nbLine)*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        k = (j+2) % nbCote;
                        index = i0*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        index = ((i+1)%nbLine)*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        glEnd();
                    }
                }
                else{
                    glBegin(GL_QUAD_STRIP);
                    for(j=0 ; j<=nbCote ; j++){
                        k = j % nbCote;
                        index = ((i+1)%nbLine)*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                        index = i0*nbCote+k;
                        glColor3fv((float*)&pnorm[index]);
                        glVertex3fv((float*)&ptuyau[index]);
                    }
                    glEnd();
                }
            }
        }
        i0 = (i+1)%nbLine;
        shl0 = shl;
        flag1 = flag2;
        if((v.z < -2.0f) && i<(nbLine-2) && (i%2)==0) i++;
    }
}


void drawLiens(point *pliens, point *pliensn, int nbLiens, float *mat, point *pnliens){
    int i,j,k;
    point v;
    int flag1,flag2,flag3;
    int loin;
    for(i=0 ; i<nbLiens ; i++){
        mult_vect(&v,mat,&pnliens[i*3]);
        flag1 = (v.x<-1.0f || v.x>1.0f || v.y<-1.0f || v.y>1.0f || v.z>0.0f);
        loin = (v.z < -2.0f);
        mult_vect(&v,mat,&pnliens[i*3+1]);
        flag2 = (v.x<-1.0f || v.x>1.0f || v.y<-1.0f || v.y>1.0f || v.z>0.0f);
        mult_vect(&v,mat,&pnliens[i*3+2]);
        flag3 = (v.x<-1.0f || v.x>1.0f || v.y<-1.0f || v.y>1.0f || v.z>0.0f);
        if(!(flag1&&flag2)){
            glBegin(GL_QUAD_STRIP);
            for(j=0 ; j<5 ; j++){
                if(loin && j==3) j++;
                k = j % 4;
                glColor3fv((float*)&pliensn[i*12+4+k]);
                glVertex3fv((float*)&pliens[i*12+4+k]);
                glColor3fv((float*)&pliensn[i*12+k]);
                glVertex3fv((float*)&pliens[i*12+k]);
            }
            glEnd();
        }
        if(!(flag1&&flag3)){
            glBegin(GL_QUAD_STRIP);
            for(j=0 ; j<5 ; j++){
                if(loin && j==3) j++;
                k = j % 4;
                glColor3fv((float*)&pliensn[i*12+k]);
                glVertex3fv((float*)&pliens[i*12+k]);
                glColor3fv((float*)&pliensn[i*12+8+k]);
                glVertex3fv((float*)&pliens[i*12+8+k]);
            }
            glEnd();
        }
    }
}

void
RollerCoaster::drawEverything()
{
    float m[16];
    float modelmat[16], projmat[16];

    glGetFloatv(GL_MODELVIEW_MATRIX,modelmat);
    glGetFloatv(GL_PROJECTION_MATRIX,projmat);
    matrix_mult(m,projmat,modelmat);
    m[2] = modelmat[2];
    m[6] = modelmat[6];
    m[10] = modelmat[10];
    m[14] = modelmat[14];

    drawTuyau0(pcyl,pcyln,nbLine,4,m,pline);
    drawTuyau(prail1,prail1n,nbLine,nbCote,m,pline1);
    drawTuyau(prail2,prail2n,nbLine,nbCote,m,pline2);
    drawLiens(pliens,pliensn,nbLiens,m,pnliens);
//  poteau_draw();
}

bool
RollerCoaster::DrawGLScene0(const float time)
{
#if 1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
    float dist; /* camera distance from origin */

    float angle = 180.0f + 360.0f*time;     /* angle in degree */
    angle = angle * M_PI_DEG;
    /* compute camera distance from the origin */
    if(maxDist*tan(aperture*M_PI/360.0f)*2.0f < maxZ)
        dist = maxZ / tan(aperture*M_PI/360.0f) / 2.0f;
    else
        dist = 0.5f + maxDist;

    gluLookAt(dist*cos(angle),dist*sin(angle),maxZ,                /* eye position */
              0.0f,0.0f,maxZ+1.0f-dist*tan(aperture*M_PI/360.0f),  /* target       */
              0.0f,0.0f,1.0f);                                     /* up vector    */
#endif

    const double zPos = 2.0;

//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-5,0,zPos,0,0,zPos,0,0,1);
    glRotated(-time*360.0,0,0,1);

    drawEverything();
#else
//  static float angle = 0.0f;
    float dist; /* camera distance from origin */

    float angle = 180.0f + 360.0f*time;     /* angle in degree */
    angle = angle * M_PI_DEG;
    /* compute camera distance from the origin */
    if(maxDist*tan(aperture*M_PI/360.0f)*2.0f < maxZ)
        dist = maxZ / tan(aperture*M_PI/360.0f) / 2.0f;
    else
        dist = 0.5f + maxDist;

    if(stereo)
    {
        float ratio,wd2,ndfl,left,right;
        glDrawBuffer(GL_BACK_RIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        wd2 = near_clip * tan(0.5f * M_PI * aperture / 180.0f);
        ndfl = near_clip / focallength;
        ratio = wndWidth / (float)wndHeight;
        left = -ratio * wd2 - 0.5f * eye_sep * ndfl;
        right = ratio * wd2 - 0.5f * eye_sep * ndfl;
        glFrustum(left,right,-wd2,wd2,near_clip,far_clip); /*left,right,bottom,top,near,far*/
        glMatrixMode(GL_MODELVIEW);
        glDrawBuffer(GL_BACK_RIGHT);
        glLoadIdentity();
        gluLookAt(dist*cos(angle)-0.5f*eye_sep*sin(angle),            /* x eye coord   */
                  dist*sin(angle)+0.5f*eye_sep*cos(angle),            /* y eye coord   */
                  maxZ,                                               /* z eye coord   */
                  0.0f,0.0f,maxZ+1.0f-dist*tan(aperture*M_PI/360.0f), /* target coords */
                  0.0f,0.0f,1.0f);                                    /* up vector     */
        drawEverything();

        glDrawBuffer(GL_BACK_LEFT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        left = -ratio * wd2 + 0.5f * eye_sep * ndfl;
        right = ratio * wd2 + 0.5f * eye_sep * ndfl;
        glFrustum(left,right,-wd2,wd2,near_clip,far_clip); /*left,right,bottom,top,near,far*/
        glMatrixMode(GL_MODELVIEW);
        glDrawBuffer(GL_BACK_LEFT);
        glLoadIdentity();
        gluLookAt(dist*cos(angle)+0.5f*eye_sep*sin(angle),            /* x eye coord   */
                  dist*sin(angle)-0.5f*eye_sep*cos(angle),            /* y eye coord   */
                  maxZ,                                               /* z eye coord   */
                  0.0f,0.0f,maxZ+1.0f-dist*tan(aperture*M_PI/360.0f), /* target coords */
                  0.0f,0.0f,1.0f);                                    /* up vector     */
        drawEverything();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /* glMatrixMode(GL_MODELVIEW); */
        glLoadIdentity();
        gluLookAt(dist*cos(angle),dist*sin(angle),maxZ,                /* eye position */
                  0.0f,0.0f,maxZ+1.0f-dist*tan(aperture*M_PI/360.0f),  /* target       */
                  0.0f,0.0f,1.0f);                                     /* up vector    */
        drawEverything();
    }
#endif

    return time>=1.0f;
}


bool
RollerCoaster::DrawGLScene(const float time)
{
    static int   index = 0;         // Current segment
    static float abscisse = 0.0f;   // Arc length along segment
    static float vitesse = 0.0f;    // Current speed

    static float timePrev = 0.0;    // Previous time
    static float timeStop = 0.0;    // Time that trolley stopped

    static bool reset = true;       // Used to trigger restart
    static bool starting = true;    // While starting, trolley gets pulled at constant speed
    static bool stopping = false;   // While stopping, break is applied
    static bool stopped  = true;    // Has the trolley already stopped?

    if (reset)
    {
        reset = false;
        starting = true;
        stopping = false;
        stopped  = false;
        index = 0;
        abscisse = 0.0;
        vitesse = 0.0;
        timePrev = 0.0;
    }

    //

    static float oldz;

    point ddv,ddv1,ddv2;

    // Advance along the line segments

    while (abscisse > pnorme[(index+1)%nbLine])
    {
        abscisse -= pnorme[(index+1)%nbLine];
        index++;
        index %= nbLine;
    }

    float t;    // Fraction along current segment
    t = abscisse / pnorme[(index+1)%nbLine];

    point position, eye;
    position = pline[index];

    point p;
    sub(&p,&pline[(index+1)%nbLine],&pline[index]);
    add_mult(&position,t,&p);
    ddv1 = ptraj[index];
    sub(&p,&ptraj[(index+1)%nbLine],&ptraj[index]);
    add_mult(&ddv1,t,&p);
    normalize(&ddv1);                /**** ddv1 vector points upward ****/
    ddv = ptang[index];
    sub(&p,&ptang[(index+1)%nbLine],&ptang[index]);
    add_mult(&ddv,t,&p);
    normalize(&ddv);                 /**** ddv vector points forward ****/
    p = ddv1;
    rotate(&ddv1, &ddv, pcourbure[index]+t*(pcourbure[(index+1)%nbLine]-pcourbure[index]), &p);
    prod_vect(&ddv2,&ddv,&ddv1);     /**** ddv2 vector points rightward ****/
    /* compute camera position */
    mult(&eye,0.2f,&ddv1);
    add(&eye,&eye,&position);

    if (stereo)
    {
        float ratio,wd2,ndfl,left,right;
        glDrawBuffer(GL_BACK_RIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        wd2 = near_clip * tan(0.5f * M_PI * aperture / 180.0f);
        ndfl = near_clip / focallength;
        ratio = wndWidth / (float)wndHeight;
        left = -ratio * wd2 - 0.5f * eye_sep * ndfl;
        right = ratio * wd2 - 0.5f * eye_sep * ndfl;
        glFrustum(left,right,-wd2,wd2,near_clip,far_clip); /*left,right,bottom,top,near,far*/
        glMatrixMode(GL_MODELVIEW);
        glDrawBuffer(GL_BACK_RIGHT);
        glLoadIdentity();
        gluLookAt(eye.x+0.5f*eye_sep*ddv2.x,
                  eye.y+0.5f*eye_sep*ddv2.y,
                  eye.z+0.5f*eye_sep*ddv2.y,
                  eye.x+ddv.x+0.5f*eye_sep*ddv2.x,
                  eye.y+ddv.y+0.5f*eye_sep*ddv2.y,
                  eye.z+ddv.z+0.5f*eye_sep*ddv2.z,
                  ddv1.x, ddv1.y, ddv1.z);
        drawEverything();

        glDrawBuffer(GL_BACK_LEFT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        left = -ratio * wd2 + 0.5f * eye_sep * ndfl;
        right = ratio * wd2 + 0.5f * eye_sep * ndfl;
        glFrustum(left,right,-wd2,wd2,near_clip,far_clip); /*left,right,bottom,top,near,far*/
        glMatrixMode(GL_MODELVIEW);
        glDrawBuffer(GL_BACK_LEFT);
        glLoadIdentity();
        gluLookAt(eye.x-0.5f*eye_sep*ddv2.x,
                  eye.y-0.5f*eye_sep*ddv2.y,
                  eye.z-0.5f*eye_sep*ddv2.y,
                  eye.x+ddv.x-0.5f*eye_sep*ddv2.x,
                  eye.y+ddv.y-0.5f*eye_sep*ddv2.y,
                  eye.z+ddv.z-0.5f*eye_sep*ddv2.z,
                  ddv1.x, ddv1.y, ddv1.z);
        drawEverything();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z,                   /* eye position */
                  eye.x+ddv.x, eye.y+ddv.y, eye.z+ddv.z, /* target       */
                  ddv1.x, ddv1.y, ddv1.z);               /* up vector    */
        drawEverything();
    }

    if(starting)
    {
        //
        // While starting, trolley gets pulled at constant speed.
        // Once trolley starts going downhill, starting mode is
        // disabled.
        //

        if (oldz>position.z)
            starting = false;
        else
            vitesse = 0.3f;
    }
    else
    {
        if (stopping || index>=brakeSegment)
        {
            stopping = true;

            if (vitesse > 0.0f)
            {
                // Apply decelleration
                vitesse = vitesse*vitesse - 5.6f * (time - timePrev);

                if(vitesse <= 0.0f)
                {
                    vitesse = 0.0f;
                    stopped = true;
                    timeStop = time;
                }
                else
                    vitesse = sqrt(vitesse);
            }
            else
            {
                if (time-timeStop>4.0)
                    return true;
            }
        }
        else
        {
            vitesse = vitesse*vitesse + 3.0f*(oldz-position.z);

            if (vitesse <= 0.0f)
                vitesse = 0.0f;
            else
                vitesse = sqrt(vitesse);
        }
    }

    abscisse += vitesse * (time - timePrev);

    oldz = position.z;
    timePrev = time;

    return stopped;
}


int
RollerCoaster::InitializeRoller(int width, int height, int stereoscopic, float viewAngle, float eyeDist, float focalLength)
{
    point light_dir={1.0f,-0.5f,2.0f};
    stereo = stereoscopic;
    aperture = viewAngle;
    eye_sep = eyeDist;
    focallength = focalLength;
    InitCurve(averageSegmentLength);
    if(startSegment < 0) startSegment = nbLine + startSegment;
    if(brakeSegment < 0) brakeSegment = nbLine + brakeSegment;
    InitLines();
    InitLiens(0.3f);
    InitNormales();
    InitCouleurs(&light_dir);
    if(!poteau_init(pline,nbLine,ptang)) return 0;
    return 1;
}


void
RollerCoaster::ChangeRollerParameters(float viewAngle, float eyeDist, float focalLength)
{
    if(aperture != viewAngle && !stereo)
    {
        aperture = viewAngle;
//      ReSizeGLScene(wndWidth,wndHeight);
    }
    aperture = viewAngle;
    eye_sep = eyeDist;
    focallength = focalLength;
}


