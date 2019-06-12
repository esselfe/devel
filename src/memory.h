#ifndef MEMORY_H
#define MEMORY_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

extern GLuint memory_vao, memory_vbo;
extern GLint memory_uniProj, memory_uniView, memory_uniModel, memory_uniRotation;
extern glm::mat4 memory_proj, memory_view, memory_model, memory_rotation;
extern GLfloat memory_vertices[];

void MemoryInit(void);
void MemoryDraw(void);

#endif /* MEMORY_H */

