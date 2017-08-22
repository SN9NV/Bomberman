#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>
#include <al.h>
#include <sndfile.hh>
#include <glfw/include/GLFW/glfw3.h>

#include "../entites/Model.hpp"
#include "../entites/TextureAtlas.h"

namespace cge {
    class Loader {
    public:
        struct AudioFile {
            int16_t	*buffer;
            SF_INFO	info;
        };

        Loader() = default;

        ~Loader();

        Texture loadTexture(const std::string &texturePath);
        TextureAtlas loadTextureAtlas(const std::string &texturePath, int row);
        tinygltf::Model &loadGLTFModel(const std::string &modelPath);
		cge::Loader::AudioFile	loadAudio(const std::string &audioPath);
		GLFWimage loadGLFWImage(const std::string &imagePath);

    private:
        std::map<std::string, GLuint>					_textures;
        std::map<std::string, TextureAtlas>				_textureAtlasas;
        std::map<std::string, tinygltf::Model>			_models;
		std::map<std::string, cge::Loader::AudioFile>	_audioFiles;

        tinygltf::TinyGLTF								_gltfLoader;
    };
}

#endif //NEW_LOADER_HPP
