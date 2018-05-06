//
// Created by Raunak Mukhia on 6/5/18.
//

#ifndef WORMHOLEDASH_TEXTUREBOX_H
#define WORMHOLEDASH_TEXTUREBOX_H


#include "../../engine/Actor.h"
#include "../../engine/getBMP.h"

class TextureBox: public Actor {
    GLuint textures[6];
    imageFile *imageCube[6];
    GLfloat buggyTransform[16];
    void updateMaterial();
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    void loadTextures();

    GLfloat *getBuggyTransform();
};


#endif //WORMHOLEDASH_TEXTUREBOX_H
