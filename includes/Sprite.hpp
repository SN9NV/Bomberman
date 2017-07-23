#pragma once

#include <cstddef>
#include <string>
#include <GL/glew.h>

#include "Structs.hpp"
#include "ResourceManager.hpp"

class Sprite
{
	public:
		Sprite();
		Sprite(float x, float y, float width, float height, const std::string &texturePath);
		~Sprite();

		void	init(float x, float y, float width, float height, const std::string &texturePath);
		void	draw(void);

	private:
		float		_x;
		float		_y;
		float		_width;
		float		_height;
		GLuint		_vboID;
		GLTexture	_texture;
};
