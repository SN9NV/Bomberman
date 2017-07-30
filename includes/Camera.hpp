#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	public:
		Camera();
		~Camera() = default;

		void		init(unsigned screenWidth, unsigned screenHeight);
		void		update();

		void		addScale(float delta);
		void		setScale(float scale);
		void		addPosition(const glm::vec3 &delta);
		void		setPosition(const glm::vec3 &position);
		void		addRotation(const glm::vec3 &delta);
		void		setRotation(const glm::vec3 &rotation);
		void		setCameraMatrix(const glm::mat4 &cameraMatrix);


		float		scale() const;
		glm::vec3	position() const;
		glm::mat4	cameraMatrix() const;

		glm::vec3	screenToWorldCoords(glm::vec2 screenCoords) const;

	private:
		unsigned	_screenWidth;
		unsigned	_screenHeight;

		bool		_bNeedsMatrixUpdate;
		float		_scale;
		glm::vec3	_position;
		glm::vec3	_rotation;
		glm::mat4	_cameraMatrix;
		glm::mat4	_orthoMatrix;
};

#endif // CAMERA2D_HPP
