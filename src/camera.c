#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "events.h"
#include "hud.h"
#include "render.h"
#include "shader.h"

struct Camera cam;

GLuint thr_vao, thr_vbo;
GLuint thr_uniOrtho, thr_uniModel;
glm::mat4 thr_model;
GLfloat thr_vertices[] = { // x, y,  r, g, b
	0.0f, 0.0f,	0.2f, 0.2f, 0.2f,
	0.0f, 100.0f,	0.2f, 0.2f, 0.2f,
	10.0f, 100.0f,	0.2f, 0.2f, 0.2f,
	10.0f, 0.0f,	0.2f, 0.2f, 0.2f,
	0.0f, 0.0f,	0.2f, 0.2f, 0.2f,

	0.0f, 0.0f,	0.4f, 0.5f, 0.6f,
	0.0f, 10.0f,	0.4f, 0.5f, 0.6f,
	10.0f, 10.0f,	0.4f, 0.5f, 0.6f,
	10.0f, 10.0f,	0.4f, 0.5f, 0.6f,
	10.0f, 0.0f,	0.4f, 0.5f, 0.6f,
	0.0f, 0.0f,	0.4f, 0.5f, 0.6f
};

void CameraInit(void) {
	cam.x = 0.0f;
	cam.y = 1.2f;
	cam.z = -5.0f;
	cam.lx = 0.0f;
	cam.ly = 1.2f;
	cam.lz = 0.0f;
	cam.step = 0.1f;
	cam.angle_y = 0.0f;
	cam.angle_step = 0.01f;
	cam.thr = 10.0f;
	cam.moving = MOVE_IDLE;
	sprintf_s(cam.thr_text, 5, "%u%%", (unsigned int)cam.thr);

	glGenVertexArrays(1, &thr_vao);
	glBindVertexArray(thr_vao);
	glGenBuffers(1, &thr_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, thr_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thr_vertices), thr_vertices, GL_DYNAMIC_DRAW);
	GLint pos_attrib = glGetAttribLocation(thr_shader_program, "position");
	glEnableVertexAttribArray(pos_attrib);
	glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint col_attrib = glGetAttribLocation(thr_shader_program, "color");
	glEnableVertexAttribArray(col_attrib);
	glVertexAttribPointer(col_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

	thr_uniOrtho = glGetUniformLocation(thr_shader_program, "ortho");
	thr_uniModel = glGetUniformLocation(thr_shader_program, "model");
	thr_model = glm::translate(glm::mat4(1.0f), glm::vec3((GLfloat)winW - 20.0f, (GLfloat)winH/2.0f, 0.0f));
	glUniformMatrix4fv(thr_uniOrtho, 1, GL_FALSE, glm::value_ptr(matrix_ortho));
	glUniformMatrix4fv(thr_uniModel, 1, GL_FALSE, glm::value_ptr(thr_model));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLfloat mx, mz;
void CameraMove(void) {
	if (cam.moving == MOVE_IDLE) return;
	if (cam.moving & THR_UP) {
		++cam.thr;
		if (cam.thr > 100) cam.thr = 100;
		sprintf_s(cam.thr_text, 5, "%u%%", (unsigned int)cam.thr);
		thr_vertices[31] = cam.thr;
		thr_vertices[36] = cam.thr;
		thr_vertices[41] = cam.thr;
		glBindBuffer(GL_ARRAY_BUFFER, thr_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(thr_vertices), thr_vertices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (cam.moving & THR_DOWN) {
		if (cam.thr != 0) {
			--cam.thr;
			sprintf_s(cam.thr_text, 5, "%u%%", (unsigned int)cam.thr);
			thr_vertices[31] = cam.thr;
			thr_vertices[36] = cam.thr;
			thr_vertices[41] = cam.thr;
			glBindBuffer(GL_ARRAY_BUFFER, thr_vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(thr_vertices), thr_vertices, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	
	if (cam.moving & MOVE_LEFT) {
		mx = (GLfloat)(cos(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/160.0f;
		mz = (GLfloat)(-sin(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/160.0f;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_RIGHT) {
		mx = (GLfloat)(cos(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/160.0f;
		mz = (GLfloat)(-sin(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/160.0f;
		cam.x += mx;
		cam.lx += mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_FRONT) {
		mx = (GLfloat)(sin(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/100.0f;
		mz = (GLfloat)(cos(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/100.0f;
		cam.x += mx;
		cam.lx += mx;
		cam.z += mz;
		cam.lz += mz;
	}
	if (cam.moving & MOVE_BACK) {
		mx = (GLfloat)(sin(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/100.0f;
		mz = (GLfloat)(cos(cam.angle_y*1.7453293f)) 		* (GLfloat)cam.thr/100.0f;
		cam.x -= mx;
		cam.lx -= mx;
		cam.z -= mz;
		cam.lz -= mz;
	}
	if (cam.moving & MOVE_UP) {
		cam.y += 0.01f * (GLfloat)cam.thr;
		cam.ly += 0.01f * (GLfloat)cam.thr;
	}
	if (cam.moving & MOVE_DOWN) {
		cam.y -= 0.01f * (GLfloat)cam.thr;
		cam.ly -= 0.01f * (GLfloat)cam.thr;
	}

	if (cam.moving & TURN_LEFT) {
		if (SDL_GetTicks() > motion_time_last + 100)
			cam.moving ^= TURN_LEFT;
		cam.angle_y -= cam.angle_step;
		if (cam.angle_y >= 3.6f) cam.angle_y -= 3.6f;
		cam.lx = (GLfloat)sin(cam.angle_y*1.7453293f)+cam.x;
		cam.lz = (GLfloat)cos(cam.angle_y*1.7453293f)+cam.z;
	}
	else if (cam.moving & TURN_RIGHT) {
		if (SDL_GetTicks() > motion_time_last + 100)
			cam.moving ^= TURN_RIGHT;
		cam.angle_y += cam.angle_step;
		if (cam.angle_y <= 0.0f) cam.angle_y += 3.6f;
		cam.lx = (GLfloat)sin(cam.angle_y*1.7453293f)+cam.x;
		cam.lz = (GLfloat)cos(cam.angle_y*1.7453293f)+cam.z;
	}
}
