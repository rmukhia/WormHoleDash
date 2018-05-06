//
// Created by Raunak Mukhia on 11/4/18.
//

#include <cstring>
#include "Game.h"

Game* Game::_instance = nullptr;
Game* Game::instance() {
    if (!_instance) {
        _instance = new Game();
    }
    return _instance;
}

char *Game::getResourcePath(const char *string) {
    return strcat(objpath, string);
}
