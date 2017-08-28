//
// Created by Owen Exall on 2017/08/18.
//

#ifndef BOMBERMAN_SETTINGS_HPP
#define BOMBERMAN_SETTINGS_HPP

#include <ios>
#include <fstream>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "../../error_handling/Exceptions.hpp"

namespace cge {
	namespace Settings {
		typedef struct	s_settings {
			/**Sound Volume**/
			float			MasterVolume;
			float			MusicVolume;
			float 			SfxVolume;

			/**Key Bindings**/
			unsigned int	KeyUpwards;
			unsigned int	KeyRight;
			unsigned int	KeyDown;
			unsigned int	KeyLeft;
			unsigned int	KeyDetonate;

			/**Window Settings**/
			bool			Fullscreen;
			unsigned		Width;
			unsigned		Height;
		}				t_settings;

		class Settings {
		public:
			Settings() = delete;
			Settings(const Settings & cpy);
			Settings operator=(const Settings & rhs);
			~Settings();

			static void						Initialise(std::string file);
			static cge::Settings::Settings*	getSingleton();

			t_settings						getSettings() const;

			/**Getters taking the master volume into account.**/
			float						getMusicVolume() const;
			float						getSfxVolume() const;

			/**Volume Setters**/
			void						setMasterVolume(float mv);
			void						setMusicVolume(float mv);
			void						setSfxVolume(float mv);

			/**Key Binding Setters**/
			void						setKeyUpwards(unsigned int ku);
			void						setKeyRight(unsigned int kr);
			void						setKeyDown(unsigned int kd);
			void						setKeyLeft(unsigned int kl);
			void						setKeyDetonate(unsigned int d);

			/**Window Setters**/
			void						setFullscreen(bool fs);
			void						setHeight(unsigned h);
			void						setWidth(unsigned w);

			void 						writeToBinaryFile();
		private:
			Settings(std::string file);

			static Settings*			s_instance;
			t_settings					_settings;
			std::string					_fileName;

			void						readFromBinaryFile();
			void						setToDefaults();
		};
	}
};


#endif //BOMBERMAN_SETTINGS_HPP
