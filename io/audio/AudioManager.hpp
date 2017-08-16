#ifndef BOMBERMAN_AUDIOMANAGER_HPP
#define BOMBERMAN_AUDIOMANAGER_HPP

#include <al.h>
#include <alc.h>

#include <vector>
#include <string>
#include "AudioDevice.hpp"
#include "AudioSource.hpp"

namespace cge {
	namespace Audio {
		class Manager {
		public:

		private:
			std::vector<cge::Audio::Device>	_devices;
			std::vector<cge::Audio::Source>	_sources;
		};
	}
}

#endif //BOMBERMAN_AUDIOMANAGER_HPP
