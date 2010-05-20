#ifndef PROGETTO_H
#define PROGETTO_H

#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Oggetto.h"
#include "Pavimento.h"
#include "Skybox.h"
#include "textureUtil.h"
#include "Luce.h"

using namespace std;
using std::list;

class Progetto{

private:
	Luce* luci[8];
	Pavimento* pavimento;
	Skybox* skybox;
	void init();

public:
	Progetto();
	~Progetto();
	list<Oggetto> listaOggetti;

	int illuminazioneAbilitata;
	void disegna(GLenum mode);
	void disegnaSkyBox();
	void addOggetto(Oggetto o);
	void removeOggetto(Oggetto *o);
	void rimuoviOggetti();
	int getNumeroOggetti();
	Oggetto* getOggetto(int id);
	char* getRiepilogo();
	Luce* getLuce(int id);
	void setSkybox(Skybox *s);
	Skybox* getSkybox();
	Pavimento* getPavimento();

};

#endif