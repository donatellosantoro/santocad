#include "Luce.h"
#include "Logger.h"
#include "materiali.h"
#include <iostream>

using namespace std;


vector3f axisSpotLightX(1.0, 0.0, 0.0);	// Asse Y. Utile nelle rotazioni
vector3f axisSpotLightY(0.0, 1.0, 0.0);	// Asse Y. Utile nelle rotazioni
vector3f axisSpotLightZ(0.0, 0.0, 1.0);	// Asse Z. Utile nelle rotazioni

Luce::Luce(int i):id(i){init();}
Luce::~Luce(){}

void Luce::init(){
	abilitata = false;
	disegnaSorgente = true;
	tipo = Luce::PUNTIFORME; 
	posizione = vector3f(0.0,1.0,0.0);
	ambientale[0] = ambientale[1] = ambientale[2] = 255;
	diffusa[0] = diffusa[1] = diffusa[2] = 255;
	speculare[0] = speculare[1] = speculare[2] = 255;
	ambientale[3] = diffusa[3] = speculare[3] = 1;	
	quadratic=gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	valoreRaggio = 20;
	valoreAttenuazione = 3;
	aggiornaRotazione();
}

void Luce::setColoreRosso() {
	ambientale[0] = ambientale[1] = ambientale[2] = 0;
	diffusa[0] = diffusa[1] = diffusa[2] = 0;
	speculare[0] = speculare[1] = speculare[2] = 0;
	ambientale[0] = diffusa[0] = speculare[0] = 255;
}

void Luce::setColoreVerde() {
	ambientale[0] = ambientale[1] = ambientale[2] = 0;
	diffusa[0] = diffusa[1] = diffusa[2] = 0;
	speculare[0] = speculare[1] = speculare[2] = 0;
	ambientale[1] = diffusa[1] = speculare[1] = 255;
}

void Luce::setColoreBlu() {
	ambientale[0] = ambientale[1] = ambientale[2] = 0;
	diffusa[0] = diffusa[1] = diffusa[2] = 0;
	speculare[0] = speculare[1] = speculare[2] = 0;
	ambientale[2] = diffusa[2] = speculare[2] = 255;
}

int Luce::getId(){
	return id;
}

void Luce::aggiornaRotazione(){
	vector3f light_direction(0.0, -1.0, 0.0);
	rotazioneSpotlight = rotate_vector(light_direction,axisSpotLightX,rotazioneSpotlightX);
	rotazioneSpotlight = rotate_vector(rotazioneSpotlight,axisSpotLightY,rotazioneSpotlightY);
	rotazioneSpotlight = rotate_vector(rotazioneSpotlight,axisSpotLightZ,rotazioneSpotlightZ);
}

vector3f Luce::getRotazioneSpotlight(){
	return rotazioneSpotlight;
}

void Luce::disegna(){
	GLint idLuce = GL_LIGHT0 + id;
	GLboolean luceAbilitata = glIsEnabled(GL_LIGHTING);
	
	if(abilitata && luceAbilitata){
		glEnable(idLuce);

		float forthComponent = 1.0;
		if(tipo == Luce::DIREZIONALE)forthComponent = 0.0;
		//Definiamo la posizione della luce
		GLfloat light_position[] = {posizione[0], posizione[1], posizione[2], forthComponent};
		glLightfv(idLuce, GL_POSITION, light_position);

		if(tipo == Luce::SPOTLIGHT) {
			GLfloat vettore_rotazione[] = {rotazioneSpotlight[0],rotazioneSpotlight[1],rotazioneSpotlight[2]};
			glLightfv(idLuce, GL_SPOT_DIRECTION, vettore_rotazione);
			glLightf(idLuce, GL_SPOT_CUTOFF, valoreRaggio);
			glLightf(idLuce, GL_SPOT_EXPONENT, valoreAttenuazione);
		}else{
			glLightf(idLuce, GL_SPOT_CUTOFF, 180.0);
			glLightf(idLuce, GL_SPOT_EXPONENT, 0.0);
		}

		//Definiamo la componente ambientale
		GLfloat light_ambient[] = {ambientale[0]/255.0, ambientale[1]/255.0, ambientale[2]/255.0, ambientale[3]};
		glLightfv(idLuce, GL_AMBIENT, light_ambient);

		//Definiamo la componente diffusa
		GLfloat light_diffuse[] = {diffusa[0]/255.0, diffusa[1]/255.0, diffusa[2]/255.0, diffusa[3]};
		glLightfv(idLuce, GL_DIFFUSE, light_diffuse);

		//Definiamo la componente speculare
		GLfloat light_specular[] = {speculare[0]/255.0, speculare[1]/255.0, speculare[2]/255.0, speculare[3]};
		glLightfv(idLuce, GL_SPECULAR, light_specular);

		if(disegnaSorgente){
			
			glPushMatrix();
				glTranslatef(posizione[0], posizione[1], posizione[2]);
				disegnaLuce(tipo == Luce::SPOTLIGHT);
			glPopMatrix();
		}
	}else{
		glDisable(idLuce);
	}
}

void Luce::disegnaLuce(bool faretto){
	if(faretto){
		//setMaterialeDefault();
		setMaterialePolishedSilver();
		glPushMatrix();
			//glBindTexture(GL_TEXTURE_2D, idTextureFaretto);
			glRotatef(rotazioneSpotlightZ * 180 / M_PI,0.0,0.0,1.0);
			glRotatef(rotazioneSpotlightY * 180 / M_PI,0.0,1.0,0.0);
			glRotatef(rotazioneSpotlightX * 180 / M_PI,1.0,0.0,0.0);
			glRotatef(-90,1.0,0.0,0.0);
			glPushMatrix();
				gluCylinder(quadratic, 0.25, 0.1, 0.2, 32, 32);
			glPopMatrix();
			glPushMatrix();
				glTranslated(0.0,0.0,0.2);
				gluDisk(quadratic,0.0,0.1,32,32);
			glPopMatrix();
		glPopMatrix();
	}

	setMaterialePolishedSilver();
	//glBindTexture(GL_TEXTURE_2D, idTextureLampadina);
	glPushMatrix();
		//glTranslated(0.0,0.0,0.1);
		glDisable(GL_LIGHTING);
			glColor3f((GLfloat)ambientale[0]/255, (GLfloat)ambientale[1]/255, (GLfloat)ambientale[2]/255);
			glutSolidSphere(0.1,32,32);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

vector3f Luce::getPosizione(){
	return posizione;
}

void Luce::setPosizione(vector3f v){
	posizione = v;
}

int* Luce::getAmbientale() {
	return ambientale;
}

int* Luce::getDiffusa() {
	return diffusa;
}

int* Luce::getSpeculare() {
	return speculare;
}

void Luce::setRotazioneSpotlight(GLfloat x,GLfloat y,GLfloat z){
	rotazioneSpotlightX = x;
	rotazioneSpotlightY = y;
	rotazioneSpotlightZ = z;
	aggiornaRotazione();
}

float Luce::getRotazioneSpotlightX(){
	return rotazioneSpotlightX;
}

float Luce::getRotazioneSpotlightY(){
	return rotazioneSpotlightY;
}

float Luce::getRotazioneSpotlightZ(){
	return rotazioneSpotlightZ;
}