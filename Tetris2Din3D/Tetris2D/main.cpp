#include "MainMenu.h"
#include "Game.h"
#include "Difficulty.h"
#include <stdlib.h>
#include <glut.h>
#include <gl\GL.h>

#define WIDTH  800 // Lunghezza finestra
#define HEIGHT  600 // altezza finestra

irrklang::ISoundEngine* enginemain ; // Oggetto per la gestione dell'audio
/*
Attributi della classe: bool
*/ 
bool stereomain = false; 
char a;
/*
Attributi della classe: oggetti principali MainMenu, Game e Difficulty
*/ 

MainMenu* mainMenu;
Game* tetris;
Difficulty* dif;

/*
Summary: Metodo che inizializza gli oggetti e carica le texture
Return: void
*/
void init()
{                             //necessaria per evitare il caricamento delle texture ogni volta che si invoca draw: evita rallentamenti inutili
	do
	{
	  cout<< " AUDIO ATTIVO? [s = SI] [n = NO] "<<endl;
	  cin>>a;
	  if(a == 's' || a == 'n')
		  break;
	  else
		  cout<<"ERRORE DI INSERIMENTO "<<endl;

	}while(true);

	if(a == 's')
		enginemain = irrklang::createIrrKlangDevice();   

	mainMenu = new MainMenu(WIDTH,HEIGHT,a);
	tetris = new  Game(WIDTH,HEIGHT,stereomain);
	dif = new Difficulty(1);
	mainMenu->initTexture();
	tetris->initTexture();
	
}
/*
Summary: Metodo che disegna il tutto
Return: void
*/
void draw()
{
	if(!mainMenu->isNewGame()){	
		mainMenu->reshape(WIDTH,HEIGHT);
		mainMenu->draw();
	}

	if(mainMenu->isNewGame()){
		tetris->setPenalityOptions(mainMenu->getTempo(),mainMenu->getPointsPen(),mainMenu->getKeyPen());   //da mettere in una initgame da eseguire un'unica volta se possibile
		dif->setDifficulty(mainMenu->getDiff());
		tetris->setDifficulty(dif);
		tetris->draw();
	}
}
/*
Summary: Metodo che gestisce la tastiera del mouse
Return: void
*/
void keyboard(int c, int w, int h)
{
	if(mainMenu->isNewGame())
		tetris->keyFunc(c,w,h);

	if(c == GLUT_KEY_F1)
		exit(0);


}
/*
Summary: Metodo che gestisce il click del mouse
Return: void
*/
void mouseClick(int button, int state, int x, int y)
{
	if(!mainMenu->isNewGame())
	{
		mainMenu->onMouseClick(button,state,x,y);
		
	}
	else
	  if(a == 's')
		 enginemain->play2D("song.mp3",true);
	if(tetris->mouseClickFunc(button,state,x,y))
	{
		if(a == 's')
		 enginemain->stopAllSounds();
		mainMenu->setMain(true);	
		mainMenu->reset();
		tetris->reset();
	}
}
/*
Summary: Metodo che gestisce il movimento del mouse
Return: void
*/
void mouseMove(int x,int y)
{
	if(!mainMenu->isNewGame())
		mainMenu->onMouseMove(x,y);

	if(mainMenu->isNewGame())
		tetris->mouseMoveFunc(x,y);

}
/*
Summary: Metodo che ridisegna il tutto
Return: void
*/
void reshape(int w,int h){
	mainMenu->reshape(w,h);
}
/*
Summary: Metodo che gestisce l'esecuzione del codice richiamato ogni tot ms
Return: void
*/
void timerFunc(int value)
{

	if(mainMenu->isNewGame()){
		tetris->timerFunction();
		glutTimerFunc(dif->getTime(),timerFunc,0);
		glutPostRedisplay();
	}
	else{
		mainMenu->animFunc();
		glutTimerFunc(150,timerFunc,0);
		glutPostRedisplay();
	}

}
/*
Summary: Metodo principale main
Return: stato del programma alla fine della sua esecuzione
*/
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	if(stereomain)
		glutInitDisplayMode(GLUT_RGBA| GLUT_ALPHA | GLUT_DOUBLE | GLUT_STEREO);
	else
		glutInitDisplayMode(GLUT_RGBA| GLUT_ALPHA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH ,HEIGHT);
	glutCreateWindow("TETRIS 2D");
	init();
	glutDisplayFunc(draw); 
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutMouseFunc(&mouseClick);
	glutPassiveMotionFunc(&mouseMove);
	glutTimerFunc(500,timerFunc,0);
	glutMainLoop();
	return(0);
}