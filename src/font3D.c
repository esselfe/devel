#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "font3D.h"
#include "font3D.h"
#include "hud.h"
#include "image.h"
#include "render.h"
#include "shader.h"
#include "score.h"
#include "sound.h"
#include "texture.h"

GLuint font3D_vao, font3D_vbo;
GLuint font3D_uniProj, font3D_uniView, font3D_uniModel, font3D_uniRotation;
glm::mat4 font3D_model, font3D_rotation;
GLfloat font3D_vertices[] = {
0.0f,0.0f, 0.0f,0.0f,
0.0f,1.0f, 0.0f,1.0f,
1.0f,1.0f, 1.0f,1.0f,
1.0f,1.0f, 1.0f,1.0f,
1.0f,0.0f, 1.0f,0.0f,
0.0f,0.0f, 0.0f,0.0f
};

void Font3DInit(void) {
	glUseProgram(font3D_shader_program);
	glGenVertexArrays(1, &font3D_vao);
	glGenBuffers(1, &font3D_vbo);
	glBindVertexArray(font3D_vao);
	glBindBuffer(GL_ARRAY_BUFFER, font3D_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(font3D_vertices), font3D_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(font3D_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	GLint tex_attrib = glGetAttribLocation(font3D_shader_program, "texcoord");
	glEnableVertexAttribArray(tex_attrib);
	glVertexAttribPointer(tex_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

	GLubyte font3D_letter[8*16*3];
	memset(font3D_letter, '#', 8*16*3);
	GLuint texture;
    glGenTextures(1, &texture);
//    if (verbose) printf("texture font %u:%c: #%u\n", letter, letter, texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 8, 16,
                  0, GL_RGB, GL_UNSIGNED_BYTE, font3D_letter);
    glUniform1i(glGetUniformLocation(font3D_shader_program, "tex_font3D"), 0);
    glBindTexture(GL_TEXTURE_2D, 0);
	
	font3D_uniProj = glGetUniformLocation(font3D_shader_program, "proj");
	font3D_uniView = glGetUniformLocation(font3D_shader_program, "view");
	font3D_uniModel = glGetUniformLocation(font3D_shader_program, "model");
	font3D_uniRotation = glGetUniformLocation(font3D_shader_program, "rotation");
	font3D_model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f));
	font3D_rotation = glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(font3D_uniProj, 1, GL_FALSE, glm::value_ptr(matrix_projection));
	glUniformMatrix4fv(font3D_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
	glUniformMatrix4fv(font3D_uniModel, 1, GL_FALSE, glm::value_ptr(font3D_model));
	glUniformMatrix4fv(font3D_uniRotation, 1, GL_FALSE, glm::value_ptr(font3D_rotation));
	
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Font3DDraw(void) {
	glUseProgram(font3D_shader_program);
	glBindVertexArray(font3D_vao);
	glBindBuffer(GL_ARRAY_BUFFER, font3D_vbo);

		font3D_model = glm::translate(glm::mat4(1.0), glm::vec3(2.0, 0.5, 1.0));
		font3D_rotation = glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(font3D_uniProj, 1, GL_FALSE, glm::value_ptr(matrix_projection));
		glUniformMatrix4fv(font3D_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
		glUniformMatrix4fv(font3D_uniModel, 1, GL_FALSE, glm::value_ptr(font3D_model));
		glUniformMatrix4fv(font3D_uniRotation, 1, GL_FALSE, glm::value_ptr(font3D_rotation));
		glBindTexture(GL_TEXTURE_2D, texture_metal);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

