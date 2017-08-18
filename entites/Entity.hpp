#ifndef NEW_ENTITY_HPP
#define NEW_ENTITY_HPP

#include <glm/glm.hpp>
#include "Model.hpp"
#include "../rendering/GLSLProgram.hpp"
#include "../io/InputManager.hpp"
#include <glm/gtc/quaternion.hpp>


namespace cge {
	class Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;

//		Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model);
		Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model, float hitBoxRadius = 0.0f);

		virtual bool	update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
		void			addPosition(const glm::vec3 &delta);
		void			setPosition(const glm::vec3 &position);
		void			addRotation(const glm::vec3 &delta);
		void			setRotation(const glm::vec3 &rotation);
		void 			setHitBoxRadius(const float &hitBoxRadius);
		void 			setScale(float scale);
		void			setAnimationTicks(double ticks);
		void			setAnimationSpeed(float speed);

		float 			getHitBoxRadius() const;
		Model			&getModel();
		glm::vec3		getPosition() const;
		glm::vec3		getRotation() const;
		float 			getScale() const;
		bool 			isAnimated() const;
		double			getAnimationSpeed() const;

	protected:
		Model		&_model;
		glm::vec3	_position;
		glm::vec3	_rotation;
		float 		_scale;
		float		_hitBoxRadius;
		glm::mat4	_transformation;
		GLint		_transformationLocation;
		double		_lastTicks;
		double		_ticksDelta;
		double		_animationTicks;
		unsigned	_currentAnimation;
		bool		_hasAnimation;
		double		_animationSpeed;

		bool		_needsTransformationUpdate;

		struct Transformation {
			glm::vec3	translation;
			glm::quat	rotation;
		};

		struct _AnimateSkeleton {
			const std::map<int, Transformation>	&transformationMap;
			glm::mat4							&parentTransform;
			std::map<int, glm::mat4>			&animatedMatrices;
			std::vector<tinygltf::Node>			&nodes;
			const glm::mat4						*inverseMatrices;
			int									startNodeIndex;
			int									rootNodeIndex;
		};

		void	_applyAnimation(cge::GLSLProgram &shader);
		void	_animateSkeleton(cge::Entity::_AnimateSkeleton &vars);
	};
}

#endif //NEW_ENTITY_HPP
