/************************
Author : Gwenaël Larmet
Mesh.h
*************************/
#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Vector.h"
#include "Polygon.h"
#include "Perlin.h"

#define M_MAX_QUADS 5000

typedef struct
{
	Vector _vertices[4];
} Quad;

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4);

typedef struct
{
	int _nb_quads;
	Quad _quads[M_MAX_QUADS];
	int _is_filled;
} Mesh;

Mesh* M_new();
void M_init(Mesh *M);
void M_print(Mesh *P, char *message);
void Q_print(Quad *Q, char *message);
void Q_draw(Quad *Q);
void Q_set(Quad *q,Vector v1,Vector v2,Vector v3,Vector v4);
void M_addQuad(Mesh *P, Quad q);
void M_addSlice(Mesh *P, Polygon *p1, Polygon *p2);
void M_revolution(Mesh *P, Polygon *p1, int nb_slices);
void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices);
void M_draw(Mesh *P);

#endif
