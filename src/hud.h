#ifndef HUD_H
#define HUD_H 1


#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

extern GLuint hud_vao, hud_vbo;
extern GLint hud_uniOrtho, hud_uniModel;
extern glm::mat4 hud_ortho, hud_model;
extern GLfloat hud_vertices[4];

extern GLuint hudelem_vao, hudelem_vbo;
extern GLint hudelem_uniOrtho, hudelem_uniModel;
extern glm::mat4 hudelem_ortho, hudelem_model;
extern GLfloat hudelem_vertices[];

#define HUD_FPS_TEXT_SIZE 10
extern char hud_fps_text[HUD_FPS_TEXT_SIZE];
#define HUD_SCORE_TEXT_SIZE 64
extern char hud_score_metal_text[HUD_SCORE_TEXT_SIZE];
extern char hud_score_mineral_text[HUD_SCORE_TEXT_SIZE];
extern char hud_element_total_text[HUD_SCORE_TEXT_SIZE];


void HudInit(void);
void HudDraw(void);

#endif /* HUD_H */
