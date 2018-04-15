//
// Created by Raunak Mukhia on 14/4/18.
//

#include "Command.h"

int Command::getOpcode() const {
    return opcode;
}

Command::Command(int opcode, int actorId) : opcode(opcode), actorId(actorId) {}

int Command::getActorId() const {
    return actorId;
}

Command::Command(int opcode, int actorId, GLfloat params) : opcode(opcode), actorId(actorId), params(params) {}
