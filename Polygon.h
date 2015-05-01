/************************
Author : Gwenaël Larmet
Polygon.h
*************************/
 
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>


#include "Vector.h"

#define P_MAX_VERTICES 1000

typedef struct
{
	int _nb_vertices;
	Vector _vertices[P_MAX_VERTICES];
	int _is_closed;
	int _is_filled;
	int _is_convex;
} Polygon;

Polygon* P_new();
void P_init(Polygon *p);
void P_copy(Polygon *original, Polygon *copy);
void P_addVertex(Polygon *P, Vector v);
void P_removeLastVertex(Polygon *P);
int P_isIntersectedByARay(Polygon *P, Vector u, Vector v);
float PixelToScreenY(int y);
float PixelToScreenX(int x);
void P_print(Polygon *P, char *message); 
void P_draw(Polygon *P);
int P_isConvex(Polygon *P);
int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M);
int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray);
int P_isInside(Polygon *P, Vector M);
void P_turnAroundY(Polygon *P, double radians);
Vector P_center(Polygon *P);
Vector P_normal(Polygon *P);
void P_scale(Polygon *P, double factor);  
void P_translate(Polygon *P, Vector trans);
void P_rotate(Polygon *P, Vector normal); 

#endif




