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

/**
 * \typedef Polygon
 * \brief un Polygon
 */
typedef struct
{
	int _nb_vertices;
	Vector _vertices[P_MAX_VERTICES];
	int _is_closed;
	int _is_filled;
	int _is_convex;
} Polygon;

/**
 * \brief crée un nouveau polygon
 * \return un nouveau Polygone
 */
Polygon* P_new();

/**
 * \brief initialise un Polygon
 * \param p un pointeur sur un polygone
 */
void P_init(Polygon *p);

/**
 * \brief copie un polygone dans un autre
 * \param original un pointeur sur un Polygon
 * \param copy un pointeur sur un Polygon
 */
void P_copy(Polygon *original, Polygon *copy);

/**
 * \brief ajoute un vertex dans un Polygon a une certain position
 * \param P un pointeur sur un polygone
 * \param v un vector a ajouter dans P
 * \param pos un entier
 */
void P_addVertex(Polygon *P, Vector v);

/**
 * \brief enkeve le dernier Vertex d'un Polygone
 * \param P un pointeur sur un Polygon
 */
void P_removeLastVertex(Polygon *P);

/**
 * \brief regarde si un polygone est intersecter par un segment
 * \param P un pointeur sur un polygon
 * \param u un vector
 * \param v un vector
 * \retval 1 si le polygone est intersecter, 0 sinon 
 */
int P_isIntersectedByARay(Polygon *P, Vector u, Vector v);

/**
 * \brief renvoie les bonnes coordonnées sur un écran OpenGL
 */
float PixelToScreenY(int y);
float PixelToScreenX(int x);

/**
 * \brief a des fins de debugs 
 * \param P un pointeur sur un Polygon
 * \param message un Message
 */
void P_print(Polygon *P, char *message); 

/**
 * \brief Dessine Un Polygon sur un écran OpenGL
 * \param P un pointeur sur un polygon
 */
void P_draw(Polygon *P);

/**
 * \brief renvoie si un polygone est convexe ou non
 * \param P un pointeur sur un Polygon
 * \retval 1 si P est convexe, 0 sinon
 */
int P_isConvex(Polygon *P);

/**
 * \brief Renvoie si un point est a gauche de tous les Points d'un polygone
 * \param P un Polygon
 * \param M un vector
 * \retval 1 si M est a gauche de tous les points, 0 sinon
 */
int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M);

/**
 * \brief renvoie le nombre de segments intersectés par un rayon
 * \param P un pointeur sur un Polygon
 * \param M un vector
 * \param u_ray un Vector
 * \retval le nombre de segments intersectés par le rayon
 */
int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray);

/**
 * \brief regarde si un point est a l'interieur d'un Polygon
 * \param P un pointeur sur un polygon
 * \param M un vector
 * \retval 1 si M est a l'interieur de P, 0 sinon
 */
int P_isInside(Polygon *P, Vector M);

/**
 * \brief tourne un Polygon autours de l'axe Y de radians degres
 * \param P un pointeur sur un Polygon
 * \param radians un double
 */
void P_turnAroundY(Polygon *P, double radians);

/**
 * \brief renvoie le centre d'un polygone
 * \param P un pointeur sur un Polygon
 * \return le centre de P
 */
Vector P_center(Polygon *P);

/**
 * \brief renvoie le vecteur normal d'un polygone
 * \param P un pointeur sur un Polygon
 * \return le vecteur normal de P
 */
Vector P_normal(Polygon *P);

/**
 * \brief aggrandit un Polygone
 * \param P un pointeur sur un Polygon
 * \param factor un double
 */ 
void P_scale(Polygon *P, double factor); 

/**
 * \brief Translate un Polygone
 * \param P un pointeur sur un Polygon
 * \param trans un Vector
 */ 
void P_translate(Polygon *P, Vector trans);

/**
 * \brief tourne un Polygone
 * \param P un pointeur sur un Polygon
 * \param normal un vector
 */ 
void P_rotate(Polygon *P, Vector normal); 



#endif // _POLYGON_H_
