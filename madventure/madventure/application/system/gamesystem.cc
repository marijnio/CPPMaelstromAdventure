#include <iostream>
#include <string>
#include <assert.h>

#include "gamesystem.h"
#include "../graph/SparseGraph.h"
#include "../model/level.h"

//#include "../event/createlevelevent.h"
//#include "../component/area.h"
//#include "../component/player.h"
//#include "../component/location.h"

using namespace std;

GameSystem::GameSystem() {
  finished_ = false;
  interpreter_system_ = new InterpreterSystem(this);
  level_system_ = new LevelSystem();
}

GameSystem::~GameSystem() {
  delete interpreter_system_;
}

void GameSystem::Init() {
  std::cout << "Welcome to Maelstrom Adventure.\n\n";

  // Create world and level.
  world_ = make_shared<World>();
  level_system_->setWorld(world_);
  shared_ptr<Level> current_level_ = level_system_->NewLevel(3, 3);

  // Select starting area.
  auto area = current_level_->graph->GetNode(0).ExtraInfo();

  // Create player and place in area.
  player_ = make_shared<Player>(area);
}

void GameSystem::Update() {
  interpreter_system_->Update();
}