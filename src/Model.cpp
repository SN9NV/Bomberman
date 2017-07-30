#include "Model.hpp"

Model::Model() :
	_vaoID(0),
	_textureID(0),
	_vertexCount(0)
{

}

Model::Model(GLint vaoID, GLint textureID, unsigned vertexCount) :
	_vaoID(vaoID),
	_textureID(textureID),
	_vertexCount(vertexCount)
{

}

Model::init(GLint vaoID, GLint textureID, unsigned vertexCount)
{
	this->_vaoID = vaoID;
	this->_textureID = textureID;
	this->_vertexCount = vertexCount;
}

GLint Model::vaoID() const
{
	return this->_vaoID;
}

GLint Model::textureID() const
{
	return this->_textureID;
}

unsigned Model::vertexCount() const
{
	return this->_vertexCount;
}
