/*
 * Created by Raunak Mukhia on 9/4/18.
 * “The beginning is always NOW.”
 */


#include <cstring>
#include "engine/OpenGLWrapper.h"
#include "engine/Game.h"
#include "engine/SceneManager.h"
#include "game/scenes/GameScreen.h"

Game *initGameContext() {
    Game * gameContext = Game::instance();
    strcpy(gameContext->gameName, "Wormhole Dash");
    gameContext->fullScreen = false;
    gameContext->sizeChanged = true;
    gameContext->wireframe = false;
    gameContext->depthTest = true;
    gameContext->blending = true;
    gameContext->lighting = true;

    //gameContext->Ztranslate = -20.0;

    gameContext->screenHeight = 700.0;
    gameContext->screenWidth = 900.0;

    gameContext->timeStep = 1.0/60.0;

    gameContext->debug = false;

    strcpy(gameContext->objpath, "../resources/");

    return gameContext;
}

void initialize() {
    SceneManager *sceneManager = SceneManager::instance();
    Scene * startScene = new GameScreen();
    startScene->create();
    sceneManager->getScenes()->push_back(startScene);
    sceneManager->setActiveScene(sceneManager->getScenes()->size() - 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char **argv)
{
    // Create game context
    Game *gameContext = initGameContext();

    // Intialize OpenGL
    initializeOpenGL(argc, argv, &initialize);
}



