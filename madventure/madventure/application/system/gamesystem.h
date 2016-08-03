#pragma once

#include <memory>

#include "interpretersystem.h"
#include "levelsystem.h"
#include "unitsystem.h"

#include "../model/world.h"
#include "../model/player.h"
#include "../model/enemy.h"

class GameSystem {
public:
  explicit GameSystem();
  ~GameSystem();

  void Init();

  void Update();
  void Quit() { finished_ = true; }

  bool is_finished() { return finished_; }
  InterpreterSystem* interpreter_system() { return interpreter_system_; }
  LevelSystem* level_system() { return level_system_; }
  UnitSystem* unit_system() { return unit_system_; }

  string GetAreaDescription(int climate);

private:
  bool finished_;

  InterpreterSystem* interpreter_system_;
  LevelSystem* level_system_;
  UnitSystem* unit_system_;

  void InjectUnits(shared_ptr<Level> level);

  map<string, string> area_descriptions_;
};