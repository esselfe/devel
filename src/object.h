#ifndef OBJECT_H
#define OBJECT_H 1

#include <GL/glew.h>

struct Object {
	struct Object *prev, *next;
	GLuint shader_program;
	GLuint vao, vbo;
	GLuint texture_id;
	GLint attrib_position, attrib_texcoord, uniform_texture;
	GLint uniProj, uniView, uniModel, uniRotation;
	glm::mat4 model, rotation;
	GLfloat x, y, z, angle_y;
	unsigned int vertex_count;
	GLfloat *vertices;
};

struct ObjectList {
	struct Object *first_object, *last_object;
};
extern struct ObjectList root_object_list;

void ObjectInit(void);
struct Object *ObjectAdd(const GLchar *vertex_source, const GLchar *fragment_source, GLfloat *vertices, char *texture_img_filename);
void ObjectPositionSet(struct Object *object, GLfloat x, GLfloat y, GLfloat z);
void ObjectRotationSet(struct Object *object, GLfloat angle_y);
void ObjectDraw(void);

#endif /* OBJECT_H */
