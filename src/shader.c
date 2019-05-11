#include <stdio.h>
#include <stdlib.h>
#ifdef LINUX
#include <unistd.h>
#endif

#include <GL/glew.h>

#include "devel.h"

GLuint element_vertex_shader, element_fragment_shader, element_shader_program;
GLuint flag01_vertex_shader, flag01_fragment_shader, flag01_shader_program;
GLuint floor_vertex_shader, floor_fragment_shader, floor_shader_program;
GLuint font_vertex_shader, font_fragment_shader, font_shader_program;
GLuint hud_vertex_shader, hud_fragment_shader, hud_shader_program;
GLuint hudelem_vertex_shader, hudelem_fragment_shader, hudelem_shader_program;
GLuint memory_vertex_shader, memory_fragment_shader, memory_shader_program;
GLuint moon_vertex_shader, moon_fragment_shader, moon_shader_program;
GLuint sky_vertex_shader, sky_fragment_shader, sky_shader_program;
GLuint thr_vertex_shader, thr_fragment_shader, thr_shader_program;

const GLchar *element_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"uniform mat4 rotation;"
"void main () {"
	"Texcoord = texcoord;"
    "gl_Position = proj * view * model * rotation * vec4 (position, 0.0f, 1.0f) * vec4(-1.0,1.0,1.0,1.0);"
"}";
const GLchar *element_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex_element;"
"void main () {"
    "outColor = texture (tex_element, Texcoord);"
"}";
const GLchar *flag01_vertex_source =
"#version 330 core\n"
"in vec3 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"uniform mat4 rotation;"
"void main () {"
	"Texcoord = texcoord;"
    "gl_Position = proj * view * model * rotation * vec4 (position, 1.0f) * vec4(-1.0,1.0,1.0,1.0);"
"}";
const GLchar *flag01_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex_flag01;"
"void main () {"
    "outColor = texture2D (tex_flag01, Texcoord);"
"}";
const GLchar *floor_vertex_source =
"#version 330 core\n"
"in vec3 position;"
"in vec2 texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"out vec2 Texcoord;"
"void main () {"
	"Texcoord = texcoord;"
    "gl_Position = proj * view * vec4 (position, 1.0f) * vec4(-1.0,1.0,1.0,1.0);"
"}";
const GLchar *floor_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex_floor;"
"void main () {"
    "outColor = texture(tex_floor,Texcoord);"
"}";
const GLchar *font_vertex_source = 
"#version 330 core\n"
"in vec2 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 ortho;"
"uniform mat4 model;"
"void main() {"
	"Texcoord = texcoord;"
	"gl_Position = ortho * model * vec4 (position, 0.0f, 1.0f) * vec4 (1.0f, -1.0f, 1.0f, 1.0f);"
"}";
const GLchar *font_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D font_texture;"
"void main() {"
	"outColor = texture(font_texture, Texcoord);"
"}";
const GLchar *hud_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"uniform mat4 ortho;"
"uniform mat4 model;"
"void main () {"
    "gl_Position = ortho * model * vec4 (position, 0.0f, 1.0f);"
"}";
const GLchar *hud_fragment_source =
"#version 330 core\n"
"out vec4 outColor;"
"void main () {"
    "outColor = vec4 (0.4f, 0.5f, 0.6f, 1.0f);"
"}";
const GLchar *hudelem_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 ortho;"
"uniform mat4 model;"
"void main () {"
	"Texcoord = texcoord;"
    "gl_Position = ortho * model * vec4 (position, 0.0f, 1.0f) * vec4 (1.0f, -1.0f, 1.0f, 1.0f);"
"}";
const GLchar *hudelem_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main () {"
    "outColor = texture(tex, Texcoord);"
"}";
const GLchar *memory_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec4 color;"
"out vec4 Color;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"void main () {"
"Color = color;"
"gl_Position = proj * view * model  * vec4 (position, 0.0f, 1.0f) * vec4(-1.0,1.0,1.0,1.0);"
"}";
const GLchar *memory_fragment_source =
"#version 330 core\n"
"in vec4 Color;"
"out vec4 outColor;"
"void main () {"
"outColor = Color;"
"}";
const GLchar *moon_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"uniform mat4 rotation;"
"void main () {"
"Texcoord = texcoord;"
"gl_Position = proj * view * model  * rotation * vec4 (position, 0.0f, 1.0f) * vec4(-1.0,1.0,1.0,1.0);"
"}";
const GLchar *moon_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex_moon;"
"void main () {"
"outColor = texture2D (tex_moon,Texcoord);"
"}";
const GLchar *sky_vertex_source =
"#version 330 core\n"
"in vec3 position;"
"in vec2 texcoord;"
"out vec2 Texcoord;"
"uniform mat4 proj;"
"uniform mat4 view;"
"uniform mat4 model;"
"void main() {"
	"Texcoord = texcoord;"
	"gl_Position = proj * view * model * vec4 (position, 1.0f) * vec4(-1.0f,1.0f,1.0f,1.0f);"
"}";
const GLchar *sky_fragment_source =
"#version 330 core\n"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex_sky;"
"void main() {"
	"outColor = texture2D (tex_sky, Texcoord);"
"}";
const GLchar *thr_vertex_source =
"#version 330 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"uniform mat4 ortho;"
"uniform mat4 model;"
"void main() {"
	"Color = color;"
	"gl_Position = ortho * model * vec4 (position, 0.0f, 1.0f);"
"}";
const GLchar *thr_fragment_source =
"#version 330 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
	"outColor = vec4 (Color, 1.0f);"
"}";

void ShaderCreate (GLuint *shader_program, const GLchar *vertex_source, const GLchar *fragment_source) {
	GLint status;
	GLuint vertex_shader = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertex_shader, 1, (const GLchar **)&vertex_source, NULL);
	glCompileShader (vertex_shader);
	glGetShaderiv (vertex_shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv (vertex_shader, GL_INFO_LOG_LENGTH, &loglen);
		char *buffer = (char *)malloc (loglen);
		glGetShaderInfoLog (vertex_shader, loglen, NULL, buffer);
		printf ("%s: vertex_shader compile error: \n%s\n%s\n", program_name, vertex_source, buffer);
		free (buffer);
		exit (1);
	}
	GLuint fragment_shader = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragment_shader, 1, (const GLchar **)&fragment_source, NULL);
	glCompileShader (fragment_shader);
	glGetShaderiv (fragment_shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv (vertex_shader, GL_INFO_LOG_LENGTH, &loglen);
		char *buffer = (char *)malloc (loglen);
		glGetShaderInfoLog (fragment_shader, loglen, NULL, buffer);
		printf ("%s: fragment_shader compile error: \n%s\n%s\n", program_name, fragment_source, buffer);
		free (buffer);
		exit (1);
	}
	*shader_program = glCreateProgram ();
	glAttachShader (*shader_program, vertex_shader);
	glAttachShader (*shader_program, fragment_shader);
	glBindFragDataLocation (*shader_program, 0, "outColor");
	glLinkProgram (*shader_program);
	glGetProgramiv (*shader_program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		GLint loglen;
		glGetShaderiv (*shader_program, GL_INFO_LOG_LENGTH, &loglen);
		char *buffer = (char *)malloc (loglen);
		glGetProgramInfoLog (*shader_program, loglen, NULL, buffer);
		printf ("%s: shader_program link error:%s\n", program_name, buffer);
		free (buffer);
		exit (1);
	}
	glDeleteShader (fragment_shader);
	glDeleteShader (vertex_shader);
}

void ShaderInit (void) {
	ShaderCreate (&element_shader_program, element_vertex_source, element_fragment_source);
	ShaderCreate (&flag01_shader_program, flag01_vertex_source, flag01_fragment_source);
	ShaderCreate (&floor_shader_program, floor_vertex_source, floor_fragment_source);
	ShaderCreate (&font_shader_program, font_vertex_source, font_fragment_source);
	ShaderCreate (&hud_shader_program, hud_vertex_source, hud_fragment_source);
	ShaderCreate (&hudelem_shader_program, hudelem_vertex_source, hudelem_fragment_source);
	ShaderCreate (&memory_shader_program, memory_vertex_source, memory_fragment_source);
	ShaderCreate (&moon_shader_program, moon_vertex_source, moon_fragment_source);
	ShaderCreate (&sky_shader_program, sky_vertex_source, sky_fragment_source);
	ShaderCreate (&thr_shader_program, thr_vertex_source, thr_fragment_source);
}

