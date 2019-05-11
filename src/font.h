#ifndef FONT_H
#define FONT_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

#define FONT_DATA_SIZE 884*16*3
#define FONT_LETTER_SIZE 8*16*3

extern GLuint font_vao, font_vbo;
extern GLuint font_uniOrtho, font_uniModel;
extern glm::mat4 font_ortho, font_model;
extern GLfloat font_vertices[];

void FontInit (void);
void FontListLetterMake (unsigned char letter);
void FontDraw (void);
void FontDrawText (unsigned int x, unsigned int y, char *text);

#endif /* FONT_H */
