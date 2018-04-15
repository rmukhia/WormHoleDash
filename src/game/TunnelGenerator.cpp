//
// Created by Raunak Mukhia on 15/4/18.
//

#include "TunnelGenerator.h"

std::list<Tunnel *> *TunnelGenerator::getTunnels(int num, GLfloat startX, GLfloat startY, GLfloat startZ) {
    std::list<Tunnel *> *tunnelList =  new std::list<Tunnel *>();
    GLfloat x = startX, y = startY, z = startZ;

    srand (time(NULL));
    for(int i = 0; i < num ; i++) {
        // length range is from 5 to 15
        GLfloat length = (GLfloat)(rand() % 500 + 500)/100.0;
        // length range is from 5 to 15
        GLfloat thetaHorizontal = (GLfloat)(rand() % 1000)/100.0;
        // length range is from 5 to 15
        GLfloat thetaVertical = (GLfloat)(rand() % 1000)/100.0;


        Tunnel * tunnel = new Tunnel(thetaHorizontal, thetaVertical, length);
        tunnel->setStartVertices(x, y, z);
        tunnel->create();
        tunnel->getEndVertices(&x, &y, &z);
        tunnelList->push_back(tunnel);
        tunnel = nullptr;
    }

    return tunnelList;
}
