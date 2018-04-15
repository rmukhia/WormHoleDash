//
// Created by Raunak Mukhia on 12/4/18.
//

#include <iostream>
#include "StartBackground.h"

void StartBackground::draw() {
    std::cout << "draw" <<std::endl;
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glutWireSphere(2.0, 12,12);
}

void StartBackground::update() {
    std::cout << "update" <<std::endl;
}

void StartBackground::destroy() {
    std::cout << "destroy" <<std::endl;
}

void StartBackground::create() {
    std::cout << "create" <<std::endl;
}

void StartBackground::act(Command *pCommand) {
    std::cout << "act" << std::endl;
}
