#pragma once
#include <string.h> 
#include <iostream>
#include <fstream>                        //necessary for the FUNCTION length()
#include <glut.h>
#include <Gl/gl.h>
#include "Field.h"
#include "GameMenu.h"
#include "Viewport.h"
#include "Difficulty.h"

class Game
{
private:

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

public:
	Game(int,int,bool);
	virtual ~Game(void);
	GLuint loadTexture(std::string Filename);
	void reset();
	void initTexture();
	void draw();
	bool isLost();
	void keyFunc(int,int,int);
	void drawField();
	void drawUnit(int**,bool);
	void timerFunction();
	void setPen(bool);
	void setPenalityOptions(bool,bool,bool);
	void mouseMoveFunc(int,int);
	bool mouseClickFunc(int,int,int,int);
	void setDifficulty(Difficulty*);
};

