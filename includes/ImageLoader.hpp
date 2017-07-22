#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <GLTexture.hpp>
#include <string>

#include "picoPNG.hpp"
#include "IO.hpp"

namespace ImageLoader {
	GLTexture	loadPNG(const std::string &filePath);
}

#endif // IMAGELOADER_HPP
