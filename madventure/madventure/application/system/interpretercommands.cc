#include "interpretercommands.h"

void InspectCommand::Execute(shared_ptr<GameSystem> game_system, vector<string> words) {

  auto player = game_system->player();
  auto area = player->area;

  auto directions = game_system->levelSystem().GetAreaDirections(area);

  //timeComponent.printTime();
  //areaComponent.printWeatherDescription();
  //areaComponent.printEnemies();
  //level.describeAvailableDirections(nodeIndex);
}

void QuitCommand::Execute(shared_ptr<GameSystem> game_system, vector<string> words) {
  game_system->Quit();
}
