//
// Created by Raunak Mukhia on 6/5/18.
//

#ifndef WORMHOLEDASH_GETBMP_H
#define WORMHOLEDASH_GETBMP_H

struct imageFile
{
    int width;
    int height;
    unsigned char *data;
};

imageFile *getBMP(const char *fileName);

#endif //WORMHOLEDASH_GETBMP_H
