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

  GLint num_indices;
  GLint *indices;

  GLint num_normals;
  GLfloat *normals;

  GLint num_uvs;
  GLfloat *uvs;


  GLfloat posX;

  GLfloat posY;

  GLfloat posZ;

  GLfloat angleX;

  GLfloat angleY;

  GLfloat angleZ;

  int meshIndex;

public:
  int getId() const;

  void setId(int id);

  char *getName() const;

  void setName(char *name);

  GLint getNum_vertices() const;

  void setNum_vertices(GLint num_vertices);

  GLfloat *getVertices() const;

  void setVertices(GLfloat *vertices);

    GLint getNum_indices() const;

    void setNum_indices(GLint num_indices);

    GLint *getIndices() const;

    void setIndices(GLint *indices);

    GLint getNum_normals() const;

    void setNum_normals(GLint num_normals);

    GLfloat *getNormals() const;

    void setNormals(GLfloat *normals);

    GLint getNum_uvs() const;

    void setNum_uvs(GLint num_uvs);

    GLfloat *getUvs() const;

    void setUvs(GLfloat *uvs);

    GLfloat getPosX() const;

  void setPosX(GLfloat posX);

  GLfloat getPosY() const;

  void setPosY(GLfloat posY);

  GLfloat getPosZ() const;

  void setPosZ(GLfloat posZ);

    GLfloat getAngleX() const;

    void setAngleX(GLfloat angleX);

    GLfloat getAngleY() const;

    void setAngleY(GLfloat angleY);

    GLfloat getAngleZ() const;

    void setAngleZ(GLfloat angleZ);

    int getMeshIndex() const;

    void setMeshIndex(int meshIndex);

    virtual void create() = 0;

  virtual void draw() = 0;

  virtual void update() = 0;

  virtual void destroy() = 0;

  virtual void act(Command *pCommand) = 0;

};

#endif // CGPROJECT_GAMEOBJECT_H
