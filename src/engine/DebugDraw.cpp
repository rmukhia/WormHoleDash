//
// Created by Raunak Mukhia on 19/4/18.
//

#include <GL/glew.h>
#include "DebugDraw.h"

void DebugDraw::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) {
    glColor3f(color.getX(), color.getY(), color.getZ());
    glBegin(GL_LINES);
    glVertex3f(from.getX(), from.getY(), from.getZ());
    glVertex3f(to.getX(), to.getY(), to.getZ());
    glEnd();
}

void DebugDraw::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime,
                                 const btVector3 &color) {
    glColor3f(color.getX(), color.getY(), color.getZ());
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex3f(PointOnB.getX(), PointOnB.getY(), PointOnB.getZ());
    glEnd();

}

void DebugDraw::reportErrorWarning(const char *warningString) {

}

void DebugDraw::draw3dText(const btVector3 &location, const char *textString) {

}

void DebugDraw::setDebugMode(int debugModeT) {
    m_debug_mode = debugModeT;
}

int DebugDraw::getDebugMode() const {
    return m_debug_mode;
}
