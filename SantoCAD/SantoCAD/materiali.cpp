#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "materiali.h"

// Definizione Colori
GLfloat colori[11][3]={{0.5, 0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 
                      {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0},
					  {0.0, 0.0, 0.0}, {0.5, 0.25, 0.0}, {1.0, 0.5, 0.0}};

int getNumeroColori(){
	return 11;
}

char* getNomeColore(int id){
	switch(id) {
		case 0: return "Gray";
		case 1: return "Red";
		case 2: return "Green";
		case 3: return "Blue";
		case 4: return "Cyan";
		case 5: return "Magenta";
		case 6: return "Yellow";
		case 7: return "White";
		case 8: return "Black";
		case 9: return "Brown";
		case 10: return "Orange";
	}
	return "";
}

void setColore(int idColore){
	glColor3fv(colori[idColore]);
}


// Definizione Materiali
int getNumeroMateriali(){
	return 21;
}
char* getNomeMateriale(int id){
	switch(id) {
		case 0: return "Black Plastic";
		case 1: return "Black Rubber";
		case 2: return "Brass";
		case 3: return "Bronze";
		case 4: return "Chrome";
		case 5: return "Copper";
		case 6: return "Emerald";
		case 7: return "Gold";
		case 8: return "Jade";
		case 9: return "Obsidian";
		case 10: return "Pearl";
		case 11: return "Pewter";
		case 12: return "Polished Bronze";
		case 13: return "Polished Copper";
		case 14: return "Polished Gold";
		case 15: return "Polished Silver";
		case 16: return "Puby";
		case 17: return "Pilver";
		case 18: return "Turquoise";
		case 19: return "White Plastic";
		case 20: return "Default";
	}
	return "";
}

void setMateriale(int idMat){
	switch(idMat) {
		case 0: setMaterialeBlackPlastic(); break;
		case 1: setMaterialeBlackRubber(); break;
		case 2: setMaterialeBrass(); break;
		case 3: setMaterialeBronze(); break;
		case 4: setMaterialeChrome(); break;
		case 5: setMaterialeCopper(); break;
		case 6: setMaterialeEmerald(); break;
		case 7: setMaterialeGold(); break;
		case 8: setMaterialeJade(); break;
		case 9: setMaterialeObsidian(); break;
		case 10: setMaterialePearl(); break;
		case 11: setMaterialePewter(); break;
		case 12: setMaterialePolishedBronze(); break;
		case 13: setMaterialePolishedCopper(); break;
		case 14: setMaterialePolishedGold(); break;
		case 15: setMaterialePolishedSilver(); break;
		case 16: setMaterialePuby(); break;
		case 17: setMaterialePilver(); break;
		case 18: setMaterialeTurquoise(); break;
		case 19: setMaterialeWhitePlastic(); break;
		case 20: setMaterialeDefault(); break;
	}
}

void setMateriale(GLfloat mat_ambient[],GLfloat mat_diffuse[],GLfloat mat_specular[],GLfloat mat_shininess[]){
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void setMaterialeBlackPlastic(){
    GLfloat mat_ambient[] = {0.00, 0.00, 0.00}; // Ambient
    GLfloat mat_diffuse[] = {0.01, 0.01, 0.01}; // Diffuse
    GLfloat mat_specular[] = {0.50, 0.50, 0.50}; // Specular
    GLfloat mat_shininess[] = {32.0f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeBlackRubber(){
    GLfloat mat_ambient[] = {0.02, 0.02, 0.02}; // Ambient
    GLfloat mat_diffuse[] = {0.01, 0.01, 0.01}; // Diffuse
    GLfloat mat_specular[] = {0.40, 0.40, 0.40}; // Specular
    GLfloat mat_shininess[] = {10.0f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeBrass(){
    GLfloat mat_ambient[] = {0.329412, 0.223529, 0.027451}; // Ambient
    GLfloat mat_diffuse[] = {0.780392, 0.568627, 0.113725}; // Diffuse
    GLfloat mat_specular[] = {0.992157, 0.941176, 0.807843}; // Specular
    GLfloat mat_shininess[] = {27.8974f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeBronze(){
    GLfloat mat_ambient[] = {0.2125  , 0.1275  , 0.054   }; // Ambient
    GLfloat mat_diffuse[] = {0.714   , 0.4284  , 0.18144 }; // Diffuse
    GLfloat mat_specular[] ={0.393548, 0.271906, 0.166721}; // Specular
    GLfloat mat_shininess[] = {25.6f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeChrome(){
    GLfloat mat_ambient[] = {0.25,     0.25,     0.25    }; // Ambient
    GLfloat mat_diffuse[] = {0.4,      0.4,      0.4     }; // Diffuse
    GLfloat mat_specular[] ={0.774597, 0.774597, 0.774597}; // Specular
    GLfloat mat_shininess[] = {76.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeCopper(){
    GLfloat mat_ambient[] = {0.19125,  0.0735,   0.0225  }; // Ambient
    GLfloat mat_diffuse[] = {0.7038,   0.27048,  0.0828  }; // Diffuse
    GLfloat mat_specular[] ={0.256777, 0.137622, 0.086014}; // Specular
    GLfloat mat_shininess[] = {12.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeEmerald(){
    GLfloat mat_ambient[] = {0.0215,  0.1745,   0.0215 };   // Ambient
    GLfloat mat_diffuse[] = {0.07568, 0.61424,  0.07568};   // Diffuse
    GLfloat mat_specular[] ={0.633,   0.727811, 0.633  };   // Specular
    GLfloat mat_shininess[] = {76.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeGold(){
    GLfloat mat_ambient[] = {0.24725,  0.1995,   0.0745};   // Ambient
    GLfloat mat_diffuse[] = {0.75164,  0.60648,  0.22648};  // Diffuse
    GLfloat mat_specular[] ={0.628281, 0.555802, 0.366065}; // Specular
    GLfloat mat_shininess[] = {51.2f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeJade(){
    GLfloat mat_ambient[] = {0.135,    0.2225,   0.1575  }; // Ambient
    GLfloat mat_diffuse[] = {0.135,    0.2225,   0.1575  }; // Diffuse
    GLfloat mat_specular[] ={0.316228, 0.316228, 0.316228}; // Specular
    GLfloat mat_shininess[] = {12.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeObsidian(){
    GLfloat mat_ambient[] = {0.05375,  0.05,     0.06625 }; // Ambient
    GLfloat mat_diffuse[] = {0.18275,  0.17,     0.22525 }; // Diffuse
    GLfloat mat_specular[] ={0.332741, 0.328634, 0.346435}; // Specular
    GLfloat mat_shininess[] = {38.4f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePearl(){
    GLfloat mat_ambient[] = {0.25,     0.20725,  0.20725 }; // Ambient
    GLfloat mat_diffuse[] = {1.0,      0.829,    0.829   }; // Diffuse
    GLfloat mat_specular[] ={0.296648, 0.296648, 0.296648}; // Specular
    GLfloat mat_shininess[] = {11.264f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePewter(){
    GLfloat mat_ambient[] = {0.105882, 0.058824, 0.113725}; // Ambient
    GLfloat mat_diffuse[] = {0.427451, 0.470588, 0.541176}; // Diffuse
    GLfloat mat_specular[] ={0.333333, 0.333333, 0.521569}; // Specular
    GLfloat mat_shininess[] = {9.84615f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePolishedBronze(){
    GLfloat mat_ambient[] = {0.25    , 0.148   , 0.06475 }; // Ambient
    GLfloat mat_diffuse[] = {0.4     , 0.2368  , 0.1036  }; // Diffuse
    GLfloat mat_specular[] ={0.774597, 0.458561, 0.200621}; // Specular
    GLfloat mat_shininess[] = {76.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePolishedCopper(){
    GLfloat mat_ambient[] = {0.2295,   0.08825,  0.0275   };    // Ambient
    GLfloat mat_diffuse[] = {0.5508,   0.2118,   0.066    };    // Diffuse
    GLfloat mat_specular[] ={0.580594, 0.223257, 0.0695701};    // Specular
    GLfloat mat_shininess[] = {51.2f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePolishedGold(){
    GLfloat mat_ambient[] = {0.24725,  0.2245,   0.0645  }; // Ambient
    GLfloat mat_diffuse[] = {0.34615,  0.3143,   0.0903  }; // Diffuse
    GLfloat mat_specular[] ={0.797357, 0.723991, 0.208006}; // Specular
    GLfloat mat_shininess[] = {83.2f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePolishedSilver(){
    GLfloat mat_ambient[] = {0.23125, 0.23125, 0.23125};    // Ambient
    GLfloat mat_diffuse[] = {0.2775,  0.2775,  0.2775};     // Diffuse
    GLfloat mat_specular[] ={0.773911, 0.773911, 0.773911}; // Specular
    GLfloat mat_shininess[] = {89.6f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePuby(){
    GLfloat mat_ambient[] = {0.1745,   0.01175,  0.01175};  // Ambient
    GLfloat mat_diffuse[] = {0.61424,  0.04136,  0.04136};  // Diffuse
    GLfloat mat_specular[] ={0.727811, 0.626959, 0.626959}; // Specular
    GLfloat mat_shininess[] = {76.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialePilver(){
    GLfloat mat_ambient[] = {0.19225,  0.19225,  0.19225 }; // Ambient
    GLfloat mat_diffuse[] = {0.50754,  0.50754,  0.50754 }; // Diffuse
    GLfloat mat_specular[] ={0.508273, 0.508273, 0.508273}; // Specular
    GLfloat mat_shininess[] = {51.2f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeTurquoise(){
    GLfloat mat_ambient[] = {0.1,      0.18725, 0.1745  };  // Ambient
    GLfloat mat_diffuse[] = {0.396,    0.74151, 0.69102 };  // Diffuse
    GLfloat mat_specular[] ={0.297254, 0.30829, 0.306678};  // Specular
    GLfloat mat_shininess[] = {12.8f};                       // Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}

void setMaterialeWhitePlastic(){
    GLfloat mat_ambient[] = {0.00, 0.00, 0.00}; // Ambient
    GLfloat mat_diffuse[] = {0.55, 0.55, 0.55}; // Diffuse
    GLfloat mat_specular[] ={0.70, 0.70, 0.70}; // Specular
    GLfloat mat_shininess[] = {32.0f};		// Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}


void setMaterialeDefault(){
    GLfloat mat_ambient[] = {1.00, 1.00, 1.00}; // Ambient
    GLfloat mat_diffuse[] = {1.00, 1.00, 1.00}; // Diffuse
    GLfloat mat_specular[] ={1.00, 1.00, 1.00}; // Specular
    GLfloat mat_shininess[] = {0.0f};		// Shininess
	setMateriale(mat_ambient,mat_diffuse,mat_specular,mat_shininess);
}