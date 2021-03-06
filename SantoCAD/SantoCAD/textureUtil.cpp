#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "FreeImage.h"
#include "Logger.h"
#include "textureUtil.h"

GLuint caricaTextureRepeat(char textName[255]){
	return caricaTexture(textName,true,false);
}

GLuint caricaTextureClamp(char textName[255]){
	return caricaTexture(textName,false,false);
}

GLuint caricaTextureMipmapRepeat(char textName[255]){
	return caricaTexture(textName,true,true);
}

GLuint caricaTextureMipmapClamp(char textName[255]){
	return caricaTexture(textName,false,true);
}

GLuint caricaTexture(char textName[255], boolean repeat, boolean mipmap){
	string s(textName);
	Logger::debug("Loading texture " + s);
	GLuint idTexture;

	// Otteniamo il formato dell'immagine
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(textName, 0);

	// Carichiamo l'immagine
	FIBITMAP *dib = FreeImage_Load(fifmt, textName,0);

	// L'immagine � convertita nel formato GL_RGB
	dib = FreeImage_ConvertTo24Bits(dib);

	if( dib != NULL ){
		glGenTextures( 1, &idTexture );
		glBindTexture( GL_TEXTURE_2D, idTexture );
		

		// Puntatore ai dati dell'immagine
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		// Poich� FreeImage carica le immagini nel formato BGR
		// usiamo l'opzione GL_BGR_EXT per indicare ad OpenGL
		// che il formato dei dati � BGR
		// L'alternativa sarebbe stata quella di convertire
		//l'immagine dopo averla caricata da BGR a RGB
		if(repeat){
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		}else{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		}

		if(mipmap){    
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
		}else{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		}

		glTexImage2D( GL_TEXTURE_2D, 0, 3, 
									FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
									GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );

		// Deallochiamo l'immagine
		FreeImage_Unload(dib);
		return idTexture;
	}else{
		Logger::error("Unable to load texture " + s);
		return -1;
	}
}

static GLenum cube[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						 GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						 GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						 GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						 GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						 GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

GLuint caricaTextureCubeMap(char **texCubeFaces){
	GLuint idTexture;
	glGenTextures(1, &idTexture);
    
	// Cube Map
	glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);        
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);

	// Load Cube Map images
	for(int i = 0; i < 6; i++)
	{        
		// Otteniamo il formato dell'immagine
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texCubeFaces[i], 0);
		// Carichiamo l'immagine
		FIBITMAP *dib = FreeImage_Load(fifmt, texCubeFaces[i], 0);
		// L'immagine � convertita nel formato GL_RGB
		dib = FreeImage_ConvertTo24Bits(dib);
	
		
		string s(texCubeFaces[i]);
		Logger::debug("Loading texture " + s);
		if(dib==NULL){
			Logger::error("Unable to load texture " + s);
			return -1;
		}
		
		// Puntatore ai dati dell'immagine
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		glTexImage2D( cube[i], 0, 3, 
									FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
									GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );
		
		// Deallochiamo l'immagine
		FreeImage_Unload(dib);
	}
	return idTexture;
}