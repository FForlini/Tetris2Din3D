#include "Tetramino.h"

/*
Attributi della classe: int
*/ 
int** matrix; // La matrice del tetramino
int** aux; // Matrice ausiliaria per la rotazione dei tetramini
int tetra; // il tipo di tetramino
int post; // La posizione del tetramino (Riferita alla rotazione
int nDown; // Il numero di volte che il tetramino scende

/*
Summary: Costruttore della classe
Return:
*/
Tetramino::Tetramino(int tetra)
{
	this->tetra = tetra;
	matrix = new int*[18];
	aux = new int*[18];
	setMatrixToZero();
	setAuxToZero();
	nDown = 0;
	post=1;
	setInitPos(tetra,1);
}
/*
Summary: Metodo che setta la posizione iniziale di ogni tetramino
Return: void
*/
void Tetramino::setInitPos(int tetra,int i)
{

	switch(tetra)
	{
	case 1: matrix[i][3] = 1;
		matrix[i][4] = 1;
		matrix[i][5] = 1;
		matrix[i][6] = 1;
		break;
	case 2: matrix[i-1][3] = 2;
		matrix[i][3] = 2;
		matrix[i][4] = 2;
		matrix[i][5] = 2;
		break;
	case 3: matrix[i][3] = 3;
		matrix[i][4] = 3;
		matrix[i][5] = 3;
		matrix[i-1][5] = 3;
		break;
	case 4:   matrix[i-1][3] = 4;
		matrix[i-1][4] = 4;
		matrix[i][3] = 4;
		matrix[i][4] = 4;
		break;
	case 5: matrix[i][3] = 5;
		matrix[i][4] = 5;
		matrix[i-1][4] = 5;
		matrix[i-1][5] = 5;
		break;
	case 6: matrix[i][3] = 6;
		matrix[i][4] = 6;
		matrix[i][5] = 6;
		matrix[i-1][4] = 6;
		break;
	case 7: matrix[i-1][3] = 7;
		matrix[i-1][4] = 7;
		matrix[i][4] = 7;
		matrix[i][5] = 7;
		break;
	}
}

/*
Summary: Distruttore virtuale
Return: 
*/
Tetramino::~Tetramino(void)
{
}

/*
Summary: Metodo che setta le matrici a 0
Return: void
*/
void Tetramino::setMatrixToZero(){

	for(int i=0;i<18;i++)
		matrix[i] =  new int[10];

	for(int i=0;i<18;i++)
		for(int j=0;j<10;j++)
			matrix[i][j] = 0;
}

/*
Summary: Metodo che la matrice ausiliaria a 0
Return: void
*/
void Tetramino::setAuxToZero(){

	for(int i=0;i<18;i++)
		aux[i] =  new int[10];

	for(int i=0;i<18;i++)
		for(int j=0;j<10;j++)
			aux[i][j] = 0;
}
/*
Summary: Metodo che ritorna la matrice del tetramino
Return: La matrice del tetramino
*/
int** Tetramino::getMatrix(){
	return matrix;
}
/*
Summary: Metodo che ruota la posizione del tetramino
Return: void
*/
void Tetramino::rotate() 

{

	setAuxToZero();

	switch(this->tetra){

	case 1:
		if(post==1){		

			for(int i=0;i<18;i++)
				for(int j=0;j<10;j++)
					if(matrix[i][j] != 0){

						setMatrixToZero();

						aux[i-1][j+1] = 1;
						aux[i][j+1] = 1;
						aux[i+1][j+1] = 1;
						aux[i+2][j+1] = 1;						

					}	
					post++;
		}
		else if(post==2){					  

			for(int i=0;i<18;i++)
				for(int j=0;j<10;j++)
					if(matrix[i][j]!=0)
					{

						if(j == 0 || j == 9)                 //collisione bordo sx e dx
							return;

						if(j == 8)
						  j--;

						setMatrixToZero();
						aux[i+1][j-1]=1;
						aux[i+1][j]=1;
						aux[i+1][j+1]=1;
						aux[i+1][j+2]=1;
						post = 1;
					}	

		}

		break;
	case 2:  if(post==1){			

		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				if(matrix[i][j]!=0)
				{
					setMatrixToZero();
					aux[i][j+2]=2;
					aux[i][j+1]=2;
					aux[i+1][j+1]=2;
					aux[i+2][j+1]=2;					
				}	

				post++;							

			 }
			 else if(post==2){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==0)                //collisione bordo sx
								 return;

							 setMatrixToZero();
							 aux[i+1][j+1]=2;
							 aux[i+2][j+1]=2;
							 aux[i+1][j]=2;
							 aux[i+1][j-1]=2;
							 post++;

						 }	
			 }               



			 else if(post==3){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 setMatrixToZero();
							 aux[i+1][j]=2;
							 aux[i+1][j+1]=2;
							 aux[i][j+1]=2;
							 aux[i-1][j+1]=2;
							 post++;

						 }	

			 }
			 else if(post==4){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==9)                 //collisione bordo dx
								 return;

							 setMatrixToZero();
							 aux[i][j-1]=2;
							 aux[i+1][j-1]=2;
							 aux[i+1][j]=2;
							 aux[i+1][j+1]=2;
							 post=1;

						 }	

			 }
			 break;
	case 3:  if(post==1){			

		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				if(matrix[i][j]!=0){

					setMatrixToZero();						
					aux[i][j-1]=3;
					aux[i+1][j-1]=3;
					aux[i+2][j-1]=3;
					aux[i+2][j]=3;						

				}	
				post++;							

			 }
			 else if(post==2){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==0)                 //collisione bordo sx
								 return;

							 setMatrixToZero();
							 aux[i+2][j-1]=3;
							 aux[i+1][j-1]=3;
							 aux[i+1][j]=3;
							 aux[i+1][j+1]=3;
							 post++;

						 }	
			 }               
			 else if(post==3){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 setMatrixToZero();						
							 aux[i-1][j]=3;
							 aux[i-1][j+1]=3;
							 aux[i][j+1]=3;
							 aux[i+1][j+1]=3;
							 post++;

						 }	


			 }
			 else if(post==4){					  



				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==8)                 //collisione bordo dx
								 return;

							 setMatrixToZero();
							 aux[i+1][j]=3;
							 aux[i+1][j+1]=3;
							 aux[i+1][j+2]=3;
							 aux[i][j+2]=3;
							 post=1;

						 }	
			 }

			 break;	
	case 4: 
		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				aux[i][j] = matrix[i][j];
		break;


	case 5:  if(post==1){			

		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				if(matrix[i][j]!=0){

					setMatrixToZero();
					aux[i][j]=5;
					aux[i+1][j]=5;
					aux[i+1][j+1]=5;
					aux[i+2][j+1]=5;						

				}	
				post++;							
			 }

			 else if(post==2){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==0)                  //collisione bordo sx
								 return;


							 setMatrixToZero();
							 aux[i+2][j-1]=5;
							 aux[i+2][j]=5;
							 aux[i+1][j]=5;
							 aux[i+1][j+1]=5;
							 post++;

						 }	
			 }               
			 else if(post==3){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 setMatrixToZero();
							 aux[i-1][j-1]=5;
							 aux[i][j-1]=5;
							 aux[i][j]=5;
							 aux[i+1][j]=5;
							 post++;

						 }	


			 }



			 else if(post==4){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==8)                  //collisione bordo dx
								 return;


							 setMatrixToZero();
							 aux[i+1][j]=5;
							 aux[i+1][j+1]=5;
							 aux[i][j+1]=5;
							 aux[i][j+2]=5;
							 post=1;

						 }	
			 }

			 break;
	case 6:  if(post==1){			

		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				if(matrix[i][j]!=0){

					setMatrixToZero();
					aux[i][j]=6;
					aux[i+1][j]=6;
					aux[i+1][j+1]=6;
					aux[i+2][j]=6;						
				}	
				post++;							

			 }
			 else if(post==2){					  



				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){


							 if(j==0)                  //collisione bordo sx
								 return;

							 setMatrixToZero();
							 aux[i+1][j-1]=6;
							 aux[i+1][j]=6;
							 aux[i+1][j+1]=6;
							 aux[i+2][j]=6;
							 post++;
						 }	
			 }               



			 else if(post==3){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 setMatrixToZero();
							 aux[i][j]=6;
							 aux[i][j+1]=6;
							 aux[i-1][j+1]=6;
							 aux[i+1][j+1]=6;
							 post++;

						 }	
			 }



			 else if(post==4){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==9)                  //collisione bordo sx
								 return;
							 setMatrixToZero();
							 aux[i][j]=6;
							 aux[i+1][j-1]=6;
							 aux[i+1][j]=6;
							 aux[i+1][j+1]=6;
							 post=1;

						 }
			 }

			 break;



	case 7:  if(post==1){			

		for(int i=0;i<18;i++)
			for(int j=0;j<10;j++)
				if(matrix[i][j]!=0){

					setMatrixToZero();						
					aux[i][j+2]=7;
					aux[i+1][j+1]=7;
					aux[i+1][j+2]=7;
					aux[i+2][j+1]=7;						

				}	
				post++;							
			 }



			 else if(post==2){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 if(j==1)                //collisione bordo sx
								 return;

							 setMatrixToZero();
							 aux[i+1][j-2]=7;
							 aux[i+1][j-1]=7;
							 aux[i+2][j-1]=7;
							 aux[i+2][j]=7;
							 post++;

						 }	
			 }               

			 else if(post==3){					  



				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){

							 setMatrixToZero();
							 aux[i][j]=7;
							 aux[i][j+1]=7;
							 aux[i-1][j+1]=7;
							 aux[i+1][j]=7;
							 post++;

						 }	


			 }



			 else if(post==4){					  

				 for(int i=0;i<18;i++)
					 for(int j=0;j<10;j++)
						 if(matrix[i][j]!=0){


							 if(j==9)                 //collisione bordo dx
								 return;

							 setMatrixToZero();
							 aux[i][j]=7;
							 aux[i][j-1]=7;
							 aux[i+1][j]=7;
							 aux[i+1][j+1]=7;
							 post=1;

						 }	
			 }

			 break;

	}

	for(int i=0;i<18;i++)
		for(int j=0;j<10;j++)
			matrix[i][j] = aux[i][j];	

}

/*
Summary: Metodo che trasla verso il basso il tetramino
Return: ritorna true nel caso il pezzo sia bloccato da un altro pezzo oppure è arrivata a fine campo di gioco
*/
bool Tetramino::down()
{
	for(int j=0; j<10; j++)
		if(matrix[17][j] != 0)
		{
			nDown = 0;
			return true;
		}
		for(int i=16;i>=0;i--)
		{
			for(int j=0;j<10;j++)
				if(matrix[i][j] > 0 && matrix[i][j] < 8)
				{
					matrix[i+1][j] = matrix[i][j];
					matrix[i][j] = 0;


				}	
		}	
		nDown++;
		return false;
}

/*
Summary: Metodo che trasla verso sinistra il pezzo
Return: Ritorna true se il pezzo ha colliso contro il muro di sinistra
*/
bool Tetramino::left()
{
	for(int i=0; i<18; i++)
		if(matrix[i][0] != 0)
			return true;

	for(int i=0;i<18;i++)
		for(int j=0;j<10;j++)
			if(matrix[i][j] > 0 && matrix[i][j] < 8)
			{
				matrix[i][j-1] = matrix[i][j];
				matrix[i][j] = 0;
			}
			return false;
}

/*
Summary: Metodo che trasla il pezzo verso destra
Return: Ritorna true se il pezzo ha colliso contro il muro di destra
*/
bool Tetramino::right()
{
	for(int i=0; i<18; i++)
		if(matrix[i][9] != 0)
			return true;

	for(int i=0;i<18;i++)
		for(int j=8;j>=0;j--)
			if(matrix[i][j] > 0 && matrix[i][j] < 8)
			{
				matrix[i][j+1] = matrix[i][j];
				matrix[i][j] = 0;
			}
			return false;
}