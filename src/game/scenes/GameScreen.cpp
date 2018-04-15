//
// Created by Raunak Mukhia on 12/4/18.
//

#include "GameScreen.h"
#include "../../engine/Game.h"
#include "../actors/start-screen/StartBackground.h"
#include "../actors/SpeedBuggy.h"
#include "../CommandCodes.h"
#include "../../engine/OpenGLWrapper.h"
#include "../TunnelGenerator.h"

enum IDS {
    buggy = 1,
    wall,
};

void StartScreen::create() {
    Game * game = Game::instance();
    Scene::create();
    Camera * camera = new Camera(20.0, game->getAspectRatio(), 10.0, 100.0);
    setCamera(camera);

    //StartBackground *background = new StartBackground();
    SpeedBuggy *buggy = new SpeedBuggy();
    buggy->setId(IDS::buggy);

    //getActors()->push_back(background);
    getActors()->push_back(buggy);

    for(auto tunnel:*TunnelGenerator::getTunnels(20, 0, 0, 0)){
        getActors()->push_back(tunnel);
    }

}

void StartScreen::preDraw() {
}

void StartScreen::draw() {
    getCamera()->project();
    preDraw();
    Scene::draw();
}

void StartScreen::update() { Scene::update(); }

void StartScreen::paused() { Scene::paused(); }

void StartScreen::destroy() { Scene::destroy(); }

void StartScreen::keyInput(unsigned char key, int x, int y) {
    Scene::keyInput(key, x, y);
    switch(key) {
        case 'a':
        case 'A':
            addCommand(new Command(SpeedBuggyCommands::MOVE_LEFT, IDS::buggy));
            break;
        case 'w':
        case 'W':
            addCommand(new Command(SpeedBuggyCommands::MOVE_ACCELERATE, IDS::buggy));
            break;
        case 'd':
        case 'D':
            addCommand(new Command(SpeedBuggyCommands::MOVE_RIGHT, IDS::buggy));
            break;
        case 's':
        case 'S':
            addCommand(new Command(SpeedBuggyCommands::MOVE_BREAK, IDS::buggy));
            break;
    }

    redraw();

}

