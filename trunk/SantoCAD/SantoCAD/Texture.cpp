#include "Texture.h"	
#include "textureUtil.h"	
#include "Logger.h"

Texture::Texture(char* s, bool r, bool m){
	nomeFile = s;
	repeat = r;
	mipmap = m;
	init();
}
Texture::~Texture(){}

void Texture::init(){
	caricaText();
	planes[0] = 0.8f; planes[1] = 0.0f; planes[2] = 0.0f; planes[3] = 0.5f;
	planet[0] = 0.0f; planet[1] = 0.8f; planet[2] = 0.0f; planet[3] = 0.5f;
	mapping = GL_OBJECT_LINEAR;
}

void Texture::caricaText(){
	id = caricaTexture(nomeFile,repeat,mipmap);
}

void Texture::disegna(){
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, mapping);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, mapping);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, planes);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, planet);

	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::fineDisegno(){
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
}

void Texture::reset() {
	planes[0] = 0.8f; planes[1] = 0.0f; planes[2] = 0.0f; planes[3] = 0.5f;
	planet[0] = 0.0f; planet[1] = 0.5f; planet[2] = 0.0f; planet[3] = 0.5f;
	mapping = GL_OBJECT_LINEAR;
	repeat = false;
	mipmap = false;
	id = caricaTexture(nomeFile,repeat,mipmap);
}

void Texture::setPlane(GLfloat s[4],GLfloat t[4]){
	planes[0] = s[0]; planes[1] = s[1]; planes[2] = s[2]; planes[3] = s[3];
	planet[0] = t[0]; planet[1] = t[1]; planet[2] = t[2]; planet[3] = t[3];
}

GLfloat* Texture::getPlanes(){
	return planes;
}

GLfloat* Texture::getPlanet(){
	return planet;
}

void Texture::setMapping(GLint m) {
	mapping = m;
}

GLint Texture::getMapping() {
	return mapping;
}

void Texture::setRepeatMipMap(bool r,bool m) {
	repeat = r;
	mipmap = m;
	id = caricaTexture(nomeFile,repeat,mipmap);
}

bool Texture::isRepeat() {
	return repeat;
}

bool Texture::isMipMapping() {
	return mipmap;
}


char* Texture::getNomeFile(){
	return nomeFile;
}