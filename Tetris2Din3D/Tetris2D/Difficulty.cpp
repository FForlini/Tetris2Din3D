#include "Difficulty.h"

/*
Attributi della classe: int
*/ 

int diffG; // La difficoltà del gioco: facile (1), medio(2), difficile(3)
int time; // La velocità con cui cadono i tretamini
int crows; // Il punteggio per vincere


/*
  Summary: Costruttore della classe: setta il tempo con cui cadono i pezzi (ms) e il numero di righe da fare per vincere il gioco
  Return:
*/
Difficulty::Difficulty(int d)
{  
  setDifficulty(d);
}
/*
  Summary: Distruttore virtuale
  Return: 
*/
Difficulty::~Difficulty(void)
{
}
/*
  Summary: Metodo per aggiornare i campi dell'oggetto una volta che è stato creato
  Return: void
*/
void Difficulty::setDifficulty(int d){   

	diffG = d;

	switch (d)
	{
	case 1: //liv. 1: 750 ms e 10 righe da completare
		time = 750;
		crows = 10;
		break;

	case 2://liv. 2: 500 ms e 15 righe da completare
		time = 500;
		crows = 15;
		break;

	case 3: //liv. 3: 250 ms e 20 righe da completare
		time = 250;
		crows = 20;
		break;
	}
}

/*
  Summary: Metodo per restituire le righe da completare
  Return: intero del numero di righe da completare
*/
int Difficulty::getCrows()
{            
	return crows;
}
/*
  Summary: Metodo per restituire il tempo con cui cadono i pezzi
  Return: intero che rappresenta il tempo 
*/
int Difficulty::getTime()
{             
    return time;
}
/*
  Summary: Metodo per restituire la difficoltà scelta
  Return: intero che rappresenta la difficoltà
*/
int Difficulty::getDiffG()
{
	return diffG;
}