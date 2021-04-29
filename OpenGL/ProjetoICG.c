/* Indrodução a Computacao Grafica
*  Autor: Kelvin Brenand
*  Baseado no projeto "moth" de Robert Doyle.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define ANGLE_STEP 10

GLdouble view_h = 360, view_v = 0;

GLfloat wall_color[] = {1.0, 1.0, 1.0, 1.0};
GLfloat wall_ambient[] = {0.5, 0.5, 0.5, 1.0};
GLfloat floor_color[] = {0.5, 0.5, 1.0, 0.5};
GLfloat column_color[] = {1.0, 0.0, 0.0, 1.0};
GLfloat column_ambient[] = {0.25, 0.0, 0.0, 1.0};

GLfloat panel_color[] = {0.1, 0.1, 1.0, 1.0};
GLfloat panel_ambient[] = {0.01, 0.01, 0.3, 1.0};

GLfloat lamp_ambient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lamp_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lamp_specular[] = {1.0, 1.0, 1.0, 1.0};

GLfloat cube_color[] = {1.0, 1.0, 0.0, 1.0};
GLfloat cube_shiny[] = {99.0};
GLfloat cube_specular[] = {0.9, 0.9, 0.9, 1.0};
GLfloat cube_ambient[] = {0.1, 0.1, 0.1, 1.0};

GLfloat shadow_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat shadow_diffuse[] = {0.0, 0.0, 0.0, 0.3};
GLfloat shadow_shiny[] = {0.0};
GLfloat shadow_specular[] = {0.0, 0.0, 0.0, 1.0};

GLuint ground_shadow_matrix = 16;
GLuint left_wall_shadow_matrix = 17;
GLuint ground = 30;
GLuint left_wall = 40;
GLuint right_wall = 50;
GLuint back_wall = 60;
GLuint ceiling_wall = 70;
GLuint front_wall = 80;
GLuint four_columns = 7;
GLuint panel1 = 303;
GLuint panel2 = 304;

static GLfloat Tx = -0.01;
static GLfloat Ty = -0.01;
static GLfloat Tz = -0.02;

static GLfloat mvt_x = -15.0;
static GLfloat mvt_y = -15.0;
static GLfloat mvt_z = -30.7;

static GLfloat Rx = 0.1;
static GLfloat mvr_d = 150.0;
static GLfloat mvr_x = 1.0;
static GLfloat mvr_y = -1.0;
static GLfloat mvr_z = -1.0;

GLfloat cubeXform[4][4];
GLfloat column1Xform[4][4];  
GLfloat column2Xform[4][4];
GLfloat column3Xform[4][4];
GLfloat four_columnsXform[4][4];

/*static GLint nest[1];*/
static float shadowMat_ground[4][4];
static float shadowMat_left[4][4];
static float shadowMat_back[4][4];
static float shadowMat_column[4][4];
static float shadowMat_right[4][4];

static float shadowMat1_ground[4][4];
static float shadowMat1_left[4][4];
static float shadowMat1_back[4][4];
static float shadowMat1_right[4][4];

static int useDB = 1;

static int tick = -1;
static int moving = 1;

static float light1Pos[4] = {0.0, 1.6, -2.0, 1.0};
static float light1Amb[4] = {1.0, 1.0, 1.0, 1.0};
static float light1Diff[4] = {1.0, 1.0, 1.0, 1.0};
static float light1Spec[4] = {1.0, 1.0, 1.0, 1.0};

static float leftPlane[4] = {1.0, 0.0, 0.0, 4.88}; /* X = -4.88 */
static float rightPlane[4] = {-1.0, 0.0, 0.0, 4.88}; /* X = 4.98 */
static float groundPlane[4] = {0.0, 1.0, 0.0, 1.450}; /* Y = -1.480 */
static float columnPlane[4] = {0.0, 0.0, 1.0, 0.899}; /* Z = -0.899 */
static float backPlane[4] = {0.0, 0.0, 1.0, 8.98}; /* Z = -8.98 */

#define S 0.7071
#define NS 0.382683
#define NC 0.923880


static float oct_vertices[8][3][4] =
{
	{
		{0.0, 0.0, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0},
		{-S, S, 0.0, 1.0}},
		
	{
		{0.0, 0.0, 0.0, 1.0},
		{-S, S, 0.0, 1.0},
		{-1.0, 0.0, 0.0, 1.0}},
	
	{
		{0.0, 0.0, 0.0, 1.0},
		{-1.0, 0.0, 0.0, 1.0},
		{-S, -S, 0.0, 1.0}},
		
	{
		{0.0, 0.0, 0.0, 1.0},
		{-S, -S, 0.0, 1.0},
		{0.0, -1.0, 0.0, 1.0}},
		
	{
		{0.0, 0.0, 0.0, 1.0},
		{0.0, -1.0, 0.0, 1.0},
		{S, -S, 0.0, 1.0}},
		
	{
		
		{0.0, 0.0, 0.0, 1.0},
		{S, -S, 0.0, 1.0},
		{1.0, 0.0, 0.0, 1.0}},
		
	{
		{0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 1.0},
		{S, S, 0.0, 1.0}},
		
	{
		{0.0, 0.0, 0.0, 1.0},
		{S, S, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0}}
};

static float oct_side_vertices[8][4][4] =
{
	{
		{-S, S, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0},
		{0.0, 1.0, -1.0, 1.0},
		{-S, S, -1.0, 1.0}},
		
	{
		{-1.0, 0.0, 0.0, 1.0},
		{-S, S, 0.0, 1.0},
		{-S, S, -1.0, 1.0},
		{-1.0, 0.0, -1.0, 1.0}},
		
	{
		{-S, -S, 0.0, 1.0},
		{-1.0, 0.0, 0.0, 1.0},
		{-1.0, 0.0, -1.0, 1.0},
		{-S, -S, -1.0, 1.0}},
		
	{
		{0.0, -1.0, 0.0, 1.0},
		{-S, -S, 0.0, 1.0},	
		{-S, -S, -1.0, 1.0},
		{0.0, -1.0, -1.0, 1.0}},
		
	{
		{S, -S, 0.0, 1.0},
		{0.0, -1.0, 0.0, 1.0},
		{0.0, -1.0, -1.0, 1.0},
		{S, -S, -1.0, 1.0}},
		
	{
		{1.0, 0.0, 0.0, 1.0},
		{S, -S, 0.0, 1.0},
		{S, -S, -1.0, 1.0},
		{1.0, 0.0, -1.0, 1.0}},
		
	{
		{S, S, 0.0, 1.0},
		{1.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, -1.0, 1.0},
		{S, S, -1.0, 1.0}},
		
	{
		{0.0, 1.0, 0.0, 1.0},
		{S, S, 0.0, 1.0},
		{S, S, -1.0, 1.0},
		{0.0, 1.0, -1.0, 1.0}}		
};			
			
static float oct_side_normals[8][3] =
{
	{-NS, NC, 0.0},
	{-NC, NS, 0.0},
	{-NC, -NS, 0.0},
	{-NS, -NC, 0.0},		
	{NS, -NC, 0.0},
	{NC, -NS, 0.0},
	{NC, NS, 0.0},
	{NS, NC, 0.0}
		
};

static float cube_vertexes[6][4][4] =
{
  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0}}
};

static float cube_normals[6][4] =
{
  {-1.0, 0.0, 0.0, 0.0},
  {1.0, 0.0, 0.0, 0.0},
  {0.0, -1.0, 0.0, 0.0},
  {0.0, 1.0, 0.0, 0.0},
  {0.0, 0.0, -1.0, 0.0},
  {0.0, 0.0, 1.0, 0.0}
};

/*!!!!!!!!!!!!!!!!!!!!!! ERRORS? !!!!!!!!!!!!!!!!!!!!*/

static void checkErrors(void)
{
  GLenum error;
  while ((error = glGetError()) != GL_NO_ERROR) 
  {
    fprintf(stderr, "Error: %s\n", (char *) gluErrorString(error));
  }
}

/*%%%%%%%%%%%%%%%%%%%% DRAW CUBE %%%%%%%%%%%%%%%%%%*/

static void drawCube(GLfloat color[4], GLfloat ambient[4])
{
  int i;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

  for (i = 0; i < 6; ++i) {
    glNormal3fv(&cube_normals[i][0]);
    glBegin(GL_POLYGON);
    glVertex4fv(&cube_vertexes[i][0][0]);
    glVertex4fv(&cube_vertexes[i][1][0]);
    glVertex4fv(&cube_vertexes[i][2][0]);
    glVertex4fv(&cube_vertexes[i][3][0]);
    glEnd();
  }
}

/*OOOOOOOOOOO DRAW OCTOGON TOP OOOOOOOOOOOOO*/

static void drawOct(void)
{
	int i;

	for (i = 0; i < 8; ++i) 
	{
    glNormal3f(0.0, 0.0, 1.0);
	    glBegin(GL_TRIANGLE_FAN);
	    glVertex4fv(&oct_vertices[i][0][0]);
	    glVertex4fv(&oct_vertices[i][1][0]);
	    glVertex4fv(&oct_vertices[i][2][0]);    
	 glEnd();
	}
}

/*################ DRAW FLOOR ################*/

void drawFloor(GLfloat f_color[4], GLfloat ambient[4])
{    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, f_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    

    glBegin (GL_QUADS);    
	    glVertex3f (-1.0, -1.0, 0.0); 
	    glVertex3f (1.0, -1.0, 0.0);
	    glVertex3f (1.0, 1.0, 0.0);
	    glVertex3f (-1.0, 1.0, 0.0);  
    glEnd();
}

/*||||||||||||||| DRAW GROUND |||||||||||||||||*/

/* Ground coordinates are in drawGround() below. Subdivision */
/* of triangles id done by subDivide(). */

void subDivide(float u1[3], float u2[3], float u3[3], int depth)
{
	GLfloat u12[3];
	GLfloat u23[3];
	GLfloat u31[3];	

	GLint i;

	if(depth == 0)
	{

	    glBegin (GL_POLYGON);    
	    	glNormal3f (0.0, 0.0, 1.0); glVertex3fv(u1);
	    	glNormal3f (0.0, 0.0, 1.0); glVertex3fv(u2);
	    	glNormal3f (0.0, 0.0, 1.0); glVertex3fv(u3);
		glEnd();
	return;
	}

	for(i = 0; i < 3; i++)
	{  
		u12[i] = (u1[i] + u2[i]) / 2.0;
		u23[i] = (u2[i] + u3[i]) / 2.0;
		u31[i] = (u3[i] + u1[i]) / 2.0;	
	} 

	subDivide(u1, u12, u31, depth - 1); 	
	subDivide(u2, u23, u12, depth - 1);
	subDivide(u3, u31, u23, depth - 1);
	subDivide(u12, u23, u31, depth - 1);	
}

void drawGround(void)
{
	/* Use two subdivided triangles for the unscaled 1X1 square. */
	/* Subdivide to this depth: */

	GLint maxdepth = 2;

	/* Coordinates of first triangle: */

	GLfloat u1[] = {-1.0, -1.0, 0.0};
	GLfloat u2[] = {1.0, -1.0, 0.0};
	GLfloat u3[] = {1.0, 1.0, 0.0};		

	/* Coordinates of second triangle: */
	    
	GLfloat v1[] = {-1.0, -1.0, 0.0};    
	GLfloat v2[] = {1.0, 1.0, 0.0};
	GLfloat v3[] = {-1.0, 1.0, 0.0};

	subDivide(u1, u2, u3, maxdepth);
	subDivide(v1, v2, v3, maxdepth);
}

/* Matrix for shadow. From Mark Kilgard's "scube". */

static void myShadowMatrix(float ground[4], float light[4], float shadowMat[4][4])
{
  float dot;

  dot = ground[0] * light[0] +
    ground[1] * light[1] +
    ground[2] * light[2] +
    ground[3] * light[3];

  shadowMat[0][0] = dot - light[0] * ground[0];
  shadowMat[1][0] = 0.0 - light[0] * ground[1];
  shadowMat[2][0] = 0.0 - light[0] * ground[2];
  shadowMat[3][0] = 0.0 - light[0] * ground[3];

  shadowMat[0][1] = 0.0 - light[1] * ground[0];
  shadowMat[1][1] = dot - light[1] * ground[1];
  shadowMat[2][1] = 0.0 - light[1] * ground[2];
  shadowMat[3][1] = 0.0 - light[1] * ground[3];

  shadowMat[0][2] = 0.0 - light[2] * ground[0];
  shadowMat[1][2] = 0.0 - light[2] * ground[1];
  shadowMat[2][2] = dot - light[2] * ground[2];
  shadowMat[3][2] = 0.0 - light[2] * ground[3];

  shadowMat[0][3] = 0.0 - light[3] * ground[0];
  shadowMat[1][3] = 0.0 - light[3] * ground[1];
  shadowMat[2][3] = 0.0 - light[3] * ground[2];
  shadowMat[3][3] = dot - light[3] * ground[3];
}

void idle(void)
{
  tick++;
  if (tick >= 60) {
    tick = 0;
  }
  glutPostRedisplay();
}

/* ARGSUSED1 */
void keyboard(unsigned char ch, int x, int y)
{
  switch (ch) 
  {
	case 27:             /* escape */
		exit(0);
    	break;
	case ' ':
    	if (!moving)
    	{
      		idle();
      		glutPostRedisplay();
    	}
  }
}

void special(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_LEFT:
    if ((view_h -= ANGLE_STEP) <= 0)
      view_h = 360;
    break;
  case GLUT_KEY_RIGHT:
    if ((view_h += ANGLE_STEP) >= 360)
      view_h = 0;
    break;
  case GLUT_KEY_UP:
    if ((view_v += ANGLE_STEP) >= 360)
      view_v = 0;
    break;
  case GLUT_KEY_DOWN:
    if ((view_v -= ANGLE_STEP) <= 0)
      view_v = 360;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}
               
void display(void)
{
  glPushMatrix(); /* Make sure the matrix stack is cleared at the end of this function. */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* Rotate the whole model */
    glRotatef(view_h, 0, 1, 0);
    glRotatef(view_v, 1, 0, 0);

	/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
	glPopMatrix();

	/*______________________ Draw Floor _______________________*/
	  
	glPushMatrix();
	  glCallList(ground);
	glPopMatrix();

	/*_________________________________________________________*/

	/*@@@@@@@@@ Draw Lamp @@@@@@@@@@*/

	glPushMatrix();
	  glCallList(21);
	glPopMatrix(); 

	glPushMatrix();
	  glCallList(22);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCallList(501);
	glDisable(GL_BLEND);
	glPopMatrix(); 

	/*||||||||||||||||||| Draw Left Wall ||||||||||||||||||*/

	glCallList(left_wall); 
    

	/*\\\\\\\\\\\\\\\\ Draw Right Wall \\\\\\\\\\\\\\*/
  
	glCallList(right_wall);


	/*\\\\\\\\\\\\\\\\ Draw Back Wall \\\\\\\\\\\\\\*/
  
  glCallList(back_wall);

  	/*\\\\\\\\\\\\\\\\ Draw Front Wall \\\\\\\\\\\\\\*/
  
  glCallList(front_wall);


	/*\\\\\\\\\\\\\\\\ Draw Ceiling Wall \\\\\\\\\\\\\\*/
  
  glCallList(ceiling_wall);

	/*.........................................................*/

	glutSwapBuffers();

	checkErrors();

	glPopMatrix(); /* Clear the matrix stack */
}

void visible(int state)
{
  if (state == GLUT_VISIBLE) {
    if (moving)
      glutIdleFunc(idle);
  } else {
    if (moving)
      glutIdleFunc(NULL);
  }
}

void myInit(void)
{
	// /*%%%%%%%% Initialize Positional Light and Ambient Light %%%%%%%%*/

	/*** Initial light position is declared in the display function ***/

	   glLightfv(GL_LIGHT1, GL_AMBIENT, light1Amb);
	   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diff);
	   glLightfv(GL_LIGHT1, GL_SPECULAR, light1Spec);
	   glEnable(GL_LIGHT1);
	   
	   glEnable(GL_LIGHTING);	   
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.02); /* try 0.07 w/ 24 bit color */


	/*....Shadow Matrices For Floor, Left Wall, Back Wall, and Right Wall......*/

	   myShadowMatrix(groundPlane, light1Pos, shadowMat1_ground);
	   myShadowMatrix(leftPlane, light1Pos, shadowMat1_left);
	   myShadowMatrix(backPlane, light1Pos, shadowMat1_back);
	   myShadowMatrix(rightPlane, light1Pos, shadowMat1_right);   


	/*========= Make Floor ==============*/ 

  glNewList(ground, GL_COMPILE);
    glPushMatrix();
      	glPushAttrib(GL_LIGHTING_BIT);
      		glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_color);
      		glMaterialfv(GL_FRONT, GL_AMBIENT, shadow_ambient);
      		glTranslatef(0.0, -1.5, -5.0);
      		glRotatef(-90.0, 1, 0, 0);
      		glScalef(10.0, 10.0, 1.0);           
      		drawGround();  /* draw ground */
   		glPopAttrib();
    glPopMatrix();
  glEndList();

	/*===============LAMP===================*/

	 glNewList(22, GL_COMPILE);
      glPushMatrix();
      	glPushAttrib(GL_LIGHTING_BIT); 
			glMaterialfv(GL_FRONT, GL_AMBIENT, lamp_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lamp_diffuse);				
			glMaterialfv(GL_FRONT, GL_SPECULAR, lamp_specular);				
			glTranslatef(0.0, 1.0, -2.0);
   			glutSolidSphere(0.3, 20.0, 20.0);   /* draw lamp */
   		glPopAttrib();
      glPopMatrix();
	 glEndList();

	/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

	/*||||||||||| Make Left Wall |||||||||||||*/

  glNewList(left_wall, GL_COMPILE);
    glPushMatrix();      
    glPushAttrib(GL_LIGHTING_BIT);
      		glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
      		glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
      		glTranslatef(0.0, -1.5, 0.0);
     		glTranslatef(0.0, 1.2, 0.0);      
      		glTranslatef(0.0, 0.0, -5.0);
      		glTranslatef(-5.0, 0.0, 0.0);
      		glRotatef(90.0, 0, 1, 0);
      		glScalef(10.0, 1.2, 1.0);       
      		glNormal3f (0.0, 0.0, 1.0);
      		drawGround();  /* draw left wall */
	glPopAttrib();
    glPopMatrix();
  glEndList();

	/*||||||||||||||||||||||||||||||||||||||||*/

	/*\\\\\\\\\\\\\ Make Right Wall \\\\\\\\\\\\\\\\\\\*/

  glNewList(right_wall, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
      glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
      glTranslatef(0.0, -1.5, 0.0);
      glTranslatef(0.0, 1.2, 0.0);

      glTranslatef(0.0, 0.0, -5.0);
      glTranslatef(5.0, 0.0, 0.0);
      glRotatef(270.0, 0, 1, 0);      
                
      glScalef(10.0, 1.2, 1.0);
      glNormal3f (0.0, 0.0, 1.0);      
      drawGround();  /* draw right wall */
    glPopAttrib();
    glPopMatrix();
  glEndList();      


	/*\\\\\\\\\\\\\ Make Back Wall \\\\\\\\\\\\\\\\\\\*/

  glNewList(back_wall, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
      glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
      glTranslatef(0.0, -1.5, 0.0);
      glTranslatef(0.0, 1.2, 0.0);

      glTranslatef(0.0, 0.0, -10.0);
      glRotatef(0.0, 0, 1, 0);      
                
      glScalef(5.0, 1.2, 1.0);
      glNormal3f (0.0, 0.0, 1.0);
      drawGround();  /* draw back wall */
    glPopAttrib();
    glPopMatrix();
  glEndList();

	/*\\\\\\\\\\\\\ Make Front Wall \\\\\\\\\\\\\\\\\\\*/

  glNewList(front_wall, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
      glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
      glTranslatef(0.0, -1.5, 0.0);
      glTranslatef(0.0, 1.2, 0.0);

      glTranslatef(0.0, 0.0, 5.0);
      glRotatef(180.0, 0, 1, 0);      
                
      glScalef(5.0, 1.2, 0.0);
      glNormal3f (0.0, 0.0, 1.0);
      drawGround();  /* draw front wall */
    glPopAttrib();
    glPopMatrix();
  glEndList();

	/*\\\\\\\\\\\\\ Make Ceiling Wall \\\\\\\\\\\\\\\\\\\*/

  glNewList(ceiling_wall, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
      glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
      glTranslatef(0.0, -1.5, 0.0);
      glTranslatef(0.0, 2.4, 0.0);

      glTranslatef(0.0, 0.0, -5.0);
      glRotatef(90.0, 1, 0, 0);      
                
      glScalef(10.0, 10.0, 10.0);
      glNormal3f (0.0, 0.0, 1.0);      
      drawGround();  /* draw ceiling wall */
    glPopAttrib();
    glPopMatrix();
  glEndList();                     

	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

	/*** Get the modelview matrix once ***/
	       glPushMatrix();
				glRotatef(-mvr_d, mvr_x, mvr_y, mvr_z);
	         		glTranslatef(-mvt_x, -mvt_y, -mvt_z);
	         glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) four_columnsXform);
	       glPopMatrix();

	glNewList(four_columns, GL_COMPILE);
	       glPushMatrix();
				glCallList(4);
				glCallList(5);
				glCallList(6);
				glCallList(17);
	       glPopMatrix();	
	glEndList();
}

/* ############################## MAIN ########################### */
int main(int argc, char **argv)
{
	int width = 700, height = 700;
	int i;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);

    glutCreateWindow("Projeto ICG");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

  myInit();  /* initialize objects in scene */
  glutDisplayFunc(display); 
  glutVisibilityFunc(visible);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-.9, .9, -.9, .9, 1.0, 35.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);      /* double your fun */
  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
	myInit();  /* initialize objects in scene */

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}