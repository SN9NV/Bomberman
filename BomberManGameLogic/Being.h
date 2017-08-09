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
	float _speed;
	//cge::GLSLProgram _shader;
	//cge::Renderer _renderer;
	glm::vec3 _n_moveDir;
	size_t _maxBomb;
	std::vector<Bomb *> _bombs;
	bool _plaseBomb;

public:
	const glm::vec3 &get_n_moveDir() const;

	bool is_placeBomb() const;
	void placeBomb(Bomb *bomb);
	bool checkBombDeterNation(Bomb *bomb);
	Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
		  float speed);

	void update(const cge::InputManager &input, unsigned lastFrameTime) override;

	void setRotation();

	float getDirAngle();
//	void render();
};


#endif //BOMBERMAN_BEING_HPP
