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

void Track::updateMaterial() {
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmb[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat matDiff[] = { 0.3, 0.3, 0,3, 1.0 };
    GLfloat matShine[] = { 50.0 };

    // emission
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

    // specular
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);

    // shine
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    // ambient
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);


    // diffuse
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
}

void Track::draw() {
    btTransform trans;
    rigidBody->getMotionState()->getWorldTransform(trans);
    GLfloat m[16];
    trans.getOpenGLMatrix(m);
    glPushMatrix();
    glMultMatrixf(m);
    glEnable(GL_COLOR_MATERIAL);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glColor4f(1.0,1.0,1.0, 0.5);
    updateMaterial();
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

void Track::update() {

}

void Track::destroy() {

}

void Track::act(Command *pCommand) {

}



