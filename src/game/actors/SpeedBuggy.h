//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_SPEEDBUGGY_H
#define WORMHOLEDASH_SPEEDBUGGY_H


#include <btBulletDynamicsCommon.h>
#include "../../glheaders.h"
#include "../../engine/Actor.h"
#include "SpeedBuggyWheel.h"

class SpeedBuggy: public Actor {
    btRigidBody *rigidBody;
    btRaycastVehicle* vehicle;
    imageFile *texture;
    GLuint textureId;

    SpeedBuggyWheel *speedBuggyWheel; // Left front, Right front, Left back, Right back

    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    btRigidBody* createGroundRigidBodyFromShape(btCollisionShape* groundShape);

    btRigidBody* createChassisRigidBodyFromShape(btCollisionShape* chassisShape);

    void addWheels(
            btVector3* halfExtents,
            btRaycastVehicle* vehicle,
            btRaycastVehicle::btVehicleTuning tuning);

    void updateMaterial();
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;
    void createBody(btDiscreteDynamicsWorld *world);

    btRigidBody *getRigidBody() const;

    void setSpeedBuggyWheels(SpeedBuggyWheel *speedBuggyWheels);

};


#endif //WORMHOLEDASH_SPEEDBUGGY_H
