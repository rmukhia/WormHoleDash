//
// Created by Raunak Mukhia on 10/4/18.
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGLWrapper.h"
#include "engine/GameContext.h"

void initializeOpenGL(int argc, char **argv) {
    GameContext *gameContext = GameContext::instance();
    glutInit(&argc, argv);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(gameContext->gameName);

    if(gameContext->fullScreen) {
        glutFullScreen();
    }

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    glutMainLoop();
}

void drawScene(void) {
}

void resize(int w, int h) {
    // Update the screen size
    GameContext *gameContext = GameContext::instance();
    gameContext->screenWidth = w;
    gameContext->screenHeight = h;
}

void keyInput(unsigned char key, int x, int y) {
}