//
// Created by Raunak Mukhia on 12/4/18.
//

#include <iostream>
#include "SpeedBuggy.h"
#include "../CommandCodes.h"

void SpeedBuggy::create() {
}

void SpeedBuggy::createBody(btDiscreteDynamicsWorld * world) {
    btTriangleMesh *mTriMesh =  new btTriangleMesh();

    int i = 0;

    btConvexHullShape *impact_shape = new btConvexHullShape();
    while(i < num_vertices * 3) {
        btVector3 v0(vertices[i++], vertices[i++], vertices[i++]);
        impact_shape->addPoint(v0);
    }

    btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0, 3, 2)));
    impact_shape->setLocalScaling(btVector3(1.,1.,1.));
    impact_shape->setMargin(0.04f);

    btScalar mass = 0.01;
    btVector3 fallInertia(0, 0, 0);


    impact_shape->calculateLocalInertia(mass, fallInertia);

    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(mass, ms, impact_shape, fallInertia);
    rigidBody = new btRigidBody(groundRigidBodyCI);
    world->addRigidBody(rigidBody);
}

void SpeedBuggy::draw() {
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    GLfloat m[16];
    trans.getOpenGLMatrix(m);
    glPushMatrix();
    glMultMatrixf(m);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void SpeedBuggy::update() {


}

void SpeedBuggy::destroy() {

}

void SpeedBuggy::act(Command *pCommand) {

    switch(pCommand->getOpcode()) {
        case MOVE_LEFT:
            std::cout<< "Move Left";
            setPosX(getPosX() - 2.0);
            break;
        case MOVE_RIGHT:
            std::cout<< "Move Right";
            setPosX(getPosX() + 2.0);
            break;
        case MOVE_ACCELERATE:
            std::cout<< "Move Accelerate";
            break;
        case MOVE_BREAK:
            std::cout <<"Move Break";
            break;
    }

}

btRigidBody *SpeedBuggy::getRigidBody() const {
    return rigidBody;
}


