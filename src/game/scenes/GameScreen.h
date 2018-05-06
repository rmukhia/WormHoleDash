//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_STARTSCREEN_H
#define WORMHOLEDASH_STARTSCREEN_H

#include "../../glheaders.h"
#include "../../engine/Scene.h"
#include "../actors/SpeedBuggy.h"
#include "../actors/TextureBox.h"
#include <btBulletDynamicsCommon.h>

class GameScreen : public Scene {
private:
    SpeedBuggy *buggy;
    TextureBox *textureBox;

    /* Bullet physics engine stuffs */
    btDbvtBroadphase *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    void setupLight();
public:
    void create() override;

    void draw(long double deltaTime) override;

    void update(long double deltaTime) override;

    void paused() override;

    void destroy() override;

    void preDraw();

    void keyInput(unsigned char key, int x, int y) override;

    void keyUp(unsigned char key, int x, int y) override;

    void loadObj();

    void loadTextures();

    virtual ~GameScreen();

    void debugDraw();
};

#endif // WORMHOLEDASH_STARTSCREEN_H
