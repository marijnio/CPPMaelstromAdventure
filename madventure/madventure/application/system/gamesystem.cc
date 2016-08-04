#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>

#include "gamesystem.h"
#include "../graph/SparseGraph.h"
#include "../model/level.h"
#include "../utility/mymath.h"
#include "commands.h"

#include "gameinfoparser.h"

using namespace std;

GameSystem::GameSystem() {
  finished_ = false;

  interpreter_system_ = new InterpreterSystem(this);
  unit_system_ = new UnitSystem();
  level_system_ = new LevelSystem();
  game_locale_ = new GameLocale();
}

GameSystem::~GameSystem() {
  delete interpreter_system_;
}

void GameSystem::Init() {
  std::cout << "Welcome to Maelstrom Adventure.\n\n";

  // Initialize the world with a level.
  auto first_level = level_system_->NewLevel(3, 3);
  level_system_->AddLevel(first_level);

  // Init first level time to 12:00.
  first_level->time_ = 12;

  // Select starting area.
  auto area = first_level->graph->GetNode(0).ExtraInfo();

  // Create player and place in area.
  unit_system_->SetPlayer(unit_system_->SpawnPlayer(area));

  // Add two extra levels
  auto second_level = level_system_->NewLevel(4, 4);
  auto third_level = level_system_->NewLevel(5, 5);

  level_system_->AddLevel(second_level);
  level_system_->AddLevel(third_level);

  // Connect the levels with gateways.
  level_system_->AddGateway(level_system_->RandomArea(first_level),
                            level_system_->RandomArea(second_level));

  level_system_->AddGateway(level_system_->RandomArea(second_level),
                            level_system_->RandomArea(third_level));

  InjectUnits(first_level);

  HelpCommand().Execute(this, vector<string>());
  InspectCommand().Execute(this, vector<string>());
  cout << "\n";
}

void GameSystem::InjectUnits(shared_ptr<Level> level) {
  auto areas = level_system_->GetAreasInLevel(level);
  vector<shared_ptr<Area>>::iterator it;
  for (it = areas.begin(); it != areas.end(); ++it) {

    // Insert n enemies based on a Poisson-distribution
    int n = GetPoisson(0.5);
    while (n > 0) {
      unit_system_->SpawnEnemy(*it);
      n--;
    }
  }
}

void GameSystem::Update() {
  interpreter_system_->Update();
}
