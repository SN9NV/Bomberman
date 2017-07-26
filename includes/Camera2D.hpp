#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D
{
	public:
		Camera2D();
		~Camera2D();

		void		init(unsigned screenWidth, unsigned screenHeight);
		void		update();

		void		addScale(float scale);
		void		setScale(float scale);
		void		addPosition(const glm::vec2 &rhs);
		void		setPosition(const glm::vec2 &position);
		void		setCameraMatrix(const glm::mat4 &cameraMatrix);

		float		getScale() const;
		glm::vec2	getPosition() const;
		glm::mat4	getCameraMatrix() const;


	private:
		unsigned	_screenWidth;
		unsigned	_screenHeight;

		bool		_bNeedsMatrixUpdate;
		float		_scale;
		glm::vec2	_position;
		glm::mat4	_cameraMatrix;
		glm::mat4	_orthoMatrix;
};

#endif // CAMERA2D_HPP
