#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>
#include <al.h>
#include <sndfile.hh>

#include "../entites/Model.hpp"

namespace cge {
	class Loader {
	public:
		struct AudioFile {
			int16_t	*buffer;
			SF_INFO	info;
		};

		Loader() = default;
		~Loader();

		cge::Texture			loadTexture(const std::string &texturePath);
		tinygltf::Model			&loadGLTFModel(const std::string &modelPath);
		cge::Loader::AudioFile	loadAudio(const std::string &audioPath);

	private:
		std::map<std::string, GLuint>					_textures;
		std::map<std::string, tinygltf::Model>			_models;
		std::map<std::string, cge::Loader::AudioFile>	_audioFiles;

		tinygltf::TinyGLTF						_gltfLoader;
	};
}

#endif //NEW_LOADER_HPP
