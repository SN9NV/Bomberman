#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <string>

#include "picoPNG.hpp"
#include "IO.hpp"
#include "Structs.hpp"

namespace ImageLoader {
	GLTexture	loadPNG(const std::string &filePath);
}

#endif // IMAGELOADER_HPP
