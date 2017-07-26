#include "TextureCache.hpp"

TextureCache::TextureCache()
{

}

GLTexture TextureCache::getTexture(const std::string &texturePath) {
	auto mapIterator = this->_textureMap.find(texturePath);

	if (mapIterator == this->_textureMap.end()) {
		GLTexture	newTexture = ImageLoader::loadPNG(texturePath);
		this->_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Loaded new texture: " << texturePath << "\n";
		return newTexture;
	}

//	std::cout << "Loaded cached texture: " << texturePath << "\n";
	return mapIterator->second;
}
