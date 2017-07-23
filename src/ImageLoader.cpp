#include "ImageLoader.hpp"

GLTexture ImageLoader::loadPNG(const std::string &filePath) {
	GLTexture	texture = {};
	std::vector<unsigned char>	in;
	std::vector<unsigned char>	out;
	unsigned long width, height;

	if (IO::readFileToBuffer(filePath, in)) {
		std::cerr << "Failed to load image: " << filePath << "\n";
		exit(1);
	}

	if (PicoPNG::decodePNG(out, width, height, &(in[0]), in.size())) {
		std::cerr << "Failed to decode PNG: " << filePath << "\n";
		exit(1);
	}

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}
