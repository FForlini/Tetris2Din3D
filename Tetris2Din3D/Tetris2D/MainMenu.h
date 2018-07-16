#include <string.h> 
#include <iostream>
#include <fstream>                        
#include <glut.h>
#include <Gl/gl.h>
#include <irrKlang.h>
using namespace std;

#pragma once
class MainMenu
{
private:

irrklang::ISoundEngine* engine ; // Oggetto per la gestione dell'audio
/*
Attributi della classe: bool
*/ 

//booleani per la selezione dei bottoni 
GLboolean selected[15];
bool tasto,tempo,punti;
GLboolean newGame, difficulty,second,controls,options,how_to_play,main,settings;                   
GLboolean easy,medium,hard,red;
bool dx;

/*
Attributi della classe: string e ifstream
*/ 

//stringhe per il testo dei bottoni
string version,button1,button2,button3,button4,button5,button6,occhio;              
string button7,button9,button10,button11,button12,button14,keyboard,time,score;
string p1,p12,p2,p3;
ifstream fin;


/*
Attributi della classe: GLuint
*/ 

// texture grafica menu principale
GLuint title,s1,s2,s3,s4; 
GLuint texture[2]; 

/*
Attributi della classe: int
*/ 
int width,height,diff; // Altezza, lunghezza e difficoltà
int xMouse,yMouse; // Le coordinate x e y del mouse

/*
Attributi della classe: float
*/ 
float i; 

public:
	MainMenu(int,int,char);
	virtual ~MainMenu(void);
	GLuint loadTexture(string);
	void initTexture();
	void draw(void);
	void animFunc();
	void texturize(GLuint ,float ,float ,float ,float );
	void drawButton(string, float, float, GLboolean );
	void write(string,void*,float ,float );
	void drawTitle(float x,float y);
	void writeLine(char[],int);
	void drawVersion(float,float );
	void setMouseCoordinates(int,int);
	void onMouseMove(int,int);
	void onMouseClick(int,int,int,int);
	void reshape(int,int);
	GLboolean isNewGame();
	void writeFromFile(char[],int);
	void readFromFile();
	int getDiff();
	bool getPen();
	void setNewGame(bool);
	void setSecond(bool);
	void setMain(bool m);
	bool getTempo();
	bool getPointsPen();
    bool getKeyPen();
	void reset();
};

