//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_STARTSCREEN_H
#define WORMHOLEDASH_STARTSCREEN_H

#include "../../glheaders.h"
#include "../../engine/Scene.h"

class StartScreen : public Scene {
public:
  void create() override;

  void draw() override;

  void update() override;

  void paused() override;

  void destroy() override;

  void preDraw();

    void keyInput(unsigned char key, int x, int y) override;
};

#endif // WORMHOLEDASH_STARTSCREEN_H
