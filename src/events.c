#include <stdio.h>
#ifdef LINUX
#include <unistd.h>
#endif
#include <math.h>

#include <SDL2/SDL.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "events.h"
#include "camera.h"
#include "element.h"
#include "flag.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "moon.h"
#include "render.h"
#include "shader.h"
#include "state.h"
#include "terminal.h"

SDL_Event event;
unsigned int mods, mouse_hold, show_keys, warping;
unsigned long motion_time_last;

void EventsInit(void) {
	mods = MOD_NONE;
	mouse_hold = 1;
	//SDL_ShowCursor(!mouse_hold);
	SDL_WarpMouseInWindow(window, winW/2, winH/2);
	show_keys = 0;
}

void EventsCheck(void) {
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			mainloop_end = 1;
			return;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (terminal_visible && event.key.keysym.sym >= ' ' && event.key.keysym.sym <= 'z') {
				TerminalKeyParse((char)event.key.keysym.sym);
				return;
			}
			if (show_keys) printf("%d:%c:%s\n", event.key.keysym.sym, (char)event.key.keysym.sym, SDL_GetKeyName(event.key.keysym.sym));
			switch(event.key.keysym.sym) {
			case SDLK_ESCAPE:
				mainloop_end = 1;
				return;
			case SDLK_RETURN:
				if (terminal_visible) TerminalCommandParse();
				break;
			case SDLK_BACKSPACE:
				if (terminal_visible) {
					term.command[term.cursor_position-- - 1] = '\0';
					terminal_vertices[30] -= 8.0f;
					terminal_vertices[35] = terminal_vertices[30];
					glUseProgram(term.shader_program);
					glBindBuffer(GL_ARRAY_BUFFER, term.vbo);
					glBufferData(GL_ARRAY_BUFFER, term.vertices_size, terminal_vertices, GL_STATIC_DRAW);
				}
				break;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods |= MOD_CTRL;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods |= MOD_CAPS;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods |= MOD_ALT2;
				break;
			case SDLK_CAPSLOCK:
				if (SDL_GetModState() & KMOD_CAPS)
					mods |= MOD_CAPS;
				else
					mods ^= MOD_CAPS;
				break;
			case SDLK_TAB:
				terminal_visible = !terminal_visible;
				break;
			case SDLK_e:
				if (!(state_mode & STATE_MODE_ELEMENT)) StateModeSet(STATE_MODE_ELEMENT);
				break;
			case SDLK_f:
				if (mods & MOD_CTRL) {
					fullscreen = !fullscreen;
					SDL_SetWindowFullscreen(window, (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0);
					if (fullscreen) {
						winWorig = winW;
						winHorig = winH;
						SDL_GetDesktopDisplayMode(0, &display_mode);
						SDL_SetWindowDisplayMode(window, &display_mode);
						winW = display_mode.w;
						winH = display_mode.h;
						SDL_SetWindowSize(window, winW, winH);
						printf("fullscreen 1: %u %u %d %d\n", winW, winH, display_mode.w, display_mode.h);
						glViewport(0, 0, winW, winH);
					}
					else {
						winW = winWorig;
						winH = winHorig;
						SDL_SetWindowPosition(window, winX, winY + 30);
						SDL_SetWindowSize(window, winW, winH);
						glViewport(0, 0, winW, winH);
					}
				}
			case SDLK_k:
				show_keys = !show_keys;
				break;
			case SDLK_m:
				if (!(state_mode & STATE_MODE_MEMORY)) StateModeSet(STATE_MODE_MEMORY);
				break;
			case SDLK_p:
				if (mods & MOD_CTRL) {
					printf("position x:%.03f y:%.03f z:%.03f lx:%.03f ly:%.03f lz:%.03f angle_y:%.03f\n",
						cam.x, cam.y, cam.z, cam.lx, cam.ly, cam.lz, cam.angle_y);
				}
				else {
					paused = !paused;
					printf("paused: %u\n", paused);
				}
				break;
			case SDLK_s:
				StateToggle(STATE_RENDER_SKY);
				break;
			case SDLK_LEFT:
				cam.moving |= MOVE_LEFT;
				break;
			case SDLK_RIGHT:
				cam.moving |= MOVE_RIGHT;
				break;
			case SDLK_UP:
				cam.moving |= MOVE_FRONT;
				break;
			case SDLK_DOWN:
				cam.moving |= MOVE_BACK;
				break;
			case SDLK_PAGEUP:
				cam.moving |= MOVE_UP;
				break;
			case SDLK_PAGEDOWN:
				cam.moving |= MOVE_DOWN;
				break;
			case SDLK_KP_MINUS:
				cam.moving |= THR_DOWN;
				break;
			case SDLK_KP_PLUS:
				cam.moving |= THR_UP;
				break;
			case SDLK_KP_2:
				flag01.moving |= MOVE_BACK;
				break;
			case SDLK_KP_8:
				flag01.moving |= MOVE_FRONT;
				break;
			case SDLK_KP_4:
				flag01.moving |= MOVE_LEFT;
				break;
			case SDLK_KP_6:
				flag01.moving |= MOVE_RIGHT;
				break;
			case SDLK_KP_9:
				flag01.moving |= MOVE_UP;
				break;
			case SDLK_KP_3:
				flag01.moving |= MOVE_DOWN;
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				mods ^= MOD_CTRL;
				break;
			case SDLK_LSHIFT:
			case SDLK_RSHIFT:
				mods ^= MOD_CAPS;
				break;
			case SDLK_LALT:
			case SDLK_RALT:
				mods ^= MOD_ALT2;
				break;
			case SDLK_LEFT:
				cam.moving ^= MOVE_LEFT;
				break;
			case SDLK_RIGHT:
				cam.moving ^= MOVE_RIGHT;
				break;
			case SDLK_UP:
				cam.moving ^= MOVE_FRONT;
				break;
			case SDLK_DOWN:
				cam.moving ^= MOVE_BACK;
				break;
			case SDLK_PAGEUP:
				cam.moving ^= MOVE_UP;
				break;
			case SDLK_PAGEDOWN:
				cam.moving ^= MOVE_DOWN;
				break;
			case SDLK_KP_MINUS:
				cam.moving ^= THR_DOWN;
				break;
			case SDLK_KP_PLUS:
				cam.moving ^= THR_UP;
				break;
			case SDLK_KP_2:
				flag01.moving ^= MOVE_BACK;
				break;
			case SDLK_KP_8:
				flag01.moving ^= MOVE_FRONT;
				break;
			case SDLK_KP_4:
				flag01.moving ^= MOVE_LEFT;
				break;
			case SDLK_KP_6:
				flag01.moving ^= MOVE_RIGHT;
				break;
			case SDLK_KP_9:
				flag01.moving ^= MOVE_UP;
				break;
			case SDLK_KP_3:
				flag01.moving ^= MOVE_DOWN;
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {
			if (mouse_hold) {
				if (event.motion.xrel > 100 || event.motion.xrel < -100) return;
				motion_time_last = event.motion.timestamp;
				if (warping) {
					warping = 0;
					printf("warp: %d\n", event.motion.xrel);
//					return;
				}
				if (event.motion.xrel < -10) event.motion.xrel = -10;
				else if (event.motion.xrel > 10) event.motion.xrel = 10;
				if (event.motion.xrel < 0) {
					if (cam.moving & MOVE_RIGHT) cam.moving ^= MOVE_RIGHT;
					cam.moving |= TURN_LEFT;
					cam.angle_step = (GLfloat)-event.motion.xrel/200.0f;
					if (event.motion.x < (int)winW/2-100) {
						warping = 1;
						SDL_WarpMouseInWindow(window, winW/2, winH/2);
					}
				}
				else if (event.motion.xrel > 0) {
					if (cam.moving & MOVE_LEFT) cam.moving ^= MOVE_LEFT;
					cam.moving |= TURN_RIGHT;
					cam.angle_step = (GLfloat)event.motion.xrel/200.0f;
					if (event.motion.x > (int)winW/2+100) {
						warping = 1;
						SDL_WarpMouseInWindow(window, winW/2, winH/2);
					}
				}
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_RIGHT) // right button
				mouse_hold = !mouse_hold;
			SDL_ShowCursor(!mouse_hold);
		}
		else if (event.type == SDL_WINDOWEVENT) {
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				printf("events: window resized %d %d\n", w, h);
			else if (event.window.event == SDL_WINDOWEVENT_RESTORED)
				printf("events: window restored %d %d\n", w, h);
			else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				printf("events: window size changed %d %d\n", w, h);
			if (event.window.data1 <= 100 || event.window.data2 <= 100) return;
			if (event.window.data1 == (int)winW && event.window.data2 == (int)winH) return;
			//winW = event.window.data1;
			//winH = event.window.data2;
			//printf("window event: %u %u\n", winW, winH);
			//glViewport(0, 0, winW, winH);
		}
	}
}
