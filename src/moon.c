#include <stdio.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "delta.h"
#include "flag.h"
#include "image.h"
#include "shader.h"
#include "texture.h"

unsigned int show_moon;
GLuint moon_vao, moon_vbo;
GLint moon_uniProj, moon_uniView, moon_uniModel, moon_uniRotation;
glm::mat4 moon_proj, moon_view, moon_model, moon_rotation;
GLfloat moon_vertices[] = {
-0.5f, -0.5f,  0.0f, 0.0f,
-0.5f, 0.5f,  0.0f, 1.0f,
0.5f, 0.5f,  1.0f, 1.0f,
0.5f, 0.5f,  1.0f, 1.0f,
0.5f, -0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.0f, 0.0f
};

void MoonInit(void) {
	show_moon = 0;
	glUseProgram(moon_shader_program);
	glGenVertexArrays(1, &moon_vao);
	printf("vao: %u\n", moon_vao);
	glBindVertexArray(moon_vao);
	glGenBuffers(1, &moon_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, moon_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(moon_vertices), moon_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(moon_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	GLint texcoord_attrib = glGetAttribLocation(moon_shader_program, "texcoord");
	glEnableVertexAttribArray(texcoord_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	GLint tex_attrib = glGetUniformLocation(moon_shader_program, "tex_moon");
	glUniform1i(tex_attrib, 0);
	moon_uniProj = glGetUniformLocation(moon_shader_program, "proj");
	moon_uniView = glGetUniformLocation(moon_shader_program, "view");
	moon_uniModel = glGetUniformLocation(moon_shader_program, "model");
	moon_uniRotation = glGetUniformLocation(moon_shader_program, "rotation");
	moon_proj = glm::perspective(glm::radians(45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 250.0f);
	moon_view = glm::lookAt(glm::vec3(cam.x, cam.y, cam.z),
		glm::vec3(cam.lx, cam.ly, cam.lz),
		glm::vec3(0.0f, 1.0f, 0.0f));
	moon_model = glm::translate(glm::mat4(1.0), glm::vec3(2.0f+cam.x,1.0f+cam.y,10.0f+cam.z));
	moon_rotation = glm::rotate(glm::mat4(1.0), delta, glm::vec3(0.0f,1.0f,0.0f));
	glUniformMatrix4fv(moon_uniProj, 1, GL_FALSE, glm::value_ptr(moon_proj));
	glUniformMatrix4fv(moon_uniView, 1, GL_FALSE, glm::value_ptr(moon_view));
	glUniformMatrix4fv(moon_uniModel, 1, GL_FALSE, glm::value_ptr(moon_model));
	glUniformMatrix4fv(moon_uniRotation, 1, GL_FALSE, glm::value_ptr(moon_rotation));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void MoonDraw(void) {
	glUseProgram(moon_shader_program);
	moon_proj = glm::perspective(glm::radians(45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 250.0f);
	moon_view = glm::lookAt(glm::vec3(cam.x, cam.y, cam.z),
		glm::vec3(cam.lx, cam.ly, cam.lz),
		glm::vec3(0.0f, 1.0f, 0.0f));
	moon_model = glm::translate(glm::mat4(1.0), glm::vec3(2.0f + cam.x, 1.0f + cam.y, 10.0f + cam.z));
	moon_rotation = glm::rotate(glm::mat4(1.0), delta, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(moon_uniProj, 1, GL_FALSE, glm::value_ptr(moon_proj));
	glUniformMatrix4fv(moon_uniView, 1, GL_FALSE, glm::value_ptr(moon_view));
	glUniformMatrix4fv(moon_uniModel, 1, GL_FALSE, glm::value_ptr(moon_model));
	glUniformMatrix4fv(moon_uniRotation, 1, GL_FALSE, glm::value_ptr(moon_rotation));
	glBindBuffer(GL_ARRAY_BUFFER, moon_vbo);
	glBindTexture(GL_TEXTURE_2D, texture_moon);
	glBindVertexArray(moon_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}
