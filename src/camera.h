#ifndef CAMERA_H
#define CAMERA_H 1

#include <GL/glew.h>
#include <glm/glm.hpp>

#define MOVE_IDLE   0
#define MOVE_LEFT   1
#define MOVE_RIGHT  (1<<1)
#define MOVE_FRONT  (1<<2)
#define MOVE_BACK   (1<<3)
#define MOVE_UP     (1<<4)
#define MOVE_DOWN   (1<<5)
#define THR_UP      (1<<6)
#define THR_DOWN    (1<<7)
#define TURN_LEFT   (1<<8)
#define TURN_RIGHT  (1<<9)

struct Camera {
	GLfloat x, y, z, lx, ly, lz;
	GLfloat step, angle_y, angle_step, thr;
	unsigned int moving;
	char thr_text[5];
};
extern struct Camera cam;

extern GLuint thr_vao, thr_vbo;
extern GLuint thr_uniOrtho, thr_uniModel;
extern glm::mat4 thr_model;
extern GLfloat thr_vertices[];

void CameraInit(void);
void CameraMove(void);

#endif /* CAMERA_H */
