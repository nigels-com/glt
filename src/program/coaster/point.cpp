#include <cmath>
#include "point.h"

void mult(point *r, float t, point *p){
    r->x = t * p->x;
    r->y = t * p->y;
    r->z = t * p->z;
}


void add_mult(point *r, float t, point *p){
    r->x += t * p->x;
    r->y += t * p->y;
    r->z += t * p->z;
}


float norme2(point *p){
    return p->x*p->x + p->y*p->y + p->z*p->z;
}


float norme(point *p){
    return sqrt(p->x*p->x + p->y*p->y + p->z*p->z);
}


void normalize(point *p){
    float n = norme(p);
    if(n == 0.0f) return;
    p->x = p->x / n;
    p->y = p->y / n;
    p->z = p->z / n;
}


void sub(point *r, point *a, point *b){
    r->x = a->x - b->x;
    r->y = a->y - b->y;
    r->z = a->z - b->z;
}


void add(point *r, point *a, point *b){
    r->x = a->x + b->x;
    r->y = a->y + b->y;
    r->z = a->z + b->z;
}


float prod_scal(point *a, point *b){
    return a->x * b->x + a->y * b->y + a->z * b->z;
}


void prod_vect(point *r, point *a, point *b){
    r->x = a->y * b->z - a->z * b->y;
    r->y = a->z * b->x - a->x * b->z;
    r->z = a->x * b->y - a->y * b->x;
}


// faire tourner le point p de l'angle t par rapport a l'axe de direction v
// le vecteur direction v doit etre unitaire
void rotate(point *r, point *v, float t, point *p){
    r->x = ( v->x * v->x + cos(t) * (1.0f - (v->x * v->x)) ) * p->x +
           ( v->x * v->y * (1.0f - cos(t)) - v->z * sin(t) ) * p->y +
           ( v->z * v->x * (1.0f - cos(t)) + v->y * sin(t) ) * p->z;
    r->y = ( v->x * v->y * (1.0f - cos(t)) + v->z * sin(t) ) * p->x +
           ( v->y * v->y + cos(t) * (1.0f - (v->y * v->y)) ) * p->y +
           ( v->y * v->z * (1.0f - cos(t)) - v->x * sin(t) ) * p->z;
    r->z = ( v->z * v->x * (1.0f - cos(t)) - v->y * sin(t) ) * p->x +
           ( v->y * v->z * (1.0f - cos(t)) + v->x * sin(t) ) * p->y +
           ( v->z * v->z + cos(t) * (1.0f - (v->z * v->z)) ) * p->z;
}


// calcul le point d'intersection de la droite passant par a de direction v avec le plan passant par p de normale n
// renvoie 0 si la droite est parallèle au plan
int intersection(point *r, point *a, point *v, point *p, point *n){
    point b;
    float t;
    sub(&b,p,a);
    t = prod_scal(v,n);
    if(t == 0.0f) return 0;
    t = prod_scal(&b,n) / t;
    r->x = a->x + t * v->x;
    r->y = a->y + t * v->y;
    r->z = a->z + t * v->z;
    return 1;
}
