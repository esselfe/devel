
#include <GL/glew.h>
#include <GL/gl.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "element.h"
#include "flag.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "image.h"
#include "memory.h"
#include "moon.h"
#include "object.h"
#include "shader.h"
#include "sky.h"
#include "state.h"
#include "terminal.h"

glm::mat4 matrix_ortho, matrix_projection, matrix_view;

void RenderInit(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	matrix_ortho = glm::ortho(0.0f, (GLfloat)winW, 0.0f, (GLfloat)winH);
	matrix_projection = glm::perspective(glm::radians(45.0f), (GLfloat)winW / (GLfloat)winH, 0.1f, 1000.0f);
	matrix_view = glm::lookAt(glm::vec3(cam.x, cam.y, cam.z), glm::vec3(cam.lx, cam.ly, cam.lz),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matrix_view = glm::lookAt(glm::vec3(cam.x, cam.y, cam.z), glm::vec3(cam.lx, cam.ly, cam.lz),
		glm::vec3(0.0f, 1.0f, 0.0f));
	
	if (state & STATE_RENDER_FLOOR) FloorDraw();
	if (state & STATE_RENDER_FLAG) FlagDraw();
	if (state & STATE_RENDER_ELEMENT) ElementDraw();
	if (state & STATE_RENDER_MEMORY) MemoryDraw();
	if (show_moon) MoonDraw();
	if (state & STATE_RENDER_SKY) SkyDraw();
	if (state & STATE_RENDER_HUD) HudDraw();
	FontDraw();
	ObjectDraw();
	if (terminal_visible) TerminalDraw();

	SDL_GL_SwapWindow(window);
}








