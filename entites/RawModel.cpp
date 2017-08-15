//
// Created by Robert JONES on 2017/08/15.
//

#include <GL/glew.h>
#include "RawModel.hpp"

namespace cge
{
	RawModel::RawModel(const std::vector<float> &data, const std::vector<unsigned int> &index)
	{
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ibo);
		glBindVertexArray(_vao);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float) , data.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()* sizeof(unsigned int), index.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
		glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	GLuint RawModel::getVao() const
	{
		return _vao;
	}

	GLuint RawModel::getVbo() const
	{
		return _vbo;
	}

	GLuint RawModel::getIbo() const
	{
		return _ibo;
	}

	RawModel::~RawModel()
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ibo);
		glDeleteVertexArrays(1, &_vao);
	}
}