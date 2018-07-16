#include "MainMenu.h"
#include <iostream>
#include <fstream>
#include <string.h>                            
#include <glut.h>
#include <Gl/gl.h>
#include <SOIL.h>
#include <irrKlang.h>

using namespace std;  

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
bool audioON;
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

/*
Summary: Costruttore 
Return:
*/
MainMenu::MainMenu(int w,int h,char audio)
{
	if(audio == 's')
	{
		audioON = true;
		engine = irrklang::createIrrKlangDevice();    
	}
	else 
		audioON = false;
	
	width = w;
	height = h;
	for(int t=0;t<15;t++)
		selected[t]=false;

	newGame = false;
	options = false;
	controls = false;
	how_to_play = false;
	second = false;
	difficulty = false;
	settings = false;
	easy = true;
	medium = false;
	hard = false;
	tasto = true;
	tempo = false;
	punti = false;
	main = true;
	red = false;
	dx = true;
	diff = 1;	
	i = 0;
	version= "v. 1.0.0";
	button1= "Nuovo gioco";
	button2= "Difficolta'";
	button3= "Opzioni";
	button4= " < Indietro";	
	button5= "Impostazioni";
	button6= "Controlli";
	button7= "Come giocare";
	button9= "Facile";
	button10= "Medio";
	button11= "Difficile";
	button12= "DX";
	button14= "SX";
	occhio="Penalizzazione occhio:";
	keyboard="Tastiera";
	time="Tempo";
	score="Punteggio";
	p1=" Incremento penalizzazione dell' ";
	p12=" occhio tramite il tasto F3";
	p2=" occhio dopo x ms";
	p3=" occhio dopo x punti";

}

/*
Summary: Distruttore virtuale 
Return:
*/
MainMenu::~MainMenu(void)
{
}

/*
Summary: Metodo che resetta tutti i campi della classe
Return: void
*/
void MainMenu::reset()
{
	for(int t=0;t<15;t++)
		selected[t]=false;

	newGame = false;
	options = false;
	controls = false;
	how_to_play = false;
	second = false;
	difficulty = false;
	settings = false;
	easy = true;
	medium = false;
	hard = false;
	tasto = true;
	tempo = false;
	punti = false;
	main = true;
	red = false;
	dx = true;  
	diff = 1;	
	i = 0;
}

/*
Summary: Metodo che inizializza tutte le texture del menu
Return: void
*/
void MainMenu::initTexture(){
	cout<<"LOADING TEXTURE 0% "<<endl;
	title = loadTexture("title.png");  
	cout<<"LOADING TEXTURE 5% "<<endl;
	s1 = loadTexture("s1.png");
	cout<<"LOADING TEXTURE 10% "<<endl;
	s2 = loadTexture("s2.png");
	cout<<"LOADING TEXTURE 15% "<<endl;
	s3 = loadTexture("s3.png");
	cout<<"LOADING TEXTURE 20% "<<endl;
	texture[0] = loadTexture("new.png");
	cout<<"LOADING TEXTURE 25% "<<endl;
	texture[1] = loadTexture("new1.png");
	cout<<"LOADING TEXTURE 30% "<<endl;
}

/*
Summary: Metodo che creare l'animazione della texture NEW
Return: void
*/
void MainMenu::animFunc(){
	i+=1;
	if(i==2)
		i=0;
}
/*
Summary: Metodo che permette di carica la singola texture da file
Return: La texture
*/
GLuint MainMenu::loadTexture(std::string Filename){                

	GLuint tex_ID = 0;

	tex_ID = SOIL_load_OGL_texture(
		Filename.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_MULTIPLY_ALPHA
		| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		| SOIL_FLAG_INVERT_Y
		);

	if( tex_ID > 0 )
	{		
		return tex_ID;
	}
	else
		return 0;
}
/*
Summary: Metodo che disegna la texture
Return: void
*/
void MainMenu::texturize(GLuint g,float x,float y,float a,float b){
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D,g);                            //binding della texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	// FRONT
	glTexCoord2f(0,0);
	glVertex2f(x+a,y);
	glTexCoord2f(1,0);
	glVertex2f(x,y);
	glTexCoord2f(1,1);
	glVertex2f(x,y+b);
	glTexCoord2f(0,1);
	glVertex2f(x+a,y+b);	

	glEnd();
	glDisable(GL_TEXTURE_2D);

}

/*
Summary: Metodo che disegna il testo generico
Return: void
*/
void MainMenu::write(string s,void *font ,float x,float y){

	glRasterPos2f(x-2,y);

	for(int i=0; i<s.length(); i++){               //disegna il testo
		if(s[i]=='\n')
			glutBitmapCharacter(font, NULL);          //EOF
		else
			glutBitmapCharacter(font, (int) s[i]);
	}
}
/*
Summary: Metodo che scrive il contenuto di un file
Return: void
*/
void MainMenu::writeFromFile(char array[],int end)          //Metodo per scrivere da file .txt
{
	char *buf; 
	int aux=0;                                     //puntatore ausiliario
	float n=3;                                     //altezza dell'inizio del testo
	buf=new char[end];                             //dinamically allocate memory	
	for(int j=0;j<end;j++,aux++){

		buf[aux]=array[j];

		if(array[j]=='\n'){
			write(buf,GLUT_BITMAP_9_BY_15,-5,n);       

			buf=new char[end];                         //svuotamento del buffer
			aux=0;                                     //reset a 0 del puntatore ausiliario
			n=n-0.7;
		}
	}
	delete buf;                                    //cancellazione del buffer
}
/*
Summary: Metodo che legge da file
Return: void
*/
void MainMenu::readFromFile(){
	int end,i=0;
	char *array;                                     //allocazione dinamica della memoria
	if(how_to_play)
		fin.open("How_to_play.txt");                     //apertura del file
	else
		fin.open("Controls.txt");   
	fin.seekg (0, ios::end);
	end = fin.tellg();                               //posizionamento alla dine del file x il calcolo della dimensione del buffer
	fin.seekg(0,ios::beg);

	array=new char[end];                             //creazione array di dimensione buffer	
	glColor3f(0,1,0);
	while(!fin.eof()){                               //lettura del file
		fin.get(array[i]);
		i++;				
	}                                         //METODO????

	writeFromFile(array,end);			
	delete array;                                    //rilascio memoria allocata
	fin.close();                                      //chiusura del file

	glPopMatrix();
}
/*
Summary: Metodo che disegna il bottone
Return: void
*/
void MainMenu::drawButton(string s,float x,float y,GLboolean selected){

	if(!second){   

		glColor3f(1.0,0.3,0.1);                      //colore arancione 

		if(selected)
			glPolygonMode(GL_FRONT, GL_FILL);            
		else
			glPolygonMode(GL_FRONT, GL_LINE);

		if(!red){
			glBegin(GL_QUADS);                          //disegna il bottone
			glVertex2f(x,y);
			glVertex2f(x+6,y);
			glVertex2f(x+6,y+2);
			glVertex2f(x,y+2);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);                          //disegna il bottone
			glVertex2f(x,y);
			glVertex2f(x+3,y);
			glVertex2f(x+3,y+2);
			glVertex2f(x,y+2);
			glEnd();
		}

		if(selected)
			glColor3f(0,0,0);                           //cambia il colore del testo per renderlo visibile quando selezionato

		write(s,GLUT_BITMAP_9_BY_15,x+3,y+1);
	}
	else
	{
		if(selected)
			glColor3f(0,0,0);                           

		write(s,GLUT_BITMAP_9_BY_15,x+3,y+1);
		glColor3f(1.0,0.3,0.1);

		if(selected)
			glPolygonMode(GL_FRONT, GL_FILL);        
		else
			glPolygonMode(GL_FRONT, GL_LINE);

		if(!red){
			glBegin(GL_QUADS);                          //disegna il bottone
			glVertex2f(x,y);
			glVertex2f(x+6,y);
			glVertex2f(x+6,y+2);
			glVertex2f(x,y+2);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);                          //disegna il bottone
			glVertex2f(x,y);
			glVertex2f(x+3,y);
			glVertex2f(x+3,y+2);
			glVertex2f(x,y+2);
			glEnd();
		}
	}
}
/*
Summary: Metodo per la texture del titolo
Return: void
*/
void MainMenu::drawTitle(float x,float y){                         

	texturize(title,x,y,10,2);
	texturize(s1,x+1.3,y-1,-5,-8);
	texturize(s2,x+14,y-1,-5.2,-8);

}
/*
Summary: Metodo che disegna la versione del gioco e gli autori
Return: void
*/
void MainMenu::drawVersion(float x,float y){          
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0,1,0);                     
	write(version,GLUT_BITMAP_9_BY_15,x+2,y+0.1); 
	write("COPY BY FORLINI:CARRARA 2013",GLUT_BITMAP_9_BY_15,x+0.3,y+0.1);
	glPopMatrix();

	glColor3f(1.0,0.3,0.1);
}
/*
Summary: Metodo che disegna l'intero menu
Return: void
*/
void MainMenu::draw(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);               //Pulisce i buffer ogni volta che viene richiamato draw(),per evitare difetti

	if(main)
	{
		texturize(texture[(int)i],-4,7.5,-4,-2.5);

		drawButton(button1,-3.5,1,selected[0]);
		drawButton(button2,-3.5,-2,selected[1]);
		drawButton(button3,-3.5,-5,selected[2]);

		drawTitle(-5.5,4);
		drawVersion(0.75,-1);
	}

	if(difficulty){                                              //sottomenu difficoltà		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor3f(0,1,0);		
		write(occhio,GLUT_BITMAP_9_BY_15,-6.4,1.5);		

		drawButton(button4,-7,4,selected[3]);

		drawButton(button9,-1,1,selected[7]);
		drawButton(button10,-1,-2,selected[8]);
		drawButton(button11,-1,-5,selected[9]);

		red=true;
		drawButton(button12,-7,-2,selected[10]);
		drawButton(button14,-7,-5,selected[11]);
		red=false;				
	}

	if(options){                                                   //sottomenu opzioni

		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawButton(button4,-7,4,selected[3]);

		drawButton(button5,-7,-2,selected[4]);
		drawButton(button6,0,1,selected[5]);
		drawButton(button7,0,-5,selected[6]);
	}
	if(settings){
		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawButton(button4,-7,4,selected[3]);

		drawButton(keyboard,0,1,selected[12]);
		drawButton(time,0,-2,selected[13]);
		drawButton(score,0,-5,selected[14]);
		glColor3f(0,1,0);
		write(p1,GLUT_BITMAP_9_BY_15,-7.4,2);	
		write(p12,GLUT_BITMAP_9_BY_15,-6.4,1.5);
		write(p1,GLUT_BITMAP_9_BY_15,-7.4,-1);
		write(p2,GLUT_BITMAP_9_BY_15,-7.4,-1.5);
		write(p1,GLUT_BITMAP_9_BY_15,-7.4,-4);
		write(p3,GLUT_BITMAP_9_BY_15,-7.4,-4.5);
	}


	if(how_to_play){                                          //sottomenu how-to play

		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawButton(button4,-7,4,selected[3]);			
		readFromFile();
		glPopMatrix();
	}

	if(controls){                                    //sottomenu controlli

		glPushMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawButton(button4,-7,4,selected[3]);				
		readFromFile();
		glPopMatrix();
	}

	glPopMatrix();

	glutSwapBuffers();
}
/*
Summary: Metodo che gestisce il movimento del mouse
Return: void
*/
void MainMenu::onMouseMove(int xMouse,int yMouse){

	float k = 1.0;                                                           //fattore di scala per diverse risoluzioni

	if(width==800)
		k=1.25;                                                              //correzione scala												

	if(xMouse<398*k && xMouse>207*k && yMouse<207*k && yMouse>144*k)         //NEW GAME
		selected[0]=true;
	else
		selected[0]=false;

	if(xMouse<398*k && xMouse>207*k && yMouse<302*k && yMouse>241*k)          //DIFFICULTY
		selected[1]=true;
	else
		selected[1]=false;

	if( difficulty &&  xMouse<479*k && xMouse>289*k && yMouse<207*k && yMouse>144*k || easy)    //EASY
		selected[7]=true;
	else
		selected[7]=false;

	if( difficulty && xMouse<479*k && xMouse>289*k && yMouse<304*k && yMouse>241*k || medium)   //MEDIUM
		selected[8]=true;
	else
		selected[8]=false;

	if( difficulty && xMouse<479*k && xMouse>289*k && yMouse<399*k && yMouse>336*k || hard)    //HARD
		selected[9]=true;
	else
		selected[9]=false;

	if( difficulty && xMouse<190*k && xMouse>95*k && yMouse<304*k && yMouse>241*k || !dx)    //SX
		selected[10]=true;
	else
		selected[10]=false;

	if( difficulty && xMouse<190*k && xMouse>95*k && yMouse<399*k && yMouse>336*k || dx)    //DX
		selected[11]=true;
	else
		selected[11]=false;

	if(xMouse<398*k && xMouse>207*k && yMouse<398*k && yMouse>337*k)          //OPTIONS
		selected[2]=true;
	else
		selected[2]=false;

	if(xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k)          //BACK
		selected[3]=true;
	else
		selected[3]=false;

	if(xMouse<287*k && xMouse>96*k && yMouse<336*k && yMouse>239*k)          //SETTINGS
		selected[4]=true;
	else
		selected[4]=false;

	if(tasto || xMouse<511*k && xMouse>320*k && yMouse<207*k && yMouse>144*k)          //TASTIERA
		selected[12]=true;
	else
		selected[12]=false;

	if(tempo || xMouse<511*k && xMouse>320*k && yMouse<303*k && yMouse>240*k)          //TEMPO
		selected[13]=true;
	else
		selected[13]=false;

	if(punti || xMouse<511*k && xMouse>320*k && yMouse<398*k && yMouse>337*k)          //PUNTEGGIO
		selected[14]=true;
	else
		selected[14]=false;

	if(options && xMouse<511*k && xMouse>319*k && yMouse<208*k && yMouse>145*k)          //CONTROLS
		selected[5]=true;
	else
		selected[5]=false;

	if(options && xMouse<511*k && xMouse>319*k && yMouse<399*k && yMouse>337*k)          //HOW TO PLAY
		selected[6]=true;
	else
		selected[6]=false;

	glutPostRedisplay();
}
/*
Summary: Metodo che gestisce il click del mouse
Return: void
*/
void MainMenu::onMouseClick(int button,int state,int xMouse,int yMouse)
{
	float k = 1.0;                               //fattore di scala

	if(width==800)
		k=1.25;                                       

	if(!options && !difficulty && xMouse<398*k && xMouse>207*k && yMouse<398*k && yMouse>337*k && state == GLUT_DOWN ){                     //click su OPTIONS
		options=true;
		main=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if(!difficulty && xMouse<398*k && xMouse>207*k && yMouse<302*k && yMouse>241*k && state==GLUT_UP){                     //click su DIFFICULTY
		difficulty=true;
		main=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if(!options && xMouse<398*k && xMouse>207*k && yMouse<207*k && yMouse>144*k && state==GLUT_DOWN){                     //click su NEW GAME
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
		   
		 
		newGame=true;
		main=false;
	}

	if(difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<207*k && yMouse>144*k){          //settaggio delle difficoltà e,m,h
		diff = 1;
		easy=true;
		medium=false;
		hard=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if( difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<304*k && yMouse>241*k){
		diff = 2;
		easy=false;
		medium=true;
		hard= false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}
	if( difficulty && state==GLUT_DOWN && xMouse<479*k && xMouse>289*k && yMouse<399*k && yMouse>336*k){
		diff = 3;
		easy=false;
		medium=false;
		hard=true;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}
	if( difficulty && state==GLUT_DOWN && xMouse<190*k && xMouse>95*k && yMouse<304*k && yMouse>241*k){
		dx=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}
	if( difficulty && state==GLUT_DOWN  && xMouse<190*k && xMouse>95*k && yMouse<399*k && yMouse>336*k ){
		dx=true;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if((options || difficulty) && state==GLUT_DOWN && xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k){      //click su BACK
		options=false;		
		difficulty=false;
		main=true;
		if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if(options && !how_to_play && state==GLUT_DOWN && xMouse<511*k && xMouse>319*k && yMouse<208*k && yMouse>145*k) {               //click su CONTROLS
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
		controls=true;
		options=false;
		main=false;
	}

	if(options && !how_to_play && !controls && state==GLUT_DOWN && xMouse<287*k && xMouse>96*k && yMouse<336*k && yMouse>239*k) {               //click su SETTINGS
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
		difficulty=false;
		settings=true;
		options=false;
		main=false;
	}

	if( settings && state==GLUT_DOWN && xMouse<511*k && xMouse>320*k && yMouse<207*k && yMouse>144*k){  //TASTIERA
		tasto=true;
		tempo=false;
		punti=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}
	if( settings && state==GLUT_DOWN && xMouse<511*k && xMouse>320*k && yMouse<303*k && yMouse>240*k){
		tasto=false;
		tempo=true;
		punti=false;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}
	if( settings && state==GLUT_DOWN && xMouse<511*k && xMouse>320*k && yMouse<398*k && yMouse>337*k){
		tasto=false;
		tempo=false;
		punti=true;
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
	}

	if(selected[6] && !controls && state==GLUT_DOWN && options && xMouse<511*k && xMouse>319*k && yMouse<399*k && yMouse>337*k){           //click su HOW TO PLAY
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
		how_to_play=true;
		options=false;
		main=false;
	}

	if((how_to_play || controls || settings) && state==GLUT_DOWN && xMouse<287*k && xMouse>96*k && yMouse<112*k && yMouse>49*k)        //click su BACK
	{       
		 if(audioON)
		   engine->play2D("Tick.mp3",false);
		how_to_play=false;
		controls=false;
		settings=false;
		options=true;
		main=false;
	}

	glutPostRedisplay();
}
/*
Summary: Metodo che ridisegna il tutto
Return: void
*/
void MainMenu::reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.,10.,
		-10.*h/w,10.*h/w,
		-10.,10.);
}
/*
Summary: Metodo che lo stato della boolea newGame
Return: La boolean newGame
*/
GLboolean MainMenu::isNewGame(){         
	if(newGame)
		return true;
	return false;
}
/*
Summary: Metodo che ritorna la difficoltà scelta dell'utente
Return: L'intero che rappresenta la difficoltà scelta dell'utente
*/
int MainMenu::getDiff()
{
	return diff;
}
/*
Summary: Metodo che ritorna la booleana che rappresenta l'occhio penalizzato
Return: Booleana che rappresenta l'occhio penalizzato
*/
bool MainMenu::getPen()
{
	return dx;
}
/*
Summary: Metodo che ritorna la penalizzazione di tipo TEMPO
Return: La booleana per la penalizzazione di tipo TEMPO
*/
bool MainMenu::getTempo()
{
	return tempo;
}
/*
Summary: Metodo che ritorna la penalizzazione di tipo PUNTI
Return: La booleana per la penalizzazione di tipo PUNTI
*/
bool MainMenu::getPointsPen()
{
	return punti;
}
/*
Summary: La booleana per la penalizzazione di tipo TASTO PREMUTO
Return: La booleana per la penalizzazione di tipo TASTO PREMUTO
*/
bool MainMenu::getKeyPen()
{
	return tasto;
}
/*
Summary: Metodo che setta lo stato del gioco
Return: void
*/
void MainMenu::setNewGame(bool n)
{
	newGame = n;
}
/*
Summary: Metodo che setta i colori alla seconda iterazione del disegno del menu
Return: void
*/
void MainMenu::setSecond(bool s)
{
	second = s;
}
/*
Summary: Metodo che setta la booleana per il menu principale
Return: void
*/
void MainMenu::setMain(bool m)
{
	main = m;
}
