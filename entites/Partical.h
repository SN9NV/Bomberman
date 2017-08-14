//
// Created by Robert JONES on 2017/08/14.
//

#ifndef BOMBERMAN_PARTICAL_H
#define BOMBERMAN_PARTICAL_H


#include "../rendering/GLSLProgram.hpp"
#include <glm/simd/platform.h>

namespace cge
{
	class Partical
	{
	protected:
		static const GLfloat vertex[] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
		};
		unsigned int _VBO;
		const GLSLProgram &_shader;
	public:
		Partical(const GLSLProgram &shader);
	};
}

#endif //BOMBERMAN_PARTICAL_H
