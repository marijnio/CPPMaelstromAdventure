#pragma once

#include <vector>
#include <memory>
#include <string>

#include "gamesystem.h"

using namespace std;

class Command {
public:
  Command() {}

  virtual void Execute(shared_ptr<GameSystem> game_system, vector<string> words) = 0;
};

class InspectCommand : public Command {
public:
  InspectCommand() {}
  void Execute(shared_ptr<GameSystem> game_system, vector<string> words);
};

class QuitCommand : public Command {
public:
  QuitCommand() {}
  void Execute(shared_ptr<GameSystem> game_system, vector<string> words);
};
