#include "pannelli.h"
//#include "xxx.h"

void creaPannelliGlui(int mainWindow){
	int window_pos_x = glutGet((GLenum)GLUT_WINDOW_X);
	int window_pos_y = glutGet((GLenum)GLUT_WINDOW_Y);
	int window_size_h = glutGet((GLenum)GLUT_WINDOW_HEIGHT);
	int window_size_w = glutGet((GLenum)GLUT_WINDOW_WIDTH);

	// Pannello sinistra
	GLUI *panelScena = GLUI_Master.create_glui("Menù scena",0,window_pos_x - 180, window_pos_y);
	panelScena->set_main_gfx_window(mainWindow);

	GLUI_Panel *panelScena_camera = new GLUI_Panel( panelScena, "Camera", GLUI_PANEL_NONE);
	camera_trans = new GLUI_Translation(panelScena_camera, "Posizione camera", GLUI_TRANSLATION_XY, camera_pos );
	camera_trans->set_speed(camera_speed);

	new GLUI_Column(panelScena_camera,true);
	camera_rot = new GLUI_Rotation(panelScena_camera, "Rotazione camera", camera_rotate );
	camera_rot->set_spin(1.0);
	camera_rot->setConstraintX(true);

	GLUI_Panel *panelScena_buttonForme = new GLUI_Panel(panelScena, "Forme", GLUI_PANEL_NONE);
	new GLUI_Button(panelScena_buttonForme, "Cubo", CUBO, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Sfera", SFERA, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Toro", TORUS, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Tetraedro", TETRA, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Teiera", TEAPOT, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Cono", CONE, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Dodecaedro", DODE, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Icosaedro", ICO, aggiungiOggetto);
	new GLUI_Button(panelScena_buttonForme, "Ottaedro", OCTA, aggiungiOggetto);
	panelScena->add_separator_to_panel(panelScena_buttonForme);
	buttonEliminaOggettoSelezionato = new GLUI_Button(panelScena_buttonForme, "Elimina oggetto", 0, cb_elimina_oggetto );

	GLUI_Panel *panelScena_checkbox = new GLUI_Panel(panelScena, "", GLUI_PANEL_NONE);
	check_oggetto_wireframe = new GLUI_Checkbox(panelScena_checkbox, "Mostra Wireframe", &oggetto_wireframe );
	check_oggetto_mostraSelezione = new GLUI_Checkbox(panelScena_checkbox, "Mostra Selezione", &oggetto_mostraSelezione );
	oggettiNellaScena = new GLUI_StaticText( panelScena, "");

	// Pavimento
	GLUI_Rollout *panel_pavimento = new GLUI_Rollout(panelScena_checkbox, "Pavimento", false );
	new GLUI_Checkbox(panel_pavimento, "Mostra Pavimento", &(progetto->getPavimento()->abilitato) );
	new GLUI_Checkbox(panel_pavimento, "Pavimento Wireframe", &(progetto->getPavimento()->wireframe) );		
	GLUI_Listbox *lista_materiali_pavimento = new GLUI_Listbox(panel_pavimento, "Materiale:", &(progetto->getPavimento()->idMateriale) );
	for(int i=0; i<getNumeroMateriali(); i++ ){
		lista_materiali_pavimento->add_item( i, getNomeMateriale(i) );
	}
	lista_materiali_pavimento->set_int_val(progetto->getPavimento()->idMateriale);
	GLUI_Spinner *pavimento_tassellazione = new GLUI_Spinner(panel_pavimento, "Tassellazione: ", &(progetto->getPavimento()->tassellazione));
	pavimento_tassellazione->set_int_limits(10, 1000 );


	// Pannello destra
	GLUI *panelComandiOggetto = GLUI_Master.create_glui("Proprietà oggetto", 0, window_pos_x + window_size_w + 20, window_pos_y);
	panelComandiOggetto->set_main_gfx_window(mainWindow);

	
	panelOggetto = new GLUI_Panel( panelComandiOggetto, "Oggetto" );
	GLUI_Panel *panelOggetto_posizioneXZ = new GLUI_Panel(panelOggetto, "", GLUI_PANEL_NONE);
	oggetto_transXZ = new GLUI_Translation(panelOggetto_posizioneXZ, "Posizione X-Z", GLUI_TRANSLATION_XY, oggetto_pos );
	oggetto_transXZ->set_speed(oggetto_speed);

	GLUI_Panel *panelOggetto_posizioneY = new GLUI_Panel(panelOggetto, "", GLUI_PANEL_NONE);
	oggetto_transY = new GLUI_Translation(panelOggetto_posizioneY, "Posizione Y", GLUI_TRANSLATION_Y, &oggetto_pos[2] );
	oggetto_transY->set_speed(oggetto_speed);
	panelComandiOggetto->add_separator_to_panel(panelOggetto_posizioneY);

	GLUI_Panel *panelOggetto_scala = new GLUI_Panel(panelOggetto, "", GLUI_PANEL_NONE);
	oggetto_scale_x = new GLUI_Spinner(panelOggetto_scala, "Scala X : ", &oggetto_scale[0], 0, cb_scale );
	oggetto_scale_x->set_float_limits( .01f, 2.0 );
	oggetto_scale_y = new GLUI_Spinner(panelOggetto_scala, "Scala Y : ", &oggetto_scale[1], 1, cb_scale );
	oggetto_scale_y->set_float_limits( .01f, 2.0 );
	oggetto_scale_z = new GLUI_Spinner(panelOggetto_scala, "Scala Z : ", &oggetto_scale[2], 2, cb_scale );
	oggetto_scale_z->set_float_limits( .01f, 2.0 );
	new GLUI_Checkbox(panelOggetto_scala, "Blocca proporzioni", &oggetto_blocca_proporzioni);

	new GLUI_Column(panelOggetto,false);
	GLUI_Panel *panelOggetto_rotazioneX = new GLUI_Panel(panelOggetto, "", GLUI_PANEL_NONE);
	oggetto_rot_x = new GLUI_Rotation(panelOggetto_rotazioneX, "Rotazione X", oggetto_rotate );
	oggetto_rot_x->set_spin(1.0);
	oggetto_rot_x->setConstraintY(true);

	GLUI_Panel *panelOggetto_rotazioneYZ = new GLUI_Panel(panelOggetto, "", GLUI_PANEL_NONE);
	oggetto_rot_y = new GLUI_Rotation(panelOggetto_rotazioneYZ, "Rotazione Y", oggetto_rotate );
	oggetto_rot_y->set_spin(1.0);
	oggetto_rot_y->setConstraintX(true);
	panelComandiOggetto->add_separator_to_panel(panelOggetto_rotazioneYZ);

	new GLUI_Column(panelOggetto_rotazioneYZ,true);
	oggetto_rot_z = new GLUI_Rotation(panelOggetto_rotazioneYZ, "Rotazione Z", oggetto_rotate );
	oggetto_rot_z->set_spin(1.0);
	oggetto_rot_z->setConstraintX(true);
	panelComandiOggetto->add_separator_to_panel(panelOggetto_rotazioneYZ);

	GLUI_Panel *panelOggetto_materialeOColore = new GLUI_Panel(panelOggetto, "Materiale e Colore", GLUI_PANEL_NONE);
	GLUI_RadioGroup *radioButton_materialeOColore = new GLUI_RadioGroup(panelOggetto_materialeOColore,&oggettoVisualizzaMateriale,1,cb_visualizzaColoreOMateriale);
	new GLUI_RadioButton(radioButton_materialeOColore, "Colore :     " );
	GLUI_StaticText *radioButtonMateriale_Separatore = new GLUI_StaticText(radioButton_materialeOColore, "");
	new GLUI_RadioButton(radioButton_materialeOColore, "Materiale : " );
	new GLUI_Column(panelOggetto_materialeOColore,false);
	lista_colori = new GLUI_Listbox(panelOggetto_materialeOColore, "", &oggetto_colore );
	for(int i=0; i<getNumeroColori(); i++ ){
		lista_colori->add_item( i, getNomeColore(i) );
	}
	GLUI_StaticText *listaColori_Separatore = new GLUI_StaticText(panelOggetto_materialeOColore, "");
	listaColori_Separatore->set_h(5);
	lista_materiali = new GLUI_Listbox(panelOggetto_materialeOColore, "", &oggetto_materiale );
	for(int i=0; i<getNumeroMateriali(); i++ ){
		lista_materiali->add_item( i, getNomeMateriale(i) );
	}

	panelTexture = new GLUI_Panel( panelComandiOggetto, "Texture" );
	GLUI_Panel *panelTexture_buttonEMapping = new GLUI_Panel(panelTexture, "", GLUI_PANEL_NONE);
	GLUI_Panel *buttonEMapping_button = new GLUI_Panel(panelTexture_buttonEMapping, "Button", GLUI_PANEL_NONE);
	buttonCaricaTexture = new GLUI_Button(buttonEMapping_button, "Carica Texture", SCEGLI_TEXTURE, cb_texture );
	new GLUI_Button(buttonEMapping_button, "Elimina Texture", ELIMINA_TEXTURE, cb_texture );
	panelComandiOggetto->add_separator_to_panel(buttonEMapping_button);
	new GLUI_Button(buttonEMapping_button, "Reset", RESET_TEXTURE, cb_texture );
	new GLUI_Column(panelTexture_buttonEMapping,false);
	GLUI_Panel *buttonEMapping_listaMapping = new GLUI_Panel(panelTexture_buttonEMapping, "Button", GLUI_PANEL_NONE);
	lista_mapping = new GLUI_Listbox(buttonEMapping_listaMapping,  "Mapping : ", &oggetto_mapping );
	lista_mapping->add_item( GL_OBJECT_LINEAR, "Object Linear" );
	lista_mapping->add_item( GL_EYE_LINEAR, "Eye Linear" );
	lista_mapping->add_item( GL_SPHERE_MAP, "Sphere" );

	GLUI_Panel *panelTexture_planeST = new GLUI_Panel(panelTexture, "", GLUI_PANEL_NONE);
	GLUI_Panel *planes_area = new GLUI_Panel(panelTexture_planeST, "Plane-S :");
	for(int i=0;i<4;i++){
		spinnerplanes[i] = new GLUI_Spinner(planes_area,"", &texture_planes[i]);
		spinnerplanes[i]->set_int_limits( 0, 5);
		spinnerplanes[i]->set_speed(0.1);
	}
	check_oggetto_repeat = new GLUI_Checkbox(panelTexture_planeST, "Repeat", &oggetto_repeat, IMPOSTA_REPEAT, cb_texture );

	new GLUI_Column(panelTexture_planeST,false);
	GLUI_Panel *planet_area = new GLUI_Panel(panelTexture_planeST, "Plane-T :");
	for(int i=0;i<4;i++){
		spinnerplanet[i] = new GLUI_Spinner(planet_area,"", &texture_planet[i]);
		spinnerplanet[i]->set_int_limits( 0, 5);
		spinnerplanet[i]->set_speed(0.1);
	}
	check_oggetto_mipmapping = new GLUI_Checkbox(panelTexture_planeST, "Mip Mapping", &oggetto_mipmapping, IMPOSTA_MIPMAPPING, cb_texture );

	// Pannello carica texture
	panelFileTexture = GLUI_Master.create_glui("Carica Texture",0,window_pos_x + 140, window_pos_y + 50);
	panelFileTexture->set_main_gfx_window(mainWindow);
	textureFileBrowser = new GLUI_FileBrowser(panelFileTexture, "", false, CARICA_TEXTURE, cb_texture);
	textureFileBrowser->set_h(380);
	panelFileTexture->hide();

	// Pannello luci
	GLUI *panelLuci = GLUI_Master.create_glui("Luci", 0, window_pos_x - 350, window_pos_y);
	panelLuci->set_main_gfx_window(mainWindow);
	new GLUI_Checkbox(panelLuci, "Abilita illuminazione", &(progetto->illuminazioneAbilitata),-1,cb_light);

	for(int i=0;i<=7;i++){
		char s[7];
		sprintf_s(s, "Luce %i",i);
		roll_lights[i] = new GLUI_Rollout(panelLuci, s, false );
		GLUI_Panel *light_enabled_area = new GLUI_Panel(roll_lights[i], "", GLUI_PANEL_NONE);
		new GLUI_Checkbox(light_enabled_area, "Abilitata", &(progetto->getLuce(i)->abilitata));
		
		GLUI_Panel *light_area = new GLUI_Panel(roll_lights[i], "", GLUI_PANEL_RAISED);
		GLUI_Listbox* lista_mapping = new GLUI_Listbox(light_area,  "Tipo:", &(progetto->getLuce(i)->tipo));
		lista_mapping->add_item( Luce::PUNTIFORME, "Puntiforme" );
		lista_mapping->add_item( Luce::DIREZIONALE, "Direzionale" );
		lista_mapping->add_item( Luce::SPOTLIGHT, "Faretto" );

		GLUI_Panel *light_position_area = new GLUI_Panel(light_area, "Posizione", GLUI_PANEL_NONE);
		luce_transXZ[i] = new GLUI_Translation(light_position_area, "X,Z", GLUI_TRANSLATION_XY, luci_pos[i] );
		luce_transXZ[i]->set_speed(luci_speed);
		new GLUI_Column(light_position_area,false);
		luce_transY[i] = new GLUI_Translation(light_position_area, "Y", GLUI_TRANSLATION_Y, &luci_pos[i][2] );
		luce_transY[i]->set_speed(luci_speed);
	}
}