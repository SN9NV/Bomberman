//
// Created by Owen EXALL on 2017/07/27.
//

#pragma once

#include <SDL_mixer.h>
#include <map>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <utility>

#define RESERVED_CHANNELS 32
#define DEFAULT_MUSIC_VOLUME 5
#define DEFAULT_SFX_VOLUME 10

namespace cge {
	class Sounds {
	public:
		enum Sfx {
			Menu_Scroll,
			Menu_Validate,
			SFX_Explosion
		};

		enum Music {
			None,
			Menu,
			LevelOne,
			LevelTwo,
			LevelThree,
			LevelFour,
			LevelFive,
			LevelSix,
			Boss,
			Battle
		};

		Sounds();
		~Sounds();

		int GetMusicVolume() const;

		void SetMusicVolume(const int volume);

		int GetSfxVolume() const;

		void SetSfxVolume(const int volume);

		void PlayMusic(Music type);

		void PlayMusicFadeOut(Music type, int ms);

		void PlaySfx(Sfx type);

	private:
		bool can_play;
		int musicVolume;
		int sfxVolume;
		Music _nowPlaying;

		std::map<Sfx, Mix_Chunk *> sfxMap;
		std::map<Music, Mix_Music *> musicMap;


		void initMixer();

		Mix_Chunk *getSfxChunk(Sfx key);

		Mix_Music *getMusic(Music key);
	};
};