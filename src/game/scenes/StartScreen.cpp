//
// Created by Raunak Mukhia on 12/4/18.
//

#include "StartScreen.h"
#include "../../engine/Game.h"

void StartScreen::create() {
    Game * game = Game::instance();
    Scene::create();
    Camera * camera = new Camera(60.0, game->getAspectRatio(), 10.0, 100.0);
    this->setCamera(camera);
}

void StartScreen::draw() { Scene::draw(); }

void StartScreen::update() { Scene::update(); }

void StartScreen::paused() { Scene::paused(); }

void StartScreen::destroy() { Scene::destroy(); }
