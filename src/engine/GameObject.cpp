//
// Created by Raunak Mukhia on 7/4/18.
//

#include "GameObject.h"

int GameObject::getId() const {
    return id;
}

void GameObject::setId(int id) {
    GameObject::id = id;
}

char *GameObject::getName() const {
    return name;
}

void GameObject::setName(char *name) {
    GameObject::name = name;
}

GLint GameObject::getNum_vertices() const {
    return num_vertices;
}

void GameObject::setNum_vertices(GLint num_vertices) {
    GameObject::num_vertices = num_vertices;
}

GLfloat *GameObject::getVertices() const {
    return vertices;
}

void GameObject::setVertices(GLfloat *vertices) {
    GameObject::vertices = vertices;
}
