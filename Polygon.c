/************************
Author : Gwenaël Larmet
Polygon.c
*************************/
#include "Polygon.h"

void P_init(Polygon *p)
{
	p->_nb_vertices = 0;
	p->_is_closed = 0;
	p->_is_filled = 0;
	p->_is_convex = 0;
}

Polygon* P_new()
{
	Polygon *poly = malloc(sizeof(Polygon));
	poly->_nb_vertices=0;
	poly->_is_closed=0;
	poly->_is_filled=0;
	poly->_is_convex=0;
	return poly;
}

void P_copy(Polygon *original, Polygon *copie)
{
	copie->_nb_vertices=original->_nb_vertices;
	copie->_is_closed=original->_is_closed;
	copie->_is_filled=original->_is_filled;
	copie->_is_convex=original->_is_convex;
	int i;
	for (i=0;i<original->_nb_vertices;i++)
		copie->_vertices[i]=original->_vertices[i];
}

void P_addVertex(Polygon *P,Vector v)
{
	P->_vertices[P->_nb_vertices] = v;
	P->_nb_vertices ++;
}

void P_removeLastVertex(Polygon *P)
{
	if (P->_nb_vertices>0)
		P->_nb_vertices--;
	if (!(V_equals2(P->_vertices[0], P->_vertices[P->_nb_vertices-1])))
		P->_is_closed=0;
	if (P_isConvex(P))
		P->_is_convex=1;
}

float PixelToScreenX(int x)
{
	return ((x/650.)*2)-1;
}

float PixelToScreenY(int y)
{
	return -(((y/650.)*2)-1);
}


void P_draw(Polygon *P)
{
	int i;
	if (P->_is_filled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (P->_nb_vertices<3)
			glBegin(GL_LINES);
		else if (P->_nb_vertices==3)
			glBegin(GL_TRIANGLES);
		else 
			glBegin(GL_POLYGON);

		for (i=0 ; i<P->_nb_vertices ; i++)
			glVertex3f(PixelToScreenX(P->_vertices[i].x),PixelToScreenY(P->_vertices[i].y),0);
		
	}
	else
	{
		if (!(P->_is_closed))
		{
			if (P->_nb_vertices==1)
				glBegin(GL_POINTS);
			else
				glBegin(GL_LINE_STRIP);
			
			for (i=0 ; i<P->_nb_vertices ; i++)
				glVertex3f(PixelToScreenX(P->_vertices[i].x),PixelToScreenY(P->_vertices[i].y),0);
			 
			glEnd();
		}
		else
		{
			if (P->_nb_vertices==1)
				glBegin(GL_POINTS);
			else
				glBegin(GL_LINE_LOOP);
		
			for (i=0 ; i<P->_nb_vertices ; i++)
				glVertex3f(PixelToScreenX(P->_vertices[i].x),PixelToScreenY(P->_vertices[i].y),0);
			
			glEnd();
		}	
	}
}

void P_print(Polygon *P, char *message)
{
	int i;
	fprintf(stderr,"nb_vertices : %d \n\n", P->_nb_vertices);
	for (i=0; i<P->_nb_vertices;i++)
		fprintf(stderr,"x : %f, y : %f, z : %f\n\n", P->_vertices[i].x, P->_vertices[i].y, P->_vertices[i].z);
	fprintf(stderr, "%s\n", message);
}

Vector P_center(Polygon *P)
{
	int i;
	Vector center = V_new (0.0, 0.0, 0.0);

	if (P != NULL && P->_nb_vertices > 0)
	{
		for (i = 0; i < P->_nb_vertices; i++)
			center = V_add (center, P->_vertices[i]);
		center = V_multiply ((float) 1. / P->_nb_vertices, center);
	}

	return center;
}

int P_isConvex(Polygon *P)
{
	int i;
	int isOnRight = V_isOnTheRight(P->_vertices[1], P->_vertices[P->_nb_vertices-1], P->_vertices[0]);

	if(isOnRight)
	{
		for (i = 2;i < P->_nb_vertices && isOnRight;i++)
			isOnRight = V_isOnTheRight(P->_vertices[i], P->_vertices[i-2], P->_vertices[i-1]);	
		isOnRight = isOnRight && V_isOnTheRight(P->_vertices[0], P->_vertices[i-2], P->_vertices[i-1]);
	}
	else
	{
		for (i = 2;i < P->_nb_vertices && !isOnRight;i++)
			isOnRight = V_isOnTheRight( P->_vertices[i], P->_vertices[i-2], P->_vertices[i-1]);
		isOnRight = !isOnRight && !V_isOnTheRight(P->_vertices[0], P->_vertices[i-2], P->_vertices[i-1]);
	}

	P->_is_convex = isOnRight;
	return isOnRight;
}	

int P_close(Polygon *P)
{
	if (!(P->_is_closed))
	{
		if (V_equals2(P->_vertices[0], P->_vertices[P->_nb_vertices]));
		P->_is_closed=1;
	}
	return P->_is_closed;
}

int P_filled(Polygon *P)
{
	return P->_is_filled;
}

int P_isIntersectedByARay(Polygon *P, Vector u, Vector v)
{
	int i;
	int res = 0;
	for (i = 1;(i < P->_nb_vertices) && !res;i++)
		res = V_segmentsIntersect(P->_vertices[i-1], P->_vertices[i], u, v);

	return res;
}

int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M)
{
	int i;
	int res = (P->_nb_vertices > 1);

	for (i = 0;res && i < P->_nb_vertices - 1;i++)
		res = ! (V_isOnTheRight(M, P->_vertices[i], P->_vertices[i + 1]));

	return res;
}

int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray)
{
	int res = 0;
	int i;
	if (P->_nb_vertices > 2)
		for (i = 0; i < P->_nb_vertices - 1; i++)
		{
			if (V_rayIntersectsSegment(M, u_ray, P->_vertices[i], P->_vertices[i + 1]))
				res++;
			if (i == P->_nb_vertices-1)
				res+=V_rayIntersectsSegment(M,u_ray, P->_vertices[i], P->_vertices[0]);
		}
	return res;
}

int P_isInside(Polygon *P, Vector M)
{
	int result = 0;

	Vector h = V_new (1.0, 0.0, 0.0);
	result = (P_nbEdgesIntersectedByRay(P, M, h) % 2) == 1;

	return result;
}
void P_turnAroundY(Polygon *P, double radians)
{
	int i;
	for (i=0; i < P->_nb_vertices; i++)
		V_turnAroundY(P->_vertices[i], radians);
}

Vector P_normal(Polygon *P)
{
	return V_unit(V_cross(V_substract(P->_vertices[1], P->_vertices[0]), V_substract(P->_vertices[2], P->_vertices[0])));
}

void P_scale(Polygon *P, double factor)
{
	int i;
	for (i=0;i<P->_nb_vertices;i++)
		V_multiply(factor,P->_vertices[i]);
}

void P_translate(Polygon *P, Vector trans)
{ 
	int i;
	for (i=0 ; i<P->_nb_vertices; i++)
		P->_vertices[i]=V_add(P->_vertices[i],trans);
}

void P_rotate(Polygon *P, Vector normal)
{
	Vector normal_p = P_normal(P);
	Vector center_p = P_center(P);
	int i;
	for (i = 0; i < P->_nb_vertices; i++)
		V_rotate(P->_vertices[i],center_p,normal_p,normal);
} 
