/************************
Author : Gwenaël Larmet
main.c
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "Vector.h"
#include "Polygon.h"
#include "Mesh.h"

Polygon P ;
Mesh M ;

int draw = 0;
Vector p_aim;
float phi = -20;
float theta = 20;
GLfloat p_light[4];

/* dimensions de la fenetre */
int width = 600;
int height = 600;
int stop_input = 0 ;

//------------------------------------------------------------

void drawRepere()
{
	glColor3d(1,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glEnd();

	glColor3d(0,1,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,1,0);
	glEnd();

	glColor3d(0,0,1);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1);
	glEnd();
}

//------------------------------------------------------------


void dessinerVecteur( Vector p1){
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(p1.x,p1.y,p1.z);
	glEnd() ;
}

void dessinerPoint( Vector p ){
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex3f( p.x , p.y , p.z ) ;
	glEnd();
}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int i;
	for(i=0; i < P._nb_vertices; i++)
		dessinerPoint(P._vertices[i]);

	if( !stop_input )
		glOrtho(-1,1,-1,1,-1,1);
	else {
		gluPerspective( 30, (float)width/height, 1, 100);
		gluLookAt(2,2,4,0,0,0,0,1,0);
		glTranslatef(p_aim.x,p_aim.y,p_aim.z);
		glRotatef(theta,1,0,0);
		glRotatef(phi,0,1,0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if( stop_input )
	{
		M_draw(&M) ;
	}
	else{
		if( P._is_convex )
			glColor3d(0,0,128);
		else glColor3d(128,0,0);
		P_draw( &P );
		glColor3d(128,128,128);
		dessinerPoint( P_center( &P ) ) ;
		dessinerVecteur( P_normal( &P) );
	}

	drawRepere();
	glutSwapBuffers();
}

void initShade()
{
	GLfloat mat_diffuse[] = {1,1,1,1.0};
	GLfloat mat_ambient[] = {0.1,0.1,0.1,0.0};

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, p_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------

void mode_dessin(){
	switch(draw){
		case 0 :
			draw = 1;
			M._is_filled = 0;
			glDisable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
			break;

		case 1 :
			draw = 2;
			M._is_filled = 1;
			initShade();
			break;

		case 2 :
			draw = 0;
			M._is_filled = 1;
			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);
			break;
	}
}

void keyboard(unsigned char keycode, int x, int y)
{
	printf("touche : (code ascii %d)\n",keycode);

	if(keycode=='d') // changer l'affichage
		mode_dessin() ;

	/* touche ECHAP */
	if (keycode==27)
		exit(0);

	glutPostRedisplay();
}

//------------------------------------------------------------

void special(int keycode, int x, int y)
{
	switch(keycode)
	{
		case GLUT_KEY_UP: 
			theta-= 10; 
			break;
		case GLUT_KEY_DOWN: 
			theta+= 10; 
			break;
		case GLUT_KEY_LEFT: 
			phi-= 10; 
			break;
		case GLUT_KEY_RIGHT: 
			phi+= 10;
			break;
		default : fprintf(stderr,"function special : unknown keycode %d\n",keycode); break;
	}
	glutPostRedisplay();
}

//------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
	float x_coord = ((float)x - (float)width/2)/(float)(width/2);
	float y_coord = ((float)height/2 - (float)y)/(float)(height/2) ;
	switch(button){
		case GLUT_LEFT_BUTTON :
			if(state==GLUT_DOWN){
				Vector new_point = V_new( x_coord , y_coord , 0 ) ;
				if( !stop_input && !P_isIntersectedByARay(&P , new_point , P._vertices[P._nb_vertices-1])){
					P_addVertex( &P , new_point ) ;	
					P_isConvex( &P ) ;
				}
			}
			glutPostRedisplay();
			break;

		case GLUT_MIDDLE_BUTTON :
			if(state==GLUT_DOWN)
				stop_input = 1 ;
			glutPostRedisplay();
			break;

		case GLUT_RIGHT_BUTTON :
			if(state==GLUT_DOWN){
				P._is_closed = 1 ;
				M_init( &M ) ;
				M_perlinExtrude( &M , &P , 128 );
				stop_input = 1 ;
				glutPostRedisplay();
				break;
			}
			glutPostRedisplay();
	}
}

/*************************************************************************/
/* Fonction principale */
/*************************************************************************/
int main(int argc, char *argv[])
{	
	P_init( &P ) ;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Transformations matricielles");
	glutDisplayFunc(display);
	p_aim = V_new(0,0,-2.75);

	p_light[0]=2.0;
	p_light[1]=4.0;
	p_light[2]=1.0;

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
