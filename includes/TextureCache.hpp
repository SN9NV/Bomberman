#ifndef TEXTURECACHE_HPP
#define TEXTURECACHE_HPP

#include <map>

#include "GLTexture.hpp"
#include "ImageLoader.hpp"

class TextureCache
{
	public:
		TextureCache();

		GLTexture	getTexture(const std::string &texturePath);

	private:
		std::map<const std::string, GLTexture>	_textureMap;
};

#endif // TEXTURECACHE_HPP
