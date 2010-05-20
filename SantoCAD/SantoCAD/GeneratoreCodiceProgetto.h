#ifndef GENERATORE_CODICE_PROGETTO_H
#define GENERATORE_CODICE_PROGETTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Progetto.h"
#include "Oggetto.h"

using namespace std;
using std::list;

class GeneratoreCodiceProgetto{

private:
	Progetto *p;
	string initFolder;
	void init();
	void generaFileMain(string *stringFileMain);
	string getCodiceDisegnoOggetti();
	string getCodiceGestioneCamera();
	string getCodiceDisegnoPavimento();
	string getCodiceGestioneLimiti();
	string getCodiceDisegnoSkybox();
	string getCodiceVariabiliTexture();
	string getCodiceCaricaTexture();
	string getCodiceVariabiliPlane();
	string getCodiceAbilitaTexture();
	string getCodiceDisabilitaTexture();
	string getCodiceGestisciIlluminazione();
	string getCodiceLuce(Luce *l);
	string codiceVariabiliTexture;
	string codiceVariabiliPlane;
	string codiceCaricaTexture;
	string PLACEHOLDER_DISEGNO_OGGETTI;
	string PLACEHOLDER_VARIABILI_TEXTURE;
	string PLACEHOLDER_DISEGNO_PAVIMENTO;
	string PLACEHOLDER_DISEGNO_SKYBOX;
	string PLACEHOLDER_CONTROLLA_LIMITI;
	string PLACEHOLDER_CARICA_TEXTURE;
	string PLACEHOLDER_VARIABILI_PLANE;
	string PLACEHOLDER_GESTISCI_ILLUMINAZIONE;
	string PLACEHOLDER_NOME_PROGETTO;
	string PLACEHOLDER_GESTIONE_CAMERA;
	bool statoTextureAbilitata;	
	vector3f pos;
	vector3f at;
	vector3f dir;
	string TAB;
	string LINE;

public:
	GeneratoreCodiceProgetto(Progetto* p, string initFolder);
	~GeneratoreCodiceProgetto();

	void genera(string folder, string nomeProgetto);
	void setCamera(vector3f p,vector3f a, vector3f d);
};

#endif