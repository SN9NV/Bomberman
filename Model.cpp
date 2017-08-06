#include "Model.hpp"

Model::Model(const tinygltf::Model &model, const Texture &texture) :
	_vaoID(0),
	_texture(texture),
	_model(model)
{
	glGenVertexArrays(1, &this->_vaoID);
	glBindVertexArray(this->_vaoID);

	for (const auto &view : model.bufferViews) {
		if (view.target == 0) {
			continue;
		}

		const tinygltf::Buffer &buffer = model.buffers[view.buffer];

		GLuint vboID = 0;
		glGenBuffers(1, &vboID);
		glBindBuffer((GLenum)view.target, vboID);
		glBufferData((GLenum)view.target, view.byteLength, buffer.data.data() + view.byteOffset, GL_STATIC_DRAW);
		glBindBuffer((GLenum)view.target, 0);

		this->_vbos.push_back(vboID);
	}
}

GLuint Model::getVaoID() const {
	return this->_vaoID;
}

Texture &Model::getTexture() {
	return this->_texture;
}

tinygltf::Model &Model::getTinygltfModel() {
	return this->_model;
}

std::vector<GLuint> &Model::getVBOs() {
	return this->_vbos;
}