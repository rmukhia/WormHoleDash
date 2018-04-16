//
// Created by Raunak Mukhia on 12/4/18.
//

#include "Camera.h"
#include "Game.h"

void Camera::project() {
    Game *game = Game::instance();
    if (game->sizeChanged) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fovy, game->getAspectRatio(), zNear, zFar);
        changed = false;
        game->sizeChanged = false;
        glMatrixMode(GL_MODELVIEW);
    }
}

void Camera::setLookAt(GLfloat *e, GLfloat *c, GLfloat *u) {
    memcpy(eye, e, sizeof(GLfloat) * 3);
    memcpy(center, c, sizeof(GLfloat) * 3);
    memcpy(up, u, sizeof(GLfloat) * 3);
    hasLookAt = true;
}

void Camera::lookAt() {
    if(hasLookAt) {
        gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    }
}
