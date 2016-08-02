#include "debugcommands.h"

#include "gamesystem.h"
#include "../model/area.h"

void PrintPositionCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;
  auto graph = area->level->graph;
  int index = area->node_index;
  Vector2D position = graph->GetNode(index).Pos();
  cout << "You are at node[" << index << "], positioned at {"
    << position.x << ", " << position.y << "}\n";
}

void PrintPathsCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->unit_system()->player();
  auto area = player->area;
  auto graph = area->level->graph;
  auto neighbors = game_system->level_system()->NeighboringNodeIndexes(area);
  vector<int>::iterator it;
  for (it = neighbors.begin(); it != neighbors.end(); ++it) {
    Vector2D position = graph->GetNode(*it).Pos();
    cout << "Path leading to node[" << *it << "], positioned at {"
      << position.x << ", " << position.y << "}\n";
  }
}
