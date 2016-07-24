#pragma once

#include "../event/gamequitevent.h"


class GameSystem {
public:
  explicit GameSystem() {};

  void configure();

  void update();

  bool is_finished() { return finished_; }

private:
  bool finished_;
  bool initialized_ = false;
};