#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "TextureCache.hpp"

class ResourceManager
{
	public:
		static GLTexture	getTexture(const std::string &texturePath);

	private:
		static TextureCache	_textureCache;
};

#endif // RESOURCEMANAGER_HPP
