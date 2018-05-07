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
#include "../actors/GroundRigid.h"
#include "../actors/SpeedBuggyWheel.h"
#include "../../engine/getBMP.h"
#include "../actors/TextureBox.h"
#include "../../engine/SceneManager.h"

enum IDS {
    BUGGY = 1,
    TRACK,
    TEXTUREBOX,
    TEXT
};


void GameScreen::loadObj() {
    Game *game = Game::instance();
    objl::Loader Loader;

    bool loadout = Loader.LoadFile(game->getResourcePath("models/track6.obj"));
    if (loadout) {

        for(auto actor: *getActors()) {
            // negative mesh id means it does not exist
            if(actor->getMeshIndex() < 0)
                continue;

            objl::Mesh curMesh = Loader.LoadedMeshes[actor->getMeshIndex()];

            // set vertices
            actor->setNum_vertices(curMesh.Vertices.size());
            actor->setNum_normals(curMesh.Vertices.size());
            if (actor->getId() != IDS::TRACK)
                actor->setNum_uvs(curMesh.Vertices.size());
            GLfloat *vertices = new GLfloat[actor->getNum_vertices() * 3];
            GLfloat *normals = new GLfloat[actor->getNum_normals() * 3];
            GLfloat *uvs;
            if (actor->getId() != IDS::TRACK)
                uvs = new GLfloat[actor->getNum_uvs() * 2];
            int j =0;
            int u = 0;
            for(int i = 0; i < actor->getNum_vertices(); i++) {
                normals[j] = curMesh.Vertices[i].Normal.X;
                if (actor->getId() != IDS::TRACK)
                    uvs[u++] = curMesh.Vertices[i].TextureCoordinate.X;
                vertices[j++] = curMesh.Vertices[i].Position.X;

                normals[j] = curMesh.Vertices[i].Normal.Y;
                if (actor->getId() != IDS::TRACK)
                    uvs[u++] = curMesh.Vertices[i].TextureCoordinate.Y;
                vertices[j++] = curMesh.Vertices[i].Position.Y;

                normals[j] = curMesh.Vertices[i].Normal.Z;
                vertices[j++] = curMesh.Vertices[i].Position.Z;
            }

            actor->setVertices(vertices);
            actor->setNormals(normals);
            actor->setUvs(uvs);

            // Load indices
            actor->setNum_indices(curMesh.Indices.size());
            GLint *indices = new GLint[actor->getNum_indices()];

            for(int i = 0; i < actor->getNum_indices(); i++)
                indices[i] =curMesh.Indices[i];

            actor->setIndices(indices);
            vertices = nullptr;
            indices = nullptr;
            uvs = nullptr;
        }
    }
}

void GameScreen::create() {
    Game * game = Game::instance();
    Scene::create();
    auto * camera = new Camera(115.0, game->getAspectRatio(), 1.0, 2000.0);
    setCamera(camera);
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, 2* -0.98, 0));


    textureBox = new TextureBox;
    textureBox->create();
    textureBox->setId(IDS::TEXTUREBOX);
    textureBox->setMeshIndex(-1);
    getActors()->push_back(textureBox);

    auto *track = new Track;
    track->create();
    track->setId(IDS::TRACK);
    track->setMeshIndex(0);
    getActors()->push_back(track);

    auto *speedBuggyWheel = new SpeedBuggyWheel;
    speedBuggyWheel->create();
    speedBuggyWheel->setId(IDS::BUGGY); // Front left
    speedBuggyWheel->setMeshIndex(1);
    getActors()->push_back(speedBuggyWheel);

    buggy = new SpeedBuggy;
    buggy->create();
    buggy->setId(IDS::BUGGY);
    buggy->setMeshIndex(2);
    buggy->setSpeedBuggyWheels(speedBuggyWheel);
    getActors()->push_back(buggy);

    startText = new StartText;
    startText->create();
    startText->setId(IDS::TEXT);
    startText->setMeshIndex(-1);
    startText->setRunning(false);
    getActors()->push_back(startText);

    timerText = new TimerText;
    timerText->create();
    timerText->setId(IDS::TEXT);
    timerText->setMeshIndex(-1);
    getActors()->push_back(timerText);

    loadTextures();
    loadObj();

    buggy->createBody(dynamicsWorld);
    track->createBody(dynamicsWorld);

    if (game->debug) {
        dynamicsWorld->setDebugDrawer(new DebugDraw);
        dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    } else {
        setupLight();
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    setLoaded(true);
}

void multiply(GLfloat  *mv, GLfloat *p, GLfloat *result) {
    result[0] = mv[0] * p[0] + mv[4] * p[1] + mv[8] *p[2] + mv[12] * 1;
    result[1] = mv[1] * p[0] + mv[5] * p[1] + mv[9] *p[2] + mv[13] * 1;
    result[2] = mv[2] * p[0] + mv[6] * p[1] + mv[10] *p[2] + mv[14] * 1;

}

void GameScreen::preDraw() {
   Camera * cam = getCamera();
   btTransform trans;
   auto buggyPosition = buggy->getRigidBody()->getCenterOfMassPosition();
   btScalar yaw, roll, pitch;
   GLfloat  m[16];
   buggy->getRigidBody()->getWorldTransform().getOpenGLMatrix(m);

   GLfloat c[3] = { 0, 0, 0 };
   GLfloat e[3] = { 0, 5.0, -10.0 };
   GLfloat u[3] = { 0, 1, 0 };

   GLfloat center[3], eye[3], up[3];

   multiply(m, c, center);
   multiply(m, e, eye);
   eye[1] = c[1] + 4.0;
   //multiply(m, u, up);

   cam->setLookAt(eye, center, u);


   // Copy the transform
   memcpy(textureBox->getBuggyTransform(), m, sizeof(GLfloat) * 16);
   memcpy(startText->getBuggyTransform(), m, sizeof(GLfloat) * 16);
   memcpy(timerText->getBuggyTransform(), m, sizeof(GLfloat) * 16);

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
    else {
        Scene::draw(deltaTime);
        if (startText->isRunning())
            timerText->updateTime(deltaTime);
    }
}

void GameScreen::update(long double deltaTime) {
    Scene::update(deltaTime);

    Game *game = Game::instance();
    if (dynamicsWorld && (startText->isRunning() || startingFrameRun-- > 0))
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
        case ' ':
            startText->setRunning(true);
            break;
        case 27:
            startText->setRunning(false);
            break;
    }

}

void GameScreen::keyUp(unsigned char key, int x, int y) {
    Scene::keyUp(key, x, y);
    switch(key) {
        case 'w':
        case 's':
        case 'S':
        case 'W':
            addCommand(new Command(SpeedBuggyCommands::RELEASE_ENGINE, IDS::BUGGY));
            break;
        case 'a':
        case 'd':
        case 'D':
        case 'A':
            addCommand(new Command(SpeedBuggyCommands::RELEASE_STEERING, IDS::BUGGY));
            break;
    }
}

GameScreen::~GameScreen() {
    delete broadphase;
    delete collisionConfiguration;
    delete dispatcher;
    delete solver;
    delete dynamicsWorld;
}

void GameScreen::setupLight() {
    GLfloat lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat globAmb[] = { 0.1, 0.1, 0.1, 1.0 };
    // Light properties.
    // Light 0
    float lightPos0[] = { 0.0, 1.0 , 0.0, 0.0 };
    GLfloat lightDifAndSpec0[] = { 0.3, 0.3, 0.3, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    // Light 1
    GLfloat lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0f);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.


    glShadeModel(GL_SMOOTH);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

    glEnable(GL_LIGHT0); // Enable particular light source.
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
}

void GameScreen::loadTextures() {
}


