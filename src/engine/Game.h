//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_GAMECONTEXT_H
#define CGPROJECT_GAMECONTEXT_H

#include "../glheaders.h"


class Game {
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


public:
    static Game * instance();

    float getAspectRatio () {
        return screenWidth/screenHeight;
    }

protected:
    Game() {
    }

private:
    static Game * _instance;
};

#endif //CGPROJECT_GAMECONTEXT_H
