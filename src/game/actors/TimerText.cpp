//
// Created by Raunak Mukhia on 7/5/18.
//

#include <cstdio>
#include <cstring>
#include "TimerText.h"

void TimerText::create() {
    timeElapsed = 0.0;

}

void multiplyTT(GLfloat *mv, GLfloat *p, GLfloat *result) {
    result[0] = mv[0] * p[0] + mv[4] * p[1] + mv[8] * p[2] + mv[12] * 1;
    result[1] = mv[1] * p[0] + mv[5] * p[1] + mv[9] * p[2] + mv[13] * 1;
    result[2] = mv[2] * p[0] + mv[6] * p[1] + mv[10] * p[2] + mv[14] * 1;

}

void TimerText::writeBitmapString(void *font, char *string) {
    char *c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to convert floating point to char string.
void TimerText::floatToString(char *destStr, int precision, float val) {
    sprintf(destStr, "%.2f", val);
}

void TimerText::draw() {
    static long font = (long) GLUT_BITMAP_8_BY_13; // Font selection.

    // Routine to draw a bitmap character string.

    if (timeElapsed > 0.0) {
        GLfloat p[3] = {-3.0, 0, 0};

        GLfloat pos[3];

        multiplyTT(buggyTransform, p, pos);
        pos[1] = p[1] + 4.0;

        glPushMatrix();

        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDisable(GL_LIGHTING);

        char timestr[20];
        char str[50];
        strcat(str, "Timer: ");
        floatToString(timestr, 4, timeElapsed);
        strcat(str, timestr);
        strcat(str," s");

        glColor4f(1.0, 0.3, 0.3, 1.0);
        glRasterPos3f(pos[0], pos[1], pos[2]);
        writeBitmapString((void *) font, str);
        glEnable(GL_LIGHTING);
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glPopMatrix();
    }

}

void TimerText::update() {

}

void TimerText::destroy() {

}

void TimerText::act(Command *pCommand) {

}

void TimerText::updateTime(long double deltaTime) {
    timeElapsed += deltaTime;
}

GLfloat *TimerText::getBuggyTransform() {
    return buggyTransform;
}
