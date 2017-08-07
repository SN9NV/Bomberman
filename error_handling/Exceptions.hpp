#ifndef NEW_EXCEPTIONS_HPP
#define NEW_EXCEPTIONS_HPP

#include <string>
#include <exception>

namespace cge {
	class BombermanException : public std::exception {
	public:
		explicit BombermanException(const char* message): _message(message) {}
		explicit BombermanException(const std::string& message): _message(message) {}
		virtual ~BombermanException() throw () {}
		virtual const char* what() const throw () { return _message.c_str(); }

	protected:
		std::string _message;
	};

	class SDL_FatalError : public BombermanException {
	public:
		using BombermanException::BombermanException;
		using BombermanException::what;
	};
}

#endif //NEW_EXCEPTIONS_HPP
