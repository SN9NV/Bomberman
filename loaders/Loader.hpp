#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>
#include <al.h>

#include "../entites/Model.hpp"

namespace cge {
	class Loader {
	public:
		Loader() = default;
		~Loader();

		Texture			loadTexture(const std::string &texturePath);
		tinygltf::Model	&loadGLTFModel(const std::string &modelPath);
		ALuint			loadAudio(const std::string &audioPath);

	private:
		std::map<std::string, GLuint>			_textures;
		std::map<std::string, tinygltf::Model>	_models;
		std::map<std::string, ALuint>			_audioFiles;

		tinygltf::TinyGLTF						_gltfLoader;
	};
}

#endif //NEW_LOADER_HPP
