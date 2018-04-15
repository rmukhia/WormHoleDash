//
// Created by Raunak Mukhia on 15/4/18.
//

#ifndef WORMHOLEDASH_TUNNELGENERATOR_H
#define WORMHOLEDASH_TUNNELGENERATOR_H


#include <list>
#include "actors/Tunnel.h"

class TunnelGenerator {
public:
    static std::list<Tunnel *> *getTunnels(int num, GLfloat startX, GLfloat startY, GLfloat startZ);
};


#endif //WORMHOLEDASH_TUNNELGENERATOR_H
