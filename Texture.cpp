#include "Texture.hpp"

Texture::Texture(GLuint textureID) :
	_textureID(textureID)
{

}

GLuint Texture::getID() const {
	return this->_textureID;
}
