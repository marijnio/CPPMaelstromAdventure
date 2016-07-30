#include <memory>

#include "interpretercommands.h"

#include "gamesystem.h"
#include "../model/area.h"

void InspectCommand::Execute(GameSystem* game_system, vector<string> words) {

  auto player = game_system->player();
  auto area = player->area;

  auto directions = game_system->levelSystem()->GetAreaDirections(area);

  //timeComponent.printTime();
  //areaComponent.printWeatherDescription();
  //areaComponent.printEnemies();
  //level.describeAvailableDirections(nodeIndex);
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
      cout << ".";
    }
    --it; // Return iterator to position.
  }
}

void QuitCommand::Execute(GameSystem* game_system, vector<string> words) {
  game_system->Quit();
}
