#ifndef NEW_MODEL_HPP
#define NEW_MODEL_HPP


#include <GL/glew.h>

#include "Texture.hpp"
#include "tinyGLTF/tiny_gltf.h"

class Model {
public:
	Model() = default;
	~Model() = default;

	Model(const tinygltf::Model &model, const Texture &texture);

	GLuint					getVaoID() const;
	std::vector<GLuint>		&getVBOs();
	Texture					&getTexture();
	tinygltf::Model 		&getTinygltfModel();

private:
	GLuint					_vaoID;
	std::vector<GLuint>		_vbos;
	Texture					_texture;
	tinygltf::Model			_model;
};


#endif //NEW_MODEL_HPP
