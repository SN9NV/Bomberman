#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>

#include "Model.hpp"
#include "Vertex.hpp"

class Loader {
public:
	Loader() = default;
	~Loader();

	Texture	loadTexture(const std::string &texturePath);

private:
	std::map<std::string, GLuint>	_textures;
};


#endif //NEW_LOADER_HPP
