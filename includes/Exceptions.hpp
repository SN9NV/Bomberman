#pragma once

#include <string>
#include <stdexcept>

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
