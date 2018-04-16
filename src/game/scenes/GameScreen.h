//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_STARTSCREEN_H
#define WORMHOLEDASH_STARTSCREEN_H

#include "../../glheaders.h"
#include "../../engine/Scene.h"
#include "../actors/Tunnel.h"

class GameScreen : public Scene {
private:
  Actor *speedBuggy;
  Tunnel *currentTunnel;
  rp3d::DynamicsWorld * world;
public:
  void create() override;

  void draw(int nSteps) override;

  void update(int nSteps) override;

  void paused() override;

  void destroy() override;

  void preDraw();

  void keyInput(unsigned char key, int x, int y) override;
};

#endif // WORMHOLEDASH_STARTSCREEN_H
