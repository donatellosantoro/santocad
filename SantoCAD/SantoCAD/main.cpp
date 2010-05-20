#include "main.h"
#include "materiali.h"

//--------- AZIONI ------
void aggiungiOggetto(int tipo){
	Oggetto *o = new Oggetto(tipo);
	o->setPosizione(at + dir*20);
	o->setRotazione(0.0,-camera_rot->getAngleY(),0.0);
	progetto->addOggetto(*o);
	if(oggettoSel!=NULL)oggettoSel->setSelezionato(false);
	oggettoSel = progetto->getOggetto(progetto->getNumeroOggetti()-1);
	aggiornaSelezione();
}

void abilitaDisabilitaComponenti() {
	// Oggetti nella scena
	if (progetto->getSkybox()->abilitato) {
		panelSkybox_texture->enable();
	} else {
		panelSkybox_texture->disable();
	}

	if (oggettoSel == NULL) {
		panelOggetto->disable();
		panelOggetto_scala->disable();
		panelTexture->disable();
		buttonEliminaOggettoSelezionato->disable();
		check_oggetto_wireframe->disable();
		check_oggetto_mostraSelezione->disable();
	} else {
		panelOggetto->enable();
		panelOggetto_scala->enable();
		buttonEliminaOggettoSelezionato->enable();
		check_oggetto_wireframe->enable();
		check_oggetto_mostraSelezione->enable();
		if(progetto->illuminazioneAbilitata==1){
			lista_colori->disable();
			lista_materiali->enable();
		} else {
			lista_colori->enable();
			lista_materiali->disable();
		}

		Texture* t = oggettoSel->getTexture();
		if(t == NULL){
			if (panelTexture->enabled) {
				panelTexture->disable();
			}
		} else {
			panelTexture->enable();
		}
		
		buttonCaricaTexture->enable();
	}

	// Luci
	for(int i=0;i<7;i++) {
		if (progetto->getLuce(i)->tipo == Luce::SPOTLIGHT) {
			scrollbarRaggio[i]->enable();
			scrollbarAttenuazione[i]->enable();
		} else {
			scrollbarRaggio[i]->disable();
			scrollbarAttenuazione[i]->disable();
		}
	}
}

void aggiornaSelezione(){
	oggettoSel->setSelezionato(true);
	oggetto_rot_x->setAngleX(oggettoSel->getRotazioneX());
	oggetto_rot_y->setAngleY(oggettoSel->getRotazioneY());
	oggetto_rot_z->setAngleY(oggettoSel->getRotazioneZ());
	oggetto_scale_x->set_float_val(oggettoSel->getScale()[0]);
	oggetto_scale_y->set_float_val(oggettoSel->getScale()[1]);
	oggetto_scale_z->set_float_val(oggettoSel->getScale()[2]);
	oggetto_wireframe = oggettoSel->isWireframe();
	check_oggetto_wireframe->set_int_val(oggetto_wireframe);
	oggetto_mostraSelezione = oggettoSel->isMostraSelezione();
	check_oggetto_mostraSelezione->set_int_val(oggetto_mostraSelezione);
	lista_colori->set_int_val(oggettoSel->getIdColore());
	lista_materiali->set_int_val(oggettoSel->getIdMateriale());
	Texture* t = oggettoSel->getTexture();
	if(t!=NULL){
		oggetto_mapping = t->getMapping();
		lista_mapping->set_int_val(oggetto_mapping);
		oggetto_repeat = t->isRepeat();
		check_oggetto_repeat->set_int_val(oggetto_repeat);
		oggetto_mipmapping = t->isMipMapping();
		check_oggetto_mipmapping->set_int_val(oggetto_mipmapping);
		for(int i=0;i<4;i++){
			spinnerplanes[i]->set_float_val(t->getPlanes()[i]);
			spinnerplanet[i]->set_float_val(t->getPlanet()[i]);
		}
	}
}

void aggiornaTextureSkybox(){
	for(int i=0;i<6;i++) {
		nomeFileTextureSkybox = progetto->getSkybox()->getTexture(i);
		campoTextureSkybox[i]->set_text(nomeFileTextureSkybox);
	}
	checkboxVisualizzaSkybox->set_int_val(progetto->getSkybox()->abilitato);
	spinnerAltezza->set_float_val(progetto->getSkybox()->posizioneY);
}

void aggiornaComponentiVista(){
	// Aggiorno le luci
	checkboxIlluminazione->set_int_val(progetto->illuminazioneAbilitata);
	cb_light(0);
	for(int i=0;i<=7;i++){
		checkboxLuceAbilitata[i]->set_int_val(progetto->getLuce(i)->abilitata);
		checkboxLuceDisegnaSorgente[i]->set_int_val(progetto->getLuce(i)->disegnaSorgente);
		listaTipoLuce[i]->set_int_val(progetto->getLuce(i)->tipo);
		scrollbarRaggio[i]->set_int_val(progetto->getLuce(i)->valoreRaggio);
		scrollbarAttenuazione[i]->set_int_val(progetto->getLuce(i)->valoreAttenuazione);
		spinnerAmbientale[i][0]->set_int_val(progetto->getLuce(i)->getAmbientale()[0]);
		spinnerAmbientale[i][1]->set_int_val(progetto->getLuce(i)->getAmbientale()[1]);
		spinnerAmbientale[i][2]->set_int_val(progetto->getLuce(i)->getAmbientale()[2]);
		spinnerDiffusa[i][0]->set_int_val(progetto->getLuce(i)->getDiffusa()[0]);
		spinnerDiffusa[i][1]->set_int_val(progetto->getLuce(i)->getDiffusa()[1]);
		spinnerDiffusa[i][2]->set_int_val(progetto->getLuce(i)->getDiffusa()[2]);
		spinnerSpeculare[i][0]->set_int_val(progetto->getLuce(i)->getSpeculare()[0]);
		spinnerSpeculare[i][1]->set_int_val(progetto->getLuce(i)->getSpeculare()[1]);
		spinnerSpeculare[i][2]->set_int_val(progetto->getLuce(i)->getSpeculare()[2]);
		spotlight_rot_x[i]->setAngleX(progetto->getLuce(i)->getRotazioneSpotlightX() * 180 / M_PI);
		spotlight_rot_y[i]->setAngleY(progetto->getLuce(i)->getRotazioneSpotlightY() * 180 / M_PI);
		spotlight_rot_z[i]->setAngleY(progetto->getLuce(i)->getRotazioneSpotlightZ() * 180 / M_PI);
	}
	// Aggiorno pavimento
	checkboxMostraPavimento->set_int_val(progetto->getPavimento()->abilitato);
	checkboxPavimentoWireframe->set_int_val(progetto->getPavimento()->wireframe);
	listaMaterialiPavimento->set_int_val(progetto->getPavimento()->idMateriale);
	pavimentoTassellazione->set_int_val(progetto->getPavimento()->tassellazione);
}
//--------- CALLBACK -----

void disegnaAssi() {
	GLboolean luceAbilitata = glIsEnabled(GL_LIGHTING);
	if(luceAbilitata)glDisable(GL_LIGHTING);

	glPushMatrix();
		glTranslatef(0.7,-0.8,-1.0);
		glRotatef(camera_rot->getAngleY(),0.0,1.0,0.0);
		glScalef(0.2,0.2,0.2);
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

void disegna(GLenum mode){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (oggetto_mostraAssiCamera) {
		disegnaAssi();
	}
	gluLookAt(pos[0], pos[1], pos[2], 
			  at[0], at[1], at[2], 
			  up[0], up[1], up[2]);

	progetto->disegna(mode);
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	disegna(GL_RENDER);
	glFlush(); 
	glutSwapBuffers();
}

void cb_scale(int id){
	if(oggetto_blocca_proporzioni){
		float nuovoValore = oggetto_scale[id];
		oggetto_scale[0] = nuovoValore;
		oggetto_scale[1] = nuovoValore;
		oggetto_scale[2] = nuovoValore;
		oggetto_scale_x->set_float_val(nuovoValore);
		oggetto_scale_y->set_float_val(nuovoValore);
		oggetto_scale_z->set_float_val(nuovoValore);
	}
}

void cb_texture(int id){
	if(oggettoSel==NULL)return;
	if(id == SCEGLI_TEXTURE_OGGETTO){
		panelFileTexture->show();
		return;
	}
	if(id == CARICA_TEXTURE_OGGETTO){
		string cartellaCorrente = Utilita::getCartellaCorrente();
		string nomeFile = textureFileBrowserOggetto->get_file();
		char* file = Utilita::stringToChar(cartellaCorrente + "\\" + nomeFile);

		Texture *t = new Texture(file,oggetto_repeat==1,oggetto_mipmapping==1);
		Texture *oldTexture = oggettoSel->getTexture();
		if (oldTexture != NULL) {
			t->setPlane(oldTexture->getPlanes(),oldTexture->getPlanet());
			t->setMapping(oldTexture->getMapping());
			t->setRepeatMipMap(oldTexture->isRepeat(),oldTexture->isMipMapping());
		}

		if(oggettoSel->getTexture()==NULL)oggettoSel->setIdMateriale(20);//Setto come materiale quello di default
		if(oggettoSel->getTexture()==NULL)oggettoSel->setIdColore(7);//Setto come colore quello di default
		oggettoSel->setTexture(t);
		//aggiornaSelezione();
		panelFileTexture->hide();
	}
	if(id == ELIMINA_TEXTURE){
		oggettoSel->setTexture(NULL);
		aggiornaSelezione();
		return;
	}

	if((id == IMPOSTA_REPEAT) && (oggettoSel->getTexture())){
		oggettoSel->getTexture()->setRepeatMipMap(oggetto_repeat==1,oggetto_mipmapping==1);
	}
	if((id == IMPOSTA_MIPMAPPING) && (oggettoSel->getTexture())){
		oggettoSel->getTexture()->setRepeatMipMap(oggetto_repeat==1,oggetto_mipmapping==1);
	}
	if((id == RESET_TEXTURE) && (oggettoSel->getTexture())){
		oggettoSel->getTexture()->reset();
	}
	if (id == ANNULLA_CARICA_TEXTURE) {
		panelFileTexture->hide();
		return;
	}
	aggiornaSelezione();
}

void cb_texture_skybox(int id) {
	if(id == MOSTRA_TEXTURE_SKYBOX){
		abilitaDisabilitaComponenti();
		return;
	}
	if(id == APRI_TEXTURE_SKYBOX){
		panelCaricaTextureSkybox->show();
		aggiornaTextureSkybox();
		return;
	}
	if(id == CARICA_TEXTURE_SKYBOX){
		string cartellaCorrente = Utilita::getCartellaCorrente();
		string nomeFile = textureFileBrowserSkybox->get_file();
		char* fileSkybox = Utilita::stringToChar(cartellaCorrente + "\\" + nomeFile);
		progetto->getSkybox()->setTexture(idTextureSkybox,fileSkybox);
		panelFileTextureSkybox->hide();
		aggiornaTextureSkybox();
		return;
	}
	if(id == CHIUDI_CARICA_SKYBOX) {
		panelCaricaTextureSkybox->hide();
		progetto->getSkybox()->ricaricaTexture();
		progetto->getSkybox()->disegna();
		return;
	}
	if(id == ANNULLA_CARICA_SKYBOX) {
		panelFileTextureSkybox->hide();
		return;
	}
	if(id == RANDOM_SKYBOX){
		string cartellaSkybox = cartellaIniziale + "Texture\\skybox\\" + scenaSkybox[(rand() % (NUM_SKYBOX - 1))] + "\\";
		progetto->getSkybox()->caricaDaCartella(cartellaSkybox);
		progetto->getSkybox()->ricaricaTexture();
		progetto->getSkybox()->disegna();
		return;
	}
	panelFileTextureSkybox->show();
	idTextureSkybox = id;
}

void cb_elimina_oggetto(int id) {
	if(oggettoSel==NULL)return;
	progetto->removeOggetto(oggettoSel);
	oggettoSel = NULL;
	panelOggetto->disable();
	panelTexture->disable();
}

void cb_light(int id){
	if(progetto->illuminazioneAbilitata==1){
		glEnable(GL_LIGHTING);
		for(int i=0;i<=7;i++){
			roll_lights[i]->enable();
		}
	}else{
		glDisable(GL_LIGHTING);
		for(int i=0;i<=7;i++){
			roll_lights[i]->disable();
		}
	}
	glutPostRedisplay();
}

void cb_genera_codice(int id){
	if(id==GENERA_CODICE){	
		GeneratoreCodiceProgetto *generatoreCodice = new GeneratoreCodiceProgetto(progetto,cartellaIniziale);
		generatoreCodice->setCamera(pos,at,dir);
		generatoreCodice->genera(cartellaCodiceGenerato,nomeProgettoCodiceGenerato);
		panelFileCodiceGenerato->hide();
	}else if(id==GENERA_CODICE_SCEGLI){
		panelFileCodiceGenerato->show();
	}else if(id==GENERA_CODICE_CHIUDI){
		panelFileCodiceGenerato->hide();
	}
}

void cb_dao_progetto(int id){
	oggettoSel = NULL;
	abilitaDisabilitaComponenti();
	if(id==CARICA_PROGETTO){
		panelFileCaricaProgetto->hide();
		string cartellaCorrente = Utilita::getCartellaCorrente();
		string nomeFile = progettoFileBrowser->get_file();
		progettoNomeFileDefault = cartellaCorrente + "\\" + nomeFile;
		char* file = Utilita::stringToChar(progettoNomeFileDefault);
		DAOProgetto::carica(progetto,file,cartellaIniziale);
		aggiornaComponentiVista();
		aggiornaTextureSkybox();
		progetto->getSkybox()->ricaricaTexture();
		progetto->getSkybox()->disegna();
		string titolo = "SantoCAD - " + nomeFile;
		glutSetWindowTitle(Utilita::stringToChar(titolo));
	}
	if(id==SALVA_PROGETTO){
		const char* file = progettoTextNomeFileSalvare->get_text();
		DAOProgetto::salva(progetto,file,cartellaIniziale);
		panelFileSalvaProgetto->hide();
		progettoFileBrowser->fbreaddir(".");
		string nomeFile(file);
		int index = nomeFile.find_last_of("\\");
		string nomePulito = nomeFile.substr(index + 1,nomeFile.length() - index + 1);
		string titolo = "SantoCAD - " + nomePulito;
		glutSetWindowTitle(Utilita::stringToChar(titolo));
	}
	if(id==CARICA_SCEGLI_FILE_PROGETTO){
		panelFileCaricaProgetto->show();
	}
	if(id==SALVA_SCEGLI_FILE_PROGETTO){
		int lunghezzaStringaNomeFileSalvare = ((string)progettoTextNomeFileSalvare->get_text()).length();
		if (lunghezzaStringaNomeFileSalvare == 0) {
			progettoTextNomeFileSalvare->set_text(progettoNomeFileDefault);
		}
		panelFileSalvaProgetto->show();
	}
	if(id==CHIUDI_CARICA_PROGETTO){
		panelFileCaricaProgetto->hide();
		panelFileSalvaProgetto->hide();
	}
}

void myIdle(){
	// ------- GESTIONE CAMERA ---------
	vector3f movimento_camera(camera_pos[0],0.0,camera_pos[1]);
	movimento_camera = rotate_vector(movimento_camera,axisY,camera_rot->getAngleRadiansY());

	float tmpPos0 = pos[0] + movimento_camera[0];
	float tmpPos2 = pos[2] - movimento_camera[2];
	if (((tmpPos0 >= 9.5) || (tmpPos0 <= -9.5)) ||
	    ((tmpPos2 >= 9.5) || (tmpPos2 <= -9.5))) {
		movimento_camera[0] = 0.0;
		movimento_camera[2] = 0.0;
	} else {
		pos[0] += movimento_camera[0];
		pos[2] -= movimento_camera[2];
	}

	camera_trans->set_x(0.0);
	camera_trans->set_y(0.0);

	dir = rotate_vector(startDir,axisY,-camera_rot->getAngleRadiansY());
	at = pos + dir;

	char stringaOggettiNellaScena[30];
	strcpy_s (stringaOggettiNellaScena,sizeof(stringaOggettiNellaScena),"Objects in scene : ");
	strcat_s (stringaOggettiNellaScena,sizeof(stringaOggettiNellaScena),progetto->getRiepilogo());
	oggettiNellaScena->set_text(stringaOggettiNellaScena);

	// -------- GESTIONE OGGETTO ---------
	if(oggettoSel != NULL){
		oggettoSel->setWireframe(oggetto_wireframe==1);
		oggettoSel->setMostraSelezione(oggetto_mostraSelezione==1);
		// Movimento
		vector3f movimento_oggetto(oggetto_pos[0],oggetto_pos[2],oggetto_pos[1]);
		movimento_oggetto = rotate_vector(movimento_oggetto,axisY,camera_rot->getAngleRadiansY());

		vector3f vecchiaPosizione = oggettoSel->getPosizione();
		vector3f nuovaPosizione(vecchiaPosizione[0] + movimento_oggetto[0],vecchiaPosizione[1] + movimento_oggetto[1],vecchiaPosizione[2] - movimento_oggetto[2]);
		oggettoSel->setPosizione(nuovaPosizione);
		
		oggetto_transXZ->set_x(0.0);
		oggetto_transXZ->set_y(0.0);
		oggetto_transY->set_y(0.0);

		// Rotazione
		GLfloat rotazioneX = oggetto_rot_x->getAngleX();
		GLfloat rotazioneY = oggetto_rot_y->getAngleY();
		GLfloat rotazioneZ = oggetto_rot_z->getAngleY();
		oggettoSel->setRotazione(rotazioneX,rotazioneY,rotazioneZ);

		// Scale
		vector3f scale_oggetto(oggetto_scale[0],oggetto_scale[1],oggetto_scale[2]);
		oggettoSel->setScale(scale_oggetto);

		// Colore e Materiale
		oggettoSel->setIdColore(oggetto_colore);
		oggettoSel->setIdMateriale(oggetto_materiale);

		// Texture
		Texture* t = oggettoSel->getTexture();
		if(t!=NULL){
			t->setPlane(texture_planes,texture_planet);
			t->setMapping(oggetto_mapping);
		}
	}

	// -------- GESTIONE LUCI ---------
	for(int i=0;i<=7;i++){
		vector3f movimento_luci(luci_pos[i][0],luci_pos[i][2],luci_pos[i][1]);
		movimento_luci = rotate_vector(movimento_luci,axisY,camera_rot->getAngleRadiansY());

		vector3f vecchiaPosizione = progetto->getLuce(i)->getPosizione();
		vector3f nuovaPosizione(vecchiaPosizione[0] + movimento_luci[0],vecchiaPosizione[1] + movimento_luci[1],vecchiaPosizione[2] - movimento_luci[2]);
		progetto->getLuce(i)->setPosizione(nuovaPosizione);
		
		luce_transXZ[i]->set_x(0.0);
		luce_transXZ[i]->set_y(0.0);
		luce_transY[i]->set_x(0.0);
		luce_transY[i]->set_y(0.0);
				
		// Rotazione
		GLfloat rotazioneX = spotlight_rot_x[i]->getAngleRadiansX();
		GLfloat rotazioneY = spotlight_rot_y[i]->getAngleRadiansY();
		GLfloat rotazioneZ = spotlight_rot_z[i]->getAngleRadiansY();
		progetto->getLuce(i)->setRotazioneSpotlight(rotazioneX,rotazioneY,rotazioneZ);
	}

	abilitaDisabilitaComponenti();
	glutPostRedisplay();
}

//---------------PICKING------------------------------
void processHits (GLint hits, GLuint buffer[]){
	GLint i, numberOfNames = 0;
	GLuint names, *ptr, minZ,*ptrNames;

	ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	for (i = 0; i < hits; i++) {	
		names = *ptr;
		ptr++;
		if (*ptr < minZ) {
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr+2;
		}

		ptr += names+2;
	}
	if (numberOfNames > 0) {
		ptr = ptrNames;
		GLint idOggettoSelezionato = *ptr;
		if(oggettoSel!=NULL)oggettoSel->setSelezionato(false);
		oggettoSel = progetto->getOggetto(idOggettoSelezionato);
		aggiornaSelezione();
	}else{
		if(oggettoSel!=NULL)oggettoSel->setSelezionato(false);
		oggettoSel = NULL;
	}
}

void mousePick(int button, int state, int x, int y){
	int mod = glutGetModifiers();
	GLuint selectBuf[PICK_BUFFER_SIZE];
	GLint hits;
	GLint viewport[4];
	if ((button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) && state == GLUT_DOWN){
		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer(PICK_BUFFER_SIZE, selectBuf);
		glRenderMode(GL_SELECT);

		glInitNames();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluPickMatrix ((GLdouble) x, (GLdouble)(viewport[3] - y), PICK_TOLLERANCE, PICK_TOLLERANCE, viewport);
			setPerspective();
			disegna(GL_SELECT);
			glMatrixMode(GL_PROJECTION);
		glPopMatrix ();
		glFlush();

		hits = glRenderMode(GL_RENDER);
		processHits (hits, selectBuf);
		glutPostRedisplay();
	}
}

//---------------INIT APPLICAZIONE---------------------
void setPerspective(){
	gluPerspective(90.0, (float)windowWidth / (float)windowHeight, 0.1, 1000.0);
}

void myReshape(int w, int h){
	windowWidth = w;
	windowHeight = h;	

	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective();
}

void init(){	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);

	oggettoSel = NULL;
	cb_light(-1);
}

void centraFinestra(int windowWidth, int windowHeight){
	int desktopWidth = glutGet(GLUT_SCREEN_WIDTH);
	int desktopHeight = glutGet(GLUT_SCREEN_HEIGHT);

	int left = (desktopWidth-windowWidth)/2;
	int top = (desktopHeight-windowHeight)/2;

	glutInitWindowPosition(left,top);
	glutInitWindowSize(windowWidth,windowHeight);
}


void creaPannelliGlui(int mainWindow){
	int window_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
	int window_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);
	int window_size_h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
	int window_size_w = glutGet((GLenum)GLUT_WINDOW_WIDTH);

	// Pannello sinistra
	GLUI *panelScena = GLUI_Master.create_glui("Panel Scene",0,window_pos_x - 180, window_pos_y);
	panelScena->set_main_gfx_window(mainWindow);

	new GLUI_Checkbox(panelScena, "Show Camera Axis", &oggetto_mostraAssiCamera );

	GLUI_Panel *panelScena_camera = new GLUI_Panel( panelScena, "Camera", GLUI_PANEL_NONE);
	camera_trans = new GLUI_Translation(panelScena_camera, "Camera Position", GLUI_TRANSLATION_XY, camera_pos );
	camera_trans->set_speed(camera_speed);

	new GLUI_Column(panelScena_camera,true);
	camera_rot = new GLUI_Rotation(panelScena_camera, "Camera Rotation", camera_rotate );
	camera_rot->set_spin(1.0);
	camera_rot->setConstraintX(true);

	GLUI_Rollout *roll_Project = new GLUI_Rollout(panelScena, "Project", true );
	new GLUI_StaticText(roll_Project, "");
	new GLUI_Button(roll_Project, "Save Project", SALVA_SCEGLI_FILE_PROGETTO, cb_dao_progetto );
	new GLUI_Button(roll_Project, "Load Project", CARICA_SCEGLI_FILE_PROGETTO, cb_dao_progetto );
	new GLUI_Button(roll_Project, "Generate Code!", GENERA_CODICE_SCEGLI, cb_genera_codice );
	new GLUI_StaticText(roll_Project, "");

	GLUI_Rollout *panelScena_buttonForme = new GLUI_Rollout(panelScena, "Forms", false );
	new GLUI_StaticText(panelScena_buttonForme, "");
	new GLUI_Button(panelScena_buttonForme, "Cube", CUBO, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Sphere", SFERA, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Torus", TORUS, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Tetrahedron", TETRA, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Teapot", TEAPOT, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Cone", CONE, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Dodecahedron", DODE, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Icosahedron", ICO, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Octahedron", OCTA, aggiungiOggetto);
	new GLUI_StaticText(panelScena_buttonForme, "");
	buttonEliminaOggettoSelezionato = new GLUI_Button(panelScena_buttonForme, "Delete object", 0, cb_elimina_oggetto );

	// Pavimento
	GLUI_Rollout *panel_pavimento = new GLUI_Rollout(panelScena, "Floor", false );
	checkboxMostraPavimento = new GLUI_Checkbox(panel_pavimento, "Show Floor", &(progetto->getPavimento()->abilitato) );
	checkboxPavimentoWireframe = new GLUI_Checkbox(panel_pavimento, "Show Wireframe Floor", &(progetto->getPavimento()->wireframe) );		
	listaMaterialiPavimento = new GLUI_Listbox(panel_pavimento, "Material:", &(progetto->getPavimento()->idMateriale) );
	for(int i=0; i<getNumeroMateriali(); i++ ){
		listaMaterialiPavimento->add_item( i, getNomeMateriale(i) );
	}
	listaMaterialiPavimento->set_int_val(progetto->getPavimento()->idMateriale);
	pavimentoTassellazione = new GLUI_Spinner(panel_pavimento, "Tessellation: ", &(progetto->getPavimento()->tassellazione));
	pavimentoTassellazione->set_int_limits(10, 1000 );

	// Skybox
	GLUI_Rollout *panel_skybox = new GLUI_Rollout(panelScena, "Skybox", false );
	checkboxVisualizzaSkybox = new GLUI_Checkbox(panel_skybox, "Show Skybox", &(progetto->getSkybox()->abilitato));		
	panelSkybox_texture = new GLUI_Panel(panel_skybox, "", GLUI_PANEL_RAISED);
	//new GLUI_StaticText(panelSkybox_texture, "");
	buttonCaricaTextureSkybox = new GLUI_Button(panelSkybox_texture, "Load Textures", APRI_TEXTURE_SKYBOX, cb_texture_skybox );
	panelScena->add_separator_to_panel(panelSkybox_texture);
	buttonCaricaTextureSkybox = new GLUI_Button(panelSkybox_texture, "Random Skybox", RANDOM_SKYBOX, cb_texture_skybox );
	new GLUI_Column(panelSkybox_texture,false);
	//new GLUI_StaticText(panelSkybox_texture, "");
	GLUI_StaticText *regolaSkybox = new GLUI_StaticText(panelSkybox_texture, "Height: ");
	spinnerAltezza = new GLUI_Spinner(panelSkybox_texture,"", &(progetto->getSkybox()->posizioneY));
	spinnerAltezza->set_int_limits(-15,15);
	spinnerAltezza->set_speed(0.5);
	spinnerAltezza->edittext->set_w(-1);
	spinnerAltezza->edittext->text_x_offset=0;


	// Riepilogo oggetti nella scena
	GLUI_Panel *panelScena_riepilogo = new GLUI_Panel(panelScena, "", GLUI_PANEL_NONE);
	oggettiNellaScena = new GLUI_StaticText(panelScena_riepilogo, "");

	// Pannello destra
	GLUI *panelComandiOggetto = GLUI_Master.create_glui("Object Properties", 0, window_pos_x + window_size_w + 20, window_pos_y);
	panelComandiOggetto->set_main_gfx_window(mainWindow);

	
	panelOggetto = new GLUI_Panel( panelComandiOggetto, "Object" ,GLUI_PANEL_NONE);
	GLUI_Panel *panelOggetto_posizione = new GLUI_Panel(panelOggetto, "Position");
	oggetto_transXZ = new GLUI_Translation(panelOggetto_posizione, "X-Z", GLUI_TRANSLATION_XY, oggetto_pos );
	oggetto_transXZ->set_speed(oggetto_speed);

	new GLUI_Column(panelOggetto_posizione,false);
	oggetto_transY = new GLUI_Translation(panelOggetto_posizione, "Y", GLUI_TRANSLATION_Y, &oggetto_pos[2] );
	oggetto_transY->set_speed(oggetto_speed);

	new GLUI_Column(panelOggetto_posizione,false);
	check_oggetto_wireframe = new GLUI_Checkbox(panelOggetto_posizione, "Show Wireframe", &oggetto_wireframe );
	check_oggetto_mostraSelezione = new GLUI_Checkbox(panelOggetto_posizione, "Show Selection", &oggetto_mostraSelezione );

	GLUI_Panel *panelOggetto_rotazioneX = new GLUI_Panel(panelOggetto, "Rotation");
	oggetto_rot_x = new GLUI_Rotation(panelOggetto_rotazioneX, "X", oggetto_rotate );
	oggetto_rot_x->set_spin(1.0);
	oggetto_rot_x->set_h(60);
	oggetto_rot_x->setConstraintY(true);

	new GLUI_Column(panelOggetto_rotazioneX,false);
	oggetto_rot_y = new GLUI_Rotation(panelOggetto_rotazioneX, "Y", oggetto_rotate );
	oggetto_rot_y->set_spin(1.0);
	oggetto_rot_y->set_h(60);
	oggetto_rot_y->setConstraintX(true);

	new GLUI_Column(panelOggetto_rotazioneX,false);
	oggetto_rot_z = new GLUI_Rotation(panelOggetto_rotazioneX, "Z", oggetto_rotate );
	oggetto_rot_z->set_spin(1.0);
	oggetto_rot_z->set_h(60);
	oggetto_rot_z->setConstraintX(true);

	GLUI_Rollout *roll_scale = new GLUI_Rollout(panelComandiOggetto, "Scale", false );
	panelOggetto_scala = new GLUI_Panel(roll_scale, "", GLUI_PANEL_NONE);
	GLUI_StaticText *staticText_scaleX = new GLUI_StaticText(panelOggetto_scala, "X:");
	staticText_scaleX->set_w(2);
	oggetto_scale_x = new GLUI_Spinner(panelOggetto_scala, "", &oggetto_scale[0], 0, cb_scale );
	oggetto_scale_x->set_float_limits( .01f, 5.0 );
	oggetto_scale_x->edittext->set_w(-1);
	oggetto_scale_x->edittext->text_x_offset=0;
	new GLUI_Column(panelOggetto_scala,false);
	GLUI_StaticText *staticText_scaleY = new GLUI_StaticText(panelOggetto_scala, "Y:");
	staticText_scaleY->set_w(2);
	oggetto_scale_y = new GLUI_Spinner(panelOggetto_scala, "", &oggetto_scale[1], 1, cb_scale );
	oggetto_scale_y->set_float_limits( .01f, 5.0 );
	oggetto_scale_y->edittext->set_w(-1);
	oggetto_scale_y->edittext->text_x_offset=0;
	new GLUI_Column(panelOggetto_scala,false);
	GLUI_StaticText *staticText_scaleZ = new GLUI_StaticText(panelOggetto_scala, "Z:");
	staticText_scaleZ->set_w(2);
	oggetto_scale_z = new GLUI_Spinner(panelOggetto_scala, "", &oggetto_scale[2], 2, cb_scale );
	oggetto_scale_z->set_float_limits( .01f, 5.0 );
	oggetto_scale_z->edittext->set_w(-1);
	oggetto_scale_z->edittext->text_x_offset=0;
	new GLUI_Checkbox(roll_scale, "Constrain Proportions", &oggetto_blocca_proporzioni);

	GLUI_Panel *panelOggetto_materialeOColore = new GLUI_Panel(panelOggetto, "Color and Material"/*, GLUI_PANEL_NONE*/);
	new GLUI_Column(panelOggetto_materialeOColore,false);
	lista_colori = new GLUI_Listbox(panelOggetto_materialeOColore, "Color:     ", &oggetto_colore );
	for(int i=0; i<getNumeroColori(); i++ ){
		lista_colori->add_item( i, getNomeColore(i) );
	}
	GLUI_StaticText *listaColori_Separatore = new GLUI_StaticText(panelOggetto_materialeOColore, "");
	listaColori_Separatore->set_h(5);
	lista_materiali = new GLUI_Listbox(panelOggetto_materialeOColore, "Material: ", &oggetto_materiale );
	for(int i=0; i<getNumeroMateriali(); i++ ){
		lista_materiali->add_item( i, getNomeMateriale(i) );
	}

	GLUI_Rollout *roll_texture = new GLUI_Rollout(panelComandiOggetto, "Texture", false );
	panelTexture = new GLUI_Panel( roll_texture, "", GLUI_PANEL_NONE);
	buttonCaricaTexture = new GLUI_Button(panelTexture, "Load", SCEGLI_TEXTURE_OGGETTO, cb_texture );
	new GLUI_Button(panelTexture, "Delete", ELIMINA_TEXTURE, cb_texture );
	panelComandiOggetto->add_separator_to_panel(panelTexture);
	new GLUI_Button(panelTexture, "Reset", RESET_TEXTURE, cb_texture );
	GLUI_StaticText *staticText_button_separator = new GLUI_StaticText(panelTexture, "");
	new GLUI_StaticText(panelTexture, "Mapping:");
	lista_mapping = new GLUI_Listbox(panelTexture,  "", &oggetto_mapping );
	lista_mapping->add_item( GL_OBJECT_LINEAR, "Object Linear" );
	lista_mapping->add_item( GL_EYE_LINEAR, "Eye Linear" );
	lista_mapping->add_item( GL_SPHERE_MAP, "Sphere" );

	new GLUI_Column(panelTexture,false);
	check_oggetto_repeat = new GLUI_Checkbox(panelTexture, "Repeat", &oggetto_repeat, IMPOSTA_REPEAT, cb_texture );
	GLUI_StaticText *staticText_planes_separator = new GLUI_StaticText(panelTexture, "");
	staticText_planes_separator->set_w(5);
	GLUI_StaticText *staticText_planes = new GLUI_StaticText(panelTexture, "Plane-S:");
	staticText_planes->set_w(5);
	for(int i=0;i<4;i++){
		spinnerplanes[i] = new GLUI_Spinner(panelTexture,"", &texture_planes[i]);
		spinnerplanes[i]->set_int_limits( 0, 5);
		spinnerplanes[i]->set_speed(0.1);
		spinnerplanes[i]->edittext->set_w(-1);
		spinnerplanes[i]->edittext->text_x_offset=0;
	}
	
	new GLUI_Column(panelTexture,false);
	check_oggetto_mipmapping = new GLUI_Checkbox(panelTexture, "MipMap", &oggetto_mipmapping, IMPOSTA_MIPMAPPING, cb_texture );
	GLUI_StaticText *staticText_planet_separator = new GLUI_StaticText(panelTexture, "");
	staticText_planet_separator->set_w(5);
	GLUI_StaticText *staticText_planet = new GLUI_StaticText(panelTexture, "Plane-T:");
	staticText_planet->set_w(5);
	for(int i=0;i<4;i++){
		spinnerplanet[i] = new GLUI_Spinner(panelTexture,"", &texture_planet[i]);
		spinnerplanet[i]->set_int_limits( 0, 5);
		spinnerplanet[i]->set_speed(0.1);
		spinnerplanet[i]->edittext->set_w(-1);
		spinnerplanet[i]->edittext->text_x_offset=0;
	}
	
	// Pannello carica texture
	panelFileTexture = GLUI_Master.create_glui("Load Texture",0,window_pos_x + 140, window_pos_y + 50);
	panelFileTexture->set_main_gfx_window(mainWindow);
	textureFileBrowserOggetto = new GLUI_FileBrowser(panelFileTexture, "", false, CARICA_TEXTURE_OGGETTO, cb_texture);
	textureFileBrowserOggetto->set_h(380);
	new GLUI_Button(panelFileTexture, "Cancel", ANNULLA_CARICA_TEXTURE, cb_texture );
	panelFileTexture->hide();

	// Pannello carica texture skybox
	panelCaricaTextureSkybox = GLUI_Master.create_glui("Texture Skybox",0,window_pos_x + 140, window_pos_y + 50);
	panelCaricaTextureSkybox->set_main_gfx_window(mainWindow);
	panelCaricaTextureSkybox->hide();
	for(int i=0;i < 6;i++) {
		panelTextureSkybox[i] = new GLUI_Panel(panelCaricaTextureSkybox,"",GLUI_PANEL_NONE);
		campoTextureSkybox[i] = new GLUI_EditText(panelTextureSkybox[i], ordineTextureSkybox[i], nomeFileTextureSkybox);
		campoTextureSkybox[i]->set_w(250);
		new GLUI_Column(panelTextureSkybox[i],false);
		new GLUI_Button(panelTextureSkybox[i], "Browse", i, cb_texture_skybox );
	}
	new GLUI_Button(panelCaricaTextureSkybox, "Close", CHIUDI_CARICA_SKYBOX, cb_texture_skybox );

	// Pannello carica texture skybox
	panelFileTextureSkybox = GLUI_Master.create_glui("Load Skybox Texture",0,window_pos_x + 140, window_pos_y + 50);
	panelFileTextureSkybox->set_main_gfx_window(mainWindow);
	textureFileBrowserSkybox = new GLUI_FileBrowser(panelFileTextureSkybox, "", false, CARICA_TEXTURE_SKYBOX, cb_texture_skybox);
	textureFileBrowserSkybox->set_h(380);
	new GLUI_Button(panelFileTextureSkybox, "Cancel", ANNULLA_CARICA_SKYBOX, cb_texture_skybox );
	panelFileTextureSkybox->hide();

	// Pannello luci
	GLUI *panelLuci = GLUI_Master.create_glui("Lights", 0, window_pos_x - 350, window_pos_y);
	panelLuci->set_main_gfx_window(mainWindow);
	checkboxIlluminazione = new GLUI_Checkbox(panelLuci, "Enable lighting", &(progetto->illuminazioneAbilitata),-1,cb_light);

	for(int i=0;i<=7;i++){
		char s[10];
		sprintf_s(s, "Light %i",i);
		roll_lights[i] = new GLUI_Rollout(panelLuci, s, false );
		GLUI_Panel *light_enabled_area = new GLUI_Panel(roll_lights[i], "", GLUI_PANEL_NONE);
		checkboxLuceAbilitata[i] = new GLUI_Checkbox(light_enabled_area, "Enable", &(progetto->getLuce(i)->abilitata));
		new GLUI_Column(light_enabled_area,false);
		checkboxLuceDisegnaSorgente[i] = new GLUI_Checkbox(light_enabled_area, "Draw light source", &(progetto->getLuce(i)->disegnaSorgente));
		
		GLUI_Panel *light_area = new GLUI_Panel(roll_lights[i], "", GLUI_PANEL_RAISED);
		listaTipoLuce[i] = new GLUI_Listbox(light_area,  "Type:", &(progetto->getLuce(i)->tipo));
		listaTipoLuce[i]->add_item( Luce::PUNTIFORME, "Positional" );
		listaTipoLuce[i]->add_item( Luce::DIREZIONALE, "Directional" );
		listaTipoLuce[i]->add_item( Luce::SPOTLIGHT, "Spotlight" );

		GLUI_Panel *light_position_area = new GLUI_Panel(light_area, "Position", GLUI_PANEL_NONE);
		luce_transXZ[i] = new GLUI_Translation(light_position_area, "X,Z", GLUI_TRANSLATION_XY, luci_pos[i] );
		luce_transXZ[i]->set_speed(luci_speed);
		new GLUI_Column(light_position_area,false);
		luce_transY[i] = new GLUI_Translation(light_position_area, "Y", GLUI_TRANSLATION_Y, &luci_pos[i][2] );
		luce_transY[i]->set_speed(luci_speed);

		GLUI_Panel *spotlight_position_area = new GLUI_Panel(light_area, "", GLUI_PANEL_NONE);
		new GLUI_Column(spotlight_position_area,false);
		spotlight_rot_x[i] = new GLUI_Rotation(spotlight_position_area, "X Rotation", luci_rotate[i] );
		spotlight_rot_x[i]->set_spin(1.0);
		spotlight_rot_x[i]->setConstraintY(true);

		new GLUI_Column(spotlight_position_area,true);
		spotlight_rot_y[i] = new GLUI_Rotation(spotlight_position_area, "Y Rotation", luci_rotate[i] );
		spotlight_rot_y[i]->set_spin(1.0);
		spotlight_rot_y[i]->setConstraintX(true);

		new GLUI_Column(spotlight_position_area,true);
		spotlight_rot_z[i] = new GLUI_Rotation(spotlight_position_area, "Z Rotation", luci_rotate[i] );
		spotlight_rot_z[i]->set_spin(1.0);
		spotlight_rot_z[i]->setConstraintX(true);

		GLUI_Panel *spotlight_raggioAttenuazione_area = new GLUI_Panel(light_area, "", GLUI_PANEL_NONE);
		GLUI_StaticText *descrizioneRaggio = new GLUI_StaticText(spotlight_raggioAttenuazione_area, "Radius");
		scrollbarRaggio[i] = new GLUI_Scrollbar(spotlight_raggioAttenuazione_area, "",GLUI_SCROLL_HORIZONTAL,&(progetto->getLuce(i)->valoreRaggio));
		scrollbarRaggio[i]->set_int_limits(0,180);

		new GLUI_Column(spotlight_raggioAttenuazione_area,true);
		GLUI_StaticText *descrizioneAttenuazione = new GLUI_StaticText(spotlight_raggioAttenuazione_area, "Attenuation");
		scrollbarAttenuazione[i] = new GLUI_Scrollbar(spotlight_raggioAttenuazione_area, "",GLUI_SCROLL_HORIZONTAL,&(progetto->getLuce(i)->valoreAttenuazione));
		scrollbarAttenuazione[i]->set_int_limits(0,180);

		GLUI_Panel *light_color_area = new GLUI_Panel(light_area, "", GLUI_PANEL_NONE);
		char string_rgb[3][4] = {"R: ","G: ","B: "};
		GLUI_Panel *light_ambientale = new GLUI_Panel(light_color_area, "Ambiental");
		for(int j=0;j<3;j++){
			spinnerAmbientale[i][j] = new GLUI_Spinner(light_ambientale,string_rgb[j], &(progetto->getLuce(i)->getAmbientale())[j]);
			spinnerAmbientale[i][j]->set_int_limits( 0, 255);
			spinnerAmbientale[i][j]->edittext->set_w(-1);
			spinnerAmbientale[i][j]->edittext->text_x_offset=0;
		}
		new GLUI_Column(light_color_area,false);

		GLUI_Panel *light_diffusa = new GLUI_Panel(light_color_area, "Diffuse");
		for(int j=0;j<3;j++){
			spinnerDiffusa[i][j] = new GLUI_Spinner(light_diffusa,string_rgb[j], &(progetto->getLuce(i)->getDiffusa())[j]);
			spinnerDiffusa[i][j]->set_int_limits( 0, 255);
			spinnerDiffusa[i][j]->edittext->set_w(-1);
			spinnerDiffusa[i][j]->edittext->text_x_offset=0;
		}
		new GLUI_Column(light_color_area,false);

		GLUI_Panel *light_speculare = new GLUI_Panel(light_color_area, "Specular");
		for(int j=0;j<3;j++){
			spinnerSpeculare[i][j] = new GLUI_Spinner(light_speculare,string_rgb[j], &(progetto->getLuce(i)->getSpeculare())[j]);
			spinnerSpeculare[i][j]->set_int_limits( 0, 255);
			spinnerSpeculare[i][j]->edittext->set_w(-1);
			spinnerSpeculare[i][j]->edittext->text_x_offset=0;
		}
		new GLUI_Column(light_color_area,false);
	}

	// Pannello carica progetto
	panelFileCaricaProgetto = GLUI_Master.create_glui("Load Project",0,window_pos_x + 140, window_pos_y + 50);
	panelFileCaricaProgetto->set_main_gfx_window(mainWindow);
	progettoFileBrowser = new GLUI_FileBrowser(panelFileCaricaProgetto, "", false, CARICA_PROGETTO, cb_dao_progetto);
	progettoFileBrowser->set_h(380);
	new GLUI_Button(panelFileCaricaProgetto, "Cancel", CHIUDI_CARICA_PROGETTO, cb_dao_progetto );
	panelFileCaricaProgetto->hide();

	// Pannello salva progetto
	panelFileSalvaProgetto = GLUI_Master.create_glui("Save Project",0,window_pos_x + 140, window_pos_y + 50);
	panelFileSalvaProgetto->set_main_gfx_window(mainWindow);
	progettoTextNomeFileSalvare = new GLUI_EditText(panelFileSalvaProgetto, "File: ", progettoNomeFileSalvare);
	progettoTextNomeFileSalvare->set_w(500);
	GLUI_Panel *pannelloPulsanti = new GLUI_Panel(panelFileSalvaProgetto, "", GLUI_PANEL_NONE);
	new GLUI_Button(pannelloPulsanti, "Save", SALVA_PROGETTO, cb_dao_progetto );
	new GLUI_Column(pannelloPulsanti,false);
	new GLUI_Button(pannelloPulsanti, "Cancel", CHIUDI_CARICA_PROGETTO, cb_dao_progetto );
	panelFileSalvaProgetto->hide();

	// Pannello salva codice generato
	panelFileCodiceGenerato = GLUI_Master.create_glui("Generate code",0,window_pos_x + 140, window_pos_y + 50);
	panelFileCodiceGenerato->set_main_gfx_window(mainWindow);
	textNomeProgettoCodiceGenerato = new GLUI_EditText(panelFileCodiceGenerato, "Project name: ", nomeProgettoCodiceGenerato);
	textNomeProgettoCodiceGenerato->set_w(300);
	textCartellaCodiceGenerato = new GLUI_EditText(panelFileCodiceGenerato, "Folder: ", cartellaCodiceGenerato);
	textCartellaCodiceGenerato->set_w(300);
	GLUI_Panel *pannelloPulsantiCodice = new GLUI_Panel(panelFileCodiceGenerato, "", GLUI_PANEL_NONE);
	new GLUI_Button(pannelloPulsantiCodice, "Generate!", GENERA_CODICE, cb_genera_codice );
	new GLUI_Column(pannelloPulsantiCodice,false);
	new GLUI_Button(pannelloPulsantiCodice, "Cancel", GENERA_CODICE_CHIUDI, cb_genera_codice );
	panelFileCodiceGenerato->hide();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	centraFinestra(600,600);
	int	mainWindow = glutCreateWindow("SantoCAD");
	GLenum err = glewInit();
	if (GLEW_OK != err){
		Logger::error("Unable to initialize Glew"); //glewGetErrorString(err)
	}

	srand(time(NULL));	
	progetto = new Progetto();
	cartellaIniziale = Utilita::getCartellaCorrente() + "\\";
	progettoNomeFileDefault = cartellaIniziale + "project.txt";
	string cartellaSkybox = cartellaIniziale + "Texture\\skybox\\" + scenaSkybox[(rand() % (NUM_SKYBOX - 1))] + "\\";
	Skybox *skybox = new Skybox(cartellaSkybox);
	progetto->setSkybox(skybox);

	GLUI_Master.set_glutReshapeFunc(myReshape);
	GLUI_Master.set_glutIdleFunc(myIdle);
	GLUI_Master.set_glutMouseFunc(mousePick);

	glutDisplayFunc(myDisplay);
	creaPannelliGlui(mainWindow);
	init();

	glutMainLoop();
	return(1);
}

