#ifndef FONT3D_H
#define FONT3D_H 1

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

extern GLuint font3D_vao, font3D_vbo;
extern GLuint font3D_uniProj, font3D_uniView, font3D_uniModel, font3D_uniRotation;
extern glm::mat4 font3D_model, font3D_rotation;
extern GLfloat font3D_vertices[];

void Font3DInit(void);
void Font3DDraw(void);

#endif /* FONT3D_H */
