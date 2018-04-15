//
// Created by Raunak Mukhia on 14/4/18.
//

#ifndef WORMHOLEDASH_COMMAND_H
#define WORMHOLEDASH_COMMAND_H


#include <GL/glew.h>

class Command {
    int opcode;
    int actorId;
public:
    GLfloat params;
    Command(int opcode, int actorId);

    Command(int opcode, int actorId, GLfloat params);

    int getOpcode() const;

    int getActorId() const;

};


#endif //WORMHOLEDASH_COMMAND_H
