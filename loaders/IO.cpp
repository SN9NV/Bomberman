#include "IO.hpp"
#include "picoPNG.hpp"

std::string	cge::IO::readFileToString(const std::string &filename) {
	std::ifstream	fileStream(filename, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not open file: " << filename << '\n';
		exit(1);
	}

	return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

bool		cge::IO::readFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer) {
	std::ifstream	fileStream(filePath, std::ios::binary);

	if (!fileStream.is_open()) {
		std::cerr << "Could not open file: " << filePath << '\n';
		return true;
	}

	buffer = std::vector<unsigned char>(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());

	return false;
}