#ifndef NEW_MODEL_HPP
#define NEW_MODEL_HPP

namespace cge {
	class Loader;
}

#include <GL/glew.h>

#include "Texture.hpp"
#include "tinyGLTF/tiny_gltf.h"
#include "Loader.hpp"

namespace cge {
	class Model {
	public:
		Model() = default;
		~Model() = default;

		Model(const std::string &modelFilePath, const std::string &textureFilePath, cge::Loader &loader);
		Model(const tinygltf::Model &model, const cge::Texture &texture);

		GLuint					getVaoID() const;
		std::vector<GLuint>		&getVBOs();
		cge::Texture			&getTexture();
		tinygltf::Model 		&getTinygltfModel();

	private:
		GLuint					_vaoID;
		std::vector<GLuint>		_vbos;
		cge::Texture			_texture;
		tinygltf::Model			_model;

		void 					_create();
	};
}


#endif //NEW_MODEL_HPP
