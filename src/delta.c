#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <sys/sysinfo.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "element.h"
#include "flag.h"
#include "hud.h"
#include "memory.h"
#include "render.h"
#include "shader.h"
#include "state.h"
#include "terminal.h"

std::chrono::high_resolution_clock::time_point t_start, t_now;
float t_prev, t_prev500, t0;
unsigned int negative_x, negative_z;
int rnd, rnd2;
struct sysinfo sinfo;

void DeltaInit(void) {
	t_start = std::chrono::high_resolution_clock::now();
	t_now = t_start;
}

void DeltaUpdateFly(void) {
	if (!element_flying_total) return;
	struct Element *elem = root_element_list.first_element;
	while (1) {
		if (elem->flying) {
		elem->x -= 0.2f;
		elem->y -= 0.1f;
		elem->z -= 0.2f;
			if (elem->y <= 0.0f) {
				elem->flying = 0;
				--element_flying_total;
			}
		}
		
		if (elem->next_element == NULL) break;
		elem = elem->next_element;
	}
}

void DeltaUpdate(void) {
	t_now = std::chrono::high_resolution_clock::now();
	t0 = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	if (terminal_visible && t0 > t_prev500 + 0.5f) {
		terminal_cursor_blink = !terminal_cursor_blink;
		t_prev500 = t0;
	}
	if (t0 > t_prev + 1.0) {
		t_prev = t0;
		sprintf_s(hud_fps_text, HUD_FPS_TEXT_SIZE, "%u fps", fps);
		hud_vertices[2] = 5;
		fps = 0;
		if ((rnd % 2) == 0) negative_x = !negative_x; // randomize with negatives included
		if ((rnd2 % 2) != 0) negative_z = !negative_z;
	}
	delta += 0.01f;
	if (delta >= 360.0f) delta -= 360.0f;
	
	if (state_mode & STATE_MODE_ELEMENT) {
		rnd = (rand() % 4);
		rnd2 = (rand() % 4);
		if (negative_x) rnd = -rnd; // randomize with negatives included
		if (negative_z) rnd2 = -rnd2;
		flag01.x += (GLfloat)rnd / 100.0f;
		flag01.z += (GLfloat)rnd2 / 100.0f;
	
		DeltaUpdateFly();
	}
	if (state_mode & STATE_MODE_MEMORY) {
		sysinfo(&sinfo);
		memory_vertices[8] = (GLfloat)(sinfo.totalram - sinfo.freeram)/1000000.0;
	    memory_vertices[15] = memory_vertices[8];
	    memory_vertices[22] = memory_vertices[8];
		printf("%f\n", memory_vertices[8]);
	}
}
