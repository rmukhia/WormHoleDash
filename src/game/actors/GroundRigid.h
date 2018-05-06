//
// Created by Raunak Mukhia on 20/4/18.
//

#ifndef WORMHOLEDASH_GROUNDRIGID_H
#define WORMHOLEDASH_GROUNDRIGID_H


#include "../../engine/Actor.h"
#include <btBulletDynamicsCommon.h>

class GroundRigid: public Actor {
    btRigidBody *createGroundRigidBodyFromShape(btCollisionShape *groundShape);
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;
    void createBody(btDiscreteDynamicsWorld *world);

};


#endif //WORMHOLEDASH_GROUNDRIGID_H
