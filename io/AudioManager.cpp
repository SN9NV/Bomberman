#include "AudioManager.hpp"

cge::AudioManager::AudioManager() {

}

cge::AudioManager::~AudioManager() {

}

std::vector<std::string> cge::AudioManager::listDevices() {


	return std::vector<std::string>();
}

static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}

list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));