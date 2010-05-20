#ifndef GENERATORE_CODICE_OGGETTO_H
#define GENERATORE_CODICE_OGGETTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Oggetto.h"

using namespace std;

class GeneratoreCodiceOggetto{

private:
	Oggetto *o;
	int pos;
	void init();
	string getStringaMateriale();
	string getStringaColore();
	string getStringaTrasformazioni();
	string getStringaOggetto();
	string getBindTexture();
	
	string TAB;
	string LINE;
	string S_STR;
	string I_END;
	string COM;

public:
	GeneratoreCodiceOggetto(Oggetto* o, int pos);
	~GeneratoreCodiceOggetto();

	string genera();
	string getVariabileTexture();
	string getCaricamentoTexture();
	string getVariabilePlane();
};

#endif