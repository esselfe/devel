#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef LINUX
#include <unistd.h>
#elif WINDOWS
#include <Windows.h>
#include <direct.h>
#endif
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "devel.h"
#include "camera.h"
#include "delta.h"
#include "element.h"
#include "events.h"
#include "flag.h"
#include "floor.h"
#include "font.h"
#include "hud.h"
#include "memory.h"
#include "moon.h"
#include "object.h"
#include "render.h"
#include "score.h"
#include "sound.h"
#include "shader.h"
#include "sky.h"
#include "state.h"
#include "terminal.h"
#include "texture.h"

char devel_version[] = "0.2.10.0";
char program_name[] = "devel";
char window_title[WINDOW_TITLE_SIZE];
unsigned int verbose = 1;
unsigned int fps;
unsigned int paused;
unsigned int fullscreen;
unsigned int mainloop_end;
unsigned int winX = 200, winY = 10, winW = 800, winH = 600, winWorig = 800, winHorig = 600;
SDL_DisplayMode display_mode;
SDL_Window *window;
SDL_GLContext context;

GLfloat delta;

int main(int argc, char **argv) {
#ifdef WINDOWS
	if (verbose) {
		char *buffer = _getcwd(NULL, 4096);
		printf("cwd:%s\n", buffer);
		free(buffer);
	}
#endif
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("%s:main():error: SDL_Init() failed.\n", program_name);
		return 1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	if (verbose) {
		int major, minor;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
		printf("SDL GL %d.%d\n", major, minor);
	}
	sprintf_s(window_title, WINDOW_TITLE_SIZE, "%s %s", program_name, devel_version);
	window = SDL_CreateWindow(window_title, winX, winY + 30, winW, winH, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		//SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_WarpMouseInWindow(window, winW / 2, winH / 2);
	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		printf("%s: Cannot create SDL2/GL context. Error: %s\n", program_name, SDL_GetError());
		SDL_Quit();
		return 1;
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("%s: Cannot initialize GLEW.\n", program_name);
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		return 1;
	}

	SoundInit();
	EventsInit();
	ShaderInit();
	FontInit();
	TextureInit();
	DeltaInit();
	CameraInit();
	ScoreLoad();
	FloorInit();
	FlagInit();
	MemoryInit();
	MoonInit();
	SkyInit();
	HudInit();
	RenderInit();
	ElementInit();
	ObjectInit();
	TerminalInit();
	StateInit();

	mainloop_end = 0;
	while (!mainloop_end) {
		++fps;
		EventsCheck();
		if (paused) { SDL_Delay(100); continue; }

		DeltaUpdate();
		CameraMove();
		if (state & STATE_RENDER_ELEMENT) ElementCollisionCheck();
		if (state & STATE_RENDER_FLAG) FlagMove(&flag01);

		Render();
	}
	printf("\n");

	ScoreSave();

	if (SDL_WasInit(SDL_INIT_AUDIO)) SDL_CloseAudio();

	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

