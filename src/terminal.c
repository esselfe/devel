#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "element.h"
#include "render.h"
#include "shader.h"
#include "terminal.h"

struct Terminal term;
unsigned int terminal_visible, terminal_cursor_blink;
GLfloat terminal_vertices[] = { // x, y, r, g, b
0.0f, 0.0f, 0.3f, 0.45f, 0.5f, // command background
0.0f, 24.0f, 0.3f, 0.45f, 0.5f,
800.0f, 24.0f, 0.3f, 0.45f, 0.5f,
800.0f, 24.0f, 0.3f, 0.45f, 0.5f,
800.0f, 0.0f, 0.3f, 0.45f, 0.5f,
0.0f, 0.0f, 0.3f, 0.45f, 0.5f,
4.0f, 2.0f,  0.1f, 0.15f, 0.2f,// cursor
4.0f, 38.0f, 0.1f, 0.15f, 0.2f
};

static const GLchar *terminal_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"uniform mat4 ortho;"
"uniform mat4 model;"
"void main() {"
"  Color = color;"
"  if (gl_VertexID <= 5) {"
"	gl_Position = ortho * model * vec4(position, -0.1f, 1.0f); }"
"  else {"
	"  gl_Position = ortho * model * vec4(position, 0.0f, 1.0f); }"
"}";
static const GLchar *terminal_fragment_source =
"#version 330 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
"	outColor = vec4(Color, 1.0f);"
"}";

void TerminalInit(void) {
	terminal_visible = 0;
	terminal_cursor_blink = 1;
	memset(term.command, 0, TERMINAL_COMMAND_SIZE);
	ShaderCreate(&term.shader_program, terminal_vertex_source, terminal_fragment_source);
	glUseProgram(term.shader_program);
	glGenVertexArrays(1, &term.vao);
	glBindVertexArray(term.vao);
	glGenBuffers(1, &term.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, term.vbo);
	term.vertices_size = sizeof(terminal_vertices);
	glBufferData(GL_ARRAY_BUFFER, term.vertices_size, terminal_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(term.shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint col_attrib = glGetAttribLocation(term.shader_program, "color");
	glEnableVertexAttribArray(col_attrib);
	glVertexAttribPointer(col_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

	term.uni_ortho = glGetUniformLocation(term.shader_program, "ortho");
	term.uni_model = glGetUniformLocation(term.shader_program, "model");
	term.model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f));
	glUniformMatrix4fv(term.uni_model, 1, GL_FALSE, glm::value_ptr(term.model));
	glUniformMatrix4fv(term.uni_ortho, 1, GL_FALSE, glm::value_ptr(matrix_ortho));
}

void TerminalCommandParse(void) {
	unsigned int cnt = 0, wcnt = 0;
	char w[TERMINAL_MAX_WORDS][64];
	memset(w, 0, TERMINAL_MAX_WORDS * 64);
	char *c = term.command;
	while (1) {
		if (*c == '\0') {
			w[wcnt][cnt] = '\0';
			break;
		}
		else if (*c == ' ') {
			if (cnt == 0) {
				++c;
				continue;
			}
			w[wcnt][cnt] = '\0';
			if (wcnt >= TERMINAL_MAX_WORDS) break;
			++wcnt;
			cnt = 0;
			++c;
			continue;
		}
		w[wcnt][cnt++] = *c;
		++c;
	}

	if (strcmp(w[0],"camera")==0) {
		if (strcmp(w[1],"get")==0) {
			if (strcmp(w[2],"position")==0)
				printf("%.2f %.2f %.2f %.2f %.2f %.2f\n", cam.x, cam.y, cam.z, cam.x, cam.ly, cam.lz);
		}
		else if (strcmp(w[1],"set")==0) {
			if (strcmp(w[2],"position")==0) {
				cam.x = (GLfloat)atoi(w[3]);
				cam.y = (GLfloat)atoi(w[4]);
				cam.z = (GLfloat)atoi(w[5]);
				cam.lx = cam.x;
				cam.ly = cam.y;
				cam.lz = cam.z + 1.0f;
			}
		}
	}
	else if (strcmp(w[0], "element") == 0) {
		if (strcmp(w[1],"add")==0) {
			unsigned int cnt, num = (unsigned int) atoi(w[2]);
			for (cnt = 0; cnt < num; cnt++) {
				if (cnt % 2) ElementAdd(ELEMENT_TYPE_METAL);
				else ElementAdd(ELEMENT_TYPE_MINERAL);
			}
		}
		else if (strcmp(w[1], "remove") == 0) {
			ElementRemove((unsigned int)atoi(w[2]));
		}
	}
	
	if (strcmp(term.command,"200elements")==0) {
		unsigned int cnt;
		for (cnt = root_element_list.element_total; cnt < 200; cnt++) {
			if (cnt % 2) ElementAdd(ELEMENT_TYPE_METAL);
			else ElementAdd(ELEMENT_TYPE_MINERAL);
		}
	}



	terminal_vertices[30] = 4.0f;
	terminal_vertices[35] = 4.0f;
	glUseProgram(term.shader_program);
	glBindBuffer(GL_ARRAY_BUFFER, term.vbo);
	glBufferData(GL_ARRAY_BUFFER, term.vertices_size, terminal_vertices, GL_DYNAMIC_DRAW);
	memset(term.command, 0, TERMINAL_COMMAND_SIZE);
	terminal_visible = 0;
	term.cursor_position = 0;
}

void TerminalKeyParse(char c) {
	term.command[term.cursor_position] = c;
	term.command[term.cursor_position + 1] = '\0';
	++term.cursor_position;
	terminal_vertices[30] = 4.0f + 8.0f *(GLfloat)term.cursor_position;
	terminal_vertices[35] = terminal_vertices[30];
	glUseProgram(term.shader_program);
	glBindBuffer(GL_ARRAY_BUFFER, term.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(terminal_vertices), terminal_vertices, GL_DYNAMIC_DRAW);
}

void TerminalDraw(void) {
	glUseProgram(term.shader_program);
	glm::mat4 ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	term.model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 0.0f));
	glUniformMatrix4fv(term.uni_ortho, 1, GL_FALSE, glm::value_ptr(ortho));
	glUniformMatrix4fv(term.uni_model, 1, GL_FALSE, glm::value_ptr(term.model));
	glBindBuffer(GL_ARRAY_BUFFER, term.vbo);
	glBindVertexArray(term.vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	if (terminal_cursor_blink) glDrawArrays(GL_LINES, 6, 2);
}
