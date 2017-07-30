#ifndef NEW_TEXTURE_HPP
#define NEW_TEXTURE_HPP


#include <GL/glew.h>

class Texture {
public:
	Texture() = default;
	~Texture() = default;

	Texture(GLuint textureID);

	GLuint		getID() const;

private:
	GLuint	_textureID;

};


#endif //NEW_TEXTURE_HPP
