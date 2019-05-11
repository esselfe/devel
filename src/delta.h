#ifndef DELTA_H
#define DELTA_H 1

#include <chrono>

#include <GL/glew.h>

extern GLfloat delta;
extern std::chrono::high_resolution_clock::time_point t_start, t_now;
extern float t_prev, t0;

void DeltaInit(void);
void DeltaUpdate(void);

#endif /* DELTA_H */
