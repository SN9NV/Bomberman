#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "Vertex.hpp"

class Sprite
{
	public:
		Sprite();
		Sprite(float x, float y, float width, float height);
		~Sprite();

		void	init(float x, float y, float width, float height);
		void	draw(void);

	private:
		float	_x;
		float	_y;
		float	_width;
		float	_height;
		GLuint	_vboID;
};
