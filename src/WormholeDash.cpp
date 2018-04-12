/*
 * Created by Raunak Mukhia on 9/4/18.
 * “The beginning is always NOW.”
 */


#include <cstring>
#include "engine/OpenGLWrapper.h"
#include "engine/Game.h"

Game *initGameContext() {
    Game * gameContext = Game::instance();
    strcpy(gameContext->gameName, "Wormhole Dash");
    gameContext->fullScreen = false;
    return gameContext;
}

int main(int argc, char **argv)
{
    // Create game context
    Game *gameContext = initGameContext();

    // Intialize OpenGL
    initializeOpenGL(argc, argv);

}



