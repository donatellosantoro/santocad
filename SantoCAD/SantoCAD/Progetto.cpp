#include "Progetto.h"
#include "Skybox.h"
#include "materiali.h"
#include "Logger.h"
#include <iostream>

using namespace std;

Progetto::Progetto(){
	init();
}
Progetto::~Progetto(){}

void Progetto::init(){
	illuminazioneAbilitata = true;
	pavimento = new Pavimento();
	for(int i=0;i<=7;i++){
		luci[i] = new Luce(i);
	}
	luci[0]->abilitata = 1;
	luci[1]->setColoreRosso();
	luci[2]->setColoreVerde();
	luci[3]->setColoreBlu();
}

void Progetto::disegna(GLenum mode){
	// Disegno il pavimento
	pavimento->disegna();

	// Disegno la skybox
	skybox->disegna();

	// Disegno gli oggetti
	list<Oggetto>::iterator o;
	int pos = 0;
	for (o = listaOggetti.begin(); o != listaOggetti.end(); ++o){
		Oggetto* oggetto = &*o;
		oggetto->disegna(mode,pos);
		pos++;
	}

	// Gestisco le luci
	for(int i=0;i<=7;i++){
		luci[i]->disegna();
	}
}

Oggetto* Progetto::getOggetto(int id){
	list<Oggetto>::iterator o;
	int pos = 0;
	for (o = listaOggetti.begin(); o != listaOggetti.end(); ++o){
		if(pos==id){
			return &*o;
		}
		pos++;
	}
	return NULL;
}

void Progetto::addOggetto(Oggetto o){
	listaOggetti.insert(listaOggetti.end(), o);
} 

void Progetto::removeOggetto(Oggetto *o) {
	list<Oggetto>::iterator it;
	for (it = listaOggetti.begin(); it != listaOggetti.end(); ++it){
		if(&*it==o){
			listaOggetti.erase(it);
			return;
		}
	}
}

void Progetto::rimuoviOggetti(){
	listaOggetti.clear();
}

int Progetto::getNumeroOggetti(){
	return listaOggetti.size();
}

char* Progetto::getRiepilogo(){
	char s[5];
	sprintf_s(s, "%i",getNumeroOggetti());
	return s;
}

Luce* Progetto::getLuce(int id){
	return luci[id];
}

Pavimento* Progetto::getPavimento(){
	return pavimento;
}

void Progetto::setSkybox(Skybox *s){
	skybox = s;
}

Skybox* Progetto::getSkybox(){
	return skybox;
}