#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "element.h"
#include "hud.h"
#include "render.h"
#include "score.h"
#include "shader.h"
#include "texture.h"

GLuint hud_vao, hud_vbo;
GLint hud_uniOrtho, hud_uniModel;
glm::mat4 hud_ortho, hud_model;
GLfloat hud_vertices[4] = {
4.0f, 10.0f,
5.0f, 10.0f
};
GLuint hudelem_vao, hudelem_vbo;
GLint hudelem_uniOrtho, hudelem_uniModel;
glm::mat4 hudelem_ortho, hudelem_model;
GLfloat hudelem_vertices[] = {
0.0f, 0.0f,  0.0f, 0.0f,
0.0f, 8.0f,  0.0f, 1.0f,
8.0f, 8.0f,  1.0f, 1.0f,
8.0f, 8.0f,  1.0f, 1.0f,
8.0f, 0.0f,  1.0f, 0.0f,
0.0f, 0.0f,  0.0f, 0.0f
};
char hud_fps_text[HUD_FPS_TEXT_SIZE];
char hud_score_metal_text[HUD_SCORE_TEXT_SIZE];
char hud_score_mineral_text[HUD_SCORE_TEXT_SIZE];
char hud_element_total_text[HUD_SCORE_TEXT_SIZE];

void HudInit(void) {
	glUseProgram(hud_shader_program);
	glGenVertexArrays(1, &hud_vao);
	glBindVertexArray(hud_vao);
	glGenBuffers(1, &hud_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, hud_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hud_vertices), hud_vertices, GL_DYNAMIC_DRAW);
	GLint pos_attrib2 = glGetAttribLocation(hud_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib2);
	glVertexAttribPointer(pos_attrib2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	hud_uniOrtho = glGetUniformLocation(hud_shader_program, "ortho");
	hud_uniModel = glGetUniformLocation(hud_shader_program, "model");
	hud_ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	hud_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f + 4.0f,(GLfloat)winH - 10.0f - 4.0f, 0.0f));
	glUniformMatrix4fv(hud_uniOrtho, 1, GL_FALSE, glm::value_ptr(hud_ortho));
	glUniformMatrix4fv(hud_uniModel, 1, GL_FALSE, glm::value_ptr(hud_model));
	
	glUseProgram(hudelem_shader_program);
	glGenVertexArrays(1, &hudelem_vao);
	glGenBuffers(1, &hudelem_vbo);
	glBindVertexArray(hudelem_vao);
	glBindBuffer(GL_ARRAY_BUFFER, hudelem_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hudelem_vertices), hudelem_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(hudelem_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	GLint tex_attrib = glGetAttribLocation(hudelem_shader_program, "texcoord");
	glEnableVertexAttribArray(tex_attrib);
	glVertexAttribPointer(tex_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	
	hudelem_uniOrtho = glGetUniformLocation(hudelem_shader_program, "ortho");
	hudelem_uniModel = glGetUniformLocation(hudelem_shader_program, "model");
	hudelem_ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	hudelem_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f + 4.0f,(GLfloat)winH - 10.0f - 4.0f, 0.0f));
	glUniformMatrix4fv(hudelem_uniOrtho, 1, GL_FALSE, glm::value_ptr(hudelem_ortho));
	glUniformMatrix4fv(hudelem_uniModel, 1, GL_FALSE, glm::value_ptr(hudelem_model));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	memset(hud_fps_text, '@', HUD_FPS_TEXT_SIZE);
	sprintf_s(hud_fps_text, HUD_FPS_TEXT_SIZE, "%u fps", fps);
	memset(hud_score_metal_text, '$', HUD_SCORE_TEXT_SIZE);
	sprintf_s(hud_score_metal_text, HUD_SCORE_TEXT_SIZE, "%u", element_metal_total);
	memset(hud_score_mineral_text, '$', HUD_SCORE_TEXT_SIZE);
	sprintf_s(hud_score_mineral_text, HUD_SCORE_TEXT_SIZE, "%u", element_mineral_total);
	memset(hud_element_total_text, '@', HUD_SCORE_TEXT_SIZE);
	sprintf_s(hud_element_total_text, HUD_SCORE_TEXT_SIZE, "%u elements", root_element_list.element_total);

}

void HudDraw(void) {
	glUseProgram(hud_shader_program);
	//glm::mat4 hud_ortho2 = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	glm::mat4 hud_model2 = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f + 4.0f,(GLfloat)winH - 10.0f - 4.0f, 0.0f));
	//glUniformMatrix4fv(hud_uniOrtho, 1, GL_FALSE, glm::value_ptr(hud_ortho2));
	glUniformMatrix4fv(hud_uniModel, 1, GL_FALSE, glm::value_ptr(hud_model2));
	glBindVertexArray(hud_vao);
	glBindBuffer(GL_ARRAY_BUFFER, hud_vbo);
	++hud_vertices[2];
	glBufferData(GL_ARRAY_BUFFER, sizeof(hud_vertices), hud_vertices, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glUseProgram(hudelem_shader_program);
	//hudelem_ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	hudelem_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f + 4.0f,(GLfloat)winH - 10.0f - 4.0f, 0.0f));
	//glUniformMatrix4fv(hudelem_uniOrtho, 1, GL_FALSE, glm::value_ptr(hudelem_ortho));
	glUniformMatrix4fv(hudelem_uniModel, 1, GL_FALSE, glm::value_ptr(hudelem_model));
	glBindVertexArray(hudelem_vao);
	glBindBuffer(GL_ARRAY_BUFFER, hudelem_vbo);
	hudelem_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 32.0f, 0.0f));
	glUniformMatrix4fv(hudelem_uniModel, 1, GL_FALSE, glm::value_ptr(hudelem_model));
	glBindTexture(GL_TEXTURE_2D, texture_metal);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	hudelem_model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 52.0f, 0.0f));
	glUniformMatrix4fv(hudelem_uniModel, 1, GL_FALSE, glm::value_ptr(hudelem_model));
	glBindTexture(GL_TEXTURE_2D, texture_mineral);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUseProgram(thr_shader_program);
	thr_model = glm::translate(glm::mat4(1.0f), glm::vec3((GLfloat)winW - 20.0f, (GLfloat)winH / 2.0f, 0.0f));
	glUniformMatrix4fv(thr_uniOrtho, 1, GL_FALSE, glm::value_ptr(matrix_ortho));
	glUniformMatrix4fv(thr_uniModel, 1, GL_FALSE, glm::value_ptr(thr_model));
	glBindVertexArray(thr_vao);
	glBindBuffer(GL_ARRAY_BUFFER, thr_vbo);
	glDrawArrays(GL_LINE_STRIP, 0, 5);
	glDrawArrays(GL_TRIANGLES, 5, 6);
}
