#include "Skybox.h"
#include "Logger.h"

Skybox::Skybox(string c){
	init(c);
}
Skybox::~Skybox(){}

void Skybox::init(string nomeCartella){
	abilitato = 1;
	posizioneY = 0.5;
	caricaDaCartella(nomeCartella);
	idTexture = caricaTextureCubeMap(texCubeFaces);
}

void Skybox::caricaDaCartella(string nomeCartella){
	texCubeFaces[0] = Utilita::stringToChar(nomeCartella + "positive_x.jpg");
	texCubeFaces[1] = Utilita::stringToChar(nomeCartella + "negative_x.jpg");
	texCubeFaces[2] = Utilita::stringToChar(nomeCartella + "positive_y.jpg");
	texCubeFaces[3] = Utilita::stringToChar(nomeCartella + "negative_y.jpg");
	texCubeFaces[4] = Utilita::stringToChar(nomeCartella + "positive_z.jpg");
	texCubeFaces[5] = Utilita::stringToChar(nomeCartella + "negative_z.jpg");
}

void Skybox::disegnaCubo() {
	GLfloat side = 20.0f;
	setMaterialeDefault();
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslatef(0.0,-posizioneY,0.0);
	glBegin(GL_QUADS);

		// Negative X
		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-side, -side, side);

		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-side, -side, -side);

		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-side, side, -side);

		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-side, side, side);

		//  Postive X
		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(side, -side, -side);

		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(side, -side, side);

		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(side, side, side);

		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(side, side, -side);

		// Negative Z 
		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-side, -side, -side);

		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(side, -side, -side);

		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(side, side, -side);

		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-side, side, -side);

		// Positive Z 
		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(side, -side, side);

		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-side, -side, side);

		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-side, side, side);

		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(side, side, side);

		// Positive Y
		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-side, side, side);

		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-side, side, -side);

		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(side, side, -side);

		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(side, side, side);

		// Negative Y
		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-side, -side, -side);

		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-side, -side, side);

		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(side, -side, side);

		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(side, -side, -side);
	glEnd();
	glPopMatrix();
}

void Skybox::disegna(){
	if(abilitato==0)return;
	glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);

	glEnable(GL_TEXTURE_CUBE_MAP);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);

	disegnaCubo();

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
}

void Skybox::ricaricaTexture() {
	idTexture = caricaTextureCubeMap(texCubeFaces);
}

void Skybox::setTexture(int i,char* nomeFile) {
	texCubeFaces[i] = nomeFile;
}

char* Skybox::getTexture(int i) {
	return texCubeFaces[i];
}