//
// Created by rojones on 2017/08/07.
//

#ifndef BOMBERMAN_BEING_HPP
#define BOMBERMAN_BEING_HPP


#include "../entites/Entity.hpp"
#include "../io/InputManager.hpp"
#include "../rendering/Renderer.hpp"
#include "Bomb.hpp"

class Being : public cge::Entity
{
protected:
	float		_speed;
	glm::vec3	_n_moveDir;
	size_t		_maxBomb;
public:
	size_t getMaxBomb() const;

	void setMaxBomb(size_t _maxBomb);

protected:
	bool		_placeBomb;
	int			_damage;
	unsigned	_deathTimeout;
	bool		_alive;
	std::vector<Bomb *> _bombs;

public:
	Being() = delete;
	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float speed, float hitBoxRadius, int damage = 2);

	int		getDamage() const;
	bool	isAlive() const;
	bool	isPlaceBomb() const;
	bool	checkBombDeterNation(Bomb *bomb);
	void	setDamage(int _damage);
	void	placeBomb(Bomb *bomb);
	void	setAlive(bool _alive);

	float	getDirAngle();
	void	setPlaceBomb(bool placeBomb);
	void	setDirection();
	void	setMoveDir(glm::vec3 newDir);
	void	setSpeed(float speed);
	float	getSpeed() const;

	const glm::vec3	&get_n_moveDir() const;

	virtual bool	update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) override;
};


#endif //BOMBERMAN_BEING_HPP
