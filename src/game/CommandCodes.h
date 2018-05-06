//
// Created by Raunak Mukhia on 14/4/18.
//

#ifndef WORMHOLEDASH_COMMANDCODES_H
#define WORMHOLEDASH_COMMANDCODES_H

enum GlobalCommands {
    ROTATE_X = 0,
    ROTATE_Y,
    ROTATE_Z,
};

enum SpeedBuggyCommands {
    MOVE_LEFT = 10,
    MOVE_RIGHT,
    MOVE_ACCELERATE,
    MOVE_BREAK,
    RELEASE_ENGINE,
    RELEASE_STEERING,
};



#endif //WORMHOLEDASH_COMMANDCODES_H
