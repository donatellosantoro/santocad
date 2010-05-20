#ifndef SKYBOX_H
#define SKYBOX_H

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "materiali.h"
#include "textureUtil.h"
#include "Utilita.h"

class Skybox{

private:
	void init(string s);
	void disegnaCubo();
	GLuint idTexture;
	char *texCubeFaces[6];

public:
	Skybox(string c);
	~Skybox();

	float posizioneY;
	void disegna();
	void ricaricaTexture();
	int abilitato;
	void setTexture(int i,char* nomeFile);
	char* getTexture(int i);
	void caricaDaCartella(string nomeCartella);
};

#endif