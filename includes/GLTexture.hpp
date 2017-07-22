#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP

#include <GL/glew.h>

struct	GLTexture {
	GLuint		id;
	unsigned	width;
	unsigned	height;
};

struct	UV {
	float u;
	float v;
};

#endif // GLTEXTURE_HPP
