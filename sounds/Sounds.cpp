//
// Created by Owen EXALL on 2017/07/27.
//

#include "Sounds.hpp"


cge::Sounds::Sounds() :
	can_play(false),
	musicVolume(DEFAULT_MUSIC_VOLUME),
	sfxVolume(DEFAULT_SFX_VOLUME),
	_nowPlaying(Sounds::Music::None)
{
	initMixer();
}

void cge::Sounds::initMixer() {
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to Initialize SDL Audio." << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return ;
	}

	if (MIX_INIT_OGG != Mix_Init(MIX_INIT_OGG))	{
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		std::cout << "Failed to Initialize SDL Mixer OGG." << std::endl;
		return ;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		Mix_Quit();
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		std::cout << "Failed to Open Audio device." << std::endl;
		return ;
	}

	Mix_AllocateChannels(RESERVED_CHANNELS);
	can_play = true;
}

cge::Sounds::~Sounds() {
	for (auto const& x : this->musicMap)
		Mix_FreeMusic(x.second);
	for (auto const& x : this->sfxMap)
		Mix_FreeChunk(x.second);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

int cge::Sounds::GetMusicVolume() const {
	return (this->musicVolume);
}
void cge::Sounds::SetMusicVolume(const int volume) {
	this->musicVolume = volume;
	Mix_VolumeMusic(this->musicVolume);
}

int cge::Sounds::GetSfxVolume() const {
	return (this->sfxVolume);
}
void cge::Sounds::SetSfxVolume(const int volume) {
	this->sfxVolume = volume;
}

Mix_Music* cge::Sounds::getMusic(Music key) {
	auto musicIterator = this->musicMap.find(key);

	if (musicIterator == this->musicMap.end()) {
		Mix_Music *music = nullptr;
		switch (key)
		{
			case (Music::LevelOne):
				music = Mix_LoadMUS("resources/sounds/Area 1.ogg");
				break;
			case (Music::LevelTwo):
				music = Mix_LoadMUS("resources/sounds/Area 2.ogg");
				break;
			case (Music::LevelThree):
				music = Mix_LoadMUS("resources/sounds/Area 3.ogg");
				break;
			case (Music::LevelFour):
				music = Mix_LoadMUS("resources/sounds/Area 4.ogg");
				break;
			case (Music::LevelFive):
				music = Mix_LoadMUS("resources/sounds/Area 5.ogg");
				break;
			case (Music::LevelSix):
				music = Mix_LoadMUS("resources/sounds/Area 6.ogg");
				break;
			case (Music::Boss):
				music = Mix_LoadMUS("resources/sounds/Boss.ogg");
				break;
			case (Music::Battle):
				music = Mix_LoadMUS("resources/sounds/Battle.ogg");
				break;
			case (Music::Menu):
			default:
				music = Mix_LoadMUS("resources/sounds/MainTheme.ogg");
				break;
		}
		if (music == nullptr) {
			std::cout << "Error: " << Mix_GetError() << std::endl;
			return (nullptr);
		}
		this->musicMap.insert(std::make_pair(key, music));
		return (music);
	}

	return (musicIterator->second);
}

Mix_Chunk* cge::Sounds::getSfxChunk(Sfx key) {
	auto sfxIterator = this->sfxMap.find(key);

	if (sfxIterator == this->sfxMap.end()) {
		Mix_Chunk *sfx = nullptr;
		switch (key)
		{
			case (Sfx::Menu_Validate):
				sfx = Mix_LoadWAV("resources/sounds/menu_validate.wav");
				break;
			case (Sfx::Menu_Scroll):
				sfx = Mix_LoadWAV("resources/sounds/menu_click.wav");
				break;
			case (Sfx::SFX_Explosion):
				sfx = Mix_LoadWAV("resources/sounds/sfx_explosion.wav");
				break;
			default:
				sfx = nullptr;
				break;
		}
		if (sfx == nullptr) {
			std::cout << "Error: " << Mix_GetError() << std::endl;
			return (nullptr);
		}
		this->sfxMap.insert(std::make_pair(key, sfx));
		return (sfx);
	}

	return (sfxIterator->second);
}

void cge::Sounds::PlayMusic(Music type) {
	if (!can_play) {
		std::cout << "PlayMusic: Can't play audio." << std::endl;
		return ;
	}
	if (type == this->_nowPlaying)
		return;

	Mix_Music *music = getMusic(type);
	if (music == nullptr) {
		std::cout << "Can't find audio." << std::endl;
		return ;
	}
	Mix_VolumeMusic(this->musicVolume);
	Mix_PlayMusic(music, -1);
	this->_nowPlaying = type;
}

void cge::Sounds::PlayMusicFadeOut(Sounds::Music type, int ms) {
	if (!can_play) {
		std::cout << "PlayMusic: Can't play audio." << std::endl;
		return ;
	}
	if (type == this->_nowPlaying)
		return;

	Mix_FadeOutMusic(ms);
	Mix_Music *music = getMusic(type);
	if (music == nullptr) {
		std::cout << "Can't find audio." << std::endl;
		return ;
	}
	Mix_VolumeMusic(this->musicVolume);
	Mix_PlayMusic(music, -1);
	this->_nowPlaying = type;
}

void cge::Sounds::PlaySfx(Sfx type) {
	if (!can_play) {
		std::cout << "PlaySfx: Can't play audio." << std::endl;
		return ;
	}

	Mix_Chunk *chunk = getSfxChunk(type);
	if (chunk == nullptr) {
		std::cout << "Can't find audio." << std::endl;
		return ;
	}

	int volume = this->sfxVolume;
	if (type == Sfx::SFX_Explosion)
		volume = 58;
	Mix_VolumeChunk(chunk, volume);
	Mix_PlayChannel(-1, chunk, 0);
}

