#ifndef NEW_MODEL_HPP
#define NEW_MODEL_HPP


#include <GL/glew.h>

#include "Texture.hpp"

class Model {
public:
	Model() = default;
	~Model() = default;

	Model(GLuint vaoID, const Texture &texture, unsigned vertexCount);

	GLuint		getVaoID() const;
	Texture		getTexture() const;
	unsigned	getVertexCount() const;

private:
	GLuint		_vaoID;
	Texture		_texture;
	unsigned	_vertexCount;
};


#endif //NEW_MODEL_HPP
