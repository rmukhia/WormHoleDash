//
// Created by Raunak Mukhia on 11/4/18.
//

#include "Scene.h"
#include "SceneManager.h"
#include "OpenGLWrapper.h"
#include "Game.h"
#include "../game/CommandCodes.h"

void Scene::create() {
    for(auto obj: actors) {
        obj->create();
    }
}

//TODO: Try to implement batch later on
void Scene::draw(int i) {
    Game *game = Game::instance();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    getCamera()->lookAt();
    glTranslated(0.0, 0.0, game->Ztranslate);

    for(auto cmd: sceneCommandQueue) {
        switch(cmd->getOpcode()) {
            case ROTATE_X:
                game->Xangle += cmd->params;
                break;
            case ROTATE_Y:
                game->Yangle += cmd->params;
                break;
            case ROTATE_Z:
                game->Zangle += cmd->params;
                break;
        }
    }
    sceneCommandQueue.clear();

    glRotatef(game->Xangle, 0, 1, 0);
    glRotatef(game->Yangle, 0, 1, 0);
    glRotatef(game->Zangle, 0, 0, 1);

    if(game->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for(auto obj: actors) {
        obj->draw();
    }
    glutSwapBuffers();
}

void Scene::update(int i) {
    // Try to apply command to all the actors in stage
    // The actor should evaluate the command and take proper steps


    for(auto cmd: commandQueue) {
        if (cmd->getActorId() == GLOBAL_ID) {
            sceneCommandQueue.push_back(cmd);
        }
        for(auto actor: actors) {
            if(cmd->getActorId() == actor->getId())
                actor->act(cmd);
        }
    }

    commandQueue.clear();

    for(auto obj: actors) {
        obj->update();
    }
}

void Scene::paused() {

}

void Scene::destroy() {
    for(auto obj: actors) {
        obj->destroy();
    }
}

Camera *Scene::getCamera() const {
    return camera;
}

void Scene::setCamera(Camera *cam) {
    camera = cam;
}

std::vector<Actor *> * Scene::getActors() {
    return &actors;
}

void Scene::setActors(const std::vector<Actor *> &actors) {
    Scene::actors = actors;
}

std::list<Command *> * Scene::getCommandQueue() {
    return &commandQueue;
}

void Scene::addCommand(Command *command) {
    commandQueue.push_back(command);
}

void Scene::keyInput(unsigned char key, int x, int y) {
    switch(key) {
        case 'x':
            addCommand(new Command(ROTATE_X, GLOBAL_ID, 5.0));
            break;
        case 'X':
            addCommand(new Command(ROTATE_X, GLOBAL_ID, -5.0));
            break;
        case 'y':
            addCommand(new Command(ROTATE_Y, GLOBAL_ID, 5.0));
            break;
        case 'Y':
            addCommand(new Command(ROTATE_Y, GLOBAL_ID, -5.0));
            break;
        case 'z':
            addCommand(new Command(ROTATE_Z, GLOBAL_ID, 5.0));
            break;
        case 'Z':
            addCommand(new Command(ROTATE_Z, GLOBAL_ID, -5.0));
            break;
    }

}
