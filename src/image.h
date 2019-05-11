#ifndef IMAGE_H
#define IMAGE_H 1

#include <GL/glew.h>

GLubyte *ImageFromRaw128 (char *filename);
GLubyte *ImageFromRaw1024 (char *filename);

#endif /* IMAGE_H */
