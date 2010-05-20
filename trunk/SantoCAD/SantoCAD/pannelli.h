#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <iostream>
#include <cml/cml.h>
#include <string>
#include <time.h>
#include "Logger.h"
#include "Progetto.h"
#include "Texture.h"
#include "Oggetto.h"

using namespace std;
using namespace cml;

Progetto *progetto;
//-------- CAMERA ---------
GLfloat camera_speed = 0.003;
GLfloat camera_pos[] = {0.0, 0.0, 0.0};
GLfloat camera_rotate[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
vector3f pos(0.0, 0.0, 0.0);	// Posizione camera
vector3f at(0.0, 0.0, -0.1);	// Punto in cui "guarda" la camera
vector3f up(0.0, 1.0, 0.0);		// Vettore up...la camera è sempre parallela al piano
vector3f startDir(0.0, 0.0, -0.1);	// Direzione dello sguardo
vector3f dir(0.0, 0.0, -0.1);	// Direzione dello sguardo
vector3f side(1.0, 0.0, 0.0);	// Direzione spostamento laterale
vector3f axisX(1.0, 0.0, 0.0);	// Asse Y. Utile nelle rotazioni
vector3f axisY(0.0, 1.0, 0.0);	// Asse Y. Utile nelle rotazioni
//-------- GUI -----------
GLUI_Rotation *camera_rot;
GLUI_Translation *camera_trans;
GLUI_Rotation *oggetto_rot_x;
GLUI_Rotation *oggetto_rot_y;
GLUI_Rotation *oggetto_rot_z;
GLUI_Spinner *oggetto_scale_x;
GLUI_Spinner *oggetto_scale_y;
GLUI_Spinner *oggetto_scale_z;
GLUI_Checkbox *check_oggetto_wireframe;
GLUI_Checkbox *check_oggetto_mostraSelezione;
GLUI_Listbox *lista_materiali;
GLUI_Listbox *lista_colori;
GLUI_Checkbox *check_oggetto_repeat;
GLUI_Checkbox *check_oggetto_mipmapping;
GLUI_Listbox *lista_mapping;
GLUI_Translation *oggetto_transXZ;
GLUI_Translation *oggetto_transY;
GLUI_Translation *luce_transXZ[8];
GLUI_Translation *luce_transY[8];
GLint windowWidth, windowHeight;
GLUI_Panel *panelOggetto;
GLUI_Button *buttonEliminaOggettoSelezionato;
GLUI_StaticText *oggettiNellaScena;
GLUI_Panel *panelTexture;
GLUI_Button *buttonCaricaTexture;
GLUI_Rollout *roll_lights[8];
//-------- OGGETTO ---------
GLfloat oggetto_speed = 0.0005;
float oggetto_pos[] = {0.0, 0.0, 0.0};
GLfloat oggetto_rotate[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
GLfloat oggetto_scale[3] = {1.0,1.0,1.0};
int oggettoVisualizzaMateriale = 1;
GLint oggetto_colore;
GLint oggetto_materiale;
GLint oggetto_mapping;
Oggetto *oggettoSel;
int oggetto_wireframe = false;
int oggetto_blocca_proporzioni = false;
int oggetto_mostraSelezione = true;
bool oggetto_texture = true;
GLfloat texture_planes[4];
GLfloat texture_planet[4];
GLUI_Spinner* spinnerplanes[4];
GLUI_Spinner* spinnerplanet[4];
int oggetto_repeat;
int oggetto_mipmapping;
GLUI *panelFileTexture;
GLUI_FileBrowser *textureFileBrowser;
//-------- LUCI ---------
GLfloat luci_speed = 0.0005;
GLfloat luci_pos[8][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};

#define SCEGLI_TEXTURE        200
#define CARICA_TEXTURE        201
#define ELIMINA_TEXTURE       202
#define IMPOSTA_REPEAT        203
#define IMPOSTA_MIPMAPPING    204
#define RESET_TEXTURE         205

#define PICK_BUFFER_SIZE 512
#define PICK_TOLLERANCE 3

//-------- PROTOTIPI -----------
void setPerspective();
void abilitaDisabilitaComponenti();
void aggiornaSelezione();
void aggiungiOggetto(int tipo);
void cb_scale(int id);
void cb_visualizzaColoreOMateriale(int id);
void cb_texture(int id);
void cb_elimina_oggetto(int id);
void cb_light(int id);
void creaPannelliGlui(int i);

#endif