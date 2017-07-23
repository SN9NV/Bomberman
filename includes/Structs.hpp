#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <GL/glew.h>

struct	Position2D {
	float	x;
	float	y;
};

struct	Colour {
	GLubyte	r;
	GLubyte	g;
	GLubyte	b;
	GLubyte	a;
};

struct	UV {
	float u;
	float v;
};

struct	Vertex {
	Position2D	position;
	Colour		colour;
	UV			uv;
};

struct	GLTexture {
	GLuint		id;
	unsigned	width;
	unsigned	height;
};

#endif // STRUCTS_HPP
