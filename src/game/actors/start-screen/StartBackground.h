//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_STARTBACKGROUND_H
#define WORMHOLEDASH_STARTBACKGROUND_H


#include "../../../glheaders.h"
#include "../../../engine/Actor.h"

class StartBackground: public Actor {
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

};


#endif //WORMHOLEDASH_STARTBACKGROUND_H
