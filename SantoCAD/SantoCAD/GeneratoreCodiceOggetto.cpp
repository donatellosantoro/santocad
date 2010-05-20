#include "GeneratoreCodiceOggetto.h"
#include "Logger.h"
#include "Utilita.h"
#include <iostream>

using namespace std;

GeneratoreCodiceOggetto::GeneratoreCodiceOggetto(Oggetto* oggetto, int p){
	o = oggetto;
	pos = p;
	init();
}
GeneratoreCodiceOggetto::~GeneratoreCodiceOggetto(){}

void GeneratoreCodiceOggetto::init(){
	TAB = "\t";
	LINE = "\n";
	S_STR = "\"";
	I_END = ");";
	COM = ", ";
}

string GeneratoreCodiceOggetto::getVariabilePlane(){
	Texture *t = o->getTexture();
	if(o->getTexture()!=NULL){
		char c_planes[255];
		sprintf_s(c_planes, "GLfloat planes%i[] = { %f, %f, %f, %f };",pos,t->getPlanes()[0],t->getPlanes()[1],t->getPlanes()[2],t->getPlanes()[3]);
		string planes(c_planes);

		char c_planet[255];
		sprintf_s(c_planet, "GLfloat planet%i[] = { %f, %f, %f, %f };",pos,t->getPlanet()[0],t->getPlanet()[1],t->getPlanet()[2],t->getPlanet()[3]);
		string planet(c_planet);

		return LINE + planes + LINE + planet;
	}else{
		return "";
	}
}

string GeneratoreCodiceOggetto::getVariabileTexture(){
	if(o->getTexture()!=NULL){
		char s[255];
		sprintf_s(s, "GLuint idTexture%i;",pos);
		string variabile(s);
		return LINE + variabile;
	}else{
		return "";
	}
}

string GeneratoreCodiceOggetto::getCaricamentoTexture(){
	Texture *t = o->getTexture();
	if(o->getTexture()!=NULL){
		char s[1000];
		string nomeFile = t->getNomeFile();
		Utilita::convertiInDoppioSlash(&nomeFile);
		string repeat = "false";
		if(t->isRepeat()){
			repeat = "true";
		}
		string mipmap = "false";
		if(t->isMipMapping()){
			mipmap = "true";
		}
		sprintf_s(s, "idTexture%i = caricaTexture(",pos);
		string istruzione(s);
		return LINE + TAB + istruzione + S_STR + nomeFile + S_STR + COM + repeat + COM + mipmap + I_END;
	}else{
		return "";
	}
}


string GeneratoreCodiceOggetto::getStringaMateriale(){
	char s[255];
	sprintf_s(s, "setMateriale(%i);",o->getIdMateriale());
	return string(s);
}

string GeneratoreCodiceOggetto::getStringaColore(){
	char s[255];
	sprintf_s(s, "setColore(%i);",o->getIdColore());
	return string(s);
}

string GeneratoreCodiceOggetto::getStringaTrasformazioni(){
	char translate[255];
	sprintf_s(translate, "glTranslatef(%f, %f, %f);",o->getPosizione()[0],o->getPosizione()[1],o->getPosizione()[2]);

	char rotate[255];
	sprintf_s(rotate, "glRotatef(%f, 1.0, 0.0, 0.0);\n\t\tglRotatef(%f, 0.0, 1.0, 0.0);\n\t\tglRotatef(%f, 0.0, 0.0, 1.0);",o->getRotazioneX(),o->getRotazioneY(),o->getRotazioneZ());

	char scale[255];
	sprintf_s(scale, "glScalef(%f, %f, %f);",o->getScale()[0],o->getScale()[1],o->getScale()[2]);

	string s;
	s += translate + LINE;
	s += TAB + TAB + rotate + LINE;
	s += TAB + TAB + scale;

	return s;
}

string GeneratoreCodiceOggetto::getStringaOggetto(){
	int tipo = o->getTipo();
	bool wireframe = o->isWireframe();
	if(tipo == CUBO){
		if(wireframe){
			return "glutWireCube(1);";
		}else{
			return "glutSolidCube(1);";
		}
	}
	if(tipo == SFERA){
		if(wireframe){
			return "glutWireSphere(0.5,30,30);";
		}else{
			return "glutSolidSphere(0.5,64,64);";
		}
	}
	if(tipo == TORUS){
		if(wireframe){
			return "glutWireTorus(0.15,0.5,8,38);";
		}else{
			return "glutSolidTorus(0.15,0.5,8,38);";
		}
	}
	if(tipo == TETRA){
		if(wireframe){
			return "glutWireTetrahedron();";
		}else{
			return "glutSolidTetrahedron();";
		}
	}
	if(tipo == CONE){
		if(wireframe){
			return "glutWireCone(0.5,0.5,30,30);";
		}else{
			return "glutSolidCone(0.5,0.5,30,30);";
		}
	}
	if(tipo == ICO){
		if(wireframe){
			return "glutWireIcosahedron();";
		}else{
			return "glutSolidIcosahedron();";
		}
	}
	if(tipo == OCTA){
		if(wireframe){
			return "glutWireOctahedron();";
		}else{
			return "glutSolidOctahedron();";
		}
	}
	if(tipo == TEAPOT){
		if(wireframe){
			return "glutWireTeapot(0.5);";
		}else{
			return "glutSolidTeapot(0.5);";
		}
	}
	if(tipo == DODE){
		if(wireframe){
			return "glScalef(0.5,0.5,0.5);\nglutWireDodecahedron();";
		}else{
			return "glScalef(0.5,0.5,0.5);\nglutSolidDodecahedron();";
		}
	}
	return "";
}

string GeneratoreCodiceOggetto::getBindTexture(){
	char s_var[255];
	sprintf_s(s_var, "idTexture%i",pos);
	string variabile(s_var);

	string mapping = "";
	if(o->getTexture()->getMapping()==GL_OBJECT_LINEAR){
		mapping = "GL_OBJECT_LINEAR";
	}else if(o->getTexture()->getMapping()==GL_EYE_LINEAR){
		mapping = "GL_EYE_LINEAR";
	}else if(o->getTexture()->getMapping()==GL_SPHERE_MAP){
		mapping = "GL_SPHERE_MAP";
	} 

	char s_planes[20];
	sprintf_s(s_planes, "planes%i",pos);
	string planes(s_planes);

	char s_planet[20];
	sprintf_s(s_planet, "planet%i",pos);
	string planet(s_planet);

	string s = TAB + TAB + "// GESTIONE TEXTURE" + LINE;
	s += TAB + TAB + "glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, " + mapping + ");" + LINE;
	s += TAB + TAB + "glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, " + mapping + ");" + LINE;
	s += TAB + TAB + "glTexGenfv(GL_S, GL_OBJECT_PLANE, " + planes + ");" + LINE;
	s += TAB + TAB + "glTexGenfv(GL_T, GL_OBJECT_PLANE, " + planet + ");" + LINE;
	s += TAB + TAB + "glBindTexture(GL_TEXTURE_2D, " + variabile + ");" + LINE;
	return s;
}

string GeneratoreCodiceOggetto::genera(){
	
	string s;

	s += TAB + "glPushMatrix();" + LINE;

	s += TAB + TAB + getStringaMateriale() + LINE;
	s += TAB + TAB + getStringaColore() + LINE;
	if(o->getTexture()!=NULL){
		s += getBindTexture();
	}	
	s += TAB + TAB + "// TRASFORMAZIONI" + LINE;
	s += TAB + TAB + getStringaTrasformazioni() + LINE;
	s += TAB + TAB + "// OGGETTO" + LINE;
	s += TAB + TAB + getStringaOggetto() + LINE;
	s += TAB + "glPopMatrix();" + LINE;


	return s;
}