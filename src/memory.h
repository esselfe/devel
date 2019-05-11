#ifndef MEMORY_H
#define MEMORY_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

extern GLuint memoroy_vao, memoroy_vbo;
extern GLint memoroy_uniProj, memoroy_uniView, memoroy_uniModel, memoroy_uniRotation;
extern glm::mat4 memoroy_proj, memoroy_view, memoroy_model, memoroy_rotation;
extern GLfloat flag01_vertices[];

void MemoryInit(void);
void MemoryDraw(void);

#endif /* MEMORY_H */

