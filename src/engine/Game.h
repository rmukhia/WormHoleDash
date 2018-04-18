//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_GAMECONTEXT_H
#define CGPROJECT_GAMECONTEXT_H

#include "../glheaders.h"


class Game {
private:
public:
    bool fullScreen;
    float screenHeight;
    float screenWidth;
    bool sizeChanged;
    float worldHeight;
    float worldWidth;
    char gameName[255];
    bool wireframe;
    GLfloat Ztranslate;
    GLfloat Xangle;
    GLfloat Yangle;
    GLfloat Zangle; // Angles to rotate hemisphere.

    float timeStep;
    char objpath[255];
    bool debug;

    char * getOBJPath(const char *string);

public:
    static Game * instance();

    float getAspectRatio () {
        return screenWidth/screenHeight;
    }

protected:
    Game() = default;

private:
    static Game * _instance;
};

#endif //CGPROJECT_GAMECONTEXT_H
