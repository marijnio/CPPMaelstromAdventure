#pragma once

#include <memory>

#include "../model/world.h"

class GameSystem {
public:
  explicit GameSystem();

  void Init();

  void update();

  bool is_finished() { return finished_; }

private:
  bool finished_;
  shared_ptr<World> world_;

  void NewLevel(int columns, int row);
};