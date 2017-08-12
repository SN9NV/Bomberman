#ifndef BOMBERMAN_AUDIODEVICE_HPP
#define BOMBERMAN_AUDIODEVICE_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <vector>

namespace cge {
	namespace Audio {
		class Device {
		public:
			explicit Device(const std::string &deviceName);

			static std::vector<std::string>	listDevices();
		private:
			ALCdevice	*_device;
			ALCcontext	*_context;
		};
	}
}

#endif //BOMBERMAN_AUDIODEVICE_HPP
