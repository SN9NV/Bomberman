//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_TEXTRENDERER_HPP
#define BOMBERMAN_TEXTRENDERER_HPP

#include "../error_handling/Exceptions.hpp"


#include <iostream>
#include <string.h>
#include <fontstash.h>

#include <GLFW/glfw3.h>
#include <glfontstash.h>

namespace cge {
	class TextRenderer {
	public:
		TextRenderer();
		~TextRenderer();

		void	DrawText(std::string text);
	private:
		FONScontext*	_context;
		int				_fontNormal;
		unsigned int	_blackColor;

		void			dash(float dx, float dy);
	};
};


#endif //BOMBERMAN_TEXTRENDERER_HPP
