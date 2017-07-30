#include "Model.hpp"

Model::Model(GLuint vaoID, const Texture &texture, unsigned vertexCount) :
	_vaoID(vaoID),
	_texture(texture),
	_vertexCount(vertexCount)
{

}

GLuint Model::getVaoID() const {
	return this->_vaoID;
}

Texture Model::getTexture() const {
	return this->_texture;
}

unsigned Model::getVertexCount() const {
	return this->_vertexCount;
}
