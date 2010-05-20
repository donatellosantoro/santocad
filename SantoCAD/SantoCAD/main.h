#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <stdio.h>
#include <iostream>
#include <cml/cml.h>
#include <string>
#include <time.h>
#include "Logger.h"
#include "Progetto.h"
#include "Texture.h"
#include "Oggetto.h"
#include "DAOProgetto.h"
#include "Utilita.h"
#include "GeneratoreCodiceProgetto.h"

using namespace std;
using namespace cml;

Progetto *progetto;
string cartellaIniziale;
//-------- CAMERA ---------
GLfloat camera_speed = 0.003;
GLfloat camera_pos[] = {0.0, 0.0, 0.0};
GLfloat camera_rotate[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
vector3f pos(0.0, 0.0, 0.0);	// Posizione camera
vector3f at(0.0, 0.0, -0.1);	// Punto in cui "guarda" la camera
vector3f up(0.0, 1.0, 0.0);		// Vettore up...la camera è sempre parallela al piano
vector3f startDir(0.0, 0.0, -0.1);	// Direzione dello sguardo
vector3f dir(0.0, 0.0, -0.1);	// Direzione dello sguardo
vector3f axisX(1.0, 0.0, 0.0);	// Asse Y. Utile nelle rotazioni
vector3f axisY(0.0, 1.0, 0.0);	// Asse Y. Utile nelle rotazioni
vector3f axisZ(0.0, 0.0, 1.0);	// Asse Z. Utile nelle rotazioni
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
GLUI_Panel *panelOggetto_scala;
GLUI_Button *buttonEliminaOggettoSelezionato;
GLUI_StaticText *oggettiNellaScena;
GLUI_Panel *panelTexture;
GLUI_Button *buttonCaricaTexture;
GLUI_Button *buttonCaricaTextureSkybox;
GLUI_Rollout *roll_lights[8];
GLUI_Rotation *spotlight_rot_x[8];
GLUI_Rotation *spotlight_rot_y[8];
GLUI_Rotation *spotlight_rot_z[8];
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
int oggetto_mostraAssiCamera = true;
bool oggetto_texture = true;
GLfloat texture_planes[4];
GLfloat texture_planet[4];
GLUI_Spinner* spinnerplanes[4];
GLUI_Spinner* spinnerplanet[4];
int oggetto_repeat;
int oggetto_mipmapping;
GLUI_Panel *panelSkybox_texture;
GLUI *panelFileTexture;
GLUI *panelFileTextureSkybox;
GLUI_Panel *panelTextureSkybox[6];
GLUI *panelCaricaTextureSkybox;
GLUI_FileBrowser *textureFileBrowserOggetto;
GLUI_FileBrowser *textureFileBrowserSkybox;
GLUI_Spinner *spinnerAltezza;
GLUI_EditText *campoTextureSkybox[6];
GLUI_Checkbox *checkboxIlluminazione;
GLUI_Checkbox *checkboxLuceAbilitata[8];
GLUI_Checkbox *checkboxLuceDisegnaSorgente[8];
GLUI_Listbox *listaTipoLuce[8];
GLUI_Scrollbar *scrollbarRaggio[8];
GLUI_Scrollbar *scrollbarAttenuazione[8];
GLUI_Spinner *spinnerAmbientale[8][3];
GLUI_Spinner *spinnerDiffusa[8][3];
GLUI_Spinner *spinnerSpeculare[8][3];
GLUI_Checkbox *checkboxMostraPavimento;
GLUI_Checkbox *checkboxPavimentoWireframe;
GLUI_Listbox *listaMaterialiPavimento;
GLUI_Spinner *pavimentoTassellazione;
GLUI *panelFileCaricaProgetto;
GLUI *panelFileSalvaProgetto;
GLUI_FileBrowser *progettoFileBrowser;
GLUI_EditText *progettoTextNomeFileSalvare;
char* progettoNomeFileSalvare;
string progettoNomeFileDefault;
GLUI *panelFileCodiceGenerato;
GLUI_EditText *textCartellaCodiceGenerato;
string cartellaCodiceGenerato = "c:\\SantoCAD Projects\\";
GLUI_EditText *textNomeProgettoCodiceGenerato;
string nomeProgettoCodiceGenerato = "Project";


GLUI_Checkbox *checkboxVisualizzaSkybox;
char* ordineTextureSkybox[6] = {"+X : ","-X : ","+Y : ","-Y : ","+Z : ","-Z : "};
char* nomeFileTextureSkybox;
int idTextureSkybox;
//-------- LUCI ---------
GLfloat luci_speed = 0.0005;
GLfloat luci_pos[8][3] = {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}};
GLfloat luci_rotate[8][16] = {{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},
                              {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},
                              {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},
                              {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1},{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}};

#define SCEGLI_TEXTURE_OGGETTO		 200
#define CARICA_TEXTURE_OGGETTO		 201
#define ELIMINA_TEXTURE				 202
#define IMPOSTA_REPEAT				 203
#define IMPOSTA_MIPMAPPING			 204
#define RESET_TEXTURE				 205
#define ANNULLA_CARICA_TEXTURE		 206

#define CARICA_PROGETTO				 301
#define SALVA_PROGETTO				 302
#define CARICA_SCEGLI_FILE_PROGETTO  303
#define SALVA_SCEGLI_FILE_PROGETTO   304
#define CHIUDI_CARICA_PROGETTO       315

#define MOSTRA_TEXTURE_SKYBOX        400
#define APRI_TEXTURE_SKYBOX          401
#define CARICA_TEXTURE_SKYBOX        402
#define CHIUDI_CARICA_SKYBOX         403
#define ANNULLA_CARICA_SKYBOX        404
#define RANDOM_SKYBOX				 405

#define GENERA_CODICE				 501
#define GENERA_CODICE_SCEGLI		 502
#define GENERA_CODICE_CHIUDI	     503

#define PICK_BUFFER_SIZE 512
#define PICK_TOLLERANCE 3

//-------- SKYBOX --------------
#define NUM_SKYBOX 28
char *scenaSkybox[NUM_SKYBOX] =	{"arch","canyon","craterlake","Creek","destroyed","glacier","jungle","lagoon","lunar","mars","mountain","museum","mystic","nvlobby","Park2","rays","redsky","reef","rock","rusted","sahara","sahara_nosun","Simpson","stormy","SwedishRoyalCastle","thunder","Vasa","winter"};

//-------- PROTOTIPI -----------
void setPerspective();
void abilitaDisabilitaComponenti();
void aggiornaSelezione();
void aggiungiOggetto(int tipo);
void cb_scale(int id);
void cb_texture(int id);
void cb_elimina_oggetto(int id);
void cb_light(int id);
char* stringToChar(string stringa);

#endif