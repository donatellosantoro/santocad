// |              Generated by SantoCAD                |
// |  Donatello Santoro (donatello.santoro@gmail.com)  |
// |  Michele Santomauro (michelesantomauro@gmail.com) |
// |                                                   |
// |  http://code.google.com/p/santocad/               |

GLuint caricaTextureRepeat(char textName[64]);
GLuint caricaTextureClamp(char textName[64]);
GLuint caricaTextureMipmapRepeat(char textName[64]);
GLuint caricaTextureMipmapClamp(char textName[64]);
GLuint caricaTexture(char textName[64], boolean repeat, boolean mipmap);
GLuint caricaTextureCubeMap(char **texCubeFaces);