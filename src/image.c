#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <GL/glew.h>

#include "devel.h"

GLubyte *ImageFromRaw128 (char *filename) {
	unsigned int pixel_size;
    FILE *fp;
#ifdef LINUX
	fp = fopen (filename, "r");
    if (fp == NULL) {
            printf ("ImageFromRaw128(): Cannot open %s: %s\n", filename, strerror(errno));
            return NULL;
    }
#else
	fopen_s (&fp, filename, "rb");
    if (fp == NULL) {
			char buffer[128];
			strerror_s (buffer, 128, errno);
            printf ("ImageFromRaw128(): Cannot open %s: %s\n", filename, buffer);
            return NULL;
    }
#endif
    fseek (fp ,0, SEEK_END);
    unsigned long filesize = ftell (fp);
	if (filesize == 128*128*4) pixel_size = 4;
	else pixel_size = 3;
    fseek (fp, 0, SEEK_SET);
    
    GLubyte *image2 = (GLubyte *)malloc (128*128*3);
    GLubyte *c = image2;
    unsigned long bytes_read = 0;
    while (bytes_read < filesize) {
        *c = fgetc (fp);
        *(c+1) = fgetc (fp);
        *(c+2) = fgetc (fp);
		if (pixel_size == 4) {
			fgetc (fp);
			bytes_read += 4;
		}
		else
			bytes_read += 3;
        c += 3;
    }
    fclose (fp);

	if (verbose) printf ("image %lu (%d) bytes, read %lu, pixel_size: %u, %s\n", filesize, 128 * 128 * 3, bytes_read, pixel_size, filename);

    return image2;
}

GLubyte *ImageFromRaw1024 (char *filename) {
	unsigned int pixel_size;
	FILE *fp;
#ifdef LINUX
	fp = fopen (filename, "r");
	if (fp == NULL) {
		printf ("ImageFromRaw1024(): Cannot open %s: %s\n", filename, strerror (errno));
		return NULL;
	}
#else
	fopen_s (&fp, filename, "rb");
	if (fp == NULL) {
		char buffer[128];
		strerror_s (buffer, 128, errno);
		printf ("ImageFromRaw1024(): Cannot open %s: %s\n", filename, buffer);
		return NULL;
	}
#endif
	fseek (fp, 0, SEEK_END);
	unsigned long filesize = ftell (fp);
	if (filesize == 1024 * 1024 * 4) pixel_size = 4;
	else pixel_size = 3;
	fseek (fp, 0, SEEK_SET);

	GLubyte *image = (GLubyte *)malloc (1024 * 1024 * 3);
	GLubyte *c = image;
	unsigned long bytes_read = 0;
	while (bytes_read < filesize) {
		*c = fgetc (fp);
		*(c + 1) = fgetc (fp);
		*(c + 2) = fgetc (fp);
		if (pixel_size == 4) {
			fgetc (fp);
			bytes_read += 4;
		}
		else
			bytes_read += 3;
		c += 3;
	}
	fclose (fp);

	if (verbose) printf ("image 1024 %lu (%d) bytes, read %lu, pixel_size: %u, %s\n", filesize, 1024 * 1024 * 3, bytes_read, pixel_size, filename);

	return image;
}
