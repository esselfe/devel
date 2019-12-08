#ifndef SHADER_H
#define SHADER_H 1

#include <GL/glew.h>

extern GLuint element_vertex_shader, element_fragment_shader, element_shader_program;
extern GLuint flag01_vertex_shader, flag01_fragment_shader, flag01_shader_program;
extern GLuint floor_vertex_shader, floor_fragment_shader, floor_shader_program;
extern GLuint font_vertex_shader, font_fragment_shader, font_shader_program;
extern GLuint font3D_vertex_shader, font3D_fragment_shader, font3D_shader_program;
extern GLuint hud_vertex_shader, hud_fragment_shader, hud_shader_program;
extern GLuint hudelem_vertex_shader, hudelem_fragment_shader, hudelem_shader_program;
extern GLuint memory_vertex_shader, memory_fragment_shader, memory_shader_program;
extern GLuint moon_vertex_shader, moon_fragment_shader, moon_shader_program;
extern GLuint sky_vertex_shader, sky_fragment_shader, sky_shader_program;
extern GLuint thr_vertex_shader, thr_fragment_shader, thr_shader_program;
extern const GLchar *obj_vertex_source, *obj_fragment_source;

void ShaderInit(void);
void ShaderCreate(GLuint *shader_program, const GLchar *vertex_source, const GLchar *fragment_source);

#endif /* SHADER_H */
