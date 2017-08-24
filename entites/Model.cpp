#include "Model.hpp"

cge::Model::Model(const tinygltf::Model &model, const Texture &texture, Model::Type type) :
		_vaoID(0),
		_texture(texture),
		_model(model),
		_type(type)
{
	this->_create();
}

cge::Model::Model(const std::string &modelFilePath, const std::string &textureFilePath, cge::Loader &loader, Model::Type type) :
		_vaoID(0),
		_texture(loader.loadTexture(textureFilePath)),
		_model(loader.loadGLTFModel(modelFilePath)),
		_type(type)
{
	this->_create();
}

GLuint cge::Model::getVaoID() const {
	return this->_vaoID;
}

const cge::Texture &cge::Model::getTexture() const {
	return this->_texture;
}

const tinygltf::Model &cge::Model::getTinygltfModel() const {
	return this->_model;
}

const std::vector<GLuint> &cge::Model::getVBOs() const {
	return this->_vbos;
}

void cge::Model::_create() {
	glGenVertexArrays(1, &this->_vaoID);
	glBindVertexArray(this->_vaoID);

	for (const auto &view : this->_model.bufferViews) {
		if (view.target == 0) {
			continue;
		}

		const tinygltf::Buffer &buffer = this->_model.buffers[view.buffer];

		GLuint vboID = 0;
		glGenBuffers(1, &vboID);
		glBindBuffer((GLenum)view.target, vboID);
		glBufferData((GLenum)view.target, view.byteLength, buffer.data.data() + view.byteOffset, (GLenum)this->_type);
		glBindBuffer((GLenum)view.target, 0);

		this->_vbos.push_back(vboID);
	}
}

cge::Model::Type cge::Model::getType() const {
	return this->_type;
}

std::ostream	&operator<<(std::ostream &out, cge::Model::Type type) {
	std::string	outString;

	switch (type) {
		case cge::Model::Type::STATIC:
			outString = "STATIC";
			break;
		case cge::Model::Type::DYNAMIC:
			outString = "DYNAMIC";
			break;;
		case cge::Model::Type::STREAMING:
			outString = "STREAMING";
	}

	out << outString;

	return out;
}