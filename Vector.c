/**
 * \file Vector.c
 * \brief Vector
 * \author HABIBI Arash
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#include "Vector.h"
#define EPSILON 1e-4


Vector V_new(float x, float y, float z)
{
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vector V_add(Vector v1, Vector v2){
	Vector v=V_new(0.,0.,0.);
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;

	return v;
}

Vector V_substract(Vector v1, Vector v2){
	Vector v=V_new(0.,0.,0.);
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;

	return v;
}

Vector V_multiply(double lambda, Vector v){
	Vector vres=V_new(0.,0.,0.);
	vres.x = v.x*lambda;
	vres.y = v.y*lambda;
	vres.z = v.z*lambda;
	return vres;
}

Vector V_cross(Vector v1, Vector v2){
	Vector v=V_new(0.,0.,0.);
	v.x = v1.y*v2.z - v1.z*v2.y;
	v.y = v1.x*v2.z - v1.z*v2.x;
	v.z = v1.x*v2.y - v1.y*v2.x;
	return v;
}

double V_dot(Vector v1, Vector v2){
	return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

double V_det(Vector a, Vector b, Vector c){
	return a.x*b.y*c.z + b.x*c.y*a.z + c.x*a.y*b.z - a.x*b.z*c.y - c.x*b.y*a.z - b.x*a.z*c.z;
}

int V_isOnTheRight(Vector M, Vector A, Vector B){
	return (V_det(A,B,M)<=0);
}

int zero(double a){
	return a < (0 + EPSILON) && a > (0 - EPSILON);
}

int V_equals(double x, double y){
	return x-y < (0 + EPSILON) && x-y > (0 - EPSILON);
}

float max(float x, float y){
	return (y<x) ? x : y;
}

float min(float x, float y){
	return (x<y) ? x : y;
}

int V_isBetweenPoints(Vector d1, Vector p1, Vector p2){
	return zero(V_det(p1, p2, d1)) &&
		d1.x <= max(p1.x, p2.x) && d1.x >= min(p1.x, p2.x) &&
		d1.y <= max(p1.y, p2.y) && d1.y >= min(p1.y, p2.y) &&
		d1.z <= max(p1.z, p2.z) && d1.z >= min(p1.z, p2.z);
}

int V_segmentsCoplanar(Vector p1, Vector p2, Vector q1, Vector q2)
{
	Vector p1p2 = V_new(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	Vector q1q2 = V_new(q2.x - q1.x, q2.y - q1.y, q2.z - q1.z);
	Vector p1q1 = V_new(q1.x - p1.x, q1.y - p1.y, q1.z - p1.z);

	if(V_equals(V_det(p1p2, q1q2, p1q1), 0.))
		return 1;

	return 0;
}
static inline float det(Vector A, Vector B, Vector M)
{
	return ( A.x * ( B.y - M.y ) - A.y * ( B.x - M.x) + B.x * M.y - B.y *M.x );
}

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2)
{	
	return (det(p1,p2,q1)*det(p1,p2,q2) < 0 && det(q1,q2,p1)*det(q1,q2,p2) < 0);
}



int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2){
	if ( det( V_add( M , u_ray ) , M , p1 ) * det( V_add( M , u_ray ) , M , p2 ) > 0.0)
		return ( det( p1 , p2 , M ) * det( p1 , p2 , V_add( p1 , u_ray ) ) > 0.0);	
	return 0;
}

double V_length(Vector v){
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

Vector V_unit(Vector v){
	Vector vUnit=V_new(v.x/V_length(v),v.y/V_length(v),v.z/V_length(v));
	return vUnit;
}

Vector V_turnAroundY(Vector p, double angle){
	return V_new(p.x*cos(angle) + p.z*sin(angle),
			p.y,
			-p.x*sin(angle) + p.z*cos(angle)
			);
}

Vector V_turnAroundZ(Vector p, double angle){
	return V_new(p.x*cos(angle) - p.y*sin(angle),
			p.x*sin(angle) + p.y*cos(angle),
			p.z
			);
}

Vector V_projectOnPlane(Vector v, Vector normal){
	Vector u_x = V_new (0.0, 0.0, 0.0);
	Vector u_y = V_new (0.0, 0.0, 0.0);
	V_uxUyFromUz(normal, & u_x, & u_y);
	double x = V_decompose (v, u_x);
	double y = V_decompose (v, u_y);

	return V_recompose (x, y, 0.0, u_x, u_y, normal);
}

double V_decompose(Vector p, Vector u){
	return V_dot(p,u) * V_length(u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w){
	return V_add(V_multiply(x,u), V_add(V_multiply(y,v), V_multiply(z,w)));
}

int V_isNull(Vector v){
	return zero(v.x) && zero(v.y) && zero(v.z);
}

void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y){
	if (u_z.x == 0 && u_z.z == 0){
		*u_x = V_new( 0, 0, u_z.y );
		*u_y = V_new( u_z.y, 0, 0 );
	}
	else{
		*u_x = V_multiply(V_length(u_z), V_unit(V_cross( V_new(0,1,0), u_z )) );
		*u_y = V_multiply(V_length(u_z), V_unit(V_cross( u_z, *u_x )) );
	}
}

Vector _V_decompose (Vector v, Vector i, Vector j, Vector k){
	return V_new(V_decompose (v, i),V_decompose (v, j),V_decompose (v, k));
}

Vector _V_recompose (Vector v, Vector i, Vector j, Vector k){
	return V_recompose (v.x, v.y, v.z, i, j, k);
}

Vector V_rotate(Vector p, Vector centre, Vector u, Vector v){
	Vector uu = V_unit(u);
	Vector uv = V_unit(v);
	Vector u_x,u_y,v_x,v_y;
	double x,y,z;
	V_substract( p , centre );
	V_uxUyFromUz( uu, &u_x, &u_y );
	V_uxUyFromUz( uv, &v_x, &v_y );
	x = V_decompose( p, u_x );
	y = V_decompose( p, u_y );
	z = V_decompose( p, uu );
	return V_add( centre, V_recompose( x, y, z, v_x, v_y, uv ));
}


int V_equals2(Vector v1, Vector v2){
	return (v1.x==v2.x && v1.y==v2.y && v1.z==v2.z);
}

//~ //------------------------------------------------
//~ // a des fin de debug
//~ 
void V_print(Vector v, char *message)
{
	fprintf(stderr,"%s : %f %f %f\n",message, v.x,v.y,v.z);
}
