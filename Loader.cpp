#include "Loader.hpp"
#include "IO.hpp"
#include "picoPNG.hpp"

namespace cge {
	Texture Loader::loadTexture(const std::string &texturePath) {
		auto foundTexture = this->_textures.find(texturePath);

		if (foundTexture == this->_textures.end()) {
			std::vector<unsigned char>	in;
			std::vector<unsigned char>	out;
			unsigned long	width;
			unsigned long	height;
			GLuint			textureID = 0;

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
			return Texture(textureID);
		}

		return foundTexture->second;
	}

	Loader::~Loader() {
		for (auto &texture : this->_textures) {
			glDeleteTextures(1, &(texture.second));
		}
	}

	tinygltf::Model &Loader::loadGLTFModel(const std::string &modelPath) {
		auto foundModel = this->_models.find(modelPath);

		if (foundModel == this->_models.end()) {
//			std::cout << "Model: " << modelPath << " not found in map. Loading from file\n";
			this->_models[modelPath] = tinygltf::Model();
			tinygltf::Model &model = this->_models[modelPath];
			std::string		err;

			this->_gltfLoader.LoadBinaryFromFile(&model, &err, modelPath);

			if (!err.empty()) {
				std::cout << "Had error loading glTF file!!!\n" << err << "\n";
				exit(1);
			}

			return model;
		}

//		std::cout << "Model: " << modelPath << " was found in map. Returning reference\n";
		return foundModel->second;
	}
}