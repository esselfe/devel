#ifndef RENDER_H
#define RENDER_H 1

#include <glm/glm.hpp>

extern glm::mat4 matrix_ortho, matrix_projection, matrix_view;

void RenderInit(void);
void Render(void);

#endif /* RENDER_H */
