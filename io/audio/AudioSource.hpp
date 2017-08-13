#ifndef BOMBERMAN_AUDIOSOURCE_HPP
#define BOMBERMAN_AUDIOSOURCE_HPP

#include <al.h>
#include <glm/vec3.hpp>

#include <string>
#include <sndfile.h>
#include "../../loaders/Loader.hpp"

namespace cge {
	namespace Audio {
		class Source {
		public:
			enum class Offset {
				MILLISECONDS = AL_SEC_OFFSET,
				SAMPLES = AL_SAMPLE_OFFSET,
				BYTES = AL_BYTE_OFFSET
			};

			Source();
			Source(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping);

			~Source();

			void	Init(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping);

			void	setAudio(const std::string &audioFilePath, cge::Loader &loader);
			void	setPitch(ALfloat pitch);
			void	setGain(ALfloat gain);
			void	setPosition(const glm::vec3 &position);
			void	setVelocity(const glm::vec3 &velocity);
			void	setLooping(bool isLooping);

			ALfloat		getPitch() const;
			ALfloat 	getGain() const;
			glm::vec3	&getPosition() const;
			glm::vec3	&getVelocity() const;
			bool 		isLooping() const;
			unsigned	getFileSize(cge::Audio::Source::Offset offsetType) const;

			void		setPlay(bool play);
			bool 		isPlaying();
			unsigned	getPlayOffset(cge::Audio::Source::Offset offsetType);
			void		setPlayOffset(cge::Audio::Source::Offset offsetType, unsigned offset);

		private:
			ALuint		_sourceID;
			ALuint		_bufferID;
			SF_INFO		_sfInfo;

			ALfloat		_pitch;
			ALfloat		_gain;
			glm::vec3	_position;
			glm::vec3	_velocity;
			bool		_isLooping;
		};
	}
}

#endif //BOMBERMAN_AUDIOSOURCE_HPP
