#ifndef LUCE_H
#define LUCE_H

#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cml/cml.h>
#include "materiali.h"
#include "Texture.h"
#include <math.h>

using namespace cml;


class Luce{

private:
	int id;
	void init();
	vector3f posizione;
	int ambientale[4];
	int diffusa[4];
	int speculare[4];
	void disegnaLuce(bool faretto);
	void aggiornaRotazione();
	GLfloat rotazioneSpotlightX;
	GLfloat rotazioneSpotlightY;
	GLfloat rotazioneSpotlightZ;
	GLUquadricObj *quadratic;
	vector3f rotazioneSpotlight;

public:
	Luce(int i);
	~Luce();

	static const int PUNTIFORME	= 0;
	static const int DIREZIONALE= 1;
	static const int SPOTLIGHT	= 2;
	//proprietà pubbliche per permettere il binding con i componenti della vista
	int tipo;
	int abilitata; 
	int disegnaSorgente;
	void disegna();
	void setPosizione(vector3f v);
	int valoreRaggio;
	int valoreAttenuazione;
	vector3f getPosizione();
	vector3f getRotazioneSpotlight();
	int* getAmbientale();
	int* getDiffusa();
	int* getSpeculare();
	void setRotazioneSpotlight(GLfloat x,GLfloat y,GLfloat z);
	float getRotazioneSpotlightX();
	float getRotazioneSpotlightY();
	float getRotazioneSpotlightZ();
	void setColoreRosso();
	void setColoreVerde();
	void setColoreBlu();
	int getId();
};

#endif