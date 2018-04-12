//
// Created by Raunak Mukhia on 12/4/18.
//

#ifndef WORMHOLEDASH_STARTSCREEN_H
#define WORMHOLEDASH_STARTSCREEN_H

#include "../../engine/Scene.h"

class StartScreen : public Scene {
public:
  void create() override;

  void draw() override;

  void update() override;

  void paused() override;

  void destroy() override;
};

#endif // WORMHOLEDASH_STARTSCREEN_H
