#ifndef NEW_MATHS_HPP
#define NEW_MATHS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"

namespace Maths {
	glm::mat4	createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale);
	glm::mat4	createViewMatrix(const Camera &camera);
}

#endif //NEW_MATHS_HPP
