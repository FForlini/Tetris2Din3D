#include "Viewport.h"
#include "Game.h"
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>
#include <string.h>

/*
Attributi della classe: float
*/ 

float xv,len; //Campi della classe: rispettivamente posizione (x) dove creare la viewport e lunghezza della stessa
float yv,he;  //Campi della classe: rispettivamente posizione (y) dove creare la viewport e altezza della stessa

/*
Attributi della classe: GLuint
*/ 
GLuint livello,pezzo,punteggio,righe; //Variabili per le texture


/*
Summary: Costruttore: setta posizione (x,y) e dimensioni della viewport da creare (viene creata effettivamente dalla primitiva glViewport)
Return: 
*/
Viewport::Viewport(float x,float y,float w,float h)   
{
	xv = x;
	yv = y;
	len = w;
	he = h;
}

/*
Summary: Metodo per il caricamento effettivo della texture
Return: La variabile che contiene la texture
*/
GLuint Viewport::loadTexture(string Filename){               

	GLuint tex_ID = 0;

	tex_ID = SOIL_load_OGL_texture(
		Filename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_MULTIPLY_ALPHA
		| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		| SOIL_FLAG_INVERT_Y
		);

	if( tex_ID > 0 )
	{		
		return tex_ID;
	}
	else
		return 0;
}
/*
Summary: Metodo per l'assegnamento delle immagini alle variabili "texture"
Return: void
*/
void Viewport::initTexture(bool pez){                         

	if(pez)
	{
		pezzo = loadTexture("pezzo.png");
		cout<<"LOADING TEXTURE 35% "<<endl;
	}
	else
	{
		livello = loadTexture("livello.png");   
		cout<<"LOADING TEXTURE 40% "<<endl;
		punteggio = loadTexture("punteggio.png");
		cout<<"LOADING TEXTURE 45% "<<endl;
		righe = loadTexture("righe.png");	
		cout<<"LOADING TEXTURE 50% "<<endl;
	}
}


/*
Summary: Distruttore virtuale
Return: 
*/
Viewport::~Viewport(void)
{
}
/*
Summary: Metodo per aggiornare i campi dell'oggetto una volta che è stato creato
Return: void
*/
void Viewport::setViewportSize(int x,int y,int w,int h)     
{
	xv=x;
	yv=y;
	len=w;
	he=h;
}
/*
Summary: Metodo per il disegno di texture in posizione (x,y) e di dimensioni (a,b)
Return: void
*/
void Viewport::texturize(GLuint g,float x,float y,float a,float b){    

	glEnable(GL_TEXTURE_2D);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D,g);                                  //binding della texture alla generica variabile "texture"

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
Summary: Metodo per disegnare la viewport contenente il pezzo successivo
Return: void
*/
void Viewport::drawVP()                                               
{
	glViewport(xv,yv,len,he);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.f,100.f,-100.*he/len,100.*he/len);
	texturize(pezzo,-100,30,190,20);
}
/*
Summary: Metodo per disegnare la viewport contenente il punteggio e le statistiche utente
Return: void
*/
void Viewport::drawVS()                                              
{
	glViewport(xv,yv,len,he);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.f,100.f,-100.*he/len,100.*he/len);	
	texturize(livello,-100,35,90,20);
	texturize(punteggio,-100,-5,140,20);
	texturize(righe,-100,-45,70,20);
}

