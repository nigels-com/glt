#ifndef _POINT_HEADER
#define _POINT_HEADER

typedef struct{
    float x,y,z;
} point;


extern void mult(point*, float, point*);

extern void add_mult(point*, float, point*);

extern float norme2(point*);

extern float norme(point*);

extern void normalize(point*);

extern void sub(point*, point*, point*);

extern void add(point*, point*, point*);

extern float prod_scal(point*, point*);

extern void prod_vect(point*, point*, point*);

extern void rotate(point*, point*, float, point*);

extern int intersection(point*, point*, point*, point*, point*);

#endif /* _POINT_HEADER */
