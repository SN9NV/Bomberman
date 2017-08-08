#include "Texture.hpp"

cge::Texture::Texture(GLuint textureID) :
		_textureID(textureID)
{

}

GLuint cge::Texture::getID() const {
	return this->_textureID;
}