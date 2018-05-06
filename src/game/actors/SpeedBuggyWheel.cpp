//
// Created by Raunak Mukhia on 6/5/18.
//

#include "SpeedBuggyWheel.h"

void SpeedBuggyWheel::create() {
    texture = getBMP("../resources/models/tyre.bmp");
    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


}

void SpeedBuggyWheel::draw() {

}

void SpeedBuggyWheel::update() {

}

void SpeedBuggyWheel::destroy() {

}

void SpeedBuggyWheel::act(Command *pCommand) {

}

void SpeedBuggyWheel::drawWheel(GLfloat *modelView) {
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glMultMatrixf(modelView);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2,GL_FLOAT,0, uvs);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

