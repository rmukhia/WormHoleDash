//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_GAMECONTEXT_H
#define CGPROJECT_GAMECONTEXT_H


class Game {
public:
    bool fullScreen;
    float screenHeight;
    float screenWidth;
    float worldHeight;
    float worldWidth;
    char gameName[255];

public:
    static Game * instance();

    float getAspectRatio () {
        return screenWidth/screenHeight;
    }

protected:
    Game() {}

private:
    static Game * _instance;
};

#endif //CGPROJECT_GAMECONTEXT_H
