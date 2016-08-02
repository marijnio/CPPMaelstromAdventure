#include <memory>

#include "commands.h"

#include "gamesystem.h"
#include "../model/area.h"
#include "../model/direction.h"

#include "../utility/mygrammar.h"

void InspectCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;

  /* Print gateway */
  if (area->gateway) {
    if (area->gateway->from == area) {
      cout << "A vast whirlpool pulls down the sea in a spiraling fashion.\n";
    }
    else {
      cout << "An intense columnar vortex funnels water into the clouds.\n";
    }
  }

  /* Print directions */
  vector<string> strings;
  auto neighbors = game_system->level_system()->NeighboringNodeIndexes(area);
  auto directions = game_system->level_system()->GetDirections(area, neighbors);

  if (!directions.empty()) {
    vector<Direction>::iterator it;
    for (it = directions.begin(); it != directions.end(); ++it) {
      strings.push_back(it->Name());
    }
  }

  /* Print gateway */
  if (area->gateway) {
    if (area->gateway->from == area) {
      strings.push_back("DOWN");
    } else {
      strings.push_back("UP");
    }
  }

  if (strings.empty()) {
    cout << "You can not go into any direction.\n";
  } else {
    cout << "You can go " << EnumerateWords(strings) << "\n";
  }

    //timeComponent.printTime();
    //areaComponent.printWeatherDescription();
    //areaComponent.printEnemies();
}

void GoCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;
  auto graph = area->level->graph;

  // Extract direction to go to.
  if (words.size() <= 1) {
    cout << "Go where?\n";
    return;
  }

  string pronoun = words.at(1);
  shared_ptr<Area> destination;

  if (area->gateway) {
    if (pronoun == "DOWN") { destination = area->gateway->to; }
    if (pronoun == "UP") { destination = area->gateway->from; }
  }

  // Proceed to verify if player can go into that direction.
  Vector2D this_position = graph->GetNode(area->node_index).Pos();

  // For every edge, if its direction name matches the pronoun,
  // move towards node to which the edge points to.

  auto edges = graph->GetEdgeList(area->node_index);
  list<NavGraphEdge>::iterator it;
  for (it = edges.begin(); it != edges.end(); ++it) {
    auto node = graph->GetNode(it->To());
    Vector2D that_position = node.Pos();
    // Find at which angle it is positioned from current node.
    int angle = LevelSystem::RelativeVectorAngle(this_position, that_position);

    if (Direction(angle).Name() == pronoun) {
      // Match found.
      destination = node.ExtraInfo();
    }
  }
  
  if (destination) {
    // Move player towards connected node.
    game_system->unit_system()->MoveUnit(player, destination);
    cout << "Moved " << pronoun << ".\n";
    // Perform inspect command.
    InspectCommand().Execute(game_system, vector<string>());
    return;
  }

  // No destination set.
  cout << "You can not go into that direction.\n";
}

void HelpCommand::Execute(GameSystem* game_system, vector<string> words) {
  cout << "Type any of the following commands to play: ";

  // Print all available commands.
  vector<string> strings;
  map<string, Command*> commands = game_system->interpreter_system()->commands;
  map<string, Command*>::iterator it;
  for (it = commands.begin(); it != commands.end(); ++it) {
    strings.push_back(it->first);
  }
  cout << EnumerateWords(strings) << "\n";
}

void QuitCommand::Execute(GameSystem* game_system, vector<string> words) {
  game_system->Quit();
}