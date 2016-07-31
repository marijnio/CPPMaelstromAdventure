#pragma once

#include <memory>

#include "interpretersystem.h"
#include "levelsystem.h"
#include "../model/world.h"
#include "../model/player.h"

class GameSystem {
public:
  explicit GameSystem();
  ~GameSystem();

  void Init();

  void Update();
  void Quit() { finished_ = true; }

  bool is_finished() { return finished_; }
  LevelSystem<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>* levelSystem() { return level_system_; }
  InterpreterSystem* interpreterSystem() { return interpreter_system_; }
  shared_ptr<Player> player() { return player_; }

private:
  bool finished_;

  InterpreterSystem* interpreter_system_;
  LevelSystem<SparseGraph<NavGraphNode<shared_ptr<Area>>, NavGraphEdge>>* level_system_;

  shared_ptr<World> world_;
  shared_ptr<Player> player_;

  shared_ptr<Level> NewLevel(int columns, int row);
};