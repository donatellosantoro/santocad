#include "Oggetto.h"	
#include "Logger.h"	

Oggetto::Oggetto(int t):tipo(t){init();}
Oggetto::~Oggetto(){}

void Oggetto::init(){
	posizione = vector3f(0.0,0.0,0.0);
	scale = vector3f(1.0,1.0,1.0);
	rotazioneX = 0.0;
	rotazioneY = 0.0;
	rotazioneZ = 0.0;
	wireframe = false;
	selezionato = false;
	mostraSelezione = true;
	texture = NULL;
	idColore = rand() % getNumeroColori();
	idMateriale = rand() % (getNumeroMateriali() - 1);
}

int Oggetto::getTipo(){
	return tipo;
}

void Oggetto::disegna(GLenum mode, int id){
	glPushMatrix();
		if(mode == GL_SELECT) glPushName(id);

		setMateriale(idMateriale);
		setColore(idColore);
		
		if(texture!=NULL)texture->disegna();
		
		glTranslatef(posizione[0], posizione[1], posizione[2]);
		glRotatef(rotazioneX, 1.0, 0.0, 0.0);
		glRotatef(rotazioneY, 0.0, 1.0, 0.0);
		glRotatef(rotazioneZ, 0.0, 0.0, 1.0);
		glScalef(scale[0],scale[1],scale[2]);

		if(tipo == CUBO){(wireframe) ? glutWireCube(1) : glutSolidCube(1);}
		if(tipo == SFERA){(wireframe) ? glutWireSphere(0.5,30,30) : glutSolidSphere(0.5,64,64);}
		if(tipo == TORUS){(wireframe) ? glutWireTorus(0.15,0.5,8,38) : glutSolidTorus(0.15,0.5,8,38);}
		if(tipo == TETRA){(wireframe) ? glutWireTetrahedron() : glutSolidTetrahedron();}
		if(tipo == CONE){(wireframe) ? glutWireCone(0.5,0.5,30,30) : glutSolidCone(0.5,0.5,30,30);}
		if(tipo == ICO){(wireframe) ? glutWireIcosahedron() : glutSolidIcosahedron();}
		if(tipo == OCTA){(wireframe) ? glutWireOctahedron() : glutSolidOctahedron();}
		if(tipo == TEAPOT){(wireframe) ? glutWireTeapot(0.5) : glutSolidTeapot(0.5);}
		if(tipo == DODE){
			glScalef(0.5,0.5,0.5);
			(wireframe) ? glutWireDodecahedron() : glutSolidDodecahedron();
		}
		if(mode == GL_SELECT) glPopName();
		if(texture!=NULL)texture->fineDisegno();
		if(selezionato) {
			evidenzia();
		}

		if((selezionato) && (mostraSelezione)) {
			disegnaAssi();
		}
	glPopMatrix();
}

void Oggetto::evidenzia(){
	if (mostraSelezione) {
		GLboolean luceAbilitata = glIsEnabled(GL_LIGHTING);
		if(luceAbilitata)glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(1.0,0.0,0.0);
			glScalef(1.01,1.01,1.01);
			if(tipo == CUBO){glutWireCube(1);}
			if(tipo == SFERA){ glutWireSphere(0.5,16,16);}
			if(tipo == TORUS){glutWireTorus(0.15,0.5,8,38);}
			if(tipo == TETRA){glutWireTetrahedron();}
			if(tipo == CONE){glutWireCone(0.5,0.5,30,30);}
			if(tipo == ICO){glutWireIcosahedron();}
			if(tipo == OCTA){glutWireOctahedron();}
			if(tipo == TEAPOT){glutWireTeapot(0.5);}
			if(tipo == DODE){glutWireDodecahedron();}
		glPopMatrix();
		if(luceAbilitata)glEnable(GL_LIGHTING);
	}
}

void Oggetto::disegnaAssi() {
	GLboolean luceAbilitata = glIsEnabled(GL_LIGHTING);
	if(luceAbilitata)glDisable(GL_LIGHTING);

	glPushMatrix();
		glBegin( GL_LINES );
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex3f( 0.80, 0.05, 0.0 );  glVertex3f( 1.0, 0.25, 0.0 ); /* Lettera X */
		glVertex3f( 0.8, 0.25, 0.0 );  glVertex3f( 1.0, 0.05, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.75, 0.0, 0.0 ); /* Asse X       */

		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0.05, 0.75, 0.0 );  glVertex3f( 0.05, 0.85, 0.0 ); /* Lettera Y */
		glVertex3f( 0.05, 0.85, 0.0 );  glVertex3f( -0.05, 1.0, 0.0 );
		glVertex3f( 0.05, 0.85, 0.0 );  glVertex3f( 0.15, 1.0, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.75, 0.0 ); /* Y axis      */

		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( -0.05, -0.05, 0.75 );  glVertex3f( 0.05, -0.05, 0.75 ); /* Lettera Z */
		glVertex3f( 0.05, -0.05, 0.75 );  glVertex3f( -0.05, -0.20, 0.75 );
		glVertex3f( -0.05, -0.20, 0.75 );  glVertex3f( 0.05, -0.20, 0.75 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 0.75 ); /* Z axis    */
		glEnd();
	glPopMatrix();

	if(luceAbilitata)glEnable(GL_LIGHTING);
}

vector3f Oggetto::getPosizione(){
	return posizione;
}

void Oggetto::setPosizione(vector3f v){
	posizione = v;
}

vector3f Oggetto::getScale(){
	return scale;
}

void Oggetto::setScale(vector3f v){
	scale = v;
}

void Oggetto::setRotazione(GLfloat x,GLfloat y,GLfloat z){
	rotazioneX = x;
	rotazioneY = y;
	rotazioneZ = z;
}

float Oggetto::getRotazioneX(){
	return rotazioneX;
}

float Oggetto::getRotazioneY(){
	return rotazioneY;
}

float Oggetto::getRotazioneZ(){
	return rotazioneZ;
}

void Oggetto::setWireframe(bool b){
	wireframe = b;
}

bool Oggetto::isWireframe(){
	return wireframe;
}

void Oggetto::setMostraSelezione(bool b) {
	mostraSelezione = b;
}

bool Oggetto::isMostraSelezione() {
	return mostraSelezione;
}

void Oggetto::setIdColore(int c){
	idColore = c; 
}

int Oggetto::getIdColore(){
	return idColore;
}

void Oggetto::setIdMateriale(int m){
	idMateriale = m; 
}

int Oggetto::getIdMateriale(){
	return idMateriale;
}

void Oggetto::setSelezionato(bool b){
	selezionato = b;
}

void Oggetto::setTexture(Texture* t){
	texture = t;
}

Texture* Oggetto::getTexture(){
	return texture;
}