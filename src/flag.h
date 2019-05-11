#ifndef FLAG_H
#define FLAG_H 1

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Flag {
	GLfloat x, y, z;
	GLfloat step;
	unsigned int moving;
};
extern struct Flag flag01;

extern GLuint flag01_vao, flag01_vbo;
extern GLint flag01_uniProj, flag01_uniView, flag01_uniModel, flag01_uniRotation;
extern glm::mat4 flag01_proj, flag01_view, flag01_model, flag01_rotation;
extern GLfloat flag01_vertices[];

void FlagInit(void);
void FlagDraw(void);
void FlagMove(struct Flag *flag);

#endif /* FLAG_H */
