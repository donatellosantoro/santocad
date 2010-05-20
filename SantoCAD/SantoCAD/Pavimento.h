#ifndef PAVIMENTO_H
#define PAVIMENTO_H

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


class Pavimento{

private:
	void init();

public:
	Pavimento();
	~Pavimento();

	void disegna();
	int abilitato;
	int wireframe;
	int idColore;
	int idMateriale;
	int tassellazione;
};

#endif