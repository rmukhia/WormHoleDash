//
// Created by Raunak Mukhia on 12/4/18.
//

#include <iostream>
#include "SpeedBuggy.h"
#include "../CommandCodes.h"

void SpeedBuggy::create() {
    rp3d::Vector3 initPosition(0.0, 0.0, 0.0);
    rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(initPosition, initOrientation);
}

void SpeedBuggy::draw() {
    std::cout << "draw" <<std::endl;
    glPushMatrix();
    glTranslatef(getPosX(), getPosY(), getPosZ());
    glColor4f(1.0, 0.0, 1.0, 1.0);
    glutWireCube(1.0);
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

