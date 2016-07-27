#pragma once

#include <memory>

#include "system/gamesystem.h"
#include "system/interpreterSystem.h"

class Application {
public:
  explicit Application();

  void Update();

  bool is_finished() { return game_system_->is_finished(); }

private:
  shared_ptr<GameSystem> game_system_;
  shared_ptr<InterpreterSystem> interpreter_system_;
};