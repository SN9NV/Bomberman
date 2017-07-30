#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glew.h>

class Model
{
	public:
		Model();
		Model(GLint vaoID, GLint textureID, unsigned vertexCount);

		init(GLint vaoID, GLint textureID, unsigned vertexCount);

		GLint		vaoID(void) const;
		GLint		textureID(void) const;
		unsigned	vertexCount(void) const;

	private:
		GLint		_vaoID;
		GLint		_textureID;
		unsigned	_vertexCount;
};

#endif // MODEL_HPP
