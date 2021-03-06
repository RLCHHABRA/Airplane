#include <GL/glut.h>
#include "src/SOIL.h"
#include <iostream>

using namespace std;

void *currentfont;
int full = 0;   //defines state of screen (fullscreen or not)
int frames = 50;

GLfloat windowWidth;
GLfloat windowHeight;

GLuint tex_2d;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
//27 is the ASCII value of the ESC key
	case 27:
		exit(0);
		break;

	case 'f':       //full screen
		if (full == 0)
		{
			glutFullScreen();
			full = 1;
		}
		else
		{
			glutReshapeWindow(800, 450);
			glutPositionWindow(320,150);
			full = 0;
		}
	}
}

void setFont(void* font)
{
	currentfont=font;
}

void drawString(float x,float y,float z,char* string)
{
	char* c;
	glRasterPos3f(x,y,z);

	for(c=string; *c!='\0'; c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void RenderScene()
{
//Clears the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	//load .png image
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_2d = SOIL_load_OGL_texture
		 (
			 "res/paper.jpg",
			 SOIL_LOAD_RGBA,
			 SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_NTSC_SAFE_RGB
		 );
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-178.0f, -100.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(178.0f, -100.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(178.0f, 100.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-178.0f, 100.0f);
	glEnd();
        glDisable(GL_TEXTURE_2D);

        setFont(GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3f(0.0,0.0,0.0);
        if(!full)
        {
                drawString(-129.0,65.0,0.0,"PES Institute of Technology");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-90.0,55.0,0.0,"Made By:");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-110.0,45.0,0.0,"Arpith K - 1PE10CS018");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-105.0,35.0,0.0,"Anil S - 1PE10CS015");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(130.0,-50.0,0.0,"Next!");
        }
        else
        {
                drawString(-105.0,65.0,0.0,"PES Institute of Technology");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-80.0,55.0,0.0,"Made By:");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-95.0,45.0,0.0,"Arpith K - 1PE10CS018");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(-92.0,35.0,0.0,"Anil S - 1PE10CS015");
                setFont(GLUT_BITMAP_TIMES_ROMAN_24);
                glColor3f(0.0,0.0,0.0);
                drawString(125.0,-50.0,0.0,"Click Here!");
                setFont(GLUT_BITMAP_HELVETICA_18);
                glColor3f(0.0,0.0,0.0);
                drawString(135.0,-55.0,0.0,"Next!");
        }


	glutSwapBuffers();

}

void SetupRC(void)
{
//Sets the clear color. Again, the values are in RGBA float format
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
	GLfloat aspectRatio;

//Prevents a divide by zero. We wouldn't want that, now, would we.
	if(h == 0)
		h = 1;

//Makes sure that the OpenGL viewport fills the whole screen
	glViewport(0, 0, w, h);

//Resets the coordinate system so that the center of the window is (0,0,0) Cartesian x,y,z style
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//Sets the clipping volume to the dimensions of the window, including depth ^_^
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		windowWidth = 100;
		windowHeight = 100 / aspectRatio;
		glOrtho (-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
	}
	else
	{
		windowWidth = 100 * aspectRatio;
		windowHeight = 100;
		glOrtho (-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
        if(x>620 && y>260 && state==GLUT_UP)
        {
                //go to next page!
                cout<<x<<" "<<y<<endl;
        }
}


//Actually opens the window, initializes all the functions I made, and throws it all into a loop. Hooray!
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,450);
	glutCreateWindow("Splash!");
	glutPositionWindow(320,150);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reshape);
	SetupRC();
	glutMainLoop();
	return 0;
}
