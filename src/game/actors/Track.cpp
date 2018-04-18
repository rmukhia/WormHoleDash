//
// Created by Raunak Mukhia on 17/4/18.
//

#include <iostream>
#include "Track.h"
#include "../../engine/Game.h"

void Track::create() {

}

void Track::createBody(btDiscreteDynamicsWorld * world) {
    btTriangleMesh *mTriMesh =  new btTriangleMesh();

    int i = 0;
    while(i < num_vertices * 3) {
        btVector3 v0(vertices[i++], vertices[i++], vertices[i++]);
        btVector3 v1(vertices[i++], vertices[i++], vertices[i++]);
        btVector3 v2(vertices[i++], vertices[i++], vertices[i++]);
        mTriMesh->addTriangle(v0, v1, v2);
    }

    btCollisionShape *mTriMeshShape = new btBvhTriangleMeshShape(mTriMesh, true);
    btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0, 0,0)));

    btScalar mass = 0;
    btVector3 fallInertia(0, 0, 0);


    mTriMeshShape->calculateLocalInertia(mass, fallInertia);

    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(mass, ms, mTriMeshShape, fallInertia);
    rigidBody = new btRigidBody(groundRigidBodyCI);
    world->addRigidBody(rigidBody);

}

void Track::draw() {
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    GLfloat m[16];
    trans.getOpenGLMatrix(m);
    glPushMatrix();
    glMultMatrixf(m);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColor4f(0.2,0.2,0.2, 1.0);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void Track::update() {

}

void Track::destroy() {

}

void Track::act(Command *pCommand) {

}



