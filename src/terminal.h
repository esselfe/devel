#ifndef TERMINAL_H
#define TERMINAL_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

#define TERMINAL_COMMAND_SIZE 4096
#define TERMINAL_MAX_WORDS 10

struct Terminal {
	GLuint shader_program,
		vao, vbo,
		vertices_size,
		uni_ortho, uni_model;
	glm::mat4 model;
	GLuint cursor_position;
	char command[TERMINAL_COMMAND_SIZE];
};
extern struct Terminal term;

extern GLfloat terminal_vertices[];
extern unsigned int terminal_visible, terminal_cursor_blink;

void TerminalInit(void);
void TerminalCommandParse(void);
void TerminalKeyParse(char c);
void TerminalDraw(void);

#endif /* TERMINAL_H */
