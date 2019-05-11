#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "element.h"
#include "flag.h"
#include "image.h"
#include "render.h"
#include "shader.h"
#include "texture.h"

GLuint vao_floor, vbo_floor;
GLint uniProj_floor, uniView_floor;
glm::mat4 proj_floor, view_floor;
GLfloat vertices_floor[] = {
-50.0f, 0.0f, -50.0f,  0.0f, 10.0f,
50.0f, 0.0f, -50.0f,  10.0f, 10.0f,
50.0f, 0.0f,  50.0f,  10.0f, 0.0f,
50.0f, 0.0f,  50.0f,  10.0f, 0.0f,
-50.0f, 0.0f,  50.0f,  0.0f, 0.0f,
-50.0f, 0.0f, -50.0f,  0.0f, 10.0f
};

void FloorInit(void) {
	glUseProgram(floor_shader_program);
	glGenVertexArrays(1, &vao_floor);
	glBindVertexArray(vao_floor);
	glGenBuffers(1, &vbo_floor);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_floor), vertices_floor, GL_STATIC_DRAW);
	GLint pos_attrib3 = glGetAttribLocation(floor_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib3);
	glVertexAttribPointer(pos_attrib3, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint tex_attrib3 = glGetAttribLocation(floor_shader_program, "texcoord");
	glEnableVertexAttribArray(tex_attrib3);
	glVertexAttribPointer(tex_attrib3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glBindTexture(GL_TEXTURE_2D, texture_floor);
	glUniform1i(glGetUniformLocation(floor_shader_program, "tex_floor"), 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	uniProj_floor = glGetUniformLocation(floor_shader_program, "proj");
	uniView_floor = glGetUniformLocation(floor_shader_program, "view");
	proj_floor = glm::perspective(glm::radians(45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 1000.0f);
	view_floor = glm::lookAt(glm::vec3(cam.x, cam.y, cam.z),
		glm::vec3(cam.lx, cam.ly, cam.lz),
		glm::vec3(0.0f, 1.0f, 0.0f) );
	glUniformMatrix4fv(uniProj_floor, 1, GL_FALSE, glm::value_ptr(proj_floor));
	glUniformMatrix4fv(uniView_floor, 1, GL_FALSE, glm::value_ptr(view_floor));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FloorDraw(void) {
	glUseProgram(floor_shader_program);
	glUniformMatrix4fv(uniView_floor, 1, GL_FALSE, glm::value_ptr(matrix_view));
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor);
	glBindTexture(GL_TEXTURE_2D, texture_floor);
	glBindVertexArray(vao_floor);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
