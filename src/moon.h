#ifndef MOON_H
#define MOON_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

extern unsigned int show_moon;
extern GLuint moon_vao, moon_vbo;
extern GLint moon_uniProj, moon_uniView, moon_uniModel, moon_uniRotation;
extern glm::mat4 moon_proj, moon_view, moon_model, moon_rotation;
extern GLfloat moon_vertices[];

void MoonInit(void);
void MoonDraw(void);

#endif /* MOON_H */
