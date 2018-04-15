//
// Created by Raunak Mukhia on 10/4/18.
//

#include <iostream>
#include "OpenGLWrapper.h"
#include "Game.h"
#include "SceneManager.h"


void setup(void (*callback)(void)) {
    Game *game = Game::instance();
    game->screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    game->screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
    callback();
}

void initializeOpenGL(int argc, char **argv, void (*callback)(void)) {
    Game *game = Game::instance();
    SceneManager *sceneManager = SceneManager::instance();
    glutInit(&argc, argv);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(game->screenWidth, game->screenHeight);
    glutInitWindowPosition(50, 50);

    glutCreateWindow(game->gameName);

    if(game->fullScreen) {
        glutFullScreen();
    }

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();
    setup(callback);
    glutMainLoop();
}

void drawScene(void) {
    SceneManager *sceneManager = SceneManager::instance();
    Scene * scene = sceneManager->getActiveScene();

    if (scene) {
        scene->update();
        scene->draw();
    }
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    // Update the screen size
    Game *game = Game::instance();
    game->screenWidth = w;
    game->screenHeight = h;
    game->sizeChanged = true;
}

void keyInput(unsigned char key, int x, int y) {
    SceneManager *sceneManager = SceneManager::instance();
    Scene * scene = sceneManager->getActiveScene();

    std::cout << key<< std::endl;

    if (scene) {
        scene->keyInput(key, x, y);
    }
}

void redraw() {
    glutPostRedisplay();
}