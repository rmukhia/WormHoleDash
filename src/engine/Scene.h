//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_SCENECONTEXT_H
#define CGPROJECT_SCENECONTEXT_H



#include "GameObject.h"
#include <vector>

class Scene {
    std::vector<GameObject> objects;
    enum state { STOPPED, PAUSED, RUNNING};

};


#endif //CGPROJECT_SCENECONTEXT_H
