#ifndef NEW_MATHS_HPP
#define NEW_MATHS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../entites/Camera.hpp"

namespace cge {
	namespace Maths {
		glm::mat4	createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale);
		glm::mat4	createViewMatrix(const Camera &camera);
		float 		vec3Len(glm::vec3 vec);
	}
}

#endif //NEW_MATHS_HPP
