#ifndef NEW_MODEL_HPP
#define NEW_MODEL_HPP

namespace cge {
	class Loader;
}

#include <GL/glew.h>

#include "Texture.hpp"
#include "../tinyGLTF/tiny_gltf.h"
#include "../loaders/Loader.hpp"

namespace cge {
	class Model {
	public:
		enum class Type {
			STATIC = GL_STATIC_DRAW,
			DYNAMIC = GL_DYNAMIC_DRAW,
			STREAMING = GL_STREAM_DRAW
		};

		Model() = delete;
		~Model() = default;

		Model(const std::string &modelFilePath, const std::string &textureFilePath, cge::Loader &loader, Model::Type type);
		Model(const tinygltf::Model &model, const cge::Texture &texture, Model::Type type);

		GLuint						getVaoID() const;
		Model::Type					getType() const;
		const std::vector<GLuint>	&getVBOs() const;
		const cge::Texture			&getTexture() const;
		const tinygltf::Model 		&getTinygltfModel() const;
		GLuint						getIndexAssessor() const;
		std::vector<GLuint>			&getAttribArrayIndexes();

	private:
		GLuint				_vaoID;
		std::vector<GLuint>	_vbos;
		std::vector<GLuint>	_AttribArrayIndexes;
		GLuint				_indexAssessor;
		cge::Texture		_texture;
		tinygltf::Model		_model;
		Model::Type			_type;

		void 				_create();
	};
}

std::ostream	&operator<<(std::ostream &out, cge::Model::Type type);


#endif //NEW_MODEL_HPP
