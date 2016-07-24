#pragma once

#include "system/gamesystem.h"
#include "system/interpreterSystem.h"
#include "system/levelsystem.h"

class Application {
public:
  explicit Application();

  void update();

  bool is_finished() { return game_system_->is_finished(); }

private:
  GameSystem* game_system_;
  InterpreterSystem* interpreter_system_;
  LevelSystem* level_system_;
};