#ifndef BOMBERMAN_AUDIOSOURCE_HPP
#define BOMBERMAN_AUDIOSOURCE_HPP

#include <al.h>
#include <glm/vec3.hpp>

#include <string>

namespace cge {
	namespace Audio {
		class Source {
		public:
			Source();
			Source(const std::string &audioFilePath);
			Source(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping);

			~Source();

			void	Init(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping);

			void	setPitch(ALfloat pitch);
			void	setGain(ALfloat gain);
			void	setPosition(const glm::vec3 &position);
			void	setVelocity(const glm::vec3 &velocity);
			void	setLooping(bool isLooping);

		private:
			ALuint	_sourceID;

			ALfloat		_pitch;
			ALfloat		_gain;
			glm::vec3	_position;
			glm::vec3	_velocity;
			bool		_isLooping;
		};
	}
}

#endif //BOMBERMAN_AUDIOSOURCE_HPP
