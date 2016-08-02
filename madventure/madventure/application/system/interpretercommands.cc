#include <memory>

#include "interpretercommands.h"

#include "gamesystem.h"
#include "../model/area.h"

void InspectCommand::Execute(GameSystem* game_system, vector<string> words) {

  auto player = game_system->player();
  auto area = player->area;

  auto neighbors = game_system->levelSystem()->GetNeighboringNodeIndices(area);
  //auto direction = game_system->levelSystem()->

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
  char initial = pronoun.at(0);

  // Verify if player can go into that direction.

  // Move player into that direction.

  // Perform inspect command.


  //auto player = game_system->player();
  //auto area = player->area;

  //auto directions = game_system->levelSystem()->GetNeighboringNodeIndices(area);
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
