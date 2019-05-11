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
#include "hud.h"
#include "image.h"
#include "render.h"
#include "shader.h"
#include "score.h"
#include "sound.h"
#include "texture.h"

struct ElementList root_element_list;
unsigned int element_flying_total,
	element_metal_total, element_mineral_total,
	element_total_maximum = 200;
GLuint element_vao, element_vbo;
GLuint element_uniProj, element_uniView, element_uniModel, element_uniRotation;
glm::mat4 element_model, element_rotation;
GLfloat element_vertices[] = {
-0.5f,0.0f, 0.0f,0.0f,
-0.5f,1.0f, 0.0f,1.0f,
0.5f,1.0f, 1.0f,1.0f,
0.5f,1.0f, 1.0f,1.0f,
0.5f,0.0f, 1.0f,0.0f,
-0.5f,0.0f, 0.0f,0.0f
};
char element_metal_img_filename[] = "images/element-metal-128.raw", 
	element_mineral_img_filename[] = "images/element-mineral-128.raw";

void ElementInit (void) {
    root_element_list.first_element = NULL;
	root_element_list.last_element = NULL;
	
	int cnt;
	for (cnt = 0; cnt < 10; cnt++) {
		ElementAdd (((cnt%2)==0)?ELEMENT_TYPE_METAL:ELEMENT_TYPE_MINERAL);
	}
	
	glUseProgram (element_shader_program);
	glGenVertexArrays (1, &element_vao);
	glGenBuffers (1, &element_vbo);
	glBindVertexArray (element_vao);
	glBindBuffer (GL_ARRAY_BUFFER, element_vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof(element_vertices), element_vertices, GL_STATIC_DRAW);
	GLint pos_attrib = glGetAttribLocation (element_shader_program, "position");
    glEnableVertexAttribArray (pos_attrib);
    glVertexAttribPointer (pos_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    GLint tex_attrib = glGetAttribLocation (element_shader_program, "texcoord");
	glEnableVertexAttribArray (tex_attrib);
	glVertexAttribPointer (tex_attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	element_uniProj = glGetUniformLocation (element_shader_program, "proj");
    element_uniView = glGetUniformLocation (element_shader_program, "view");
    element_uniModel = glGetUniformLocation (element_shader_program, "model");
	element_uniRotation = glGetUniformLocation (element_shader_program, "rotation");
    element_model = glm::translate (glm::mat4(1.0), glm::vec3(0.0f));
	element_rotation = glm::rotate (glm::mat4(1.0f), delta, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv (element_uniProj, 1, GL_FALSE, glm::value_ptr(matrix_projection));
    glUniformMatrix4fv (element_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
    glUniformMatrix4fv (element_uniModel, 1, GL_FALSE, glm::value_ptr(element_model));
	glUniformMatrix4fv (element_uniRotation, 1, GL_FALSE, glm::value_ptr(element_rotation));
    
    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
}

void ElementAdd (unsigned int type) {
	struct Element *elem = (struct Element *)malloc (sizeof(struct Element));
	if (root_element_list.first_element == NULL) {
		root_element_list.first_element = elem;
		elem->prev_element = NULL;
	}
	else {
		root_element_list.last_element->next_element = elem;
		elem->prev_element = root_element_list.last_element;
	}
	elem->next_element = NULL;
	elem->type = type;
	elem->value = rand()%100;
	ElementPositionSetRandom (elem);
	root_element_list.last_element = elem;
	++root_element_list.element_total;
	sprintf_s (hud_element_total_text, HUD_SCORE_TEXT_SIZE, "%u elements", root_element_list.element_total);
}

void ElementRemove (unsigned int count) {
	struct Element *elem = root_element_list.last_element;
	unsigned int cnt;
	for (cnt = 0; cnt < count; cnt++) {
		if (elem->prev_element == NULL) {
			free (elem);
			root_element_list.first_element = NULL;
			root_element_list.last_element = NULL;
			break;
		}
		elem = elem->prev_element;
		free (elem->next_element);
		elem->next_element = NULL;
		root_element_list.last_element = elem;
		--root_element_list.element_total;
		sprintf_s (hud_element_total_text, HUD_SCORE_TEXT_SIZE, "%u elements", root_element_list.element_total);
	}
}

void ElementPositionSetRandom (struct Element *elem) {
	int rnd1 = rand()%50,
		rnd2 = rand()%50;
	if (rnd1%2) rnd1 = -rnd1;
	if (rnd2%2) rnd2 = -rnd2;
	elem->x = (GLfloat)rnd1 + 100.0f;
	elem->y = 50.0f;
	elem->z = (GLfloat)rnd2 + 100.0f;
	elem->flying = 1;
	elem->flying = 1;
	++element_flying_total;
}

void ElementCollisionCheck (void) {
	struct Element *elem = root_element_list.first_element;
	while (1) {
		if ((elem->x >= cam.x - 1.0f) && (elem->x <= cam.x + 1.0f) &&
			(elem->z >= cam.z - 1.0f) && (elem->z <= cam.z + 1.0f)) {
			if (elem->type == ELEMENT_TYPE_METAL) {
				element_metal_total += elem->value;
				sprintf_s (hud_score_metal_text, HUD_SCORE_TEXT_SIZE, "%u", element_metal_total);
			}
			else if (elem->type == ELEMENT_TYPE_MINERAL) {
				element_mineral_total += elem->value;
				sprintf_s (hud_score_mineral_text, HUD_SCORE_TEXT_SIZE, "%u", element_mineral_total);
			}
			ElementPositionSetRandom (elem);
			if (root_element_list.element_total < element_total_maximum)
				ElementAdd (elem->type);
			if (sound_enabled)
				SoundThreadStart ();
		}
		
		if (elem->next_element == NULL) break;
		elem = elem->next_element;
	}
}

void ElementDraw (void) {
    glUseProgram (element_shader_program);
    glUniformMatrix4fv(element_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
	glBindVertexArray (element_vao);
	glBindBuffer (GL_ARRAY_BUFFER, element_vbo);

	struct Element *elem = root_element_list.first_element;
	while (1) {
		element_model = glm::translate (glm::mat4(1.0), glm::vec3(elem->x, elem->y+0.1, elem->z));
		element_rotation = glm::rotate (glm::mat4 (1.0f), delta + (GLfloat)elem->value / 100.0f, glm::vec3 (0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(element_uniModel, 1, GL_FALSE, glm::value_ptr(element_model));
		glUniformMatrix4fv (element_uniRotation, 1, GL_FALSE, glm::value_ptr (element_rotation));
		if (elem->type == ELEMENT_TYPE_METAL) {
			glBindTexture (GL_TEXTURE_2D, texture_metal);
		}
		else if (elem->type == ELEMENT_TYPE_MINERAL) {
			glBindTexture (GL_TEXTURE_2D, texture_mineral);
		}
		glDrawArrays (GL_TRIANGLES, 0, 6);
		
		if (elem->next_element == NULL) break;
		elem = elem->next_element;
	}
}
