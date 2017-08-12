#ifndef BOMBERMAN_AUDIOMANAGER_HPP
#define BOMBERMAN_AUDIOMANAGER_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include <vector>
#include <string>

namespace cge {
	class AudioManager {
		AudioManager();
		~AudioManager();

		std::vector<std::string>	listDevices();
	};
}

#endif //BOMBERMAN_AUDIOMANAGER_HPP
