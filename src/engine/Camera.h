//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_CAMERA_H
#define WORMHOLEDASH_CAMERA_H

#include <cstring>
#include "../glheaders.h"

class Camera {
private:
  GLdouble fovy;
  GLdouble aspect;
  GLdouble zNear;
  GLdouble zFar;
  bool changed;

  GLfloat eye[3];
  GLfloat center[3];
  GLfloat up[3];
  bool hasLookAt;


public:
  Camera(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
      : fovy(fovy), aspect(aspect), zNear(zNear), zFar(zFar) {
    changed = true;
    hasLookAt = false;
  }

  void project();

  void lookAt();

  void setLookAt(GLfloat *e, GLfloat *c, GLfloat *u);

  GLdouble getFovy() const { return fovy; }

  void setFovy(GLdouble fovy) {
    changed = true;
    Camera::fovy = fovy;
  }

  GLdouble getAspect() const { return aspect; }

  void setAspect(GLdouble aspect) {
    changed = true;
    Camera::aspect = aspect;
  }

  GLdouble getZNear() const { return zNear; }

  void setZNear(GLdouble zNear) {
    changed = true;
    Camera::zNear = zNear;
  }

  GLdouble getZFar() const { return zFar; }

  void setZFar(GLdouble zFar) {
    changed = true;
    Camera::zFar = zFar;
  }
};

#endif // WORMHOLEDASH_CAMERA_H
