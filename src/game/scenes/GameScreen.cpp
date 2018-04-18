//
// Created by Raunak Mukhia on 12/4/18.
//

#include "GameScreen.h"
#include "../../engine/Game.h"
#include "../actors/start-screen/StartBackground.h"
#include "../actors/SpeedBuggy.h"
#include "../CommandCodes.h"
#include "../../engine/OpenGLWrapper.h"
#include "../actors/Track.h"
#include "OBJ_Loader.h"
#include "../../engine/DebugDraw.h"

enum IDS {
    BUGGY = 1,
    TRACK,
};

void GameScreen::loadObj() {
    Game *game = Game::instance();
    objl::Loader Loader;

    bool loadout = Loader.LoadFile(game->getOBJPath("track5_1.obj"));
    if (loadout) {

        for(auto actor: *getActors()) {
            // negative mesh id means it does not exist
            if(actor->getMeshIndex() < 0)
                continue;

            objl::Mesh curMesh = Loader.LoadedMeshes[actor->getMeshIndex()];

            // set vertices
            actor->setNum_vertices(curMesh.Vertices.size());
            GLfloat *vertices = new GLfloat[actor->getNum_vertices() * 3];
            int j =0;
            for(int i = 0; i < actor->getNum_vertices(); i++) {
                vertices[j++] = curMesh.Vertices[i].Position.X;
                vertices[j++] = curMesh.Vertices[i].Position.Y;
                vertices[j++] = curMesh.Vertices[i].Position.Z;
            }

            actor->setVertices(vertices);

            // Load indices
            actor->setNum_indices(curMesh.Indices.size());
            GLint *indices = new GLint[actor->getNum_indices()];

            for(int i = 0; i < actor->getNum_indices(); i++)
                indices[i] =curMesh.Indices[i];

            actor->setIndices(indices);

            vertices = nullptr;
            indices = nullptr;
        }
    }
}

void GameScreen::create() {
    Game * game = Game::instance();
    Scene::create();
    auto * camera = new Camera(60.0, game->getAspectRatio(), 1.0, 100.0);
    setCamera(camera);
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -0.4, 0));

    auto *buggy = new SpeedBuggy;
    buggy->create();
    buggy->setId(IDS::BUGGY);
    buggy->setMeshIndex(0);
    getActors()->push_back(buggy);

    auto *track = new Track;
    track->create();
    track->setId(IDS::TRACK);
    track->setMeshIndex(1);
    getActors()->push_back(track);

    loadObj();

    buggy->createBody(dynamicsWorld);
    track->createBody(dynamicsWorld);

    if (game->debug) {
        dynamicsWorld->setDebugDrawer(new DebugDraw);
        dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    }

}

void GameScreen::preDraw() {
}

void GameScreen::debugDraw() {
    Game *game = Game::instance();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    getCamera()->lookAt();
    glTranslated(0.0, 0.0, game->Ztranslate);

    for(auto cmd: *getSceneCommandQueue()) {
        switch(cmd->getOpcode()) {
            case ROTATE_X:
                game->Xangle += cmd->params;
                break;
            case ROTATE_Y:
                game->Yangle += cmd->params;
                break;
            case ROTATE_Z:
                game->Zangle += cmd->params;
                break;
        }
    }
    getSceneCommandQueue()->clear();

    glRotatef(game->Xangle, 0, 1, 0);
    glRotatef(game->Yangle, 0, 1, 0);
    glRotatef(game->Zangle, 0, 0, 1);

    dynamicsWorld->debugDrawWorld();

    glutSwapBuffers();

}

void GameScreen::draw(long double deltaTime) {
    Game *game = Game::instance();
    getCamera()->project();
    preDraw();
    if (game->debug)
        debugDraw();
    else
        Scene::draw(deltaTime);
}

void GameScreen::update(long double deltaTime) {
    Scene::update(deltaTime);

    Game *game = Game::instance();
    if (dynamicsWorld)
        dynamicsWorld->stepSimulation(deltaTime, 7);
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

GameScreen::~GameScreen() {
    delete broadphase;
    delete collisionConfiguration;
    delete dispatcher;
    delete solver;
    delete dynamicsWorld;
}

