#pragma once
class Tetramino
{
private:

/*
Attributi della classe: int
*/ 
int** matrix; // La matrice del tetramino
int** aux; // Matrice ausiliaria per la rotazione dei tetramini
int tetra; // il tipo di tetramino
int post; // La posizione del tetramino (Riferita alla rotazione
int nDown; // Il numero di volte che il tetramino scende


public:
	Tetramino(int);
	~Tetramino(void);
	void setAuxToZero();
	void rotate();
	void setMatrixToZero();
	int** getMatrix();
	bool down();
	bool left();
	bool right();
	void setInitPos(int,int);
};
