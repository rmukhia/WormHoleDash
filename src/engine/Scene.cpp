//
// Created by Raunak Mukhia on 11/4/18.
//

#include <GL/freeglut.h>
#include "Scene.h"

void Scene::create() {
    for(auto obj: objects) {
        obj->create();
    }
}

// Try to implement batch later on
// Explicitly pass the camera, although it may already be
// a member of the same class.
void Scene::draw() {
    glMatrixMode(GL_PROJECTION);
    getCamera()->project();
    glMatrixMode(GL_MODELVIEW);
    for(auto obj: objects) {
        obj->draw();
    }
    glutSwapBuffers();
}

void Scene::update() {
    for(auto obj: objects) {
        obj->update();
    }
}

void Scene::paused() {

}

void Scene::destroy() {
    for(auto obj: objects) {
        obj->destroy();
    }
}

Camera *Scene::getCamera() const {
    return camera;
}

void Scene::setCamera(Camera *cam) {
    Scene::camera = camera;
}
