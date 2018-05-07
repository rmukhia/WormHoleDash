//
// Created by Raunak Mukhia on 7/5/18.
//

#ifndef WORMHOLEDASH_TIMERTEXT_H
#define WORMHOLEDASH_TIMERTEXT_H


#include "../../engine/Actor.h"

class TimerText : public Actor {
    GLfloat buggyTransform[16];
    long double timeElapsed;
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    void updateTime(long double deltaTime);

    GLfloat *getBuggyTransform();

    void writeBitmapString(void *font, char *string);

    void floatToString(char *destStr, int precision, float val);
};


#endif //WORMHOLEDASH_TIMERTEXT_H
