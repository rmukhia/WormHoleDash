//
// Created by Raunak Mukhia on 7/4/18.
//

#include "Actor.h"

int Actor::getId() const { return id; }

void Actor::setId(int id) { Actor::id = id; }

char *Actor::getName() const { return name; }

void Actor::setName(char *name) { Actor::name = name; }

GLint Actor::getNum_vertices() const { return num_vertices; }

void Actor::setNum_vertices(GLint num_vertices) {
  Actor::num_vertices = num_vertices;
}

GLfloat *Actor::getVertices() const { return vertices; }

void Actor::setVertices(GLfloat *vertices) { Actor::vertices = vertices; }

GLfloat Actor::getPosX() const { return posX; }

void Actor::setPosX(GLfloat posX) { Actor::posX = posX; }

GLfloat Actor::getPosY() const { return posY; }

void Actor::setPosY(GLfloat posY) { Actor::posY = posY; }

GLfloat Actor::getPosZ() const { return posZ; }

void Actor::setPosZ(GLfloat posZ) { Actor::posZ = posZ; }

GLfloat Actor::getAngleX() const {
  return angleX;
}

void Actor::setAngleX(GLfloat angleX) {
  Actor::angleX = angleX;
}

GLfloat Actor::getAngleY() const {
  return angleY;
}

void Actor::setAngleY(GLfloat angleY) {
  Actor::angleY = angleY;
}

GLfloat Actor::getAngleZ() const {
  return angleZ;
}

void Actor::setAngleZ(GLfloat angleZ) {
  Actor::angleZ = angleZ;
}

int Actor::getMeshIndex() const {
    return meshIndex;
}

void Actor::setMeshIndex(int meshIndex) {
    Actor::meshIndex = meshIndex;
}

GLint Actor::getNum_indices() const {
    return num_indices;
}

void Actor::setNum_indices(GLint num_indices) {
    Actor::num_indices = num_indices;
}

GLint * Actor::getIndices() const {
    return indices;
}

void Actor::setIndices(GLint *indices) {
    Actor::indices = indices;
}

GLint Actor::getNum_normals() const {
    return num_normals;
}

void Actor::setNum_normals(GLint num_normals) {
    Actor::num_normals = num_normals;
}

GLfloat *Actor::getNormals() const {
    return normals;
}

void Actor::setNormals(GLfloat *normals) {
    Actor::normals = normals;
}

GLint Actor::getNum_uvs() const {
    return num_uvs;
}

void Actor::setNum_uvs(GLint num_uvs) {
    Actor::num_uvs = num_uvs;
}

GLfloat *Actor::getUvs() const {
    return uvs;
}

void Actor::setUvs(GLfloat *uvs) {
    Actor::uvs = uvs;
}
