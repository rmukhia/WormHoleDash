//
// Created by Raunak Mukhia on 10/4/18.
//

#ifndef CGPROJECT_OPENGLSTATES_H
#define CGPROJECT_OPENGLSTATES_H

#include "../glheaders.h"

void initializeOpenGL(int argc, char **argv, void (* callback)(void));
void drawScene(void);
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
void redraw();

#endif //CGPROJECT_OPENGLSTATES_H
