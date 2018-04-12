//
// Created by Raunak Mukhia on 11/4/18.
//

#include "Game.h"

Game* Game::_instance = 0;
Game* Game::instance() {
    if (!_instance) {
        _instance = new Game();
    }
    return _instance;
}
