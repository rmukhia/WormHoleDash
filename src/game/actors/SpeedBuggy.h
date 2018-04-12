//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_SPEEDBUGGY_H
#define WORMHOLEDASH_SPEEDBUGGY_H


#include "../../engine/Actor.h"

class SpeedBuggy: public Actor {

public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;
};


#endif //WORMHOLEDASH_SPEEDBUGGY_H
