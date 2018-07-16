#pragma once
#include <iostream>
#include <glut.h>
#include <gl\GL.h>
#include <SOIL.h>

using namespace std;

class GameMenu
{
private:

/*
Attributi della classe: Bool
*/

GLboolean selectedl1,selectedl2; // Booleani per la selezione dei bottoni 
GLboolean retry,continuew,win; // Booleani per la selezione dei bottoni 

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

public:
	GameMenu(int ,int);
	~GameMenu(void);
	void write(string ,void *font ,float ,float );
	void texturize(GLuint g,float,float,float,float);
	void drawButton(string ,float ,float ,GLboolean );    
	void draw(GLuint ,bool ,int );
	void onMouseMove(int ,int );	
    bool onMouseClick(int ,int ,int ,int );
};

