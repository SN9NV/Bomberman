//
// Created by Robert Jones on 2017/08/16.
//

#include "TextureAtlas.hpp"
namespace cge {
    TextureAtlas::TextureAtlas(GLuint textureID, int row) : Texture(textureID), _row(row), _stages(row * row){}

	int TextureAtlas::getRow() const {
		return _row;
	}

	int TextureAtlas::getStages() const {
		return _stages;
	}
}