#ifndef ELEMENT_H
#define ELEMENT_H 1

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define ELEMENT_TYPE_METAL      1
#define ELEMENT_TYPE_MINERAL    2

struct Element {
	struct Element *prev_element, *next_element;
	unsigned int flying;
	unsigned int type;
	unsigned int value;
	GLfloat x, y, z;
};

struct ElementList {
	struct Element *first_element, *last_element;
	unsigned int element_total;
};
extern struct ElementList root_element_list;

extern unsigned int element_flying_total,
	element_metal_total, element_mineral_total,
	element_total_maximum;

extern GLuint element_vao, element_vbo;
extern GLuint element_uniProj, element_uniView, element_uniModel, element_uniRotation;
extern glm::mat4 element_model, element_rotation;
extern GLfloat element_vertices[];

void ElementInit (void);
void ElementAdd (unsigned int type);
void ElementRemove (unsigned int count);
void ElementPositionSetRandom (struct Element *elem);
void ElementCollisionCheck (void);
void ElementDraw (void);

#endif /* ELEMENT_H */
