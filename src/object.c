#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"
#include "devel.h"
#include "image.h"
#include "render.h"
#include "shader.h"
#include "texture.h"
#include "vertices.h"

struct ObjectList root_object_list;

const GLchar *obj_vertex_source =
"#version 330 core\n"
"in vec3 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"uniform mat4 rotation;"
"void main() {"
"Texcoord = texcoord;"
"	gl_Position = proj * view * model * rotation * vec4(position, 1.0f) * vec4(-1.0f,1.0f,1.0f,1.0f);"
"}";
const GLchar *obj_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D uni_texture;"
"void main() {"
"	outColor = texture2D (uni_texture, Texcoord);"
"}";

void ObjectInit(void) {
	struct Object *obj;

	obj = ObjectAdd(obj_vertex_source, obj_fragment_source, vertices_obj001, texture_obj001_img_filename);
	ObjectPositionSet(obj, 1.0f, 0.0f, 10.0f);
	//ObjectRotationSet(obj, 30.0f);
}

struct Object *ObjectAdd(const GLchar *vertex_source, const GLchar *fragment_source, GLfloat *vertices, char *texture_img_filename) {
	struct Object *obj = (struct Object *)malloc(sizeof(struct Object));
	if (root_object_list.first_object == NULL) {
		root_object_list.first_object = obj;
		obj->prev = NULL;
	}
	else {
		obj->prev = root_object_list.last_object;
		root_object_list.last_object->next = obj;
	}
	obj->next = NULL;
	root_object_list.last_object = obj;

	ShaderCreate(&obj->shader_program, vertex_source, fragment_source);
	
	obj->vertex_count = 6;
	glGenVertexArrays(1, &obj->vao);
	glBindVertexArray(obj->vao);
	glGenBuffers(1, &obj->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glUseProgram(obj->shader_program);
	obj->attrib_position = glGetAttribLocation(obj->shader_program, "position");
	glEnableVertexAttribArray(obj->attrib_position);
	glVertexAttribPointer(obj->attrib_position, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	obj->attrib_texcoord = glGetAttribLocation(obj->shader_program, "texcoord");
	glEnableVertexAttribArray(obj->attrib_texcoord);
	glVertexAttribPointer(obj->attrib_texcoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	GLubyte *image = ImageFromRaw128(texture_img_filename);
	glGenTextures(1, &obj->texture_id);
	glBindTexture(GL_TEXTURE_2D, obj->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(image);
	obj->uniform_texture = glGetUniformLocation(obj->shader_program, "uni_texture");
	glUniform1i(obj->uniform_texture, 0);
	obj->uniProj = glGetUniformLocation(obj->shader_program, "proj");
	obj->uniView = glGetUniformLocation(obj->shader_program, "view");
	obj->uniModel = glGetUniformLocation(obj->shader_program, "model");
	obj->uniRotation = glGetUniformLocation(obj->shader_program, "rotation");
	obj->model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
	obj->rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f));
	glUniformMatrix4fv(obj->uniProj, 1, GL_FALSE, glm::value_ptr(matrix_projection)); // rem glm::mat4 matrices from render.c
	glUniformMatrix4fv(obj->uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
	glUniformMatrix4fv(obj->uniModel, 1, GL_FALSE, glm::value_ptr(obj->model));
	glUniformMatrix4fv(obj->uniRotation, 1, GL_FALSE, glm::value_ptr(obj->rotation));

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

	obj->x = 0.0f;
	obj->y = 0.0f;
	obj->z = 0.0f;
	obj->angle_y = 0.0f;
	obj->vertices = vertices;
	
	return obj;
}

void ObjectPositionSet(struct Object *object, GLfloat x, GLfloat y, GLfloat z) {
	object->x = x;
	object->y = y;
	object->z = z;
	glUseProgram(object->shader_program);
	object->model = glm::translate(glm::mat4(1.0f), glm::vec3(object->x, object->y, object->z));
	glUniformMatrix4fv(object->uniModel, 1, GL_FALSE, glm::value_ptr(object->model));
	glUseProgram(0);
}

void ObjectRotationSet(struct Object *object, GLfloat angle_y) {
	object->angle_y = angle_y;
	glUseProgram(object->shader_program);
	object->rotation = glm::rotate(glm::mat4(1.0f), object->angle_y, glm::vec3(1.0f));
	glUniformMatrix4fv(object->uniRotation, 1, GL_FALSE, glm::value_ptr(object->rotation));
	glUseProgram(0);
}

void ObjectDraw(void) {
	if (root_object_list.first_object == NULL) return;
	struct Object *obj = root_object_list.first_object;
	while (1) {
		glUseProgram(obj->shader_program);
		glUniformMatrix4fv(obj->uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
		glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
		glBindTexture(GL_TEXTURE_2D, obj->texture_id);
		glBindVertexArray(obj->vao);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertex_count);

		glUseProgram(0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (obj->next == NULL) break;
		obj = obj->next;
	}
}

















