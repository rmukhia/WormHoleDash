//
// Created by Raunak Mukhia on 12/4/18.
//

#include <GL/glu.h>
#include "Camera.h"

void Camera::project() {
    if (changed) {
        glLoadIdentity();
        gluPerspective(fovy, aspect, zNear, zFar);
        changed = false;
    }
}
