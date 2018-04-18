//
// Created by Raunak Mukhia on 19/4/18.
//

#ifndef WORMHOLEDASH_DUBUGDRAW_H
#define WORMHOLEDASH_DUBUGDRAW_H


#include <LinearMath/btIDebugDraw.h>

class DebugDraw: public btIDebugDraw {
    int m_debug_mode;

public:
    void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;

    void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime,
                          const btVector3 &color) override;

    void reportErrorWarning(const char *warningString) override;

    void draw3dText(const btVector3 &location, const char *textString) override;

    void setDebugMode(int debugMode) override;

    int getDebugMode() const override;
};


#endif //WORMHOLEDASH_DUBUGDRAW_H
