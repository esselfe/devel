#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include "devel.h"
#include "image.h"
#include "shader.h"

char texture_flag01_img_filename[] = "images/flag02-128.raw",
	texture_floor_img_filename[] = "images/tile-128.raw",
	texture_metal_img_filename[] = "images/element-metal-128.raw",
	texture_mineral_img_filename[] = "images/element-mineral-128.raw",
	texture_moon_img_filename[] = "images/moon01-128.raw",
	texture_obj001_img_filename[] = "images/obj001-128.raw",
	texture_sky01_img_filename[] = "images/sky01-1024.raw",
	texture_sky02_img_filename[] = "images/sky02-1024.raw",
	texture_sky03_img_filename[] = "images/sky03-1024.raw",
	texture_sky04_img_filename[] = "images/sky04-1024.raw";
GLuint texture_flag01, texture_flag02, texture_floor,
	texture_metal, texture_mineral,
	texture_moon,
	texture_sky01, texture_sky02, texture_sky03, texture_sky04;

void TextureInit (void) {
	glEnable (GL_TEXTURE_2D);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	GLubyte *image = ImageFromRaw128 (texture_metal_img_filename);
	glGenTextures (1, &texture_metal);
	if (verbose) printf ("texture metal #%u\n", texture_metal);
	glBindTexture (GL_TEXTURE_2D, texture_metal);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);
	
	image = ImageFromRaw128 (texture_mineral_img_filename);
	glGenTextures (1, &texture_mineral);
	if (verbose) printf ("texture mineral #%u\n", texture_mineral);
	glBindTexture (GL_TEXTURE_2D, texture_mineral);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);
	
	image = ImageFromRaw128 (texture_flag01_img_filename);
	glGenTextures (1, &texture_flag01);
	if (verbose) printf ("texture flag01 #%u\n", texture_flag01);
	glBindTexture (GL_TEXTURE_2D, texture_flag01);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw128 (texture_floor_img_filename);
	glGenTextures (1, &texture_flag02);
	if (verbose) printf ("texture flag02 #%u\n", texture_flag02);
	glBindTexture (GL_TEXTURE_2D, texture_flag02);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw128 (texture_floor_img_filename);
	glGenTextures (1, &texture_floor);
	if (verbose) printf ("texture floor #%u\n", texture_floor);
	glBindTexture (GL_TEXTURE_2D, texture_floor);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw128 (texture_moon_img_filename);
	glGenTextures (1, &texture_moon);
	if (verbose) printf ("texture moon #%u\n", texture_moon);
	glBindTexture (GL_TEXTURE_2D, texture_moon);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw1024 (texture_sky01_img_filename);
	glGenTextures (1, &texture_sky01);
	if (verbose) printf ("texture sky01 #%u\n", texture_sky01);
	glBindTexture (GL_TEXTURE_2D, texture_sky01);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw1024 (texture_sky02_img_filename);
	glGenTextures (1, &texture_sky02);
	if (verbose) printf ("texture sky02 #%u\n", texture_sky02);
	glBindTexture (GL_TEXTURE_2D, texture_sky02);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw1024 (texture_sky03_img_filename);
	glGenTextures (1, &texture_sky03);
	if (verbose) printf ("texture sky03 #%u\n", texture_sky03);
	glBindTexture (GL_TEXTURE_2D, texture_sky03);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

	image = ImageFromRaw1024 (texture_sky04_img_filename);
	glGenTextures (1, &texture_sky04);
	if (verbose) printf ("texture sky04 #%u\n", texture_sky04);
	glBindTexture (GL_TEXTURE_2D, texture_sky04);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture (GL_TEXTURE_2D, 0);
	free (image);

}
