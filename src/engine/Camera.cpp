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
