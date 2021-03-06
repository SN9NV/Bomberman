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

			explicit Source();
			Source(const std::string &audioPath, cge::Loader &loader);
			Source(const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping, ALfloat pitch = 1.0f, ALfloat gain = 1.0f);
			Source(const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping, const std::string &audioPath, cge::Loader &loader, ALfloat pitch = 1.0f, ALfloat gain = 1.0f);

			~Source();

			void	Init(const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping, ALfloat pitch = 1.0f, ALfloat gain = 1.0f);
			void	setAudio(const std::string &audioFilePath, cge::Loader &loader);
			void	setPitch(ALfloat pitch);
			void	setGain(ALfloat gain);
			void	setPosition(const glm::vec3 &position);
			void	setVelocity(const glm::vec3 &velocity);
			void	setLooping(bool isLooping);
			void	setAttenuation(ALenum attenuationType = AL_LINEAR_DISTANCE_CLAMPED, float maxDistance = 15.0f, float refrenceDistance = 2.0f);

			ALfloat		getPitch() const;
			ALfloat 	getGain() const;
			glm::vec3	getPosition() const;
			glm::vec3	getVelocity() const;
			bool 		isLooping() const;
			unsigned	getFileSize(cge::Audio::Source::Offset offsetType) const;
			std::string	getName() const;
			SF_INFO		getInfo() const;

			void		setPlaying(bool play = true) const;
			bool 		isPlaying()const;
			unsigned	getPlayOffset(cge::Audio::Source::Offset offsetType);
			void		setPlayOffset(cge::Audio::Source::Offset offsetType, unsigned offset);

		private:
			ALuint		_sourceID;
			ALuint		_bufferID;
			SF_INFO		_sfInfo;

			std::string	_audioPath;
			std::string	_name;
			ALfloat		_pitch;
			ALfloat		_gain;
			glm::vec3	_position;
			glm::vec3	_velocity;
			bool		_isLooping;
		};
	}
}

#endif //BOMBERMAN_AUDIOSOURCE_HPP
