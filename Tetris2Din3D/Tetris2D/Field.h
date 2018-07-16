#include "Tetramino.h"


using namespace std;

#pragma once
class Field
{

private:
/* 
  Attributi della classe: int
*/

int nT; // Numero di tetramino creati durante la partita
int** fieldM; // Matrice che gestisce i tetramini nel campo di gioco
int** tempF; // Matrice temporanea del campo di gioco
int** tempT; // Matrice temporanea del etramino
int** temp; //matrice temporanea per vari utilizzi
int nR; // Numero di righe completate
int row; // Variabile temporanea che rappresenta l'attuale riga completata
int num,absol; // interi utilizzati per il calcolo del punteggio
int t; // punteggio per ogni riga completata

/* 
  Attributi della classe: Tetramino
*/

Tetramino* currTetra; // Oggetto Tetramino attuale 
Tetramino* next; // Oggetto Tetramino successivo

/* 
  Attributi della classe: bool
*/

bool isNext; // Boolean che identifica quando dovrà essere generato un nuovo tetramino
bool rowComplete; // Boolean che identifica se la riga è completa oppure no
bool lost; // Boolean che identifica lo stato di perdita


public:
	Field(void);
	~Field(void);
	void generateTetramino();
	void setMatrixToZero();
	bool startNext();
	bool isLost();
	bool isWon(int);
	int** updateMatrix(int**,int**,bool);
	void translateLeft();
	void translateRight();
	void translateDown();
	int** getFieldMatrix();
	int** equalM(int** m);
	void printMatrix(int** m);
	void rotate();
	void checkCompleteRows();
	Tetramino* getNext();
	int getRow();
	int getPoints(int);
	int getDec();
	int getNum();
	int getAbsol();
};

