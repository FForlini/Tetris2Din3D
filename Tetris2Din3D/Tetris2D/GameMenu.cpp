#include "GameMenu.h"
#include <iostream>
#include <glut.h>
#include <gl\GL.h>
#include <SOIL.h>

using namespace std;

/*
Attributi della classe: Bool
*/

GLboolean selectedl1,selectedl2; // Booleani per la selezione dei bottoni 
GLboolean retry,continuew,win;   // Booleani per la selezione dei bottoni 

/*
Attributi della classe: Bool
*/
string buttonw1,buttonw2;  // Stringhe per i bottoni

/*
Attributi della classe: Bool
*/
int widthL,heightL; // Altezza e lunghezza della finestra

/*
Attributi della classe: GLuint
*/
GLuint youLose; // texture vincita/perdita

/*
Summary: Costruttore
Return:
*/
GameMenu::GameMenu(int w,int h)
{
	widthL = w;
	heightL = h;
	selectedl1 = false;
	selectedl2 = false;
	retry = false;
	continuew = false;
	win = false;	
	buttonw1 = "Continua";
	buttonw2 ="Esci";
}

/*
Summary: Distruttore virtuale
Return: 
*/
GameMenu::~GameMenu(void)
{
}

/*
Summary: Metodo che scrive le singole parole 
Return: void
*/
void GameMenu::write(string s,void *font ,float x,float y){                  

	glRasterPos2f(x,y);	  
	for(int i=0; i< s.length(); i++){             //scrive il testo
		if(s[i]=='\n')
			glutBitmapCharacter(font, 0);        //se è un terminatore di stringa non scrive nulla
		else
			glutBitmapCharacter(font, (int) s[i]);
	}

}
/*
Summary: Metodo che disegna le texture
Return: void
*/
void GameMenu::texturize(GLuint g,float x,float y,float a,float b){

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D,g);                            //binding della texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	// FRONT
	glTexCoord2f(0,0);
	glVertex2f(x+a,y);
	glTexCoord2f(1,0);
	glVertex2f(x,y);
	glTexCoord2f(1,1);
	glVertex2f(x,y+b);
	glTexCoord2f(0,1);
	glVertex2f(x+a,y+b);	

	glEnd();
	glDisable(GL_TEXTURE_2D);

}

/*
Summary: Metodo che disegna i bottoni nel menu
Return: void
*/
void GameMenu::drawButton(string s,float x,float y,GLboolean selected){        

	if(selected)
		glPolygonMode(GL_FRONT, GL_FILL);      
	else
		glPolygonMode(GL_FRONT, GL_LINE);

	glBegin(GL_QUADS);                          
	glVertex2f(x,y);
	glVertex2f(x+0.5,y);
	glVertex2f(x+0.5,y+0.2);
	glVertex2f(x,y+0.2);
	glEnd();

	if(selected)
		glColor3f(0,0,0);                         

	write(s,GLUT_BITMAP_9_BY_15,x+0.15,y+0.1);

	glColor3f(1.0,0.3,0.1);
}

/*
Summary: Metodo che disegna tutte le componenti del menu
Return: void
*/
void GameMenu::draw(GLuint texture,bool win,int scoreG)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glViewport( 0,0, widthL, heightL );

	texturize(texture,-0.6,0.4,1.2,0.3);

	if(!win){
		drawButton(buttonw1,-0.25,0,selectedl1);
		drawButton(buttonw2,-0.25,-0.4,selectedl2);	
	}
	else{
		drawButton(buttonw1,-0.25,0,selectedl1);
		drawButton(buttonw2,-0.25,-0.4,selectedl2);	
	}

	glutPostRedisplay();
	glColor3f(1.0,0.3,0.1);

	glutSwapBuffers();
}

/*
Summary: Metodo che gestisce il movimento del mouse
Return: void
*/
void GameMenu::onMouseMove(int xMouse,int yMouse){

	float k = 1.0;                               //scale factor

	if(widthL == 800)
		k=1.25; 

	if(xMouse<399*k && xMouse>240*k && yMouse<239*k && yMouse>193*k)         //RETRY
		selectedl1=true;
	else
		selectedl1=false;

	if(xMouse<399*k && xMouse>240*k && yMouse<335*k && yMouse>288*k)         //EXIT
		selectedl2=true;
	else
		selectedl2=false;

	glutPostRedisplay();
}
/*
Summary: Metodo che gestisce il click del mouse
Return: void
*/
bool GameMenu::onMouseClick(int button,int state,int xMouse,int yMouse){

	float k = 1.0;     	//fattore di scala

	if(widthL==800)
		k=1.25;     

	if(xMouse<399*k && xMouse>240*k && yMouse<239*k && yMouse>193*k && state==GLUT_DOWN){         //RETRY
		return true;
	}

	if(xMouse<399*k && xMouse>240*k && yMouse<335*k && yMouse>288*k){         //EXIT
		exit(0);
	}
	glutPostRedisplay();
	return false;

}