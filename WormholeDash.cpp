/*
 * Created by Raunak Mukhia on 9/4/18.
 * “The beginning is always NOW.”
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstring>
#include "src/OpenGLWrapper.h"
#include "src/engine/GameContext.h"

GameContext *initGameContext() {
    GameContext * gameContext = GameContext::instance();
    strcpy(gameContext->gameName, "Wormhole Dash");
    gameContext->fullScreen = true;
    return gameContext;
}

int main(int argc, char **argv)
{
    // Create game context
    GameContext *gameContext = initGameContext();

    // Intialize OpenGL
    initializeOpenGL(argc, argv);

}



