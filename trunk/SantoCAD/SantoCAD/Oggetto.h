#ifndef OGGETTO_H
#define OGGETTO_H

#include <iostream>
#include <string>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cml/cml.h>
#include "materiali.h"
#include "Texture.h"
#include <math.h>

using namespace cml;

#define CUBO	1
#define SFERA	2
#define TORUS	3
#define TETRA	4
#define TEAPOT	5
#define CONE	6
#define DODE	7
#define ICO		8
#define OCTA	9

class Oggetto{

private:
	int tipo;
	void init();
	vector3f posizione;
	vector3f scale;
	GLfloat rotazioneX;
	GLfloat rotazioneY;
	GLfloat rotazioneZ;
	bool wireframe;
	int idColore;
	int idMateriale;
	void evidenzia();
	void disegnaAssi();
	bool selezionato;
	bool mostraSelezione;
	Texture* texture;

public:
	Oggetto(int t);
	~Oggetto();

	int getTipo();
	void disegna(GLenum mode, int id);
	void setPosizione(vector3f v);
	vector3f getPosizione();
	void setScale(vector3f v);
	vector3f getScale();
	void setRotazione(GLfloat x,GLfloat y,GLfloat z);
	float getRotazioneX();
	float getRotazioneY();
	float getRotazioneZ();
	void setWireframe(bool b);
	bool isWireframe();
	void setMostraSelezione(bool b);
	bool isMostraSelezione();
	void Oggetto::setIdColore(int c);
	int getIdColore();
	void setIdMateriale(int m);
	int getIdMateriale();
	void setSelezionato(bool b);
	void setTexture(Texture* t);
	Texture* getTexture();
};

#endif