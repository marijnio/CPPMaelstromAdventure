#pragma once

#include <vector>
#include <string>

#include "gamesystem.h"

#include "../event/gamequitevent.h"

namespace ex = entityx;
using namespace std;

class Command {
public:
  Command() {}

  virtual void execute(GameSystem game_system, vector<string> words) = 0;
};

class InspectCommand : public Command {
public:
  InspectCommand() {}
  void execute(GameSystem game_system, vector<string> words);
};

class QuitCommand : public Command {
public:
  QuitCommand() {}
  void execute(GameSystem game_system, vector<string> words) {
    //events.emit<GameQuitEvent>();
  }
};
