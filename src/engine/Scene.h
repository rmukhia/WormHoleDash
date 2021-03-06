//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_SCENECONTEXT_H
#define CGPROJECT_SCENECONTEXT_H

#include "../glheaders.h"
#include <vector>
#include <list>
#include "Camera.h"
#include "Actor.h"

class Scene {
private:
    Camera *camera;
    std::vector<Actor*> actors;
    enum state { STOPPED, PAUSED, RUNNING};
    std::list<Command *> commandQueue;
    std::list<Command *> sceneCommandQueue;
    bool loaded;
public:
    bool running = false;
    virtual void create();

    virtual void draw(long double deltaTime);

    virtual void update(long double deltaTime);

    virtual void paused();

    virtual void destroy();

    virtual void keyInput(unsigned char key, int x, int y);

    virtual void keyUp(unsigned char key, int x, int y);

    std::vector<Actor *>  * getActors();

    void setActors(const std::vector<Actor *> &actors);

    Camera *getCamera() const;

    void setCamera(Camera *cam);

    void addCommand(Command *command);

    std::list<Command *>  *getCommandQueue();
    std::list<Command *>  *getSceneCommandQueue();

    bool isLoaded() const;

    void setLoaded(bool loaded);

};


#endif //CGPROJECT_SCENECONTEXT_H
