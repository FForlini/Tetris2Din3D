#include "Field.h"
#include "Tetramino.h"
#include <time.h>
#include <cstdlib>
/* 
Attributi della classe: int
*/

int nT; // Numero di tetramino creati durante la partita
int** fieldM; // Matrice che gestisce i tetramini nel campo di gioco
int** tempF; // Matrice temporanea del campo di gioco
int** tempT; // Matrice temporanea del etramino
int nR; // Numero di righe completate
int row; // Variabile temporanea che rappresenta l'attuale riga completata
int num,absol; // interi utilizzati per il calcolo del punteggio
int t; // punteggio per ogni riga completata
int** temp; //matrice temporanea per vari utilizzi

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

/*
Summary: Costruttore della classe
Return: 
*/
Field::Field(void)
{
	nT = 0; 
	setMatrixToZero();
	generateTetramino();
	isNext = false;
	rowComplete = false;
	nR = 0;
	num = 0;
	absol = 0;
	row = 0;	
}

/*
Summary: Metodo che setta le matrici utilizzate a 0
Return: void
*/
void Field::setMatrixToZero()
{


	fieldM = new int*[18];
	tempT = new int*[18];
	tempF = new int*[18];
	temp = new int*[18];


	for(int i=0;i<18;i++){
		fieldM[i] =  new int[10];
		tempT[i] = new int[10];
		tempF[i] = new int[10];
		temp[i] = new int[10];
	}

	for(int i=0;i<18;i++)
		for(int j=0;j<10;j++)
		{
			fieldM[i][j] = 0;
			tempT[i][j] = 0;
			tempF[i][j] = 0;
			temp[i][j] = 0;
		}
}
/*
Summary: Distruttore virtuale
Return: 
*/
Field::~Field(void)
{
}

/*
Summary: Metodo per ritorna il tetramino successivo
Return: L'oggetto tretramino
*/
Tetramino* Field::getNext()
{
	return next;
}
/*
Summary: Metodo che genera il nuovo tetramino
Return: void
*/
void Field::generateTetramino()
{
	srand(time(NULL));
	int tetraType;  

	if(nT == 0)
	{
		nT++;
		tetraType = rand() % 7 + 1;
		currTetra = new Tetramino(tetraType);
		fieldM = updateMatrix(fieldM,currTetra->getMatrix(),true);
		tetraType = rand() % 7 + 1; 
		next = new Tetramino(tetraType);
	}
	else
	{
		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				temp[i][j] = fieldM[i][j];

		currTetra = next;
		fieldM = updateMatrix(fieldM,currTetra->getMatrix(),true);
		lost = isLost();
		if(lost)
		{
			for(int i=0;i<18;i++)
				for(int j=0;j<10;j++)
					fieldM[i][j] = temp[i][j];
		}
		else
		{
			tetraType = rand() % 7 + 1; 
			next = new Tetramino(tetraType);
			nT++;
		}
	}

	return;
}

/*
Summary: Metodo che trasla la posizione del tetramino verso sinistra
Return: void
*/
void Field::translateLeft()
{

	tempF = equalM(fieldM); // inserisce il contenuto della matrice del campo in una temporanea tempF

	tempT = currTetra->getMatrix(); // inserisce il contenuto della matrice del tetramino attuale in una temporanea tempT

	tempF = updateMatrix(tempF,tempT,false); // elimina da tempF la posizione precendente...

	currTetra->left();

	tempF = updateMatrix(tempF,currTetra->getMatrix(),true);//...e aggiunge quella attuale

	for(int i=0; i<18; i++) // passa tutti i valori della matrice... 
		for(int j=0; j<10; j++)
			if(tempF[i][j] != currTetra->getMatrix()[i][j] && currTetra->getMatrix()[i][j] != 0 && tempF[i][j] != 0)// ...per controllare se la matrice con il nuovo spostamente è diversa da quella del tetramino solo quando la matrice del tetramino è diversa da zero
			{
				currTetra->right();
				tempF = equalM(fieldM);
				return;
			}


			fieldM = equalM(tempF);
}
/*
Summary:  Metodo che trasla la posizione del tetramino verso destra
Return: void
*/
void Field::translateRight()
{

	tempF = equalM(fieldM); // inserisce il contenuto della matrice del campo in una temporanea tempF

	tempT = currTetra->getMatrix(); // inserisce il contenuto della matrice del tetramino attuale in una temporanea tempT

	tempF = updateMatrix(tempF,tempT,false); // elimina da tempF la posizione precendente...

	currTetra->right();

	tempF = updateMatrix(tempF,currTetra->getMatrix(),true);//...e aggiunge quella attuale


	for(int i=0; i<18; i++) // passa tutti i valori della matrice... 
		for(int j=0; j<10; j++)
			if(tempF[i][j] != currTetra->getMatrix()[i][j] && currTetra->getMatrix()[i][j] != 0 && tempF[i][j] != 0)// ...per controllare se la matrice con il nuovo spostamente è diversa da quella del tetramino solo quando la matrice del tetramino è diversa da zero
			{ 
				currTetra->left();
				tempF = equalM(fieldM);
				return;
			}

			fieldM = equalM(tempF);

}

/*
Summary: Metodo che trasla la posizione del tetramino verso il basso
Return: void
*/
void Field::translateDown()
{

	tempF = equalM(fieldM); // inserisce il contenuto della matrice del campo in una temporanea tempF

	tempT = currTetra->getMatrix(); // inserisce il contenuto della matrice del tetramino attuale in una temporanea tempT

	tempF = updateMatrix(tempF,tempT,false); // elimina da tempF la posizione precendente...

	isNext = currTetra->down(); // richiama il metodo per far scendere il tetramino

	tempF = updateMatrix(tempF,currTetra->getMatrix(),true);//...e aggiunge quella attuale

	for(int i=0; i<18; i++) // passa tutti i valori della matrice... 
		for(int j=0; j<10; j++)
			if(tempF[i][j] != currTetra->getMatrix()[i][j] && currTetra->getMatrix()[i][j] != 0 && tempF[i][j] != 0)// ...per controllare se la matrice con il nuovo spostamente è diversa da quella del tetramino solo quando la matrice del tetramino è diversa da zero
			{
				checkCompleteRows();
				generateTetramino();
				return;
			}

			fieldM = equalM(tempF);

			if(isNext)
			{
				checkCompleteRows();
				generateTetramino();

			}

}
/*
Summary: Metodo che controlla l'eventuale perdita
Return: Boolean che assume il valore true nel caso di perdita altrimenti false
*/
bool Field::isLost(){

	for(int i=0; i<2; i++)
		for(int j=0;j<10;j++)
			if(fieldM[i][j] != 0 && temp[i][j] != 0)
				return true;

	return false;			
}
/*
Summary:  Metodo che controlla l'eventuale vittoria
Return: Boolean che assume il valore true nel caso di vittoria
*/
bool Field::isWon(int nRG)
{
	if(absol == nRG)
		return true;
	return false;
}
/*
Summary: Metodo che controlla le righe completate
Return: void
*/
void Field::checkCompleteRows() 
{

	int l = 0;
	for(int i=0; i<18; i++) {

		if(fieldM[i][0] != 0 && fieldM[i][1] != 0 
			&& fieldM[i][2] != 0 && fieldM[i][3] != 0 
			&& fieldM[i][4] != 0 && fieldM[i][5] != 0 
			&& fieldM[i][6] != 0 && fieldM[i][7] != 0
			&& fieldM[i][8] != 0 && fieldM[i][9] != 0)
		{
			rowComplete = true;
			nR++;
			absol++;			
			row = i;
		}

		if(rowComplete)
		{
			for(int i=row; i>0; i--) 
				for(int j=0; j<10; j++)
				{
					fieldM[i][j] = fieldM[i-1][j];
				}
				rowComplete = false;
		}
	}


}

/*
Summary: Metodo che ruota la posizione del tetramino
Return: void
*/
void Field::rotate()
{
	tempF = equalM(fieldM); // inserisce il contenuto della matrice del campo in una temporanea tempF

	tempT = currTetra->getMatrix(); // inserisce il contenuto della matrice del tetramino attuale in una temporanea tempT

	tempF = updateMatrix(tempF,tempT,false); // elimina da tempF la posizione precendente...

	currTetra->rotate();

	tempF = updateMatrix(tempF,currTetra->getMatrix(),true);//...e aggiunge quella attuale

	for(int i=0; i<18; i++) // passa tutti i valori della matrice... 
		for(int j=0; j<10; j++)
			if(tempF[i][j] != currTetra->getMatrix()[i][j] && currTetra->getMatrix()[i][j] != 0 && tempF[i][j] != 0)// ...per controllare se la matrice con il nuovo spostamente è diversa da quella del tetramino solo quando la matrice del tetramino è diversa da zero
			{
				currTetra->rotate();
				currTetra->rotate();
				currTetra->rotate();
				tempF = equalM(fieldM);
				isNext = false;
				return;
			}

			fieldM = equalM(tempF);
}
/*
Summary: Metodo che aggiorna lo stato delle matrici sommando o sottraendo i valori corrispondenti
Return: La nuova matrice dopo la somma/sottrazione
*/
int** Field::updateMatrix(int**m1,int** m,bool aors)
{

	if(aors) // se somma
		for(int i=0; i< 18;i++)
			for(int j=0;j < 10; j++)
				m1[i][j] += m[i][j];
	else // altrimenti sottrazione
		for(int i=0; i< 18;i++)
			for(int j=0;j < 10; j++)
				m1[i][j] -= m[i][j];
	return m1;
}
/*
Summary: Metodo che ritorna la matrice del campo
Return: La matrice del campo
*/
int** Field::getFieldMatrix()
{
	return fieldM;
}

/*
Summary: Metodo che assegna i valori di una matrice ad un'altra
Return: La matrice modificata
*/
int** Field::equalM(int** m)
{
	int** m1 = new int*[18];

	for(int i=0; i< 18;i++)
		m1[i] = new int[10];

	for(int i=0; i< 18;i++)
		for(int j=0;j < 10; j++)
		{
			m1[i][j] = 0;
			m1[i][j] = m[i][j];
		}
		return m1;
}
/*
Summary: Metodo che ritorna il numero di righe completate
Return: Il valore intero che rappresenta il numero di righe completate
*/
int Field::getRow(){
	if(nR == 10)
	{
		num++;
		nR=0;
	}
	return nR;
}
/*
Summary: Metodo che ritorna i punti attuali del giocatore
Return: Intero che rappresenta i punti attuali
*/
int Field::getPoints(int diffF)
{

	switch (diffF)               //qui setto t per i metodi successivi
	{
	case 1:		
		t=1;
		break;
	case 2:		
		t=3;
		break;
	case 3:		
		t=5;
		break;
	}

	int points = absol*t;
	
	return points % 10;
}
/*
Summary: Metodo che ritorna il punteggio in numero decimale
Return: Intero che rappresenta il numero decimale
*/
int Field::getDec(){
	int dec = absol*t;	
	return dec / 10;
}
/*
Summary: Metodo che
Return: 
*/
int Field::getNum(){
	return num;
}
/*
Summary: Metodo che
Return: 
*/
int Field::getAbsol()
{
	return absol;
}
/* for collisions http://tetris.wikia.com/wiki/ARS */

