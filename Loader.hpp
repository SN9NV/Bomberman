#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>

#include "Model.hpp"
#include "Vertex.hpp"

namespace cge {
	class Loader {
	public:
		Loader() = default;
		~Loader();

		Texture			loadTexture(const std::string &texturePath);
		tinygltf::Model	&loadGLTFModel(const std::string &modelPath);

	private:
		std::map<std::string, GLuint>			_textures;
		std::map<std::string, tinygltf::Model>	_models;

		tinygltf::TinyGLTF						_gltfLoader;
	};
}

#endif //NEW_LOADER_HPP
