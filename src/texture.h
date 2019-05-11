#ifndef TEXTURE_H
#define TEXTURE_H 1

#include <GL/glew.h>

extern char texture_flag01_img_filename[],
	texture_floor_img_filename[],
	texture_metal_img_filename[], texture_mineral_img_filename[],
	texture_moon_img_filename[],
	texture_obj001_img_filename[],
	texture_sky01_img_filename[], texture_sky02_img_filename[], texture_sky03_img_filename[], texture_sky04_img_filename[];
extern GLuint texture_flag01, texture_flag02,
	texture_floor,
	texture_metal, texture_mineral,
	texture_moon,
	texture_sky01, texture_sky02, texture_sky03, texture_sky04;

void TextureInit (void);

#endif /* TEXTURE_H */
