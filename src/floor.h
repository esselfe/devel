#ifndef FLOOR_H
#define FLOOR_H 1

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

extern GLuint vao_floor, vbo_floor;
extern GLint uniProj_floor, uniView_floor;
extern glm::mat4 proj_floor, view_floor;
extern GLfloat vertices_floor[];

void FloorInit (void);
void FloorDraw (void);

#endif /* FLOOR_H */
