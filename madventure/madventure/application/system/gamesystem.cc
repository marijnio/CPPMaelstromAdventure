#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>

#include "gamesystem.h"
#include "../graph/SparseGraph.h"
#include "../model/level.h"
#include "../model/trap.h"
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
  cout << "Welcome to Maelstrom Adventure.\n\n";

  cout << "Please enter the name of your ship.\n";
  string name = interpreter_system_->RequestWord("Name: ");
  cout << endl;

  cout << "The " << name << " has set sail.\n";
  cout << "Good luck.\n\n";

  // Initialize the world with a level.
  auto first_level = level_system_->NewLevel(3, 3);
  level_system_->AddLevel(first_level);

  // Init first level time to 12:00.
  first_level->time_ = 12;

  // Select starting area.
  auto area = first_level->graph->GetNode(0).ExtraInfo();

  // Create player and place in area.
  unit_system_->SetPlayer(unit_system_->SpawnPlayer(area, name, 100));

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
  InjectUnits(second_level);
  InjectUnits(third_level);

  InjectTraps(first_level, 0.2, 2.0);
  InjectTraps(second_level, 0.3, 4.0);
  InjectTraps(third_level, 0.4, 6.0);

  HelpCommand().Execute(this, vector<string>());
  InspectCommand().Execute(this, vector<string>());
  cout << "\n";
}

void GameSystem::InjectUnits(shared_ptr<Level> level) {
  auto areas = level_system_->GetAreasInLevel(level);
  vector<shared_ptr<Area>>::iterator it;
  for (it = areas.begin(); it != areas.end(); ++it) {

    // Insert n enemies based on a Poisson-distribution.
    int n = GetPoisson(0.5);
    while (n > 0) {
      unit_system_->SpawnEnemy(*it, 100);
      n--;
    }
  }
}

void GameSystem::InjectTraps(shared_ptr<Level> level, double chance,
                             double average_difficulty) {
  auto areas = level_system_->GetAreasInLevel(level);
  vector<shared_ptr<Area>>::iterator it;
  for (it = areas.begin(); it != areas.end(); ++it) {

    // Skip areas containing gateways.
    if ((*it)->gateway) {
      continue;
    }

    // Roll for a random number between 0.0 and 1.0.
    double roll = ((double)rand() / (double)RAND_MAX);

    if (roll < chance) {
      // Roll for individual trap difficulty on a normal distribution.
      random_device rd;
      default_random_engine generator;
      generator.seed(rd());
      normal_distribution<double> distribution(average_difficulty, 1.0);
      double difficulty = distribution(generator);

      // Insert trap.
      (*it)->trap = make_shared<Trap>(difficulty);
    }
  }
}

void GameSystem::Update() {
  interpreter_system_->Update();
  if (unit_system_->player()->health <= 0) {
    cout << "Your ship sinked to the bottom of the ocean.\n";
    cout << "GAME OVER\n";
  }
}
