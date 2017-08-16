#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>

#include "../entites/Model.hpp"
#include "../entites/TextureAtlas.h"

namespace cge {
    class Loader {
    public:
        Loader() = default;

        ~Loader();

        Texture loadTexture(const std::string &texturePath);
        TextureAtlas loadTextureAtlas(const std::string &texturePath, int row);
        tinygltf::Model &loadGLTFModel(const std::string &modelPath);

    private:
        std::map<std::string, GLuint> _textures;
        std::map<std::string, TextureAtlas> _textureAtlasas;
        std::map<std::string, tinygltf::Model> _models;
        tinygltf::TinyGLTF _gltfLoader;

    };
}

#endif //NEW_LOADER_HPP
