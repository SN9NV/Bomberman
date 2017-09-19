#ifndef NEW_TEXTURE_HPP
#define NEW_TEXTURE_HPP

#include "../shared.hpp"

namespace cge {
	class Texture {
	public:
		Texture() = default;
		~Texture() = default;

		Texture(GLuint textureID);

		GLuint		getID() const;

	protected:
		GLuint	_textureID;

	};
}

#endif //NEW_TEXTURE_HPP
