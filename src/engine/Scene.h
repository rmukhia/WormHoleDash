//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_SCENECONTEXT_H
#define CGPROJECT_SCENECONTEXT_H

#include <vector>
#include "Camera.h"
#include "Actor.h"

class Scene {
    Camera *camera;
    std::vector<Actor*> objects;
    enum state { STOPPED, PAUSED, RUNNING};
public:
    virtual void create();

    virtual void draw();

    virtual void update();

    virtual void paused();

    virtual void destroy();

    Camera *getCamera() const;

    void setCamera(Camera *camera);
};


#endif //CGPROJECT_SCENECONTEXT_H
