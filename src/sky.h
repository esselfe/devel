#ifndef SKY_H
#define SKY_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

extern GLuint sky_vao, sky_vbo;
extern GLuint sky_uniProj, sky_uniView, sky_uniModel;
extern glm::mat4 sky_proj, sky_view, sky_model;
extern GLfloat sky_vertices[];

void SkyInit(void);
void SkyDraw(void);

#endif /* SKY_H */
