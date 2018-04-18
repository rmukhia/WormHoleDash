//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_SPEEDBUGGY_H
#define WORMHOLEDASH_SPEEDBUGGY_H


#include <btBulletDynamicsCommon.h>
#include "../../glheaders.h"
#include "../../engine/Actor.h"

class SpeedBuggy: public Actor {
    btRigidBody *rigidBody;
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;
    void createBody(btDiscreteDynamicsWorld *world);

    btRigidBody *getRigidBody() const;
};


#endif //WORMHOLEDASH_SPEEDBUGGY_H
