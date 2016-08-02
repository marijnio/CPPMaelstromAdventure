#include <memory>

#include "commands.h"

#include "gamesystem.h"
#include "../model/area.h"
#include "../model/direction.h"

void InspectCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->player();
  auto area = player->area;
  auto neighbors = game_system->levelSystem()->GetNeighboringNodeIndices(area);
  auto directions = game_system->levelSystem()->GetDirections(area, neighbors);

  if (directions.empty()) {
    cout << "You can not move in any direction.\n";
  } else {
    vector<Direction>::iterator it;
    cout << "You can move ";
    for (it = directions.begin(); it != directions.end(); ++it) {
      cout << it->Name();

      // Separate with comma if not at last in map.
      if (++it != directions.end()) {
        cout << ", ";
      }
      else {
        cout << ".\n";
      }
      --it; // Return iterator to position.
    }
  }

  //timeComponent.printTime();
  //areaComponent.printWeatherDescription();
  //areaComponent.printEnemies();
  //level.describeAvailableDirections(nodeIndex);
}

void GoCommand::Execute(GameSystem* game_system, vector<string> words) {
  // Extract direction to go to.
  if (words.size() <= 1) {
    cout << "Go where?\n";
    return;
  }

  string pronoun = words.at(1);

  // Proceed to verify if player can go into that direction.

  auto player = game_system->player();
  auto area = player->area;
  auto graph = area->level->graph;
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
      // Match found. Move player towards connected node.
      player->area = node.ExtraInfo();
      // Perform inspect command.
      InspectCommand().Execute(game_system, vector<string>());
      return;
    }
  }
  cout << "You can not move into that direction.\n";
}

void HelpCommand::Execute(GameSystem* game_system, vector<string> words) {
  map<string, Command*> commands = game_system->interpreterSystem()->commands;
  map<string, Command*>::iterator it;
  cout << "Type any of the following commands to play: ";
  for (it = commands.begin(); it != commands.end(); ++it) {
    string name = it->first;
    cout << name;

    // Separate with comma if not at last in map.
    if (++it != commands.end()) {
      cout << ", ";
    } else {
      cout << ".\n";
    }
    --it; // Return iterator to position.
  }
}

void QuitCommand::Execute(GameSystem* game_system, vector<string> words) {
  game_system->Quit();
}