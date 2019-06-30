#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "font.h"
#include "hud.h"
#include "shader.h"
#include "terminal.h"

unsigned char *font_data;
unsigned char *font_letter;
unsigned int bytes_per_line = (884*3);
GLuint font_vao, font_vbo;
GLuint font_uniOrtho, font_uniModel;
glm::mat4 font_ortho, font_model;
GLfloat font_vertices[] = {
0.0f,0.0f, 0.0f,0.0f,
0.0f,16.0f, 0.0f,0.9f,
8.0f,16.0f, 1.0f,0.9f,
8.0f,16.0f, 1.0f,0.9f,
8.0f,0.0f, 1.0f,0.0f,
0.0f,0.0f, 0.0f,0.0f
};

void FontInit(void) {
	unsigned int cnt;
	font_data = (unsigned char *)malloc(FONT_DATA_SIZE); // hold the whole image(courier-884x16.raw)
	font_letter = (unsigned char *)malloc(FONT_LETTER_SIZE);
	char filename[] = "images/courier-884x16.raw";
	FILE *fp;
#ifdef LINUX
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("devel:FontInit(): Cannot open %s: %s\n", filename, strerror(errno));
		return;
	}
#else
	fopen_s(&fp, filename, "r");
	if (fp == NULL) {
		char buffer[128];
		strerror_s(buffer, 128, errno);
		printf("devel:FontInit(): Cannot open %s: %s\n", filename, buffer);
		return;
	}
#endif
	if (verbose) {
		fseek(fp, 0, SEEK_END);
		printf("font image size: %lu | %d\n", ftell(fp),884*16*3);
		fseek(fp, 0, SEEK_SET);
	}
	fread(font_data, 1, FONT_DATA_SIZE, fp);
	fclose(fp);
	
	glUseProgram(font_shader_program);
	glGenVertexArrays(1, &font_vao);
	glGenBuffers(1, &font_vbo);
	glBindVertexArray(font_vao);
	glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(font_vertices), font_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(font_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	GLint tex_attrib = glGetAttribLocation(font_shader_program, "texcoord");
	glEnableVertexAttribArray(tex_attrib);
	glVertexAttribPointer(tex_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	
	char c;
	for (cnt = 0, c = ' '; cnt < 94; cnt++,c++) {
		FontListLetterMake(c);
	}
	free(font_data);
	free(font_letter);
	
	font_uniOrtho = glGetUniformLocation(font_shader_program, "ortho");
	font_uniModel = glGetUniformLocation(font_shader_program, "model");
	font_ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	font_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f + 4.0f,4.0f + 4.0f, 0.0f));
	glUniformMatrix4fv(font_uniOrtho, 1, GL_FALSE, glm::value_ptr(font_ortho));
	glUniformMatrix4fv(font_uniModel, 1, GL_FALSE, glm::value_ptr(font_model));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontListLetterMake(unsigned char letter) {
	unsigned int cnt, iter, offset;
	for (cnt = 0, offset = (letter-30)*9*3-15; cnt < FONT_LETTER_SIZE; cnt += 8*3) {
		for (iter = 0; iter < 24; iter++)
			*(font_letter + cnt + iter) = *(font_data + offset + iter);
		offset += bytes_per_line;
	}
	
	GLuint texture;
	glGenTextures(1, &texture);
	if (verbose) printf("texture font %u:%c: #%u\n", letter, letter, texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 8, 16,
				  0, GL_RGB, GL_UNSIGNED_BYTE, font_letter);
	glUniform1i(glGetUniformLocation(font_shader_program, "font_texture"), 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontDraw(void) {
	glUseProgram(font_shader_program);
	glBindVertexArray(font_vao);
	glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
	
	FontDrawText(4, 4 + 4, hud_fps_text);
	FontDrawText(4 + 12, 4 + 4 + 20, hud_score_metal_text);
	FontDrawText(4 + 12, 4 + 4 + 40, hud_score_mineral_text);
	FontDrawText(4 + 12, 4 + 4 + 60, hud_element_total_text);
	if (cam.thr == 100)
		FontDrawText(winW - 40, winH / 2, cam.thr_text);
	else if (cam.thr < 100 && cam.thr >= 10)
		FontDrawText(winW - 32, winH / 2, cam.thr_text);
	else if (cam.thr < 10)
		FontDrawText(winW - 24, winH / 2, cam.thr_text);
	//if (terminal_visible && term.cursor_position != 0)
		FontDrawText(14.0, (GLfloat)winH - 16.0f - 14.0f, term.command);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FontDrawText(unsigned int x, unsigned int y, char *text) {
	unsigned char *c;
	unsigned int cnt;
	for (c = (unsigned char *)text, cnt = 0; *c != '\0'; c++, cnt++) {
		font_model = glm::translate(glm::mat4(1.0f), glm::vec3((GLfloat)x + (GLfloat)cnt * 8.0f, (GLfloat)y, 0.1f));
		glUniformMatrix4fv(font_uniModel, 1, GL_FALSE, glm::value_ptr(font_model));
		// rem font texture ids start @ 1 and the first letter is 32(see font.c glGenTextures() call)
		glBindTexture(GL_TEXTURE_2D, (*c)-31);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

