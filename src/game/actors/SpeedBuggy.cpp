//
// Created by Raunak Mukhia on 12/4/18.
//

#include <iostream>
#include "SpeedBuggy.h"
#include "../CommandCodes.h"

void SpeedBuggy::create() {
    texture = getBMP("../resources/models/car.bmp");
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

#if 0
void SpeedBuggy::createBody(btDiscreteDynamicsWorld * world) {
    btTriangleMesh *mTriMesh =  new btTriangleMesh();
    int i = 0;

    btConvexHullShape *impact_shape = new btConvexHullShape();
    while(i < num_vertices * 3) {
        btVector3 v0(vertices[i++], vertices[i++], vertices[i++]);
        impact_shape->addPoint(v0);
    }

    btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0, 0.2, 2)));
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
#else
void SpeedBuggy::createBody(btDiscreteDynamicsWorld * world) {
    {
        //the dimensions for the boxShape are half extents, so 0,5 equals to
        btVector3 halfExtends(1.7, btScalar(0.5), 3.5);

        //The btBoxShape is centered at the origin
        btCollisionShape* chassisShape = new btBoxShape(halfExtends);

        //Stores on an array for reusing
        collisionShapes.push_back(chassisShape);

        //A compound shape is used so we can easily shift the center of gravity of our vehicle to its bottom
        //This is needed to make our vehicle more stable
        btCompoundShape* compound = new btCompoundShape();

        collisionShapes.push_back(compound);

        btTransform localTransform;
        localTransform.setIdentity();
        localTransform.setOrigin(btVector3(0, 1, 0));

        //The center of gravity of the compound shape is the origin. When we add a rigidbody to the compound shape
        //it's center of gravity does not change. This way we can add the chassis rigidbody one unit above our center of gravity
        //keeping it under our chassis, and not in the middle of it
        compound->addChildShape(localTransform, chassisShape);

        //Creates a rigid body
        btRigidBody* chassisRigidBody = this->createChassisRigidBodyFromShape(compound);

        //Adds the vehicle chassis to the world
        world->addRigidBody(chassisRigidBody);

        btVehicleRaycaster* vehicleRayCaster = new btDefaultVehicleRaycaster(world);

        btRaycastVehicle::btVehicleTuning tuning;

        //Creates a new instance of the raycast vehicle
        this->vehicle = new btRaycastVehicle(tuning, chassisRigidBody, vehicleRayCaster);

        //Never deactivate the vehicle
        chassisRigidBody->setActivationState(DISABLE_DEACTIVATION);

        //Adds the vehicle to the world
        world->addVehicle(this->vehicle);

        //Adds the wheels to the vehicle
        this->addWheels(&halfExtends, this->vehicle, tuning);

        rigidBody = chassisRigidBody;

        btTransform tr;
        tr.setIdentity();
        btQuaternion quat;
        quat.setEuler(1.5,0.1,0.0);
        tr.setRotation(quat);
        rigidBody->setCenterOfMassTransform(tr);
        rigidBody->translate(btVector3(+10.0, 0.0, 0.0));
    }

}
btRigidBody* SpeedBuggy::createChassisRigidBodyFromShape(btCollisionShape* chassisShape)
{
    btTransform chassisTransform;
    chassisTransform.setIdentity();
    chassisTransform.setOrigin(btVector3(0, 1, 0));

    {
        //chassis mass
        btScalar mass(1200);

        //since it is dynamic, we calculate its local inertia
        btVector3 localInertia(0, 0, 0);
        chassisShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(chassisTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, groundMotionState, chassisShape, localInertia);

        return new btRigidBody(rbInfo);
    }
}

btRigidBody* SpeedBuggy::createGroundRigidBodyFromShape(btCollisionShape* groundShape)
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

void SpeedBuggy::addWheels(
        btVector3* halfExtents,
        btRaycastVehicle* vehicle,
        btRaycastVehicle::btVehicleTuning tuning)
{
    //The direction of the raycast, the btRaycastVehicle uses raycasts instead of simiulating the wheels with rigid bodies
    btVector3 wheelDirectionCS0(0, -1, 0);

    //The axis which the wheel rotates arround
    btVector3 wheelAxleCS(-1, 0, 0);

    btScalar suspensionRestLength(0.7);

    btScalar wheelWidth(0.4);

    btScalar wheelRadius(0.5);

    //The height where the wheels are connected to the chassis
    btScalar connectionHeight(1.2);

    //All the wheel configuration assumes the vehicle is centered at the origin and a right handed coordinate system is used
    btVector3 wheelConnectionPoint(halfExtents->x() - wheelRadius, connectionHeight, halfExtents->z() - wheelWidth);

    //Adds the front wheels
    vehicle->addWheel(wheelConnectionPoint, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);

    vehicle->addWheel(wheelConnectionPoint * btVector3(-1, 1, 1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, true);

    //Adds the rear wheels
    vehicle->addWheel(wheelConnectionPoint* btVector3(1, 1, -1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);

    vehicle->addWheel(wheelConnectionPoint * btVector3(-1, 1, -1), wheelDirectionCS0, wheelAxleCS, suspensionRestLength, wheelRadius, tuning, false);

    //Configures each wheel of our vehicle, setting its friction, damping compression, etc.
    //For more details on what each parameter does, refer to the docs
    for (int i = 0; i < vehicle->getNumWheels(); i++)
    {
        btWheelInfo& wheel = vehicle->getWheelInfo(i);
        //wheel.m_suspensionStiffness = 50;
        wheel.m_suspensionStiffness = 25;
        //wheel.m_wheelsDampingCompression = btScalar(0.3) * 2 * btSqrt(wheel.m_suspensionStiffness);//btScalar(0.8);
        wheel.m_wheelsDampingCompression = btScalar(1) * 2 * btSqrt(wheel.m_suspensionStiffness);//btScalar(0.8);
        //wheel.m_wheelsDampingRelaxation = btScalar(0.5) * 2 * btSqrt(wheel.m_suspensionStiffness);//1;
        wheel.m_wheelsDampingRelaxation = btScalar(1.2) * 2 * btSqrt(wheel.m_suspensionStiffness);//1;
        //Larger friction slips will result in better handling
        //wheel.m_frictionSlip = btScalar(1.2);
        wheel.m_frictionSlip = btScalar(3.0);
        //wheel.m_rollInfluence = 1;
        wheel.m_rollInfluence = 1;
    }
}
#endif

void SpeedBuggy::updateMaterial() {
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat matDiff[] = { 0.6, 0.6, 0,6, 1.0 };
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

void SpeedBuggy::draw() {
    btTransform trans;
    GLfloat m[16];
    rigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);

    // Body
    glPushMatrix();
    glMultMatrixf(m);
    glEnable(GL_COLOR_MATERIAL);

    glTranslatef(0, 1.0, -1.0);

    // fill data
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    // Enable texture
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2,GL_FLOAT,0, uvs);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // color property
    glColor4f(1.0, 1.0, 1.0, 1.0);
    updateMaterial();


    // draw
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    // textures disable
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // lights
    GLfloat spotlight_direction[] = {0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, spotlight_direction);
    float lightPos1[] = { 0.0, 1.0 , 10.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();

    // Wheels, front left, front right, back left, back right
    for(int i = 0; i < 4; i++) {
        vehicle->getWheelTransformWS(i).getOpenGLMatrix(m);
        speedBuggyWheel->drawWheel(m);
    }


}

void SpeedBuggy::update() {


}

void SpeedBuggy::destroy() {

}

void SpeedBuggy::act(Command *pCommand) {

    switch(pCommand->getOpcode()) {
        case MOVE_LEFT:
            std::cout<< "Move Left";
            this->vehicle->setSteeringValue(btScalar(0.8), 0);
            this->vehicle->setSteeringValue(btScalar(0.8), 1);
            break;
        case MOVE_RIGHT:
            std::cout<< "Move Right";
            this->vehicle->setSteeringValue(btScalar(-0.8), 0);
            this->vehicle->setSteeringValue(btScalar(-0.8), 1);
            break;
        case MOVE_ACCELERATE:
            std::cout<< "Move Accelerate";
            this->vehicle->applyEngineForce(5000, 2);
            this->vehicle->applyEngineForce(5000, 3);
            break;
        case MOVE_BREAK:
            std::cout <<"Move Break";
            this->vehicle->applyEngineForce(-3000, 2);
            this->vehicle->applyEngineForce(-3000, 3);
            break;
        case RELEASE_ENGINE:
            std::cout <<"Release engine";
            this->vehicle->applyEngineForce(0, 2);
            this->vehicle->applyEngineForce(0, 3);

            //Default braking force, always added otherwise there is no friction on the wheels
            this->vehicle->setBrake(10, 2);
            this->vehicle->setBrake(10, 3);

            break;
        case RELEASE_STEERING:
            std::cout <<"Release steering";
            this->vehicle->setSteeringValue(0, 0);
            this->vehicle->setSteeringValue(0, 1);
            break;
    }

}

btRigidBody *SpeedBuggy::getRigidBody() const {
    return rigidBody;
}

void SpeedBuggy::setSpeedBuggyWheels(SpeedBuggyWheel *speedBuggyWheels) {
    SpeedBuggy::speedBuggyWheel = speedBuggyWheels;
}

