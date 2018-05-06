//
// Created by Raunak Mukhia on 20/4/18.
//

#include "GroundRigid.h"

void GroundRigid::createBody(btDiscreteDynamicsWorld * world) {
        //Creates the ground shape
        btCollisionShape* groundShape = new btBoxShape(btVector3(100, 1, 100));

        //Stores on an array for reusing

        //Creates the ground rigidbody
        btRigidBody* groundRigidBody = this->createGroundRigidBodyFromShape(groundShape);

        //Adds it to the world
        world->addRigidBody(groundRigidBody);
}
btRigidBody* GroundRigid::createGroundRigidBodyFromShape(btCollisionShape* groundShape)
{
        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(0, -1, 0));

        {
                //The ground is not dynamic, we set its mass to 0
                btScalar mass(0);

                //No need for calculating the inertia on a static object
                btVector3 localInertia(0, 0, 0);

                //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* groundMotionState = new btDefaultMotionState(groundTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, groundMotionState, groundShape, localInertia);

                return new btRigidBody(rbInfo);
        }
}

void GroundRigid::create() {

}

void GroundRigid::draw() {

}

void GroundRigid::update() {

}

void GroundRigid::destroy() {

}

void GroundRigid::act(Command *pCommand) {

}
