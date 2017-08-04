#include "Loader.hpp"
#include "IO.hpp"
#include "picoPNG.hpp"

Model Loader::loadToVAO(const std::vector<Vertex> &vertices, const std::vector<unsigned> &indices, const std::string &texturePath) {
	GLuint	vaoID = this->_createVAO();

	this->_uploadVertexArray(vertices);
	this->_bindIndicesBuffer(indices);

	glBindVertexArray(0);

	Texture texture = this->loadTexture(texturePath);

	return Model(vaoID, texture, static_cast<unsigned>(indices.size()));
}

Texture Loader::loadTexture(const std::string &texturePath) {
	std::vector<unsigned char>	in;
	std::vector<unsigned char>	out;
	unsigned long	width;
	unsigned long	height;

	if (IO::readFileToBuffer(texturePath, in)) {
		std::cerr << "Failed to load image: " << texturePath << "\n";
		exit(1);
	}

	if (PicoPNG::decodePNG(out, width, height, in.data(), in.size()) > 0) {
		std::cerr << "Failed to decode PNG: " << texturePath << "\n";
		exit(1);
	}

	GLuint	textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	this->_textureIDs.push_back(textureID);

	return Texture(textureID);
}

GLuint Loader::_createVAO() {
	GLuint	vaoID = 0;

	glGenVertexArrays(1, &vaoID);
	this->_vaos.push_back(vaoID);
	glBindVertexArray(vaoID);

	return vaoID;
}

GLuint Loader::_createVBO(GLenum target) {
	GLuint	vboID = 0;

	glGenBuffers(1, &vboID);
	this->_vbos.push_back(vboID);
	glBindBuffer(target, vboID);

	return vboID;
}

void Loader::_storeDataInAttributeList(GLuint attributeNumber, unsigned coordinateSize, const std::vector<float> &data) {
	this->_createVBO(GL_ARRAY_BUFFER);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::_bindIndicesBuffer(const std::vector<unsigned> &indices) {
	this->_createVBO(GL_ELEMENT_ARRAY_BUFFER);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Loader::~Loader() {
	for (auto &vao : this->_vaos) {
		glDeleteVertexArrays(1, &vao);
	}

	for (auto &vbo : this->_vbos) {
		glDeleteBuffers(1, &vbo);
	}

	for (auto &texture : this->_textureIDs) {
		glDeleteTextures(1, &texture);
	}
}

void Loader::_uploadVertexArray(const std::vector<Vertex> &vertices) {
	this->_createVBO(GL_ARRAY_BUFFER);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model Loader::loadToVAO(const std::vector<float> &vertices, const std::vector<float> &normals,
						const std::vector<float> &uv, const std::vector<unsigned> &indices,
						const std::string &texturePath) {
	GLuint	vaoID = this->_createVAO();

	this->_storeDataInAttributeList(0, 3, vertices);
	this->_storeDataInAttributeList(1, 3, normals);
	this->_storeDataInAttributeList(2, 2, uv);
	this->_bindIndicesBuffer(indices);

	glBindVertexArray(0);

	Texture texture = this->loadTexture(texturePath);

	return Model(vaoID, texture, static_cast<unsigned>(indices.size()));
}
