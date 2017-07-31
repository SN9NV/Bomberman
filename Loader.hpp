#ifndef NEW_LOADER_HPP
#define NEW_LOADER_HPP

#include <vector>
#include <string>
#include <regex>

#include <GL/glew.h>

#include "Model.hpp"
#include "ImageLoader.hpp"
#include "Vertex.hpp"

class Loader {
public:
	Loader() = default;
	~Loader();

	Model	loadToVAO(const std::vector<Vertex> &vertices, const std::vector<unsigned> &indices, const std::string &texturePath);
//	Model	loadToVAO(const std::string &objPath, const std::string &texturePath);
	Texture	loadTexture(const std::string &texturePath);

private:
	std::vector<GLuint>	_vaos;
	std::vector<GLuint>	_vbos;
	std::vector<GLuint>	_textureIDs;

	GLuint	_createVAO();
	void	_storeDataInAttributeList(GLuint attributeNumber, unsigned coordinateSize, const std::vector<float> &data);
	void	_uploadVertexArray(const std::vector<Vertex> &vertices);
	void	_bindIndicesBuffer(const std::vector<unsigned> &indices);
};


#endif //NEW_LOADER_HPP
