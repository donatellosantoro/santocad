#ifndef DAO_PROGETTO_H
#define DAO_PROGETTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Oggetto.h"
#include "Pavimento.h"
#include "Skybox.h"
#include "Luce.h"

using namespace std;
using std::list;

class DAOProgetto{

private:
	static const int DELIMITATORE_PROGETTO = 100;
	static const int DELIMITATORE_OGGETTO = 101;
	static const int DELIMITATORE_LUCE = 102;
	static const int DELIMITATORE_SKYBOX = 103;

	static void caricaProgetto(Progetto *p,string linea){
		stringstream s_linea(linea);
		int delimitatore;
		s_linea >> delimitatore;

		s_linea >> p->illuminazioneAbilitata;
		s_linea >> p->getPavimento()->abilitato;
		s_linea >> p->getPavimento()->idColore;
		s_linea >> p->getPavimento()->idMateriale;
		s_linea >> p->getPavimento()->tassellazione;
		s_linea >> p->getPavimento()->wireframe;
		s_linea >> p->getSkybox()->abilitato;
		s_linea >> p->getSkybox()->posizioneY;
	}

	static void caricaSkybox(Progetto *p,string linea, string cartellaIniziale){
		stringstream s_linea(linea);
		int delimitatore;
		s_linea >> delimitatore;

		int id;
		s_linea >> id;			
		
		string nomeFile;
		s_linea.ignore();
		getline(s_linea, nomeFile);
		nomeFile = Utilita::getPercorsoAssoluto(nomeFile,cartellaIniziale);
		p->getSkybox()->setTexture(id,Utilita::stringToChar(nomeFile));

	}

	static void caricaLuce(Progetto *p,string linea){
		stringstream s_linea(linea);
		int delimitatore;
		s_linea >> delimitatore;

		int id;
		s_linea >> id;
		Luce *l = p->getLuce(id);

		float posizione[3];
		s_linea >> posizione[0];
		s_linea >> posizione[1];
		s_linea >> posizione[2];
		vector3f posizione_v(posizione[0],posizione[1],posizione[2]);
		l->setPosizione(posizione_v);

		s_linea >> l->getAmbientale()[0];
		s_linea >> l->getAmbientale()[1];
		s_linea >> l->getAmbientale()[2];
		s_linea >> l->getAmbientale()[4];

		s_linea >> l->getDiffusa()[0];
		s_linea >> l->getDiffusa()[1];
		s_linea >> l->getDiffusa()[2];
		s_linea >> l->getDiffusa()[4];

		s_linea >> l->getSpeculare()[0];
		s_linea >> l->getSpeculare()[1];
		s_linea >> l->getSpeculare()[2];
		s_linea >> l->getSpeculare()[4];


		GLfloat rotazioneX;
		s_linea >> rotazioneX;
		GLfloat rotazioneY;
		s_linea >> rotazioneY;
		GLfloat rotazioneZ;
		s_linea >> rotazioneZ;
		l->setRotazioneSpotlight(rotazioneX,rotazioneY,rotazioneZ);

		s_linea >> l->tipo;
		s_linea >> l->abilitata;
		s_linea >> l->disegnaSorgente;
		s_linea >> l->valoreRaggio;
		s_linea >> l->valoreAttenuazione;
	}

	static Oggetto* caricaOggetto(string linea, string cartellaIniziale){
		stringstream s_linea(linea);
		int delimitatore;
		s_linea >> delimitatore;

		int tipo;
		s_linea >> tipo;

		Oggetto *o = new Oggetto(tipo);

		float posizione[3];
		s_linea >> posizione[0];
		s_linea >> posizione[1];
		s_linea >> posizione[2];
		vector3f posizione_v(posizione[0],posizione[1],posizione[2]);
		o->setPosizione(posizione_v);

		float scale[3];
		s_linea >> scale[0];
		s_linea >> scale[1];
		s_linea >> scale[2];
		vector3f scale_v(scale[0],scale[1],scale[2]);
		o->setScale(scale_v);

		float rotazione[3];
		s_linea >> rotazione[0];
		s_linea >> rotazione[1];
		s_linea >> rotazione[2];
		o->setRotazione(rotazione[0],rotazione[1],rotazione[2]);

		bool wireframe;
		s_linea >> wireframe;
		o->setWireframe(wireframe);

		int idColore;
		s_linea >> idColore;
		o->setIdColore(idColore);

		int idMateriale;
		s_linea >> idMateriale;
		o->setIdMateriale(idMateriale);

		bool mostraSelezione;
		s_linea >> mostraSelezione;
		o->setMostraSelezione(mostraSelezione);

		bool hasTexture;
		s_linea >> hasTexture;
		if(hasTexture){
			Logger::debug("Object has texture.. Loading");
			
			GLfloat planes[4];
			s_linea >> planes[0];
			s_linea >> planes[1];
			s_linea >> planes[2];
			s_linea >> planes[3];

			GLfloat planet[4];
			s_linea >> planet[0];
			s_linea >> planet[1];
			s_linea >> planet[2];
			s_linea >> planet[3];

			GLint mapping;
			s_linea >> mapping;

			bool repeat;
			s_linea >> repeat;

			bool mipmap;
			s_linea >> mipmap;

			string nomeFile;
			s_linea.ignore();
			getline(s_linea, nomeFile);

			nomeFile = Utilita::getPercorsoAssoluto(nomeFile,cartellaIniziale);
			char* file = Utilita::stringToChar(nomeFile);
			Texture *t = new Texture(file,repeat,mipmap);
			t->setPlane(planes,planet);
			t->setMapping(mapping);
			o->setTexture(t);
		}
		return o;
	}



public:

	static void salva(Progetto* p,const char* nomeFile,string cartellaIniziale){
		ofstream out(nomeFile);

		out << DELIMITATORE_PROGETTO << " ";
		out << p->illuminazioneAbilitata << " ";
		out << p->getPavimento()->abilitato << " ";
		out << p->getPavimento()->idColore << " ";
		out << p->getPavimento()->idMateriale << " ";
		out << p->getPavimento()->tassellazione << " ";
		out << p->getPavimento()->wireframe << " ";
		out << p->getSkybox()->abilitato << " ";
		out << p->getSkybox()->posizioneY;
		out << endl;

		for(int i=0;i<p->getNumeroOggetti();i++){
			Oggetto* o = p->getOggetto(i);
			out << DELIMITATORE_OGGETTO << " ";
			out << o->getTipo() << " ";
			out << o->getPosizione() << " ";
			out << o->getScale() << " ";
			out << o->getRotazioneX() << " ";
			out << o->getRotazioneY() << " ";
			out << o->getRotazioneZ() << " ";
			out << o->isWireframe() << " ";
			out << o->getIdColore() << " ";
			out << o->getIdMateriale() << " ";
			out << o->isMostraSelezione() << " ";
			out << (o->getTexture()!=NULL) << " ";

			if(o->getTexture()!=NULL){
				Texture *t = o->getTexture();
				out << t->getPlanes()[0] << " ";
				out << t->getPlanes()[1] << " ";
				out << t->getPlanes()[2] << " ";
				out << t->getPlanes()[3] << " ";
				out << t->getPlanet()[0] << " ";
				out << t->getPlanet()[1] << " ";
				out << t->getPlanet()[2] << " ";
				out << t->getPlanet()[3] << " ";
				out << t->getMapping() << " ";
				out << t->isRepeat() << " ";
				out << t->isMipMapping() << " ";
				
				string percorsoRelativo = Utilita::getPercorsoRelativo(t->getNomeFile(),cartellaIniziale);
				out << percorsoRelativo;
			}

			out << endl;
		}

		for(int i=0;i<8;i++){
			Luce *l = p->getLuce(i);
			out << DELIMITATORE_LUCE << " ";
			out << i << " ";
			out << l->getPosizione() << " ";
			out << l->getAmbientale()[0] << " ";
			out << l->getAmbientale()[1] << " ";
			out << l->getAmbientale()[2] << " ";
			out << l->getAmbientale()[3] << " ";
			out << l->getDiffusa()[0] << " ";
			out << l->getDiffusa()[1] << " ";
			out << l->getDiffusa()[2] << " ";
			out << l->getDiffusa()[3] << " ";
			out << l->getSpeculare()[0] << " ";
			out << l->getSpeculare()[1] << " ";
			out << l->getSpeculare()[2] << " ";
			out << l->getSpeculare()[3] << " ";
			out << l->getRotazioneSpotlightX() << " ";
			out << l->getRotazioneSpotlightY() << " ";
			out << l->getRotazioneSpotlightZ() << " ";
			out << l->tipo << " ";
			out << l->abilitata << " ";
			out << l->disegnaSorgente << " ";
			out << l->valoreRaggio << " ";
			out << l->valoreAttenuazione << " ";
			out << endl;
		}

		for(int i=0;i<6;i++){
			out << DELIMITATORE_SKYBOX << " ";
			out << i << " ";
			string percorsoRelativo = Utilita::getPercorsoRelativo(p->getSkybox()->getTexture(i),cartellaIniziale);
			out << percorsoRelativo;
			out << endl;
		}

		out.close();
	}

	static void carica(Progetto* p, char* nomeFile, string cartellaIniziale){
		p->rimuoviOggetti();

		string s(nomeFile);
		Logger::debug("Loading project from file " + s);
		ifstream in(nomeFile);

		string linea;
		while(getline(in,linea)){
			stringstream s_linea(linea);

			int identificatore;
			s_linea >> identificatore;

			if(identificatore == DELIMITATORE_PROGETTO){
				caricaProgetto(p,linea);
			}else if(identificatore == DELIMITATORE_OGGETTO){
				Oggetto *o = caricaOggetto(linea,cartellaIniziale);
				p->addOggetto(*o);
				Logger::debug("Loaded a new object of type: ",o->getTipo());

			}else if(identificatore == DELIMITATORE_LUCE){
				caricaLuce(p,linea);
			}else if(identificatore == DELIMITATORE_SKYBOX){
				caricaSkybox(p,linea,cartellaIniziale);
			}else{
				Logger::error("Unknown delimiter: ",identificatore);
				return;
			}
		}
		in.close();
	}

};

#endif