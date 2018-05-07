//
// Created by Raunak Mukhia on 10/4/18.
//

#include <iostream>
#include <sys/time.h>
#include "OpenGLWrapper.h"
#include "Game.h"
#include "SceneManager.h"

static long double previousFrameTime = -1.0;
static long double timeAccumulator = 0.0;

void setup(void (*callback)()) {
    Game *game = Game::instance();
    game->screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    game->screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
    if(game->depthTest)
        glEnable(GL_DEPTH_TEST);
    if(game->blending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    if(game->lighting) {
        glEnable(GL_LIGHTING);
    }

    callback();
}

void initializeOpenGL(int argc, char **argv, void (*callback)()) {
    Game *game = Game::instance();
    SceneManager *sceneManager = SceneManager::instance();
    glutInit(&argc, argv);
    glutInitContextVersion(4, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    if (game->depthTest)
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    else
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(game->screenWidth, game->screenHeight);
    glutInitWindowPosition(50, 50);

    glutCreateWindow(game->gameName);

    if(game->fullScreen) {
        glutFullScreen();
    }

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutKeyboardUpFunc(keyUp);

    glewExperimental = GL_TRUE;
    glewInit();
    setup(callback);
    glutMainLoop();
}

long double getCurrentSystemTime() {
    timeval time{};
    gettimeofday(&time, nullptr);
    long t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return t/1000.0;
}

long double timestepUpdate() {
    int num_steps = 0;
    Game *game = Game::instance();
    float timeStep = game->timeStep;

    long double currentFrameTime = getCurrentSystemTime();

    if (previousFrameTime <= 0.0) {
        previousFrameTime  = currentFrameTime;
    }

    long double deltaTime  = currentFrameTime - previousFrameTime;

    previousFrameTime = currentFrameTime;

    timeAccumulator += deltaTime;

    while (timeAccumulator >= timeStep) {
        num_steps++;
        timeAccumulator -= timeStep;
    }

    return deltaTime;
}

void drawScene() {
    SceneManager *sceneManager = SceneManager::instance();
    Scene * scene = sceneManager->getActiveScene();

    if (scene && scene->isLoaded()) {
        long double deltaTime = timestepUpdate();
        scene->update(deltaTime);
        scene->draw(deltaTime);
    }
    redraw();
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

    if (scene)
        scene->keyInput(key, x, y);
}

void keyUp(unsigned char key,int x, int y)
{
    SceneManager *sceneManager = SceneManager::instance();
    Scene * scene = sceneManager->getActiveScene();

    if(scene)
        scene->keyUp(key, x, y);
}

void redraw() {
    glutPostRedisplay();
}