#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace IO {
	bool	readFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer);
}

#endif // IO_HPP
