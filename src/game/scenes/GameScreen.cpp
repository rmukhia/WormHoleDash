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
    BUGGY = 1,
    TUNNEL,
};

void GameScreen::create() {
    Game * game = Game::instance();
    Scene::create();
    auto * camera = new Camera(60.0, game->getAspectRatio(), 1.0, 100.0);
    setCamera(camera);
    rp3d::Vector3 gravity(0.0, -9.81, 0.0);
    world = new rp3d::DynamicsWorld(gravity);

    //StartBackground *background = new StartBackground();
    auto *buggy = new SpeedBuggy();
    buggy->setId(IDS::BUGGY);

    //getActors()->push_back(background);
    getActors()->push_back(buggy);

    speedBuggy = buggy;

    for(auto tunnel:*TunnelGenerator::getTunnels(20, 0, 0, 0)){
        tunnel->setId(IDS::TUNNEL);
        getActors()->push_back(tunnel);
    }

}

GLfloat *getPoint(GLfloat p1[3], GLfloat p2[3], GLfloat z) {
    GLfloat  v[3];
    GLfloat *result = new GLfloat[3];
    v[0] = p2[0] - p1[0];
    v[1] = p2[1] - p1[1];
    v[2] = p2[2] - p1[2];

    GLfloat t = (z - p1[2])/ v[2];
    GLfloat x = p1[0] + v[0] * t;
    GLfloat y = p1[1] + v[1] * t;

    result[0] = x;
    result[1] = y;
    result[2] = z;

    return result;
}

void GameScreen::preDraw() {
    /* Figure out which tunnel the buggy is in */
    for(auto actor: *getActors()) {
        if(actor->getId() != IDS::TUNNEL)
            continue;
        auto *tunnel = (Tunnel *)actor;
        if(speedBuggy->getPosZ() <= tunnel->getStartZ() && speedBuggy->getPosZ() >= tunnel->getEndZ()) {
            currentTunnel = tunnel;
            break;
        }
    }

    GLfloat up[3] = {0, 1, 0};
    GLfloat center[3] = { speedBuggy->getPosX(), speedBuggy->getPosY(), speedBuggy->getPosZ()};
    GLfloat * tStart = currentTunnel->_getStartVertices();
    GLfloat * tEnd = currentTunnel->_getEndVertices();

    GLfloat zPos = speedBuggy->getPosZ()  + 10.0;
    GLfloat *p = getPoint(tStart, tEnd, zPos);

    if (currentTunnel) {}
        getCamera()->setLookAt(p, &tEnd[0], &up[0]);
}

void GameScreen::draw(int nSteps) {
    getCamera()->project();
    preDraw();
    Scene::draw(nSteps);
}

void GameScreen::update(int nSteps) {
    Scene::update(nSteps);

    Game *game = Game::instance();
    for(int i = 0; i < nSteps; i++)
        world->update(game->timeStep);
}

void GameScreen::paused() { Scene::paused(); }

void GameScreen::destroy() { Scene::destroy(); }

void GameScreen::keyInput(unsigned char key, int x, int y) {
    Scene::keyInput(key, x, y);
    switch(key) {
        case 'a':
        case 'A':
            addCommand(new Command(SpeedBuggyCommands::MOVE_LEFT, IDS::BUGGY));
            break;
        case 'w':
        case 'W':
            addCommand(new Command(SpeedBuggyCommands::MOVE_ACCELERATE, IDS::BUGGY));
            break;
        case 'd':
        case 'D':
            addCommand(new Command(SpeedBuggyCommands::MOVE_RIGHT, IDS::BUGGY));
            break;
        case 's':
        case 'S':
            addCommand(new Command(SpeedBuggyCommands::MOVE_BREAK, IDS::BUGGY));
            break;
    }

    redraw();

}

