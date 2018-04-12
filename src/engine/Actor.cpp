//
// Created by Raunak Mukhia on 7/4/18.
//

#include <GL/gl.h>
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