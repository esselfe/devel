#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "flag.h"
#include "font.h"
#include "image.h"
#include "render.h"
#include "shader.h"
#include "texture.h"

struct Flag flag01;
char flag01_img_filename[] = "images/flag01-128.raw";
GLuint flag01_vao, flag01_vbo;
GLint flag01_uniProj, flag01_uniView, flag01_uniModel, flag01_uniRotation;
glm::mat4 flag01_proj, flag01_view, flag01_model, flag01_rotation;
GLfloat flag01_vertices[] = {
-0.5f, 0.0f, -0.5,    0.0f, 0.0f,
-0.5f, 0.0f, 0.5,    0.0f, 1.0f,
0.5f, 0.0f, 0.5,    1.0f, 1.0f,
0.5f, 0.0f, 0.5,    1.0f, 1.0f,
0.5f, 0.0f, -0.5,    1.0f, 0.0f,
-0.5f, 0.0f, -0.5,    0.0f, 0.0f
};

void FlagInit (void) {
	flag01.x = 0.0f;
	flag01.y = 0.0f;
	flag01.z = 0.0f;
	flag01.step = 0.1f;
	flag01.moving = MOVE_IDLE;
	
	glUseProgram (flag01_shader_program);
    glGenVertexArrays (1, &flag01_vao);
    glBindVertexArray (flag01_vao);
    glGenBuffers (1, &flag01_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, flag01_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof(flag01_vertices), flag01_vertices, GL_DYNAMIC_DRAW);
    GLint pos_attrib = glGetAttribLocation (flag01_shader_program, "position");
    glEnableVertexAttribArray (pos_attrib);
    glVertexAttribPointer (pos_attrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    GLint tex_attrib = glGetAttribLocation (flag01_shader_program, "texcoord");
	glEnableVertexAttribArray (tex_attrib);
	glVertexAttribPointer (tex_attrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnable (GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texture_flag01);
	glUniform1i (glGetUniformLocation(flag01_shader_program, "tex_flag01"), 0);
	glBindTexture (GL_TEXTURE_2D, 0);
	flag01_uniProj = glGetUniformLocation (flag01_shader_program, "proj");
    flag01_uniView = glGetUniformLocation (flag01_shader_program, "view");
    flag01_uniModel = glGetUniformLocation (flag01_shader_program, "model");
	flag01_uniRotation = glGetUniformLocation (flag01_shader_program, "rotation");
    flag01_proj = glm::perspective (glm::radians(45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 250.0f);
    flag01_view = glm::lookAt (glm::vec3(cam.x, cam.y, cam.z),
        glm::vec3(cam.lx, cam.ly, cam.lz),
        glm::vec3(0.0f, 1.0f, 0.0f) );
    flag01_model = glm::translate (glm::mat4(1.0), glm::vec3(flag01.x, flag01.y+0.1, flag01.z));
	flag01_rotation = glm::rotate (glm::mat4(1.0), delta, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv (flag01_uniProj, 1, GL_FALSE, glm::value_ptr(flag01_proj));
    glUniformMatrix4fv (flag01_uniView, 1, GL_FALSE, glm::value_ptr(flag01_view));
    glUniformMatrix4fv (flag01_uniModel, 1, GL_FALSE, glm::value_ptr(flag01_model));
	glUniformMatrix4fv (flag01_uniRotation, 1, GL_FALSE, glm::value_ptr(flag01_rotation));
    
    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindTexture (GL_TEXTURE_2D, 0);
}

void FlagDraw (void) {
    glUseProgram (flag01_shader_program);
    flag01_model = glm::translate (glm::mat4(1.0), glm::vec3(flag01.x, flag01.y+0.1, flag01.z));
	flag01_rotation = glm::rotate (glm::mat4(1.0), delta, glm::vec3(0.0f,1.0f,0.0f));
    glUniformMatrix4fv (flag01_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
    glUniformMatrix4fv (flag01_uniModel, 1, GL_FALSE, glm::value_ptr(flag01_model));
	glUniformMatrix4fv (flag01_uniRotation, 1, GL_FALSE, glm::value_ptr(flag01_rotation));
	glBindBuffer (GL_ARRAY_BUFFER, flag01_vbo);
	glBindTexture (GL_TEXTURE_2D, texture_flag01);
	glBindVertexArray (flag01_vao);
	glDrawArrays (GL_TRIANGLES, 0, 6);
}

void FlagMove (struct Flag *flag) {
	if (flag->moving & MOVE_LEFT)
		flag->x -= flag->step;
    if (flag->moving & MOVE_RIGHT)
        flag->x += flag->step;
    if (flag->moving & MOVE_UP)
        flag->y += flag->step;
    if (flag->moving & MOVE_DOWN)
        flag->y -= flag->step;
    if (flag->moving & MOVE_FRONT)
        flag->z += flag->step;
    if (flag->moving & MOVE_BACK)
        flag->z -= flag->step;
}
