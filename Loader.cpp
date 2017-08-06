#include "Loader.hpp"
#include "IO.hpp"
#include "picoPNG.hpp"

Texture Loader::loadTexture(const std::string &texturePath) {
	auto foundTexture = this->_textures.find(texturePath);
	GLuint	textureID = 0;

	if (foundTexture == this->_textures.end()) {
		std::vector<unsigned char>	in;
		std::vector<unsigned char>	out;
		unsigned long	width;
		unsigned long	height;

		if (IO::readFileToBuffer(texturePath, in)) {
			std::cerr << "Failed to load image: " << texturePath << "\n";
			exit(1);
		}

		if (PicoPNG::decodePNG(out, width, height, in.data(), in.size()) > 0) {
			std::cerr << "Failed to decode PNG: " << texturePath << "\n";
			exit(1);
		}

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		this->_textures[texturePath] = textureID;
	} else {
		textureID = foundTexture->second;
	}

	return Texture(textureID);
}

Loader::~Loader() {
	for (auto &texture : this->_textures) {
		glDeleteTextures(1, &(texture.second));
	}
}