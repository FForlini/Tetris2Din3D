#pragma once
class Difficulty
{
private:

// Attributi della classe: int

int diffG; // La difficolt� del gioco: facile (1), medio(2), difficile(3)
int time; // La velocit� con cui cadono i tretamini
int crows; // Il punteggio per vincere
    
public:
	Difficulty(int);
	~Difficulty();
	void setDifficulty(int);
	int getCrows();
	int getTime();
	int getDiffG();
};

