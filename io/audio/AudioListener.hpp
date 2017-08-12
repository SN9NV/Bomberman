#ifndef BOMBERMAN_AUDIOLISTENER_HPP
#define BOMBERMAN_AUDIOLISTENER_HPP

#include <glm/glm.hpp>
#include "AudioDevice.hpp"

namespace cge {
	namespace Audio {
		class Listener {
		public:
			explicit Listener(cge::Audio::Device &device);

			void	setLocation(const glm::vec3 &location);
			void	setVelocity(const glm::vec3 &velocity);
			void	setOrientation(float orientation[6]);

		private:
			cge::Audio::Device	&_device;
			glm::vec3			_location;
			glm::vec3			_velocity;
			float				*_orientation;
		};
	}
}

#endif //BOMBERMAN_AUDIOLISTENER_HPP
