//
// Created by Raunak Mukhia on 11/4/18.
//

#include "GameContext.h"

GameContext* GameContext::_instance = 0;
GameContext* GameContext::instance() {
    if (!_instance) {
        _instance = new GameContext();
    }
    return _instance;
}
