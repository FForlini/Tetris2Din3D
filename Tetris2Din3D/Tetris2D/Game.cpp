#include "Game.h"
#include "GameMenu.h"
#include "Field.h"
#include "Viewport.h"
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>

/* 
Attributi della classe: int
*/
int WIDTH,HEIGHT; // Le variabili che rappresentano altezza e lunghezza della finestra

/* 
Attributi della classe: float
*/

float side; // La grandezza del lato del tetramino
float alpha; // Il parametro per applicare la penalizzazione e determina la trasparenza del tetramino

/* 
Attributi della classe: Oggetti delle classi
*/

Field* f; // L'oggetto Field 
Viewport* viewNext; // La viewport del pezzo successivo
Viewport* viewScore; // La viewport del punteggio
GameMenu* gMenu; // L'oggetto Menu di gioco
Difficulty* d; // L'oggetto che rappresenta la difficoltà

/* 
Attributi della classe: bool
*/

bool fullscreen; // Boolean per settaggio Fullscreen
bool stereo; // Boolean che permette di eseguire il gioco in 3D Stereo
bool timePen,pointsPen,keyPen,pause; // Boolean per il tipo di penalizzazione
bool pen; // Attiva la penalizzazione
bool glost,won,isInPause; // Booleani che dicono lo stato del gioco rispettivamente: perso, vinto, in pausa

/* 
Attributi della classe: GLuint
*/

GLuint texLose,texWin,punti; // Le texture della vittoria, perdita e punti
GLuint n[10]; // Le texture per il punteggio

/*
Summary: Metodo che viene richiamato ogni tot ms per permettere la traslazione dei pezzi verso il basso
Return: void
*/
void Game::timerFunction() 
{
	if(!pause){
		f->translateDown();
		if(timePen)
			alpha -= 0.01;
		if(pointsPen)
			alpha = 0.8 - (f->getAbsol()*0.05);   //penalizzazione data dal punteggio
		glutPostRedisplay();
	}
}
/*
Summary: Costruttore
Return: 
*/
Game::Game(int w,int h,bool s)                 
{
	WIDTH = w;
	HEIGHT = h;	
	f = new Field();
	viewNext = new Viewport(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
	viewScore = new Viewport(WIDTH/2,0,WIDTH/2,HEIGHT/2);
	stereo = s;
	glost = false;
	won = false;
	gMenu = new GameMenu(WIDTH,HEIGHT);	
	alpha = 0.6;
	side = 10;
	fullscreen = false;
	pause = false;
}
/*
Summary: Metodo che setta il boolean per il tipo di penalizzazione: Tempo, Pungettio e da Tastiera
Return: void
*/
void Game::setPenalityOptions(bool timePen,bool pointsPen,bool keyPen) // metodo che setta i bool che gestiscono le 3 differenti tipologie di penalizzazione: Penalizzazione al passare del tempo, in base ai punti oppure al tasto premuto
{
	this->timePen = timePen;
	this->pointsPen = pointsPen;
	this->keyPen = keyPen;	
}
/*
Summary: Distruttore virtuale
Return: 
*/
Game::~Game(void)                       
{
}
/*
Summary: Metodo che resetta tutti gli attributi delle classe
Return: void
*/
void Game::reset()
{
	f = new Field();
	alpha = 0.6;
	glost = false;
	won = false;
	fullscreen = false;
	gMenu = new GameMenu(WIDTH,HEIGHT);
	timePen = false;
	pointsPen = false;
	keyPen = false;
	d = NULL;
	timePen = false;
	pointsPen = false;
	keyPen = false;
}
/*
Summary: Metodo che disegna il campo di gioco
Return: void 
*/
void Game::drawField(){                             //Draws the game field

	glPushMatrix();

	glBegin(GL_LINES); // AREA DI GIOCO
	glColor3f(0.77,0.88,1);
	if(pause)
		glColor4f(0.1,0.1,0.1,0.2);

	for(int i=0;i<=100;i+=10)
	{
		glVertex2f(-60 + i,90);
		glVertex2f(-60 + i,-90);

	}

	for(int j=0;j<=180;j+=10)
	{
		glVertex2f(-60,-90 + j);
		glVertex2f(40,-90 + j);	
	}

	glEnd(); // AREA DI GIOCO

	glPopMatrix();

}
/*
Summary: Metodo che permette il caricamento della texture
Return: Ritorna il valore che contiene la texture caricata
*/
GLuint Game::loadTexture(std::string Filename){                

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
Summary: Metodo che carica tutte le texture presenti nel gioco
Return: void
*/
void Game::initTexture(){

	viewNext->initTexture(true);	
	viewScore->initTexture(false);
	punti = loadTexture("punteggio.png");
	cout<<"LOADING TEXTURE 55% "<<endl;
	texLose = loadTexture("lose.png");
	cout<<"LOADING TEXTURE 60% "<<endl;
	texWin = loadTexture("win.png");
	cout<<"LOADING TEXTURE 65% "<<endl;
	n[0] = loadTexture("0.png");
	cout<<"LOADING TEXTURE 70% "<<endl;
	n[1] = loadTexture("1.png");
	cout<<"LOADING TEXTURE 75% "<<endl;
	n[2] = loadTexture("2.png");
	cout<<"LOADING TEXTURE 80% "<<endl;
	n[3] = loadTexture("3.png");
	cout<<"LOADING TEXTURE 85% "<<endl;
	n[4] = loadTexture("4.png");
	cout<<"LOADING TEXTURE 90% "<<endl;
	n[5] = loadTexture("5.png");
	cout<<"LOADING TEXTURE 92% "<<endl;
	n[6] = loadTexture("6.png");
	cout<<"LOADING TEXTURE 96% "<<endl;
	n[7] = loadTexture("7.png");
	cout<<"LOADING TEXTURE 98% "<<endl;
	n[8] = loadTexture("8.png");
	cout<<"LOADING TEXTURE 99% "<<endl;
	n[9] = loadTexture("9.png");
	cout<<"LOADING TEXTURE 100% "<<endl;
}
/*
Summary: Metodo che ritorna la variabile booleana che reppresenta la perdita
Return: La variabile booleana che reppresenta la perdita
*/
bool Game::isLost(){

	return glost;

}
/*
Summary: Metodo che disegna la singola unità del tetramino con il relativo bordo / Nel caso 3D utilizza il canale alpha per aumentare la trasparenza
Return: void
*/
void Game::drawUnit(int** m,bool p){ 

	float r = 0,g = 0,b = 0;
	int x,y;

	glPushMatrix(); 

	for(int i=0; i<18; i++)
		for(int j=0; j<10; j++)
			if(m[i][j] != 0)
			{

				x= j*10 - 60;
				y= 80 - (i*10); 

				m[i][j]==1?(r=0,g=1,b=1):m[i][j]==2?(r=0,g=0,b=0.8):m[i][j] ==3?(r=1,g=0.3,b=0.1):m[i][j]==4?(r=1,g=1,b=0):m[i][j]==5?(r=0,g=1,b=0):m[i][j]==6?(r=1,g=0,b=1):m[i][j]==7?(r=1,g=0,b=0):(r=0,g=0,b=0);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				if(!p)
					glColor3f(r, g, b);
				else
					glColor4f(r,g,b,alpha);
				if(pause)
					glColor4f(0.1,0.1,0.1,0.2);

				glBegin(GL_POLYGON); // DRAW THE QUADS __ the order of the vertex matters
				glVertex2f(x+0.5,y+0.5);
				glVertex2f(x+0.5,y+side-1);
				glVertex2f(x+side-1,y+side-1);
				glVertex2f(x+side-1,y+0.5);   	
				glEnd();

				if(!p)
					glColor3f(1.f,1.f,1.f);
				else
					glColor4f(1.f,1.f,1.f,alpha);

				if(pause)
					glColor4f(0.1,0.1,0.1,0.2);

				glBegin(GL_QUADS); //Draw the Basic unit
				glVertex2f(x,y);
				glVertex2f(x+side,y);
				glVertex2f(x+side,y+side);
				glVertex2f(x,y+side);	
				glEnd(); // Draw the Basic unit

				glDisable(GL_BLEND);

			}	

			glPopMatrix();
}
/*
Summary: Metodo che disegna l'intero gioco
Return: void
*/
void Game::draw()
{
	glost = f->isLost();
	won = f->isWon(d->getCrows());

	if(stereo)
	{				

		if(!glost && !won){

			glDrawBuffer(GL_BACK_LEFT);
			glClear(GL_COLOR_BUFFER_BIT);


			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				glViewport(0,0,2*WIDTH/3,HEIGHT);// creazione viewport di gioco
			else
				glViewport(0,0,8*WIDTH/16,HEIGHT);// creazione viewport di gioco

			glMatrixMode(GL_PROJECTION);// matrice di proiezione e imposta il punto di vista 
			glLoadIdentity();

			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				gluOrtho2D(-100.f,100.f,-100.*HEIGHT/(2*WIDTH/3),100.*HEIGHT/(2*WIDTH/3));
			else
				gluOrtho2D(-100.f,100.f,-100.*(HEIGHT)/(8*WIDTH/16),100.*(HEIGHT)/(8*WIDTH/16));

			glMatrixMode(GL_MODELVIEW);

			drawField();

			glPushMatrix();		
			drawUnit(f->getFieldMatrix(),pen);
			glPopMatrix();

			viewNext->drawVP();

			glPushMatrix();   // pezzo successivo
			glTranslatef(0,-100,0);
			glScalef(1.25,1.25,1.25);
			drawUnit(f->getNext()->getMatrix(),pen);
			glPopMatrix();

			viewScore->drawVS();		
			viewScore->texturize(n[f->getRow()],0,-45,10,20);
			viewScore->texturize(n[f->getNum()],-12,-45,10,20);         

			viewScore->texturize(n[d->getDiffG()],0,35,10,20);

			viewScore->texturize(n[f->getPoints(d->getDiffG())],70,-5,10,20);
			viewScore->texturize(n[f->getDec()],58,-5,10,20);           

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			glDrawBuffer(GL_BACK_RIGHT);
			glClear(GL_COLOR_BUFFER_BIT);

			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				glViewport(0,0,2*WIDTH/3,HEIGHT);// creazione viewport di gioco
			else
				glViewport(0,0,8*WIDTH/16,HEIGHT);// creazione viewport di gioco

			glMatrixMode(GL_PROJECTION);// matrice di proiezione e imposta il punto di vista 
			glLoadIdentity();

			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				gluOrtho2D(-100.f,100.f,-100.*HEIGHT/(2*WIDTH/3),100.*HEIGHT/(2*WIDTH/3));
			else
				gluOrtho2D(-100.f,100.f,-100.*(HEIGHT)/(8*WIDTH/16),100.*(HEIGHT)/(8*WIDTH/16));

			glMatrixMode(GL_MODELVIEW);

			drawField();

			glPushMatrix();		
			drawUnit(f->getFieldMatrix(),!pen);
			glPopMatrix();

			viewNext->drawVP();

			glPushMatrix();   // pezzo successivo
			glTranslatef(0,-100,0);
			glScalef(1.25,1.25,1.25);
			drawUnit(f->getNext()->getMatrix(),!pen);	
			glPopMatrix();

			viewScore->drawVS();		
			viewScore->texturize(n[f->getRow()],0,-45,10,20);
			viewScore->texturize(n[f->getNum()],-12,-45,10,20);           

			viewScore->texturize(n[d->getDiffG()],0,35,10,20);

			viewScore->texturize(n[f->getPoints(d->getDiffG())],70,-5,10,20);
			viewScore->texturize(n[f->getDec()],58,-5,10,20);           

		}
		else
		{
			glDrawBuffer(GL_BACK);
			if(glost)
				gMenu->draw(texLose,false,f->getRow()-48);           
			else
				gMenu->draw(texWin,false,f->getRow()-48);

			if(fullscreen)
			{
				WIDTH = 800;
				HEIGHT = 600;
				viewNext->setViewportSize(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
				viewScore->setViewportSize(WIDTH/2,0,WIDTH/2,HEIGHT/2);
				glutReshapeWindow(WIDTH, HEIGHT);
				glutPositionWindow(100,100);
				fullscreen = false;
			}
		}

		glutSwapBuffers();
	}//per la penalizzazione dell'occhio importa l'ultimo buffer su cui disegno. es. right-->non vedo con il sx
	else{

		if(!glost && !won)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				glViewport(0,0,2*WIDTH/3,HEIGHT);// creazione viewport di gioco
			else
				glViewport(0,0,8*WIDTH/16,HEIGHT);// creazione viewport di gioco

			glMatrixMode(GL_PROJECTION);// matrice di proiezione e imposta il punto di vista 
			glLoadIdentity();

			if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				gluOrtho2D(-100.f,100.f,-100.*HEIGHT/(2*WIDTH/3),100.*HEIGHT/(2*WIDTH/3));
			else
				gluOrtho2D(-100.f,100.f,-100.*(HEIGHT)/(8*WIDTH/16),100.*(HEIGHT)/(8*WIDTH/16));

			glMatrixMode(GL_MODELVIEW);

			drawField();

			glPushMatrix();		
			drawUnit(f->getFieldMatrix(),false);
			glPopMatrix();

			viewNext->drawVP();

			glPushMatrix();   // pezzo successivo
			glTranslatef(10,-110,0);
			glScalef(1.25,1.25,1.25);
			drawUnit(f->getNext()->getMatrix(),false);		
			glPopMatrix();

			viewScore->drawVS();		
			viewScore->texturize(n[f->getRow()],0,-45,10,20);
			viewScore->texturize(n[f->getNum()],-12,-45,10,20);          

			viewScore->texturize(n[d->getDiffG()],0,35,10,20);
			 
			viewScore->texturize(n[f->getPoints(d->getDiffG())],70,-5,10,20);
			viewScore->texturize(n[f->getDec()],58,-5,10,20);          

			glutSwapBuffers();
		}else
		{
			if(glost)
				gMenu->draw(texLose,false,f->getRow()-48);            
			else
				gMenu->draw(texWin,false,f->getRow()-48);

			if(fullscreen)
			{
				WIDTH = 800;
				HEIGHT = 600;
				viewNext->setViewportSize(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
				viewScore->setViewportSize(WIDTH/2,0,WIDTH/2,HEIGHT/2);
				glutReshapeWindow(WIDTH, HEIGHT);
				glutPositionWindow(100,100);
				fullscreen = false;
			}
		}

	}

}
/*
Summary: Metodo che gestione il movimento del mouse
Return: void
*/
void Game::mouseMoveFunc(int xMouse,int yMouse)
{
	if(glost || won)
	{
		gMenu->onMouseMove(xMouse,yMouse);
	}

} 

/*
Summary: Metodo che gestisce il click del mouse
Return: Ritorna la boolean per entrare nel menu di vittoria/perdita
*/
bool Game::mouseClickFunc(int button,int state,int xMouse,int yMouse)
{

	if(glost || won)
	{
		gMenu->onMouseClick(button,state,xMouse,yMouse);

		return true;

	}	

	return false;
}

/*
Summary: Metodo che gestisce la tastiera
Return: void
*/
void Game::keyFunc(int c,int w,int h)
{
	switch(c)

	{
	case GLUT_KEY_F1: exit(0); break;

	case GLUT_KEY_UP: 
		if(!pause)
			f->rotate();
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT: 
		if(!pause)
			f->translateLeft();
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:  
		if(!pause)
			f->translateRight();
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		if(!pause)
			f->translateDown();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F2: 
		if(!pause)
			if(!fullscreen)
			{

				glutFullScreen(); 
				WIDTH = glutGet(GLUT_SCREEN_WIDTH);
				HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
				if((float)glutGet((GLenum)GLUT_WINDOW_WIDTH) / (float)glutGet((GLenum)GLUT_WINDOW_HEIGHT) < 1.7) // controlla se lo schermo è in 4:3 o in 16:9
				{
					viewNext->setViewportSize(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
					viewScore->setViewportSize(WIDTH/2,0,WIDTH/2,HEIGHT/2);
				}
				else
				{
					viewNext->setViewportSize(3*WIDTH/4,HEIGHT/2,3*WIDTH/8,HEIGHT/2);
					viewScore->setViewportSize(3*WIDTH/4,0,3*WIDTH/4,HEIGHT/2);
				}

				glutPostRedisplay();
				fullscreen = true;
			}else
			{
				WIDTH = 800;
				HEIGHT = 600;
				viewNext->setViewportSize(WIDTH/2,HEIGHT/2,WIDTH/2,HEIGHT/2);
				viewScore->setViewportSize(WIDTH/2,0,WIDTH/2,HEIGHT/2);
				glutReshapeWindow(WIDTH, HEIGHT);
				glutPositionWindow(100,100);
				fullscreen = false;
			}
			break;

	case GLUT_KEY_F3: 
		if(!pause)
			if(keyPen)
			{				
				alpha -= 0.1;
				if(alpha<0)
					alpha=0;			
				glutPostRedisplay();
			}
			break;

	case GLUT_KEY_F10: if(pause)
						   pause = false;
					   else
						   pause = true;
		glutPostRedisplay();
		break;
	}
}
/*
Summary: Metodo che setta la boolean che determina la presenza di penalizzazione
Return: void
*/
void Game::setPen(bool p)
{
	pen = p;
}
/*
Summary: Metodo che setta l'oggetto difficulty 
Return: 
*/
void Game::setDifficulty(Difficulty* le)
{
	d = le;
}
