#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <string>

#include "picoPNG.hpp"
#include "IO.hpp"
#include "Texture.hpp"

namespace ImageLoader {
	Texture	loadPNG(const std::string &filePath);
}

#endif // IMAGELOADER_HPP
