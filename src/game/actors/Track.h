//
// Created by Raunak Mukhia on 17/4/18.
//

#ifndef WORMHOLEDASH_TRACK_H
#define WORMHOLEDASH_TRACK_H


#include <btBulletDynamicsCommon.h>
#include "../../glheaders.h"
#include "../../engine/Actor.h"

class Track: public Actor {
    btRigidBody *rigidBody;
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    void createBody(btDiscreteDynamicsWorld *world);

    void updateMaterial();
};


#endif //WORMHOLEDASH_TRACK_H
