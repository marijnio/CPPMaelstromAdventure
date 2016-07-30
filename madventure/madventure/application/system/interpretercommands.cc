#include "interpretercommands.h"

#include "gamesystem.h"

void InspectCommand::Execute(GameSystem* game_system, vector<string> words) {

  auto player = game_system->player();
  auto area = player->area;

  auto directions = game_system->levelSystem().GetAreaDirections(area);

  //timeComponent.printTime();
  //areaComponent.printWeatherDescription();
  //areaComponent.printEnemies();
  //level.describeAvailableDirections(nodeIndex);
}

void HelpCommand::Execute(GameSystem* game_system, vector<string> words) {
  
}

void QuitCommand::Execute(GameSystem* game_system, vector<string> words) {
  game_system->Quit();
}
