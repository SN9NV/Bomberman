#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <glm/glm.hpp>
#include "SpriteBatch.hpp"
#include "Structs.hpp"
#include "ResourceManager.hpp"


class Projectile
{
	public:
		Projectile();
		Projectile(glm::vec2 position, glm::vec2 direction, float speed, unsigned lifeTime);
		~Projectile();

		void		init(glm::vec2 position, glm::vec2 direction, float speed, unsigned lifeTime);
		void		draw(SpriteBatch &spriteBatch);
		bool		update();

		unsigned	lifeTime() const;

	private:
		float		_speed;
		glm::vec2	_direction;
		glm::vec2	_position;
		unsigned	_lifeTime;
};

#endif // PROJECTILE_HPP
