GLuint caricaTextureRepeat(char textName[64]);
GLuint caricaTextureClamp(char textName[64]);
GLuint caricaTextureMipmapRepeat(char textName[64]);
GLuint caricaTextureMipmapClamp(char textName[64]);
GLuint caricaTexture(char textName[64], boolean repeat, boolean mipmap);
GLuint caricaTextureCubeMap(char **texCubeFaces);