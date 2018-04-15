//
// Created by Raunak Mukhia on 15/4/18.
//

#ifndef WORMHOLEDASH_TUNNEL_H
#define WORMHOLEDASH_TUNNEL_H


#include "../../engine/Actor.h"

class Tunnel: public Actor {
private:
    /*
     * The equation of the line y = k z^n
     * k can be both negative and positive
     * n should be odd.
     */
    GLfloat thetaHorizontal;
    GLfloat thetaVertical;
    GLfloat length;

    GLfloat startVertices[3];
    GLfloat endVertices[3];

public:
    Tunnel(GLfloat thetaHorizontal, GLfloat thetaVertical, GLfloat length);

    void create() override;

    void draw() override;

    void update() override;

    void destroy() override;

    void act(Command *pCommand) override;

    void setStartVertices(GLfloat x, GLfloat y, GLfloat z);

    void getEndVertices(GLfloat *x, GLfloat *y, GLfloat *z);

};


#endif //WORMHOLEDASH_TUNNEL_H
