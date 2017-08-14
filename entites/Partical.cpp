//
// Created by Robert JONES on 2017/08/14.
//

#include <GL/glew.h>
#include "Partical.h"

namespace cge
{
	Partical::Partical(const GLSLProgram &shader) : _shader(shader)
	{
		glGenBuffers(1, &_VBO);
	}
}
