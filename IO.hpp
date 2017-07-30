#ifndef NEW_IO_HPP
#define NEW_IO_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace IO {
	std::string	readFileToString(const std::string &filename);
	bool		readFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer);
}


#endif //NEW_IO_HPP
