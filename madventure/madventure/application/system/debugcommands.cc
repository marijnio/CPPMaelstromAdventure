#include "debugcommands.h"

#include "gamesystem.h"
#include "../model/area.h"

void DebugPositionCommand::Execute(GameSystem* game_system, vector<string> words) {
  auto player = game_system->player();
  auto area = player->area;
  auto graph = area->level->graph;
  Vector2D position = graph->GetNode(area->node_index).Pos();
  cout << "You are at [" << position.x << ", " << position.y << "]\n";
}