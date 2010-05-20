#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class Texture{

private:
	char* nomeFile;
	GLuint id;
	void init();
	void caricaText();
	GLfloat planes[4];
	GLfloat planet[4];
	GLint mapping;
	bool repeat;
	bool mipmap;

public:
	Texture(char* s, bool r, bool m);
	~Texture();
	void disegna();
	void fineDisegno();
	void reset();
	void setPlane(GLfloat s[4],GLfloat t[4]);
	GLfloat* getPlanes();
	GLfloat* getPlanet();
	void setMapping(GLint m);
	GLint getMapping();
	void setRepeatMipMap(bool r,bool m);
	bool isRepeat();
	bool isMipMapping();
	char* getNomeFile(); 
};

#endif