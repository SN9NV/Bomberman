#include "Model.hpp"
#include "../rendering/Renderer.hpp"

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
		glBufferData((GLenum)view.target, view.byteLength, buffer.data.data() + view.byteOffset, GL_STATIC_DRAW);
		glBindBuffer((GLenum)view.target, 0);

		this->_vbos.push_back(vboID);
	}

	/// Bind stuff
	for (auto &attr : this->_model.meshes[0].primitives[0].attributes) {
		const auto &accessor = this->_model.accessors[attr.second];

		glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[accessor.bufferView]);

		GLint size;

		switch (accessor.type) {
			case TINYGLTF_TYPE_VEC2:
				size = 2;
				break;
			case TINYGLTF_TYPE_VEC3:
				size = 3;
				break;
			case TINYGLTF_TYPE_VEC4:
				size = 4;
				break;
			default:
				size = 1;
		}

		GLuint index = cge::Renderer::attrType::convert(attr.first);

		if (index != cge::Renderer::attrType::UNKNOWN) {
			glVertexAttribPointer(
					index,
					size,
					(GLenum) accessor.componentType,
					(GLboolean) ((accessor.normalized) ? GL_TRUE : GL_FALSE),
					(GLsizei) this->_model.bufferViews[accessor.bufferView].byteStride,
					BUFFER_OFFSET(accessor.byteOffset)
			);

			this->_AttribArrayIndexes.push_back(index);
		}
	}

	this->_indexAssessor = this->_vbos[this->_model.accessors[this->_model.meshes[0].primitives[0].indices].bufferView];

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

cge::Model::Type cge::Model::getType() const {
	return this->_type;
}

std::vector<GLuint> &cge::Model::getAttribArrayIndexes() {
	return this->_AttribArrayIndexes;
}

GLuint cge::Model::getIndexAssessor() const {
	return this->_indexAssessor;
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