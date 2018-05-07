//
// Created by Raunak Mukhia on 7/5/18.
//

#ifndef WORMHOLEDASH_STARTTEXT_H
#define WORMHOLEDASH_STARTTEXT_H


#include "../../engine/Actor.h"

class StartText : public Actor{
    GLfloat buggyTransform[16];
    bool running;
public:
    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    GLfloat *getBuggyTransform();

    bool isRunning() const;

    void setRunning(bool running);

    void writeBitmapString(void *font, char *string);

    void floatToString(char *destStr, int precision, float val);
};


#endif //WORMHOLEDASH_STARTTEXT_H
