#include <iostream>
#include <string>
#include <assert.h>

#include "gamesystem.h"
#include "../graph/SparseGraph.h"
#include "../model/level.h"

#include "commands.h"

using namespace std;

GameSystem::GameSystem() {
  finished_ = false;

  interpreter_system_ = new InterpreterSystem(this);
  unit_system_ = new UnitSystem();
  level_system_ = new LevelSystem();
}

GameSystem::~GameSystem() {
  delete interpreter_system_;
}

void GameSystem::Init() {
  std::cout << "Welcome to Maelstrom Adventure.\n\n";

  // Initialize the world with a level.
  auto first_level = level_system_->NewLevel(3, 3);
  level_system_->AddLevel(first_level);

  // Select starting area.
  auto area = first_level->graph->GetNode(0).ExtraInfo();

  // Create player and place in area.
  unit_system_->SetPlayer(unit_system_->SpawnPlayer(area));

  // Add two extra levels
  auto second_level = level_system_->NewLevel(3, 3);
  auto third_level = level_system_->NewLevel(3, 3);

  level_system_->AddLevel(second_level);
  level_system_->AddLevel(third_level);

  // Connect the levels with gateways.
  level_system_->AddGateway(level_system_->RandomArea(first_level),
                            level_system_->RandomArea(second_level));

  level_system_->AddGateway(level_system_->RandomArea(second_level),
                            level_system_->RandomArea(third_level));

  HelpCommand().Execute(this, vector<string>());
  InspectCommand().Execute(this, vector<string>());
  cout << "\n";
}

void GameSystem::Update() {
  interpreter_system_->Update();
}