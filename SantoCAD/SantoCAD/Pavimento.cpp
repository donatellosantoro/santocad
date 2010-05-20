#include "Pavimento.h"	
#include "Logger.h"	

Pavimento::Pavimento(){init();}
Pavimento::~Pavimento(){}

void Pavimento::init(){
	wireframe = 1;
	idColore = 0;
	idMateriale = 19;
	tassellazione = 50;
	abilitato = 1;
}	

void Pavimento::disegna(){
	if(abilitato==0)return;
	glColor3f(1.0,1.0,1.0);
	setMateriale(idMateriale);
	setColore(idColore);

	glPushMatrix();
		glTranslatef(0.0,-0.5,0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		glScalef(20,20,1);

		GLfloat i = 0;
		GLfloat j = 0;
		GLfloat step = (GLfloat)2/tassellazione;

		for(i=-1; i<1; i+=step){
			for(j=1; j>-1; j-=step){
				if(wireframe){
					glBegin(GL_LINE_LOOP);
				}else{
					glBegin(GL_QUADS);
					//Senso antiorario
				}
				
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f(i		,j - step, 0);
				glVertex3f(i + step	,j - step, 0);
				glVertex3f(i + step	, j, 0);
				glVertex3f(i		, j, 0);

				glEnd();
			}
		}
	glPopMatrix();
}