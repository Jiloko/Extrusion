/************************
Author : Gwenaël Larmet
Vector.h
*************************/
 
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	float x, y, z;
} Vector;

Vector V_new(float x, float y, float z);
void V_print(Vector v, char *message);
Vector V_add(Vector v1, Vector v2);
Vector V_substract(Vector v1, Vector v2);
Vector V_multiply(double lambda, Vector v);
Vector V_cross(Vector v1, Vector v2);
double V_dot(Vector v1, Vector v2);
int V_segmentsCoplanar(Vector p1, Vector p2, Vector q1, Vector q2);
int V_isBetweenPoints(Vector q1, Vector p1, Vector p2);
double V_length(Vector v);
Vector V_unit(Vector v);
float min(float x, float y);
float max(float x, float y);
int V_isOnTheRight(Vector M, Vector A, Vector B);
int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2);
int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2);
Vector V_turnAroundY(Vector p, double angle);
Vector V_turnAroundZ(Vector p, double angle);
Vector V_projectOnPlane(Vector v, Vector normal);
int V_isNull(Vector v);
double V_decompose(Vector p, Vector u); 
Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w); 
void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y); 
Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2);
int V_equals2(Vector v1, Vector v2);
int V_equals(double x, double y);

#endif