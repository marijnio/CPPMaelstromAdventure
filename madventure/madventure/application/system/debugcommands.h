#pragma once

#include "commands.h"

class PrintPositionCommand : public Command {
public:
  PrintPositionCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};

class PrintPathsCommand : public Command {
public:
  PrintPathsCommand() {}
  void Execute(GameSystem* game_system, vector<string> words);
};