#include <array>
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

		for (auto &audioBuffer : this->_audioFiles) {
			alDeleteBuffers(1, &(audioBuffer.second.bufferID));
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
			/// SF_INFO holds info on the audio file
			SF_INFO	sfInfo = {};

			///	Open audio file
			SNDFILE	*file = sf_open(audioPath.c_str(), SFM_READ, &sfInfo);

			if (file == nullptr) {
				std::cerr << "Could not open audio file: " << audioPath << "\n";
				exit(1);
			}

			/// Read file info buffer
			std::vector<int16_t>	buffer(static_cast<unsigned long>(sfInfo.channels * sfInfo.frames));
			sf_readf_short(file, buffer.data(), sfInfo.frames);
			sf_close(file);

			/// Generate buffer to store audio
			ALuint	bufferID = 0;

			alGenBuffers(1, &bufferID);
			if (bufferID == AL_INVALID_VALUE) {
				std::cerr << "Error creating buffer\n";
				exit(1);
			}

			alBufferData(
					bufferID,
					(sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
					buffer.data(),
					static_cast<ALsizei>(buffer.size() * sizeof(uint16_t)),
					sfInfo.samplerate
			);

			cge::Loader::AudioFile	ret = { bufferID, sfInfo };
			this->_audioFiles[audioPath] = ret;

			return ret;
		}

		return foundAudio->second;
	}
}