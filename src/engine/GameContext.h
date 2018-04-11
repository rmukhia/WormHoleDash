//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_GAMECONTEXT_H
#define CGPROJECT_GAMECONTEXT_H


class GameContext {
public:
    bool fullScreen;
    float screenHeight;
    float screenWidth;
    float worldHeight;
    float worldWidth;
    char gameName[255];

public:
    static GameContext * instance();

protected:
    GameContext() {}

private:
    static GameContext * _instance;
};

#endif //CGPROJECT_GAMECONTEXT_H
