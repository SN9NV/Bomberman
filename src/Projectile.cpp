#include "Projectile.hpp"

Projectile::Projectile()
{

}

Projectile::Projectile(glm::vec2 position, glm::vec2 direction, float speed, unsigned lifeTime)
{
	this->init(position, direction, speed, lifeTime);
}

Projectile::~Projectile()
{

}

void Projectile::init(glm::vec2 position, glm::vec2 direction, float speed, unsigned lifeTime)
{
	this->_position = position;
	this->_direction = direction;
	this->_speed = speed;
	this->_lifeTime = lifeTime;
}

void Projectile::draw(SpriteBatch &spriteBatch)
{
	GLTexture	texture = ResourceManager::getTexture("images/cartoon-bullet-2400px.png");
	glm::vec4	positionAndSize(this->_position.x, this->_position.y, 32, 32);

	spriteBatch.draw(positionAndSize, texture.id, 0.0f);
}

bool Projectile::update()
{
	this->_position += this->_direction * this->_speed;
	return (!--this->_lifeTime);
}

unsigned Projectile::lifeTime() const
{
	return this->_lifeTime;
}
