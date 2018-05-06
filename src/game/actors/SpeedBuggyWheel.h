//
// Created by Raunak Mukhia on 6/5/18.
//

#ifndef WORMHOLEDASH_SPEEDBUGGYWHEELS_H
#define WORMHOLEDASH_SPEEDBUGGYWHEELS_H


#include "../../engine/Actor.h"
#include "../../engine/getBMP.h"

class SpeedBuggyWheel: public Actor {
    imageFile *texture;
    GLuint textureId;
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    void drawWheel(GLfloat *modelView);

};


#endif //WORMHOLEDASH_SPEEDBUGGYWHEELS_H
