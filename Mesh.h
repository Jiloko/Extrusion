/**
 * \file Mesh.h
 * \brief Mesh
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

#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <GL/glut.h>
//#include <GL/glx.h>

#include "Vector.h"
#include "Polygon.h"
#include "Perlin.h"

#define M_MAX_QUADS 5000
/**
 * \typedef Quad
 * \brief type Quadrilatère
*/
typedef struct
{
	Vector _vertices[4];
} Quad;

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4);

//--------------------------------------------

/**
 * \typedef Mesh
 * \brief type Maillage
 */
typedef struct
{
	int _nb_quads;
	Quad _quads[M_MAX_QUADS];
	int _is_filled;
	// int _is_smooth;
} Mesh;

/**
 * \brief Création d'un nouveau Maillage
 * \return un Mesh
 */
Mesh* M_new();

/**
 * \brief initialise un Mesh
 * \param M un pointeur sur un Mesh
 */
void M_init(Mesh *M);

/**
 * \brief A des fins de débugs pour un Mesh
 * \param P un pointeur sur un Mesh
 * \param message, un message
 */
void M_print(Mesh *P, char *message);

/**
 * \brief A des fins de débugs pour un Quad
 * \param Q un pointeur sur un Quad
 * \param message, un message
 */
void Q_print(Quad *Q, char *message);

/**
 * \brief Dessine un Quad sur un écran OpenGl
 * \param Q un pointeur sur un Quad
 */
void Q_draw(Quad *Q);

/**
 * \brief met les valeurs d'un quad au nouvelles valeurs
 * \param q un quad
 * \param v1,v2,v3,v4 des vectors
 */
void Q_set(Quad *q,Vector v1,Vector v2,Vector v3,Vector v4);

/**
 * \brief ajoute un quadrilatère à un Mesg
 * \param P un pointeur sur un Mesh
 * \param q un Quad
 */
void M_addQuad(Mesh *P, Quad q);

/**
 * \brief ajoute a un Mesh les quads obtenus en reliant deux a deux les sommets de 2 Polygons
 * \param P un pointeur sur un Mesh
 * \param p1 un pointeur sur un Polygon
 * \param p2 un pointeur sur un Polygon
 */
void M_addSlice(Mesh *P, Polygon *p1, Polygon *p2);

/**
 * \brief Ajoute a un maillage les Quads nécessaires pour réaliser une révolution du mesh autours de l'axe Y
 * \param P un pointeur sur un Mesh
 * \param p1 un pointeur sur un Polygon
 * \param nb_slices un entier correspondant au nombre de tranches
 */
void M_revolution(Mesh *P, Polygon *p1, int nb_slices);

/**
 * \brief Extrusion d'un Mesh par rapport à un bruit de Perlin
 * \param QM un pointeur sur un Mesh
 * \param p un pointeur sur un Polygon
 * \param nb_slices un entier correspondant au nombre de tranches
 */
void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices);

/**
 * \brief Dessine un Mesh sous OpenGL
 * \param P un pointeur sur un Mesh
 */
void M_draw(Mesh *P);

#endif // _MESH_H_
