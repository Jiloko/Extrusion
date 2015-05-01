/************************
Author : Gwenaël Larmet
Mesh.c
*************************/
#include "Mesh.h"

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4)
{
	Quad q;
	q._vertices[0]=v1;
	q._vertices[1]=v2;
	q._vertices[2]=v3;
	q._vertices[3]=v4;
	return q;
}

void Q_set(Quad *q,Vector v1,Vector v2,Vector v3,Vector v4)
{
	q->_vertices[0]=v1;
	q->_vertices[1]=v2;
	q->_vertices[2]=v3;
	q->_vertices[3]=v4;
}

void M_AddQuad(Mesh *M, Quad Q)
{
	M->_quads[M->_nb_quads]=Q;
	M->_nb_quads++;
}

void Q_print(Quad *Q, char *message)
{
	int i;
	for (i=0; i<4; i++)
		V_print(Q->_vertices[i], "");
	fprintf(stderr,"%s \n",message);
}

void M_init(Mesh *M)
{
	M->_nb_quads = 0;
	M->_is_filled = 0;
}

void Q_draw(Quad *Q)
{
	int i;
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glBegin (GL_POLYGON);

	for (i = 0; i < 4; ++i)
	{
		double colour = 0.5;
		glColor3d(colour, colour, colour);
		Vector v = Q->_vertices[i];
		glVertex3d(v.x, v.y, v.z);
	}
	glEnd();
}

Mesh* M_new()
{
	Mesh *m = malloc(sizeof(Mesh));
	m->_nb_quads=0;
	m->_is_filled=0;
	return m;
}

void M_print(Mesh *P, char *message)
{
	int i;
	printf("%d", P->_nb_quads);
	for (i=0; i< P->_nb_quads; i++)
	{
		Q_print(&P->_quads[i], "");
	}
	fprintf(stderr,"%s :\n", message);
}

void M_addQuad(Mesh *m, Quad q)
{
	if (m->_nb_quads < M_MAX_QUADS)
	{
		m->_quads[m->_nb_quads]=q;
		m->_nb_quads++;
	}
}

void M_addSlice(Mesh *M, Polygon *P1, Polygon *P2)
{
	int i;
	for (i = 1; i < P1->_nb_vertices ; i++)
		M_addQuad(M, Q_new(P1->_vertices[i - 1], P1->_vertices[i], P2->_vertices[i], P2->_vertices[i-1]));

	M_addQuad(M, Q_new(P1->_vertices[P1->_nb_vertices-1], P1->_vertices[0], P2->_vertices[0], P2->_vertices[P2->_nb_vertices-1]));
}

void M_revolution(Mesh *P, Polygon *p1, int nb_slices)
{
	int i;
	if (P != NULL && p1 != NULL && nb_slices > 0)
	{
		Polygon a, b;
		P_copy (p1, & a);
		P_copy (p1, & b);

		double angle = (double) 2.0 * M_PI / nb_slices;
		for (i = 0; i < nb_slices; i++)
		{
			P_turnAroundY(& b, angle);
			M_addSlice(P, & a, & b);
			P_copy (& b, & a);
		}
	}
}

void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices)
{
	int i;
	Vector noise_p;
	Polygon plg;

	for (i = 0; i < nb_slices; i++)
	{
		noise_p = PRLN_vectorNoise( P_center(p));
		P_copy(p, &plg);
		P_translate(p, noise_p);
		P_rotate(p, noise_p);
		M_addSlice(QM, &plg, p);
	}
}

void M_draw(Mesh *M)
{
	Vector v1, v2, v3, v4;
	int i;
	float color;
	for(i=0;i<M->_nb_quads;i++)
	{
		v1 = M->_quads[i]._vertices[0];
		v2 = M->_quads[i]._vertices[1];
		v3 = M->_quads[i]._vertices[2];
		v4 = M->_quads[i]._vertices[3];

		if(M->_is_filled)	
			glBegin(GL_QUADS);
		else				
			glBegin(GL_LINE_LOOP);

		color=0.99-((float)i/M->_nb_quads);
		if (color==1)
			color = i;
		glColor3f(color, color, color); 

		glVertex3f(v1.x,v1.y,v1.z);
		glVertex3f(v2.x,v2.y,v2.z);
		glVertex3f(v3.x,v3.y,v3.z);
		glVertex3f(v4.x,v4.y,v4.z);
		glEnd();
	}
}