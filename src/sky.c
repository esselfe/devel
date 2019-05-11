
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "render.h"
#include "shader.h"
#include "texture.h"

GLuint sky_vao, sky_vbo;
GLuint sky_uniProj, sky_uniView, sky_uniModel;
glm::mat4 sky_proj, sky_view, sky_model;
GLfloat sky_vertices[] = {
-500.0f, -50.0f, 500.0f,    0.0f, 0.0f,
-500.0f, 300.0f, 500.0f,    0.0f, 1.0f,
500.0f, 300.0f, 500.0f,    1.0f, 1.0f,
500.0f, 300.0f, 500.0f,    1.0f, 1.0f,
500.0f, -50.0f, 500.0f,    1.0f, 0.0f,
-500.0f, -50.0f, 500.0f,    0.0f, 0.0f,

500.0f, -50.0f, 500.0f,    0.0f, 0.0f,
500.0f, 300.0f, 500.0f,    0.0f, 1.0f,
500.0f, 300.0f, -500.0f,    1.0f, 1.0f,
500.0f, 300.0f, -500.0f,    1.0f, 1.0f,
500.0f, -50.0f, -500.0f,    1.0f, 0.0f,
500.0f, -50.0f, 500.0f,    0.0f, 0.0f,

500.0f, -50.0f, -500.0f,    0.0f, 0.0f,
500.0f, 300.0f, -500.0f,    0.0f, 1.0f,
-500.0f, 300.0f, -500.0f,    1.0f, 1.0f,
-500.0f, 300.0f, -500.0f,    1.0f, 1.0f,
-500.0f, -50.0f, -500.0f,    1.0f, 0.0f,
500.0f, -50.0f, -500.0f,    0.0f, 0.0f,

-500.0f, -50.0f, -500.0f,    0.0f, 0.0f,
-500.0f, 300.0f, -500.0f,    0.0f, 1.0f,
-500.0f, 300.0f, 500.0f,    1.0f, 1.0f,
-500.0f, 300.0f, 500.0f,    1.0f, 1.0f,
-500.0f, -50.0f, 500.0f,    1.0f, 0.0f,
-500.0f, -50.0f, -500.0f,    0.0f, 0.0f
};

void SkyInit (void) {
	glUseProgram (sky_shader_program);
	glGenVertexArrays (1, &sky_vao);
	glBindVertexArray (sky_vao);
	glGenBuffers (1, &sky_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, sky_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(sky_vertices), sky_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation (sky_shader_program, "position");
	glEnableVertexAttribArray (pos_attrib);
	glVertexAttribPointer (pos_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint tex_attrib = glGetAttribLocation (sky_shader_program, "texcoord");
	glEnableVertexAttribArray (tex_attrib);
	glVertexAttribPointer (tex_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

	sky_uniProj = glGetUniformLocation (sky_shader_program, "proj");
	sky_uniView = glGetUniformLocation (sky_shader_program, "view");
	sky_uniModel = glGetUniformLocation (sky_shader_program, "model");
	sky_proj = glm::perspective (glm::radians (45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 850.0f);
	sky_view = glm::lookAt (glm::vec3 (cam.x, cam.y, cam.z),
		glm::vec3 (cam.lx, cam.ly, cam.lz),
		glm::vec3 (0.0f, 1.0f, 0.0f));
	sky_model = glm::translate (glm::mat4(1.0f), glm::vec3(cam.x, cam.y, cam.z));
	glUniformMatrix4fv (sky_uniProj, 1, GL_FALSE, glm::value_ptr (sky_proj));
	glUniformMatrix4fv (sky_uniView, 1, GL_FALSE, glm::value_ptr (sky_view));
	glUniformMatrix4fv (sky_uniModel, 1, GL_FALSE, glm::value_ptr (sky_model));

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);
}

void SkyDraw (void) {
	glUseProgram (sky_shader_program);
	sky_model = glm::translate (glm::mat4 (1.0f), glm::vec3 (cam.x, cam.y, cam.z));
	glUniformMatrix4fv (sky_uniView, 1, GL_FALSE, glm::value_ptr (matrix_view));
	glUniformMatrix4fv (sky_uniModel, 1, GL_FALSE, glm::value_ptr (sky_model));
	glBindBuffer (GL_ARRAY_BUFFER, sky_vbo);
	glBindVertexArray (sky_vao);

	glBindTexture (GL_TEXTURE_2D, texture_sky01);
	glDrawArrays (GL_TRIANGLES, 0, 6);

	glBindTexture (GL_TEXTURE_2D, texture_sky02);
	glDrawArrays (GL_TRIANGLES, 6, 6);
	
	glBindTexture (GL_TEXTURE_2D, texture_sky03);
	glDrawArrays (GL_TRIANGLES, 12, 6);

	glBindTexture (GL_TEXTURE_2D, texture_sky04);
	glDrawArrays (GL_TRIANGLES, 18, 6);
}
