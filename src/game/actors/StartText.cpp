//
// Created by Raunak Mukhia on 7/5/18.
//

#include <cstdio>
#include "StartText.h"

void StartText::create() {

}
void StartText::writeBitmapString(void *font, char *string) {
    char *c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to convert floating point to char string.
void StartText::floatToString(char *destStr, int precision, float val) {
    sprintf(destStr, "%f", val);
    destStr[precision] = '\0';
}

void StartText::draw() {
    static long font = (long) GLUT_BITMAP_8_BY_13; // Font selection.

    // Routine to draw a bitmap character string.
    //glEnable(GL_COLOR_MATERIAL);
    if (!running) {
        glPushMatrix();
        glMultMatrixf(buggyTransform);

        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glRasterPos3f(4.0, 10.0, -4.0);
        writeBitmapString((void *) font, "Press Space to Start.");
        glRasterPos3f(4.0, 8.0, -4.0);
        writeBitmapString((void *) font, "w: accelerate");
        glRasterPos3f(4.0, 6.0, -4.0);
        writeBitmapString((void *) font, "s: break");
        glRasterPos3f(4.0, 4.0, -4.0);
        writeBitmapString((void *) font, "a: turn left");
        glRasterPos3f(4.0, 2.0, -4.0);
        writeBitmapString((void *) font, "d: turn right");
        glRasterPos3f(4.0, 0.0, -4.0);
        writeBitmapString((void *) font, "esc: pause");

        glEnable(GL_LIGHTING);
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
        //glDisable(GL_COLOR_MATERIAL);
    }

}

void StartText::update() {

}

void StartText::destroy() {

}

void StartText::act(Command *pCommand) {

}

GLfloat *StartText::getBuggyTransform() {
    return buggyTransform;
}

bool StartText::isRunning() const {
    return running;
}

void StartText::setRunning(bool running) {
    StartText::running = running;
}
