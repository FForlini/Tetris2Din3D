#pragma once
#include <iostream>
#include <string.h>
#include<glut.h>

using namespace std;

class Viewport
{
private:

/*
Attributi della classe: float
*/ 

float xv,len; //Campi della classe: rispettivamente posizione (x) dove creare la viewport e lunghezza della stessa
float yv,he;  //Campi della classe: rispettivamente posizione (y) dove creare la viewport e altezza della stessa

/*
Attributi della classe: GLuint
*/ 
GLuint livello,pezzo,punteggio,righe; //Variabili per le texture

public:

	Viewport(float,float,float,float);
	~Viewport(void);
	GLuint loadTexture(string);
	void initTexture(bool);
	void texturize(GLuint,float,float,float,float);
	void drawVP();
	void drawVS();
	void setViewportSize(int,int,int,int);

};
