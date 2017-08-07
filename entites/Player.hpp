#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "Entity.hpp"

namespace cge {
	class Player : public Entity {
	public:


		using Entity::Entity;
		Player() = default;
		~Player() = default;

		void	update(const InputManager &input, unsigned lastFrameTime);

	private:
	};
}

#endif //BOMBERMAN_PLAYER_HPP
