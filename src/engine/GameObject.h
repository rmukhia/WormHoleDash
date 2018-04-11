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


#include <GL/glew.h>

class GameObject {
protected:
    int id;                         // object id
    char *name;                     // object name
    GLint num_vertices;
    GLfloat *vertices;
public:
    int getId() const;
    void setId(int id);

    char *getName() const;
    void setName(char *name);

    GLint getNum_vertices() const;

    void setNum_vertices(GLint num_vertices);

    GLfloat *getVertices() const;

    void setVertices(GLfloat *vertices);
};


#endif //CGPROJECT_GAMEOBJECT_H
