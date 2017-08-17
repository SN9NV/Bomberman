#ifndef BOMBERMAN_AUDIODEVICE_HPP
#define BOMBERMAN_AUDIODEVICE_HPP

#include <al.h>
#include <alc.h>

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <map>
#include "AudioSource.hpp"

namespace cge {
	namespace Audio {
		class Device {
		public:
			Device();
			explicit Device(const std::string &deviceName);
			~Device();

			static std::vector<std::string>	listDevices();
			static std::string				defaultDevice();

			void	setToCurrentContext() const;
			void	update() const;

			std::string			getDeviceName() const;
			const ALCdevice		*getDevice() const;
			const ALCcontext	*getContext() const;

			void	setLocation(const glm::vec3 &location, bool update = false);
			void	setVelocity(const glm::vec3 &velocity, bool update = false);
			void	setOrientation(const std::vector<float> &orientation, bool update = false);

			void	updateLocation() const;
			void	updateVelocity() const;
			void	updateOrientation() const;

			glm::vec3			getLocation() const;
			glm::vec3			getVelocity() const;
			std::vector<float>	getOrientation() const;

		private:
			std::string	_deviceName;
			ALCdevice	*_device;
			ALCcontext	*_context;

			std::map<std::string, cge::Audio::Source>	_sources;

			glm::vec3			_location;
			glm::vec3			_velocity;
			std::vector<float>	_orientation;

			void	_Init(const std::string &deviceName);
		};
	}
}

#endif //BOMBERMAN_AUDIODEVICE_HPP
