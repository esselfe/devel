#ifndef BASE_H
#define BASE_H 1

#include <GL/glew.h>
#include <SDL2/SDL.h>

#define sprintf_s snprintf

extern char devel_version[];
extern char program_name[];
#define WINDOW_TITLE_SIZE 128
extern char window_title[WINDOW_TITLE_SIZE];
extern unsigned int verbose;
extern unsigned int fps;
extern unsigned int paused;
extern unsigned int fullscreen;
extern unsigned int winX, winY, winW, winH, winWorig, winHorig;
extern GLfloat delta;
extern SDL_DisplayMode display_mode;
extern SDL_Window *window;
extern SDL_GLContext context;

extern unsigned int mainloop_end;



#endif /* BASE_H */
