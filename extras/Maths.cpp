#include "Maths.hpp"

namespace cge {
	namespace Maths {
		glm::mat4	createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale) {
			glm::mat4	transformation(1.0f);

			transformation = glm::translate(transformation, translation);
			transformation = glm::rotate(transformation, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			transformation = glm::rotate(transformation, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			transformation = glm::rotate(transformation, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			transformation = glm::scale(transformation, glm::vec3(scale, scale, scale));

			return transformation;
		}

		glm::mat4	createViewMatrix(const Camera &camera) {
			glm::mat4	viewMatrix(1.0f);
			glm::vec3	cameraPosition = camera.getPosition();
			glm::vec3	cameraRotation = camera.getRotation();

			viewMatrix = glm::rotate(viewMatrix, cameraRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			viewMatrix = glm::rotate(viewMatrix, cameraRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			viewMatrix = glm::rotate(viewMatrix, cameraRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

			viewMatrix = glm::translate(viewMatrix, cameraPosition * -1.0f);

			return viewMatrix;
		}

		float 		vec3Len(glm::vec3 vec)
		{
			return ((float)sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
		}

		glm::vec3	scaleVec3(float scale, glm::vec3 vec)
		{
			glm::vec3 re = {vec.x * scale, vec.y * scale,vec.z * scale};
			return (re);
		}
	}
}