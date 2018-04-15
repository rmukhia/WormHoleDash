//
// Created by Raunak Mukhia on 7/4/18.
//
/* The format is VVVV NNNN TTTT
 * V: vertex
 * N: normals
 * Texcoords
 */

#ifndef CGPROJECT_GAMEOBJECT_H
#define CGPROJECT_GAMEOBJECT_H

#include "../glheaders.h"
#include "Command.h"

class Actor {
protected:
  int id; // object id

  char *name; // object name

  GLint num_vertices;

  GLfloat *vertices;

  GLfloat posX;

  GLfloat posY;

  GLfloat posZ;

public:
  int getId() const;

  void setId(int id);

  char *getName() const;

  void setName(char *name);

  GLint getNum_vertices() const;

  void setNum_vertices(GLint num_vertices);

  GLfloat *getVertices() const;

  void setVertices(GLfloat *vertices);

  GLfloat getPosX() const;

  void setPosX(GLfloat posX);

  GLfloat getPosY() const;

  void setPosY(GLfloat posY);

  GLfloat getPosZ() const;

  void setPosZ(GLfloat posZ);

  virtual void create() = 0;

  virtual void draw() = 0;

  virtual void update() = 0;

  virtual void destroy() = 0;

  virtual void act(Command *pCommand) = 0;
};

#endif // CGPROJECT_GAMEOBJECT_H
