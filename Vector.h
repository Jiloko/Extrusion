/************************
Author : Gwenaël Larmet
Vector.h
*************************/
 
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum{
	FALSE,
	TRUE,
};

/**
 * \typedef Vector
 * \brief un Vector
 */
typedef struct
{
	float x, y, z;
} Vector;

/**
 * \brief Crée un nouveau Vector
 * \return un Vector
 */
Vector V_new(float x, float y, float z);

/**
 * \brief a des fins de debugs
 * \param v un vector
 * \param message un message
 */
void V_print(Vector v, char *message);

/**
 * \brief additionne 2 vector
 * \param v1 un vector
 * \param v2 un vector
 * \return un Vector, addition des deux vectors passés en paramètre
 */
Vector V_add(Vector v1, Vector v2);

/**
 * \brief soustrait 2 vector
 * \param v1 un vector
 * \param v2 un vector
 * \return un Vector, soustraction des deux vectors passés en paramètre
 */
Vector V_substract(Vector v1, Vector v2);

/**
 * \brief multiplie un vector par un facteur
 * \param v1 un vector
 * \param lambda un double égal au facteur de multiplication
 * \return un Vector, multiplication de du vector par le facteur de multiplication
 */
Vector V_multiply(double lambda, Vector v);

/**
 * \brief produit vectoriel de 2 vector
 * \param v1 un vector
 * \param v2 un vector
 * \return un Vector, produit vectoriel des deux vectors passés en paramètre
 */
Vector V_cross(Vector v1, Vector v2);

/**
 * \brief produit scalaire 2 vector
 * \param v1 un vector
 * \param v2 un vector
 * \return un Vector, produit scalaire des deux vectors passés en paramètre
 */
double V_dot(Vector v1, Vector v2);

/**
 * \brief Indique si 2 segments sont coplanaires
 * \param p1 un vector
 * \param p2 un vector
 * \param q1 un vector
 * \param q2 un vector
 * \retval 1 si [p1p2] et [q1q2] sont coplanaires, 0 sinon
 */
int V_segmentsCoplanar(Vector p1, Vector p2, Vector q1, Vector q2);

/**
 * \brief regarde si un point est sur un segment
 * \param q1 un vector
 * \param p1 un vector
 * \param p2 un vector
 * \retval 1 si q1 est sur [p1p2], 0 sinon
 */
int V_isBetweenPoints(Vector q1, Vector p1, Vector p2);

/**
 * \brief donne la taille d'un vector
 * \param v un vector
 * \retval la taille du vector
 */
double V_length(Vector v);

/**
 * \brief donne la version unitaire d'un vector
 * \param v un vector
 * \return un vector, égale au vecteur unitaire du vector passé en paramètre
 */
Vector V_unit(Vector v);

/**
 * \brief renvoie la plus petite valeure entre 2 nombres
 */
float min(float x, float y);
/**
 * \brief renvoie la plus grande valeure entre 2 nombres
 */
float max(float x, float y);

/**
 * \brief indique si un point est a droite d'une droite
 * \param M un vector
 * \param A un vector
 * \param B un vector
 * \retval 1 si M est a droite de (AB), 0 sinon
 */
int V_isOnTheRight(Vector M, Vector A, Vector B);

/**
 * \brief indique si deux segments s'intersectent
 * \param p1 un vector
 * \param p2 un vector
 * \param q1 un vector
 * \param q2 un vector
 * \retval 1 si [p1p2] et [q1q2] s'intersectent, 0 sinon
 */
int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2);

/**
 * \brief indique si un rayon intersecte un segment en M
 * \param M un vector
 * \param u_ray un vector
 * \param p1 un vector
 * \param p2 un vector
 * \retval 1 si [uray] et [p1p2] s'intersectent en M, 0 sinon
 */
int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2);

/**
 * \brief tourne autours de l'axe Y
 * \param p un vector
 * \param angle un double
 * \return un vector, égal au vector passé en paramètre qui a tourné autours de Y de angle degres
 */
Vector V_turnAroundY(Vector p, double angle);

/**
 * \brief tourne autours de l'axe Z
 * \param p un vector
 * \param angle un double
 * \return un vector, égal au vector passé en paramètre qui a tourné autours de Z de angle degres
 */
Vector V_turnAroundZ(Vector p, double angle);

/**
 * \brief Projette un vecteur sur un plan
 * \param v un vector
 * \param normal un vector
 * \return un vector égal a v qui à été projeter sur le plan de vecteur normal normal
 */
Vector V_projectOnPlane(Vector v, Vector normal);

/**
 * \brief renvoie le caractère nul d'un vector
 * \param v un vector
 * \retval 1 si v est nul, 0 sinon
 */
int V_isNull(Vector v);

/**
 * \brief voir sujet
 * \param p un vector
 * \param u un vector
 * \return un double egale a la décomposition de p par u
 */
double V_decompose(Vector p, Vector u); 

/**
 * \brief voir sujet
 * \param x un double
 * \param y un double
 * \param z un double
 * \param u un vector
 * \param v un vector
 * \param w un vector
 * \return un vector égal a la recomposition de (xyz) par (uvw)
 */
Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w); 

/**
 * \brief voir sujet
 * \param u_z un vector
 * \param u_x un pointeur sur un vectordragonforce a la flute
 * \param u_y un pointeur sur un vector
 */
void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y); 

/**\brief voir sujet
 * \param p un vector
 * \param centre un vector
 * \param v1 un vector
 * \param v2 un vector
 * \return un vector égale a p qui a tourner autours de centre d'un angle qui modifie v1 en v2
 */
Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2);

/**
 * \brief deux fonctions pour savoir si deux vector sont égaux ou deux double sont égaux
 * \retval 1 si oui, 0 sinon
 */
int V_equals2(Vector v1, Vector v2);
int V_equals(double x, double y);

#endif // __VECTOR_H__
