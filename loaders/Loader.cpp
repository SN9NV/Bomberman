#include "Loader.hpp"
#include "IO.hpp"
#include "picoPNG.hpp"
#include "../entites/TextureAtlas.h"

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
	TextureAtlas Loader::loadTextureAtlas(const std::string &texturePath, int row) {
		auto foundTexture = this->_textureAtlasas.find(texturePath);

		if (foundTexture == this->_textureAtlasas.end()) {
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

			TextureAtlas tmp(textureID, row);
			this->_textureAtlasas[texturePath] = tmp;
			return tmp;
		}

		return foundTexture->second;
	}
	Loader::~Loader() {
		for (auto &texture : this->_textures) {
			glDeleteTextures(1, &(texture.second));
		}
		for (auto &texture : this->_textureAtlasas) {
			GLuint id = texture.second.getID();
			glDeleteTextures(1, &(id));
		}
	}

	tinygltf::Model &Loader::loadGLTFModel(const std::string &modelPath) {
		auto foundModel = this->_models.find(modelPath);

		if (foundModel == this->_models.end()) {
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

		return foundModel->second;
	}

	cge::Loader::AudioFile Loader::loadAudio(const std::string &audioPath) {
		auto foundAudio = this->_audioFiles.find(audioPath);

		if (foundAudio == this->_audioFiles.end()) {
			SF_INFO	sfInfo = {};

			SNDFILE	*file = sf_open(audioPath.c_str(), SFM_READ, &sfInfo);

			if (file == nullptr) {
				std::cerr << "Could not open audio file: " << audioPath << "\n";
				exit(1);
			}

			auto	*buffer = new int16_t[sfInfo.channels * sfInfo.frames];
			sf_readf_short(file, buffer, sfInfo.frames);
			sf_close(file);

			cge::Loader::AudioFile	ret = { buffer, sfInfo };
			this->_audioFiles[audioPath] = ret;

			return ret;
		}

		return foundAudio->second;
	}
}