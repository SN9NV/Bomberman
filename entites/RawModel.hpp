//
// Created by Robert JONES on 2017/08/15.
//

#ifndef BOMBERMAN_RAWMODEL_H
#define BOMBERMAN_RAWMODEL_H


#include <vector>
#include <GL/glew.h>

namespace cge
{
	class RawModel
	{
		RawModel() = default;

	private:
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
	public:
		GLuint getVao() const;

		GLuint getVbo() const;

		GLuint getIbo() const;

		RawModel(const std::vector<float> &data, const std::vector<unsigned int> &index, bool UV = false);

		virtual ~RawModel();
	};

}
#endif //BOMBERMAN_RAWMODEL_H
