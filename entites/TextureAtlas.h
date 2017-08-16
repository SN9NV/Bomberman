//
// Created by Robert Jones on 2017/08/16.
//

#ifndef BOMBERMAN_TEXTUREATLAS_H
#define BOMBERMAN_TEXTUREATLAS_H

#include "Texture.hpp"

namespace cge {
    class TextureAtlas : public Texture {
    public:
        TextureAtlas() = default;
        ~TextureAtlas() = default;

        int getRow() const;

        int getStages() const;

        TextureAtlas(GLuint textureID, int row);

    protected:
        int _row;
        int _stages;
    };
}


#endif //BOMBERMAN_TEXTUREATLAS_H
