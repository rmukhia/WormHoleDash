//
// Created by Raunak Mukhia on 15/4/18.
//

#include <cmath>
#include <iostream>
#include "Tunnel.h"
#define NUM_VERTICES_PER_CIRCLE 16
#define NUM_FLOAT_PER_CIRCLE NUM_VERTICES_PER_CIRCLE * 3
#define NUM_FLOAT_PER_TUNNEL NUM_FLOAT_PER_CIRCLE * 2
#define RADIUS 5.0;

void Tunnel::create() {
    //TODO: increase algorithm complexity
    endVertices[0] = startVertices[0] + thetaHorizontal; // x
    endVertices[1] = startVertices[1] + thetaVertical; // y
    endVertices[2] = startVertices[2] - length; // z

    vertices = new GLfloat[NUM_FLOAT_PER_TUNNEL + 6];

    int i = 0;
    int v = 0;
    auto rDeltaAngle = (GLfloat)RADIAN(360.0/NUM_VERTICES_PER_CIRCLE);
    GLfloat rAngle = 0.0;
    while(v <= NUM_FLOAT_PER_TUNNEL) {
        // x
        vertices[v++] = startVertices[0] + cos(rAngle) * RADIUS;
        // y
        vertices[v++] = startVertices[1] + sin(rAngle) * RADIUS;
        // z
        vertices[v++] =startVertices[2];

        // x
        vertices[v++] = endVertices[0] + cos(rAngle) * RADIUS;
        // y
        vertices[v++] = endVertices[1] + sin(rAngle) * RADIUS;
        // z
        vertices[v++] = endVertices[2];
        rAngle += rDeltaAngle;
    }
}

void Tunnel::draw() {
    glPushMatrix();
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    for(int  i = 0; i <= NUM_FLOAT_PER_TUNNEL + 3; i += 3) {
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    glEnd();
    glPopMatrix();
}

void Tunnel::update() {


}

void Tunnel::destroy() {

}

void Tunnel::act(Command *pCommand) {

}

Tunnel::Tunnel(GLfloat thetaHorizontal, GLfloat thetaVertical, GLfloat length) : thetaHorizontal(thetaHorizontal),
                                                                                 thetaVertical(thetaVertical),
                                                                                 length(length) {}

void Tunnel::setStartVertices(GLfloat x, GLfloat y, GLfloat z) {
    startVertices[0] = x;
    startVertices[1] = y;
    startVertices[2] = z;
}

void Tunnel::getEndVertices(GLfloat *x, GLfloat *y, GLfloat *z) {
    *x = endVertices[0];
    *y = endVertices[1];
    *z = endVertices[2];
}
