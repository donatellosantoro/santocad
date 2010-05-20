#include "GeneratoreCodiceProgetto.h"
#include "GeneratoreCodiceOggetto.h"
#include "Logger.h"
#include "Utilita.h"
#include <iostream>
#include <ERRNO.H>

using namespace std;

GeneratoreCodiceProgetto::GeneratoreCodiceProgetto(Progetto* progetto,string f){
	p = progetto;
	initFolder = f;
	init();
}
GeneratoreCodiceProgetto::~GeneratoreCodiceProgetto(){}

void GeneratoreCodiceProgetto::init(){
	PLACEHOLDER_DISEGNO_OGGETTI = "//${DISEGNO_OGGETTI}";
	PLACEHOLDER_DISEGNO_PAVIMENTO = "//${DISEGNO_PAVIMENTO}";
	PLACEHOLDER_CONTROLLA_LIMITI = "//${CONTROLLA_LIMITI}";
	PLACEHOLDER_DISEGNO_SKYBOX = "//${DISEGNO_SKYBOX}";
	PLACEHOLDER_VARIABILI_TEXTURE = "//${VARIABILI_TEXTURE}";
	PLACEHOLDER_VARIABILI_PLANE = "//${VARIABILI_PLANE}";
	PLACEHOLDER_CARICA_TEXTURE = "//${CARICA_TEXTURE}";
	PLACEHOLDER_GESTISCI_ILLUMINAZIONE = "//${GESTISCI_ILLUMINAZIONE}";
	PLACEHOLDER_GESTIONE_CAMERA = "//${GESTIONE_CAMERA}";
	PLACEHOLDER_NOME_PROGETTO = "${NOME_PROGETTO}";
	statoTextureAbilitata = false;
	TAB = "\t";
	LINE = "\n";
	pos[0] = pos[1] = pos[2] = 0.0;
	at[0] = at[1] = 0.0;
	at[2] = -0.1;
	dir[0] = dir[1] = 0.0;
	dir[2] = -0.05;
}

void GeneratoreCodiceProgetto::genera(string folder, string nomeProgetto){
	if(folder.find_last_of("\\") != (folder.length()-1)) folder += "\\";
	_mkdir(Utilita::stringToChar(folder));
	folder += nomeProgetto + "\\";
	_mkdir(Utilita::stringToChar(folder));
	Logger::debug("Generate code in folder " + folder);

	string projectFolder = folder + nomeProgetto + "\\";
	int result = _mkdir(Utilita::stringToChar(projectFolder));
	if(result==-1 && errno != EEXIST){
		Logger::error("Unable to load folder " + projectFolder);
		return;
	}

	string resFolder = initFolder + "Resource\\";
	string file[6] = {"materiali.cpp","materiali.h","scenaUtil.cpp","scenaUtil.h","textureUtil.cpp","textureUtil.h"};
	for(int i=0;i<6;i++){
		Utilita::copiaFile(resFolder + file[i], projectFolder + file[i]);
	}

	string lib_file[8] = {"FreeImage.lib","glew32.lib","GlU32.lib","glut32.lib","OpenGL32.lib","FreeImage.dll","glew32.dll","glut32.dll"};
	for(int i=0;i<8;i++){
		Utilita::copiaFile(initFolder + lib_file[i], projectFolder + lib_file[i]);
	}

	_mkdir(Utilita::stringToChar(projectFolder + ""));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "gl\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\core\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\et\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\mathlib\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\matrix\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\matvec\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\quaternion\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\vector\\"));
	_mkdir(Utilita::stringToChar(projectFolder + "cml\\core\\meta\\"));

	string include_file[110] = {"FreeImage.h","cml\\cml.h","cml\\constants.h","cml\\defaults.h","cml\\dynamic.h","cml\\external.h","cml\\fixed.h","cml\\matrix.h","cml\\quaternion.h","cml\\util.h","cml\\vector.h","cml\\core\\cml_assert.h","cml\\core\\cml_meta.h","cml\\core\\common.h","cml\\core\\dynamic_1D.h","cml\\core\\dynamic_2D.h","cml\\core\\external_1D.h","cml\\core\\external_2D.h","cml\\core\\fixed_1D.h","cml\\core\\fixed_2D.h","cml\\core\\fwd.h","cml\\core\\meta\\common.h","cml\\core\\meta\\if.h","cml\\core\\meta\\switch.h","cml\\et\\array_promotions.h","cml\\et\\scalar_ops.h","cml\\et\\scalar_promotions.h","cml\\et\\size_checking.h","cml\\et\\tags.h","cml\\et\\traits.h","cml\\mathlib\\checking.h","cml\\mathlib\\coord_conversion.h","cml\\mathlib\\epsilon.h","cml\\mathlib\\frustum.h","cml\\mathlib\\helper.h","cml\\mathlib\\interpolation.h","cml\\mathlib\\mathlib.h","cml\\mathlib\\matrix_basis.h","cml\\mathlib\\matrix_concat.h","cml\\mathlib\\matrix_misc.h","cml\\mathlib\\matrix_ortho.h","cml\\mathlib\\matrix_projection.h","cml\\mathlib\\matrix_rotation.h","cml\\mathlib\\matrix_transform.h","cml\\mathlib\\matrix_translation.h","cml\\mathlib\\misc.h","cml\\mathlib\\picking.h","cml\\mathlib\\projection.h","cml\\mathlib\\quaternion_basis.h","cml\\mathlib\\quaternion_rotation.h","cml\\mathlib\\typedef.h","cml\\mathlib\\vector_angle.h","cml\\mathlib\\vector_misc.h","cml\\mathlib\\vector_ortho.h","cml\\mathlib\\vector_transform.h","cml\\matrix\\class_ops.h","cml\\matrix\\determinant.h","cml\\matrix\\dynamic.h","cml\\matrix\\external.h","cml\\matrix\\fixed.h","cml\\matrix\\inverse.h","cml\\matrix\\lu.h","cml\\matrix\\matop_macros.h","cml\\matrix\\matrix_comparison.h","cml\\matrix\\matrix_expr.h","cml\\matrix\\matrix_functions.h","cml\\matrix\\matrix_mul.h","cml\\matrix\\matrix_ops.h","cml\\matrix\\matrix_print.h","cml\\matrix\\matrix_promotions.h","cml\\matrix\\matrix_rowcol.h","cml\\matrix\\matrix_traits.h","cml\\matrix\\matrix_transpose.h","cml\\matrix\\matrix_unroller.h","cml\\matvec\\matvec_mul.h","cml\\matvec\\matvec_promotions.h","cml\\quaternion\\conjugate.h","cml\\quaternion\\inverse.h","cml\\quaternion\\quaternion.h","cml\\quaternion\\quaternion_comparison.h","cml\\quaternion\\quaternion_dot.h","cml\\quaternion\\quaternion_expr.h","cml\\quaternion\\quaternion_functions.h","cml\\quaternion\\quaternion_mul.h","cml\\quaternion\\quaternion_ops.h","cml\\quaternion\\quaternion_print.h","cml\\quaternion\\quaternion_promotions.h","cml\\quaternion\\quaternion_traits.h","cml\\quaternion\\quatop_macros.h","cml\\vector\\class_ops.h","cml\\vector\\dynamic.h","cml\\vector\\external.h","cml\\vector\\fixed.h","cml\\vector\\vecop_macros.h","cml\\vector\\vector_comparison.h","cml\\vector\\vector_expr.h","cml\\vector\\vector_functions.h","cml\\vector\\vector_ops.h","cml\\vector\\vector_print.h","cml\\vector\\vector_products.h","cml\\vector\\vector_promotions.h","cml\\vector\\vector_traits.h","cml\\vector\\vector_unroller.h","gl\\GL.h","gl\\glew.h","gl\\GLU.h","gl\\glui.h","gl\\glut.h","gl\\glxew.h","gl\\wglew.h"};
	for(int i=0;i<110;i++){
		Utilita::copiaFile(initFolder + include_file[i], projectFolder + include_file[i]);
	}

	string stringSln = Utilita::caricaFile(Utilita::stringToChar(resFolder + "Exported.sln"));
	Utilita::sostituisciStringaRicorsiva(&stringSln,PLACEHOLDER_NOME_PROGETTO,nomeProgetto);
	ofstream outFileSln(Utilita::stringToChar(folder + nomeProgetto + ".sln"));
	outFileSln << stringSln;
	outFileSln.close();

	string stringVcp = Utilita::caricaFile(Utilita::stringToChar(resFolder + "Exported.vcproj"));
	Utilita::sostituisciStringaRicorsiva(&stringVcp,PLACEHOLDER_NOME_PROGETTO,nomeProgetto);
	ofstream outFileVcp(Utilita::stringToChar(projectFolder + nomeProgetto + ".vcproj"));
	outFileVcp << stringVcp;
	outFileVcp.close();
	
	string stringFileMain = Utilita::caricaFile(Utilita::stringToChar(resFolder + "main.cpp"));
	generaFileMain(&stringFileMain);
	ofstream outFileMain(Utilita::stringToChar(projectFolder + "main.cpp"));
	outFileMain << stringFileMain;
	outFileMain.close();
}

void GeneratoreCodiceProgetto::generaFileMain(string *stringFileMain){
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_DISEGNO_OGGETTI,getCodiceDisegnoOggetti());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_DISEGNO_PAVIMENTO,getCodiceDisegnoPavimento());
	Utilita::sostituisciStringaRicorsiva(stringFileMain,PLACEHOLDER_CONTROLLA_LIMITI,getCodiceGestioneLimiti());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_DISEGNO_SKYBOX,getCodiceDisegnoSkybox());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_VARIABILI_TEXTURE,getCodiceVariabiliTexture());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_VARIABILI_PLANE,getCodiceVariabiliPlane());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_CARICA_TEXTURE,getCodiceCaricaTexture());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_GESTIONE_CAMERA,getCodiceGestioneCamera());
	Utilita::sostituisciStringa(stringFileMain,PLACEHOLDER_GESTISCI_ILLUMINAZIONE,getCodiceGestisciIlluminazione());
}

string GeneratoreCodiceProgetto::getCodiceGestioneLimiti(){
	if (!p->getSkybox()->abilitato)return "";
	return LINE + TAB + TAB + "controllaLimiti(&pos);";
}

string GeneratoreCodiceProgetto::getCodiceGestioneCamera(){
	string s;

	char s_pos[255];
	sprintf_s(s_pos, "vector3f pos(%f, %f, %f);",pos[0],pos[1],pos[2]);
	string pos(s_pos);

	char s_at[255];
	sprintf_s(s_at, "vector3f at(%f, %f, %f);",at[0],at[1],at[2]);
	string at(s_at);

	char s_dir[255];
	sprintf_s(s_dir, "vector3f dir(%f, %f, %f);",dir[0],dir[1],dir[2]);
	string dir(s_dir);

	s += pos + LINE + at + LINE + dir;
	return s;
}

string GeneratoreCodiceProgetto::getCodiceGestisciIlluminazione(){
	string s = "";
	if(p->illuminazioneAbilitata){
		s += TAB + "glEnable(GL_LIGHTING);" + LINE;;
	
		for(int i=0;i<8;i++){
			Luce *l = p->getLuce(i);
			s += getCodiceLuce(l);
		}

	}else{
		s += TAB + "glDisable(GL_LIGHTING);";
	}
	return s;
}

string GeneratoreCodiceProgetto::getCodiceLuce(Luce *l){
	if(l->abilitata==false)return "";

	char s_id_luce[15];
	sprintf_s(s_id_luce, "%i",l->getId());
	string id_luce(s_id_luce);

	char s_valoreRaggio[15];
	sprintf_s(s_valoreRaggio, "%i",l->valoreRaggio);
	string valoreRaggio(s_valoreRaggio);

	char s_valoreAttenuazione[15];
	sprintf_s(s_valoreAttenuazione, "%i",l->valoreAttenuazione);
	string valoreAttenuazione(s_valoreAttenuazione);

	string s = LINE + TAB + "// Gestisco la luce " + id_luce + LINE;
		
	s += TAB + "glEnable(GL_LIGHT" + id_luce + ");" + LINE;

	string forthComponent = "1.0";
	if(l->tipo == Luce::DIREZIONALE)forthComponent = "0.0";

	char c_pos[255];
	sprintf_s(c_pos, "GLfloat light_position%i[] = { %f, %f, %f, ",l->getId(),l->getPosizione()[0],l->getPosizione()[1],l->getPosizione()[2]);
	string pos(c_pos);

	s += TAB + pos + forthComponent + "};" + LINE;
	s += TAB + "glLightfv(GL_LIGHT" + id_luce + ", GL_POSITION, light_position" + id_luce + ");" + LINE;

	if(l->tipo == Luce::SPOTLIGHT) {
		char c_dir[255];
		sprintf_s(c_dir, "GLfloat vettore_rotazione%i[] = { %f, %f, %f };",l->getId(),l->getRotazioneSpotlight()[0],l->getRotazioneSpotlight()[1],l->getRotazioneSpotlight()[2]);
		string dir(c_dir);
		s += TAB + dir + LINE;
		s += TAB + "glLightfv(GL_LIGHT" + id_luce + ", GL_SPOT_DIRECTION, vettore_rotazione" + id_luce + ");" + LINE;
		s += TAB + "glLightf(GL_LIGHT" + id_luce + ", GL_SPOT_CUTOFF, " + valoreRaggio + ");" + LINE;
		s += TAB + "glLightf(GL_LIGHT" + id_luce + ", GL_SPOT_EXPONENT, " + valoreAttenuazione + ");" + LINE;
	}else{
		s += TAB + "glLightf(GL_LIGHT" + id_luce + ", GL_SPOT_CUTOFF, 180.0);" + LINE;
		s += TAB + "glLightf(GL_LIGHT" + id_luce + ", GL_SPOT_EXPONENT, 0.0);" + LINE;
	}
			
	char c_light_ambient[255];
	sprintf_s(c_light_ambient, "GLfloat light_ambient%i[] = { %f, %f, %f , 1.0};",l->getId(),l->getAmbientale()[0]/255.0,l->getAmbientale()[1]/255.0,l->getAmbientale()[2]/255.0);
	string light_ambient(c_light_ambient);
	s += TAB + light_ambient + LINE;
	s += TAB + "glLightfv(GL_LIGHT" + id_luce + ", GL_AMBIENT, light_ambient" + id_luce + ");" + LINE;

	char c_light_diffuse[255];
	sprintf_s(c_light_diffuse, "GLfloat light_diffuse%i[] = { %f, %f, %f , 1.0};",l->getId(),l->getDiffusa()[0]/255.0,l->getDiffusa()[1]/255.0,l->getDiffusa()[2]/255.0);
	string light_diffuse(c_light_diffuse);
	s += TAB + light_diffuse + LINE;
	s += TAB + "glLightfv(GL_LIGHT" + id_luce + ", GL_DIFFUSE, light_diffuse" + id_luce + ");" + LINE;

	char c_light_specular[255];
	sprintf_s(c_light_specular, "GLfloat light_specular%i[] = { %f, %f, %f , 1.0};",l->getId(),l->getSpeculare()[0]/255.0,l->getSpeculare()[1]/255.0,l->getSpeculare()[2]/255.0);
	string light_specular(c_light_specular);
	s += TAB + light_specular + LINE;
	s += TAB + "glLightfv(GL_LIGHT" + id_luce + ", GL_SPECULAR, light_specular" + id_luce + ");" + LINE;

	return s;
}

string GeneratoreCodiceProgetto::getCodiceVariabiliPlane(){
	return codiceVariabiliPlane;
}

string GeneratoreCodiceProgetto::getCodiceVariabiliTexture(){
	return codiceVariabiliTexture;
}

string GeneratoreCodiceProgetto::getCodiceCaricaTexture(){
	return codiceCaricaTexture;
}

string GeneratoreCodiceProgetto::getCodiceAbilitaTexture(){
	return "\tglEnable(GL_TEXTURE_2D);\n\tglEnable(GL_TEXTURE_GEN_S);\n\tglEnable(GL_TEXTURE_GEN_T);\n\n";
}

string GeneratoreCodiceProgetto::getCodiceDisabilitaTexture(){
	return "\tglDisable(GL_TEXTURE_2D);\n\tglDisable(GL_TEXTURE_GEN_S);\n\tglDisable(GL_TEXTURE_GEN_T);\n\n";
}

string GeneratoreCodiceProgetto::getCodiceDisegnoSkybox(){
	Skybox *s = p->getSkybox();
	if(!s->abilitato)return "";
	string codiceDisegnoSkybox = "// DISEGNO LA SKYBOX \n";

	char s_posizioneY[20];
	sprintf_s(s_posizioneY, "%f",s->posizioneY);
	string posizioneY(s_posizioneY);
	
	codiceDisegnoSkybox += TAB + "disegnaSkybox(idTextureSkybox, " + posizioneY + ");" + LINE;
	codiceVariabiliTexture += LINE + "GLint idTextureSkybox;";

	string codiceCaricamentoSkybox = "char *texCubeFaces[6];" + LINE;
	for(int i=0;i<6;i++){
		char s_i[2];
		sprintf_s(s_i, "%i",i);
		string string_i(s_i);
		string nomeFile = s->getTexture(i);
		Utilita::convertiInDoppioSlash(&nomeFile);
		codiceCaricamentoSkybox += TAB + "texCubeFaces[" + string_i + "] = \"" + nomeFile + "\";" + LINE;
	}
	codiceCaricamentoSkybox += TAB + "idTextureSkybox = caricaTextureCubeMap(texCubeFaces);";
	codiceCaricaTexture +=  LINE + TAB + codiceCaricamentoSkybox;
	
	return codiceDisegnoSkybox;
}

string GeneratoreCodiceProgetto::getCodiceDisegnoPavimento(){
	Pavimento *pavimento = p->getPavimento();
	if(!pavimento->abilitato)return "";
	string codiceDisegnoPavimento = "// DISEGNO IL PAVIMENTO \n";

	char s_materiale[255];
	sprintf_s(s_materiale, "setMateriale(%i);",pavimento->idMateriale);
	string materiale(s_materiale);

	char s_colore[255];
	sprintf_s(s_colore, "setColore(%i);",pavimento->idColore);
	string colore(s_colore);

	char s_tassellazione[10];
	sprintf_s(s_tassellazione, "%i",pavimento->tassellazione);
	string tassellazione(s_tassellazione);

	string wireframe = "false";
	if(pavimento->wireframe)wireframe = "true";

	codiceDisegnoPavimento += TAB + colore + LINE;
	codiceDisegnoPavimento += TAB + materiale + LINE;
	codiceDisegnoPavimento += TAB + "disegnaPavimento(" + tassellazione + ", " + wireframe + ");" + LINE;

	return codiceDisegnoPavimento;
}
string GeneratoreCodiceProgetto::getCodiceDisegnoOggetti(){
	string codiceDisegnoOggetti = "// DISEGNO GLI OGGETTI \n";
	codiceVariabiliTexture = "// Variabili texture";
	codiceCaricaTexture = "\t// Carico le texture";
	codiceVariabiliPlane = "// Variabili plane-s plane-t";


	list<Oggetto>::iterator o;
	int pos = 0;
	for (o = p->listaOggetti.begin(); o != p->listaOggetti.end(); ++o){
		Oggetto* oggetto = &*o;

		if(o->getTexture()==NULL && statoTextureAbilitata==true){
			//Devo disabilitare le texture
			codiceDisegnoOggetti += getCodiceDisabilitaTexture();
			statoTextureAbilitata=false;
		}
		if(o->getTexture()!=NULL && statoTextureAbilitata==false){
			//Devo abilitare le texture
			codiceDisegnoOggetti += getCodiceAbilitaTexture();
			statoTextureAbilitata=true;
		}
		
		GeneratoreCodiceOggetto *generatoreOggetto = new GeneratoreCodiceOggetto(oggetto,pos);
		codiceDisegnoOggetti += generatoreOggetto->genera() + "\n";
		codiceVariabiliTexture += generatoreOggetto->getVariabileTexture();
		codiceVariabiliPlane += generatoreOggetto->getVariabilePlane();
		codiceCaricaTexture += generatoreOggetto->getCaricamentoTexture();

		pos++;
	}		
	
	if(statoTextureAbilitata==true){
		//Devo disabilitare le texture
		codiceDisegnoOggetti += getCodiceDisabilitaTexture();
		statoTextureAbilitata=false;
	}


	return codiceDisegnoOggetti;
}

void GeneratoreCodiceProgetto::setCamera(vector3f p,vector3f a,vector3f d){
	pos = p;
	at = a;
	dir = d;
}