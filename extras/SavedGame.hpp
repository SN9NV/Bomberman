//
// Created by Owen Exall on 2017/08/18.
//

#ifndef BOMBERMAN_SAVEDGAME_HPP
#define BOMBERMAN_SAVEDGAME_HPP


#include <string>

namespace cge {
	namespace Saves {
		class SavedGame {
		public:
			explicit SavedGame(int slot);
			SavedGame(const SavedGame& sg);
			SavedGame& operator=(const SavedGame& rhs);
			~SavedGame();

			int getSlot() const;
			void setSlot(int _slot);

			bool isAvailable() const;
			void setAvailable(bool _available);

			const std::string &getFileName() const;
			void setFileName(const std::string &_fileName);

			const std::string &getCreationTime() const;
			void setCreationTime(const std::string &_creationTime);

		private:
			int			_slot;
			bool		_available;
			std::string	_fileName;
			std::string	_creationTime;
		};
	}
};


#endif //BOMBERMAN_SAVEDGAME_HPP
